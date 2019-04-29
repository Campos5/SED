/*--- Ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
#include "def.h"
#include <stdlib.h>
#include<stdlib.h>
#include<time.h>


/*--- Definición de macros ---*/
#define KEY_VALUE_MASK 0xF
/*--- Variables globales ---*/
volatile UCHAR *keyboard_base = (UCHAR *)0x06000000;
int key;
/*--- Funciones externas ---*/
extern void D8Led_symbol(int value);
extern void dibujar_coco(int x, int y);
extern void poner_punto(int x, int y, int z);
extern void pantalla_en_negro();

extern int mapa[(240/16)][(320/16)];

extern int pos_racman_propio_x;
extern int pos_racman_propio_y;

extern int pos_racman_enemigo_x;
extern int pos_racman_enemigo_y;

extern int direccion_racman_propio;
extern int direccion_defecto_propio;

extern int jugador;

int puntos_jugador_1;
int puntos_jugador_2;

int puntos_jugador;

extern int tipo_juego;
int comido;
int fantasmas[8];

/*--- Declaracion de funciones ---*/
void keyboard_init();
void KeyboardInt(void) __attribute__ ((interrupt ("IRQ")));


void realizar_movimiento();
int comprobar_mov_propio(int direccion);
int comprobar_mov_enemigo(int direccion);
void comproar_mov_fantasma();
int envios_uart(int mover);
int fantasma_come(int racmanX, int racmanY, int fantasmaX, int fantasmaY); //devuelve 1 si el fantasma come
int quedan_puntos();
void fin_de_partida(int gana);
int* obtener_mejorer_movimientos(int racmanX, int racmanY, int fantasmaX, int fantasmaY, int better_movs[]);
int* mover_fantasma(int x, int y, int direccion, int f, int movs[]);
int comprobarFantasmaMovido(int pos_fantasmas[], int j, int i);

/*--- Codigo de las funciones ---*/
void keyboard_init()
{

	puntos_jugador_1 = 0;
	puntos_jugador_2 = 0;
	puntos_jugador = 0;
	/* Configurar el puerto G (si no lo estuviese ya) */	
		// Establece la funcion de los pines (EINT0-7)
	//rPCONG = 0xFFFF3
	rPCONG = rPCONG | (1 << 2); //pone a 1 el 2
	rPCONG = rPCONG | (1 << 3);

		// Habilita el "pull up" del puerto
	rPUPG = 0x0;

		// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	rEXTINT = rEXTINT & ~(1 << 6);
	rEXTINT = rEXTINT | (1 << 5);

	/* Establece la rutina de servicio para EINT1 */
		//
	pISR_EINT1 = (unsigned)KeyboardInt;
	/* Configurar controlador de interrupciones */
		// Borra INTPND escribiendo 1s en I_ISPC
	rI_ISPC = BIT_EINT1;
		// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0;
		// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON = rINTCON & ~(1<<1);
	rINTCON = rINTCON & ~(1<<2);
	rINTCON = rINTCON | (1<<0);
	/* Habilitar linea EINT1 */
		//
	rINTMSK = ~(BIT_EINT1 | BIT_GLOBAL);

	/* Por precaucion, se vuelven a borrar los bits de INTPND correspondientes*/
		//
	rI_ISPC = BIT_EINT1;
}


void KeyboardInt(void)
{
	/* Esperar trp mediante la funcion DelayMs()*/
	//
	DelayMs(20);
	/* Identificar la tecla */
	key = key_read();

	/* Esperar a se libere la tecla: consultar bit 1 del registro de datos del puerto G */
	while ( (rPDATG & (1 << 1) ) == 0){
		//NOTHING
	}

	switch (key){
		case 1: //mover arriba

			//if(pos_racman_propio_y - 1 >= 0 && mapa[pos_racman_propio_y - 1][pos_racman_propio_x] != 0)
				direccion_racman_propio = 0;
			break;

		case 2: //mover arriba
			//if(pos_racman_propio_y - 1 >= 0 && mapa[pos_racman_propio_y - 1][pos_racman_propio_x] != 0)
				direccion_racman_propio = 0;
			break;

		case 4: //mover izquierda
			//if(pos_racman_propio_x - 1 >= 0 && mapa[pos_racman_propio_y][pos_racman_propio_x - 1] != 0)
			// comprobar si es legal el movimiento
				direccion_racman_propio = 1;
			break;

		case 8: //mover izquierda
			//if(pos_racman_propio_x - 1 >= 0 && mapa[pos_racman_propio_y - 1][pos_racman_propio_x - 1] != 0)
				direccion_racman_propio = 1;
			break;

		case 7: //mover derecha
			//if(pos_racman_propio_x + 1 <= 19 && mapa[pos_racman_propio_y][pos_racman_propio_x + 1] != 0)
				direccion_racman_propio = 2;
			break;

		case 11: //mover derecha
			//if(pos_racman_propio_x + 1 <= 19 && mapa[pos_racman_propio_y][pos_racman_propio_x + 1] != 0)
				direccion_racman_propio = 2;
			break;

		case 13: //mover abajo
			//if(pos_racman_propio_y + 1 <= 15 && mapa[pos_racman_propio_y + 1][pos_racman_propio_x] != 0)
				direccion_racman_propio = 3;
			break;

		case 14: //mover abajo
			//if(pos_racman_propio_y + 1 <= 15 && mapa[pos_racman_propio_y + 1][pos_racman_propio_x] != 0)
				direccion_racman_propio = 3;
			break;

		default: //eres un inútil que no sabe apretar los botones
			break;

	}




	/* Esperar trd mediante la funcion Delay() */
	//
	DelayMs(100);
	/* Borrar interrupción de teclado */
	//
	rI_ISPC = ~0x0;
}


int key_read(){
	int value= -1;
	char temp;
	// Identificar la tecla mediante ''scanning''

	// Si la identificación falla la función debe devolver -1
	temp = *(keyboard_base + 0xfd) & KEY_VALUE_MASK;

	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
		case 0x7:  value = 0; break;
		case 0xB:  value = 1; break;
		case 0xD:  value = 2; break;
		case 0xE:  value = 3; break;
	}

	/*
	* ESCRIBIR EL CÓDIGO CORRESPONDIENTE A LAS OTRAS FILAS Y COLUMNAS
	*/
	temp = *(keyboard_base + 0xfb) & KEY_VALUE_MASK;
	switch (temp) {
		case 0x7:  value = 4; break;
		case 0xB:  value = 5; break;
		case 0xD:  value = 6; break;
		case 0xE:  value = 7; break;
	}
	temp = *(keyboard_base + 0xf7) & KEY_VALUE_MASK;

	switch (temp) {
		case 0x7:  value = 8; break;
		case 0xB:  value = 9; break;
		case 0xD:  value = 10; break;
		case 0xE:  value = 11; break;
	}
	temp = *(keyboard_base + 0xef) & KEY_VALUE_MASK;
	switch (temp) {
		case 0x7:  value = 12; break;
		case 0xB:  value = 13; break;
		case 0xD:  value = 14; break;
		case 0xE:  value = 15; break;
	}
	
	return value;

}

void realizar_movimiento(){

	int x_ant = pos_racman_propio_x;
	int y_ant = pos_racman_propio_y;

	int fin_partida = -1;
	int mover = 0;

	mover = comprobar_mov_propio(direccion_racman_propio);


	if(mover == 1){ //se ha movido donde dice el user
		direccion_defecto_propio = direccion_racman_propio;

		//limpiar la casilla donde se encuentra racman
		limpiar_pixels(x_ant, y_ant);


		//poner a racman en la nueva posicion
		dibujar_racman(pos_racman_propio_x, pos_racman_propio_y, 0, 0);

	}else if(mover == 0){ //se mueve, o lo intenta, en la direccion que llevaba antes

		if(comprobar_mov_propio(direccion_defecto_propio) == 1){

			//limpiar la casilla donde se encuentra racman
			limpiar_pixels(x_ant, y_ant);


			//poner a racman en la nueva posicion
			dibujar_racman(pos_racman_propio_x, pos_racman_propio_y, 0, 0);

		}

	}else{
		if(tipo_juego == 0){
			fin_partida = 0;
		}else{
			mapa[pos_racman_propio_y][pos_racman_propio_x] -= 0;
			limpiar_pixels(pos_racman_propio_x, pos_racman_propio_y);
			//Al tener -1 como posición no va a poder moverse
			pos_racman_propio_x = -1;
			pos_racman_propio_y = -1;


		}
	}

	if(tipo_juego == 0){
		comproar_mov_fantasma();
		if(comido == 1)
			fin_partida = 0;
	}
	if(tipo_juego == 1){
		if(jugador == 1){
			comproar_mov_fantasma();
			if(comido == 1)
				mover = -1;
		}
		
		int direccion_enemigo = envios_uart(mover);
/*
		if(mover == 1){

			Uart_SendByte(direccion_racman_propio);
		}else if (mover == 0){

			Uart_SendByte(direccion_defecto_propio);
		}else{ //cuando mover es -1, racman ha muerto
			Uart_SendByte(mover); 
		}

		//TODO mandar posición de los fantasmas si es el jugador 1
		//TODO mandar los puntos

		char str[1];
		char *pt_str = str;
		while(1){
			//TODO dibujar fantasmas y actualizar el mapa si es el jugador 2
			*pt_str = Uart_Getch(); // leer caracter
			direccion_enemigo = *pt_str;
			break;
			pt_str = str;
		}
		//TODO leer los puntos de cada jugador
		if(jugador == 1){
			puntos_jugador_1 = puntos_jugador;
			puntos_jugador_2 = 5; //TODO
		}else{
			puntos_jugador_2 = puntos_jugador;
			puntos_jugador_1 = 5; //TODO
		}
*/
		if(direccion_enemigo == -1){
			//poner -1 a las posiciones y eliminar los pixels del enemigo
			limpiar_pixels(pos_racman_enemigo_x, pos_racman_enemigo_y);
			pos_racman_enemigo_x = -1;
			pos_racman_enemigo_y = -1;
		}else{
			x_ant = pos_racman_enemigo_x;
			y_ant = pos_racman_enemigo_y;
			if(comprobar_mov_enemigo(direccion_enemigo) == 1){

				//limpiar la casilla donde se encuentra racman
				limpiar_pixels(x_ant, y_ant);


				//poner a racman en la nueva posicion
				dibujar_racman(pos_racman_enemigo_x, pos_racman_enemigo_y, 1, 0);

			}
		}

		if(direccion_enemigo == -1 && mover == -1) //ambos han perdido
			fin_de_partida(-1);

	}

	if(quedan_puntos() == 0){
		fin_partida = 1;
	}

	if(fin_partida == -1){
		lanzarTimer(0);

	}else{
		fin_de_partida(fin_partida);
	}


}

int comprobar_mov_propio(int direccion){

	int mover = 0;
	switch (direccion){
		case 0: //mover arriba
			// comprobar si es legal el movimiento
			if(pos_racman_propio_y - 1 >= 0 && mapa[pos_racman_propio_y - 1][pos_racman_propio_x] != -1){

				//todo añadir comprbante de si había bolita o no para sumar al contador
				if(mapa[pos_racman_propio_y][pos_racman_propio_x] > 3*jugador || mapa[pos_racman_propio_y][pos_racman_propio_x] < 3*jugador+3){ //se lleva puntos

					puntos_jugador += mapa[pos_racman_propio_y][pos_racman_propio_x] - 3*jugador;
					
				}
				if(fantasma_come(pos_racman_propio_x, pos_racman_propio_y - 1, -1, -1)){
					return -1;
				}

				mapa[pos_racman_propio_y][pos_racman_propio_x] = 0;
				pos_racman_propio_y -= 1;

				mapa[pos_racman_propio_y][pos_racman_propio_x] += 3*jugador;

				mover = 1;
			}
			break;

		case 1: //mover izquierda
			// comprobar si es legal el movimiento
			if(pos_racman_propio_x - 1 >= 0 && mapa[pos_racman_propio_y][pos_racman_propio_x - 1] != -1){

				//todo añadir comprbante de si había bolita o no para sumar al contador
				if(mapa[pos_racman_propio_y][pos_racman_propio_x] > 3*jugador || mapa[pos_racman_propio_y][pos_racman_propio_x] < 3*jugador+3){ //se lleva puntos
					
					puntos_jugador += mapa[pos_racman_propio_y][pos_racman_propio_x] - 3*jugador;

					
				}
				if(fantasma_come(pos_racman_propio_x - 1, pos_racman_propio_y, -1, -1)){
					return -1;
				}

				mapa[pos_racman_propio_y][pos_racman_propio_x] = 0;

				pos_racman_propio_x -= 1;

				mapa[pos_racman_propio_y][pos_racman_propio_x] += 3*jugador;

				mover = 1;

			}
			break;

		case 2: //mover derecha
			// comprobar si es legal el movimiento
			if(pos_racman_propio_x + 1 <= 19 && mapa[pos_racman_propio_y][pos_racman_propio_x + 1] != -1){

				//todo añadir comprbante de si había bolita o no para sumar al contador
				if(mapa[pos_racman_propio_y][pos_racman_propio_x] > 3*jugador || mapa[pos_racman_propio_y][pos_racman_propio_x] < 3*jugador+3){ //se lleva puntos

					puntos_jugador += mapa[pos_racman_propio_y][pos_racman_propio_x] - 3*jugador;
				
				}

				if(fantasma_come(pos_racman_propio_x + 1, pos_racman_propio_y, -1, -1)){
					return -1;
				}

				mapa[pos_racman_propio_y][pos_racman_propio_x] = 0;

				pos_racman_propio_x += 1;

				mapa[pos_racman_propio_y][pos_racman_propio_x] += 3*jugador;

				mover = 1;

			}
			break;

		case 3: //mover abajo
			// comprobar si es legal el movimiento
			if(pos_racman_propio_y + 1 <= 15 && mapa[pos_racman_propio_y + 1][pos_racman_propio_x] != -1){

				//todo añadir comprbante de si había bolita o no para sumar al contador
				if(mapa[pos_racman_propio_y][pos_racman_propio_x] > 3*jugador || mapa[pos_racman_propio_y][pos_racman_propio_x] < 3*jugador){ //se lleva puntos

					puntos_jugador += mapa[pos_racman_propio_y][pos_racman_propio_x] - 3*jugador;
				
				}
				if(fantasma_come(pos_racman_propio_x, pos_racman_propio_y + 1, -1, -1)){
					return -1;
				}

				mapa[pos_racman_propio_y][pos_racman_propio_x] = 0;

				pos_racman_propio_y += 1;

				mapa[pos_racman_propio_y][pos_racman_propio_x] += 3*jugador;

				mover = 1;
			}
			break;

		default:
			break;

	}

	return mover;
}

int comprobar_mov_enemigo(int direccion){

	int mover = 0;
	switch (direccion){
		case 0: //mover arriba
			// comprobar si es legal el movimiento
			if(pos_racman_enemigo_y - 1 >= 0 && mapa[pos_racman_enemigo_y - 1][pos_racman_enemigo_x] != -1){


				mapa[pos_racman_enemigo_y][pos_racman_enemigo_x] = 0;
				pos_racman_enemigo_y -= 1;

				mapa[pos_racman_enemigo_y][pos_racman_enemigo_x] += 3*jugador;

				mover = 1;
			}
			break;

		case 1: //mover izquierda
			// comprobar si es legal el movimiento
			if(pos_racman_enemigo_x - 1 >= 0 && mapa[pos_racman_enemigo_y][pos_racman_enemigo_x - 1] != -1){

				mapa[pos_racman_enemigo_y][pos_racman_enemigo_x] = 0;

				pos_racman_enemigo_x -= 1;

				mapa[pos_racman_enemigo_y][pos_racman_enemigo_x] += 3*jugador;

				mover = 1;

			}
			break;

		case 2: //mover derecha
			// comprobar si es legal el movimiento
			if(pos_racman_enemigo_x + 1 <= 19 && mapa[pos_racman_enemigo_y][pos_racman_enemigo_x + 1] != -1){

				mapa[pos_racman_enemigo_y][pos_racman_enemigo_x] = 0;

				pos_racman_enemigo_x += 1;

				mapa[pos_racman_enemigo_y][pos_racman_enemigo_x] += 3*jugador;

				mover = 1;

			}
			break;

		case 3: //mover abajo
			// comprobar si es legal el movimiento
			if(pos_racman_enemigo_y + 1 <= 15 && mapa[pos_racman_enemigo_y + 1][pos_racman_enemigo_x] != -1){

				mapa[pos_racman_enemigo_y][pos_racman_enemigo_x] = 0;

				pos_racman_enemigo_y += 1;

				mapa[pos_racman_enemigo_y][pos_racman_enemigo_x] += 3*jugador;

				mover = 1;
			}
			break;

		default:
			break;

	}

	return mover;
}

void comproar_mov_fantasma(){

	int i, j, k;
	//int *pos_fantasmas;
	//TODO comprobar si esto funciona
	int* pos_fantasmas = (int *) malloc(sizeof(int) * 8);
	for(k = 0; k < 8; k++)
		pos_fantasmas[k] = -1;
		
	int fantasma = 0;
	for (i = 0; i<320/16; i++){
		for (j = 0; j<240/16; j++){


			int check = comprobarFantasmaMovido(pos_fantasmas, j, i);
			if(mapa[j][i] > 8 && mapa[j][i] < 12 && check != 0){
				
				int distancia_propio = fabs(pos_racman_propio_x - i) + fabs(pos_racman_propio_y - j);
				int distancia_enemigo = fabs(pos_racman_enemigo_x - i) + fabs(pos_racman_enemigo_y - j);

				int* mejores_movimientos = (int *) malloc(sizeof(int) * 8);

				if(distancia_enemigo > distancia_propio)
					mejores_movimientos = obtener_mejorer_movimientos(pos_racman_propio_x, pos_racman_propio_y, i, j, mejores_movimientos);
				else
					mejores_movimientos = obtener_mejorer_movimientos(pos_racman_enemigo_x, pos_racman_enemigo_y, i, j, mejores_movimientos);
					

				int k;
				int movido = 0; //1 si se ha movido
				for(k = 0; k < 4; k++){
					if(movido == 1)
						break;

					switch (mejores_movimientos[k])
					{
						case 0:
							if(mapa[j-1][i] > -1 && mapa[j-1][i] < 9){
								movido = 1;
								pos_fantasmas = mover_fantasma(i, j, 0, fantasma, pos_fantasmas);
							}
							break;
						case 1:
							if(mapa[j][i-1] > -1 && mapa[j][i-1] < 9){
								movido = 1;
								pos_fantasmas = mover_fantasma(i, j, 1, fantasma, pos_fantasmas);
							}
							break;
						case 2:
							if(mapa[j][i+1] > -1 && mapa[j][i+1] < 9){
								movido = 1;
								pos_fantasmas = mover_fantasma(i, j, 2, fantasma, pos_fantasmas);
							}
							break;
						case 3:
							if(mapa[j+1][i] > -1 && mapa[j+1][i] < 9){
								movido = 1;
								pos_fantasmas = mover_fantasma(i, j, 3, fantasma, pos_fantasmas);
							}
							break;
						
						default:
							break;
					}
				}
				free(mejores_movimientos);
				fantasma++;
			}

		}
	}

	free(pos_fantasmas);

}

int* obtener_mejorer_movimientos(int racmanX, int racmanY, int fantasmaX, int fantasmaY, int better_movs[8]){
	
	int aux[2] = {racmanX - fantasmaX, racmanY - fantasmaY};

	int i;

	for(i = 0; i < 4; i++ ){
		better_movs[i] = -1;
	}
	
	if(aux[0] == 0 && aux[1] == 0){ 
		//esto sería si un fantasma come a un racman, hay que controlarlo antes
		//no debería entrar nunca aquí
		return better_movs;
	}
	int algun_cero = 0;

	for(i = 0; i < 3; i++ ){
		if( algun_cero == 1) //si alguno de los valores es cero ya se han rellenado todos
			break;
		switch (i)
		{
			case 0:
				if(fabs(aux[0]) >= fabs(aux[1])){ //mov horizontal
					if(aux[0] > 0){ //derecha
						better_movs[i] = 2;
					}else { //izquierda
						better_movs[i] = 1;
					}
				}else{		
					if(aux[1] > 0){ //abajo
						better_movs[i] = 3;
					}else { //arriba
						better_movs[i] = 0;
					}
				}
				break;
			case 1: //misma comprobación que antes pero ahora con el otro eje
				if(fabs(aux[0]) >= fabs(aux[1])){
					if(aux[1] > 0){
						better_movs[i] = 3;
					}else if (aux[1] < 0){
						better_movs[i] = 0;
					}else{ //en caso de ser cero, lo movemos en el otro eje
						srand(time(NULL));
						int num = rand();
  						num=rand()%2;
	
						if (num){
							better_movs[i] = 0;
							better_movs[i+1] = 3;

						}else{
							better_movs[i] = 3;
							better_movs[i+1] = 0;
							
						}	
						if(aux[0] > 0){
							better_movs[3] = 1; 
						}else{
							better_movs[3] = 2;
						}
					}
				}else{		
					if(aux[0] > 0){
						better_movs[i] = 2;
					}else if (aux[0] < 0){
						better_movs[i] = 1;
					}else{ //en caso de ser cero, lo movemos en el otro eje
						srand(time(NULL));
						int num = rand();
  						num=rand()%2;
	
						if (num){
							better_movs[i] = 2;
							better_movs[i+1] = 1;

						}else{
							better_movs[i] = 2;
							better_movs[i+1] = 1;
							
						}	
						if(aux[1] > 0){
							better_movs[3] = 0; 
						}else{
							better_movs[3] = 3;
						}
					}
				algun_cero = 1;
				}
				break;

			default:
				//una vez puestos los dos mejores, de forma "aleatoria" se ponen los otros dos
				better_movs[2] = (better_movs[2] * 3 +3) % 4;
				better_movs[3] = 6 - better_movs[0] - better_movs[1] - better_movs[2];
				
				break;
		}
	}

	return better_movs;
}

int* mover_fantasma(int x, int y, int direccion, int f, int movs[]){

	int aux = mapa[y][x];
	if(mapa[y][x] == 9 ){
		limpiar_pixels(x, y);
	}else if(mapa[y][x] == 10){
		limpiar_pixels(x, y);
		poner_punto(x, y, 0);
	}else{
		limpiar_pixels(x, y);
		poner_punto(x, y, 1);
	}
	mapa[y][x] -= 9;

	comido = 0;
	switch (direccion){
		case 0: //mover arriba

			dibujar_coco(x, y-1);

			if(fantasma_come(pos_racman_propio_x, pos_racman_propio_y, x, y-1)){
				comido = 1;
				mapa[y-1][x] = 9;
			}else
				mapa[y-1][x] += 9;

			movs[f*2] = y-1;
			movs[f*2 +1] = x;

			break;

		case 1: //mover izquierda

			dibujar_coco(x-1, y);
			if(fantasma_come(pos_racman_propio_x, pos_racman_propio_y, x-1, y)){
				comido = 1;
				mapa[y][x-1] = 9;
			}else
				mapa[y][x-1] += 9;

			movs[f*2] = y;
			movs[f*2 +1] = x-1;

			break;

		case 2: //mover derecha

			dibujar_coco(x+1, y);
			if(fantasma_come(pos_racman_propio_x, pos_racman_propio_y, x+1, y)){
				comido = 1;
				mapa[y][x+1] = 9;
			}else
				mapa[y][x+1] += 9;

			movs[f*2] = y;
			movs[f*2 +1] = x+1;

			break;

		case 3: //mover abajo

			dibujar_coco(x, y+1);
			if(fantasma_come(pos_racman_propio_x, pos_racman_propio_y, x, y+1)){
				comido = 1;
				mapa[y+1][x] = 9;
			}else
				mapa[y+1][x] += 9;

			movs[f*2] = y+1;
			movs[f*2 +1] = x;

			break;

		default:
			break;

	}
	int i;
	if(movs[7] != -1)
		for(i = 0; i < 8; i++)
			fantasmas[i] = movs[i];
	
	return movs;

}

int comprobarFantasmaMovido(int pos_fantasmas[], int j, int i){
	int k;
	for(k = 0; k < 8; k+=2){
		if(*(pos_fantasmas+k) == j && *(pos_fantasmas+k+1) == i)
			return 0;
	}
	return 1;
}

int envios_uart(int mover){
	
	int i;
	int direccion_enemigo;
	if (jugador == 1){
		char recepcion[3];
		char envio[11];


		if(mover == 1){
			envio[0] = direccion_racman_propio;
		}else if (mover == 0){
			envio[0] = direccion_defecto_propio;
		
		}else{ //cuando mover es -1, racman ha muerto
			envio[0] = -1;		
		}
		envio[1] = puntos_jugador; 
		
		for(i = 0; i < 8; i++){
			envio[i+2] = fantasmas[i];
		}
		envio[10] = 'f';

		Uart_SendByte(*envio);
		char *pt_str = recepcion;
		i = 0;
		while(1){
			//TODO dibujar fantasmas y actualizar el mapa si es el jugador 2
			*pt_str = Uart_Getch(); // leer caracter
			if(*pt_str == 'f')
				break;
			recepcion[i] = *pt_str;
			i++;
			pt_str = recepcion;
		}
		//TODO leer los puntos de cada jugador
		puntos_jugador_1 = puntos_jugador;
		puntos_jugador_2 = recepcion[1];
		
		direccion_enemigo = recepcion[0];

	}else{
		char recepcion[11];
		char envio[3];

		if(mover == 1){
			envio[0] = direccion_racman_propio;
		}else if (mover == 0){
			envio[0] = direccion_defecto_propio;
		}else{ //cuando mover es -1, racman ha muerto
			envio[0] = -1;		
		}
		envio[1] = puntos_jugador;

		envio[2] = 'f';

		Uart_SendByte(*envio);
		char *pt_str = recepcion;
		i = 0;
		while(1){
			//TODO dibujar fantasmas y actualizar el mapa si es el jugador 2
			*pt_str = Uart_Getch(); // leer caracter
			if(*pt_str == 'f')
				break;
			recepcion[i] = *pt_str;
			i++;
			pt_str = recepcion;
		}
		//TODO leer los puntos de cada jugador
		puntos_jugador_2 = puntos_jugador;
		puntos_jugador_1 = recepcion[1];
		
		direccion_enemigo = recepcion[0];
		for(i = 2; i < 6; i += 2){
			mapa[recepcion[i]][recepcion[i+1]] += 9;
		}
	}
	
	return direccion_enemigo;
}

int fantasma_come(int racmanX, int racmanY, int fantasmaX, int fantasmaY){
	//TODO
	if(fantasmaX == -1){
		if(mapa[racmanY][racmanX] >= 9 && mapa[racmanY][racmanX] <= 11)
			return 1;
	}else{
		if(racmanX == fantasmaX && racmanY == fantasmaY)
			return 1;
	}
	return 0;

}

int quedan_puntos(){
	int i, j;
	int fantasma = 0;
	for (i = 0; i<320/16; i++){
		for (j = 0; j<240/16; j++){
			if(!(mapa[j][i] % 3) && mapa[j][i] != -1)
				return 1;
		}
	}
	return 0;

}

void fin_de_partida(int gana){
	//TODO
	if(jugador == 1)
		puntos_jugador_1 = puntos_jugador;
	else
		puntos_jugador_2 = puntos_jugador;

	if( tipo_juego == 0){
		pantalla_en_negro();
		DelayMs(1000);
		pantalla_fin_juego_solitario(gana);
		
	}else{
		pantalla_en_negro();
		DelayMs(1000);
		pantalla_fin_juego_doble(puntos_jugador_1, puntos_jugador_2);

	}


}
