/*--- Ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
#include "def.h"
/*--- Definición de macros ---*/
#define KEY_VALUE_MASK 0xF
/*--- Variables globales ---*/
volatile UCHAR *keyboard_base = (UCHAR *)0x06000000;
int key;
/*--- Funciones externas ---*/
extern void D8Led_symbol(int value);
extern void dibujar_coco(int x, int y);
extern void poner_punto(int x, int y, int z);


extern int mapa[(240/16)][(320/16)];

extern int pos_racman_propio_x;
extern int pos_racman_propio_y;

extern int pos_racman_enemigo_x;
extern int pos_racman_enemigo_y;

extern int direccion_racman_propio;
extern int direccion_defecto_propio;

extern int jugador;

extern int puntos_jugador_1;


extern int tipo_juego;

/*--- Declaracion de funciones ---*/
void keyboard_init();
void KeyboardInt(void) __attribute__ ((interrupt ("IRQ")));



void realizar_movimiento();
int comprobar_mov(int direccion);
void comproar_mov_fantasma();
int* mover_fantasma(int x, int y, int direccion, int f, int movs[]);
int comprobarFantasmaMovido(int pos_fantasmas[], int j, int i);


/*--- Codigo de las funciones ---*/
void keyboard_init()
{
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


int key_read()
{
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

	int mover = 0;

	mover = comprobar_mov(direccion_racman_propio);


	if(mover == 1){ //se ha movido donde dice el user
		direccion_defecto_propio = direccion_racman_propio;

		//limpiar la casilla donde se encuentra racman
		limpiar_pixels(x_ant, y_ant);


		//poner a racman en la nueva posicion
		dibujar_racman(pos_racman_propio_x, pos_racman_propio_y, 0, 0);

	}else{ //se mueve, o lo intenta, en la direccion que llevaba antes

		if(comprobar_mov(direccion_defecto_propio) == 1){

			//limpiar la casilla donde se encuentra racman
			limpiar_pixels(x_ant, y_ant);


			//poner a racman en la nueva posicion
			dibujar_racman(pos_racman_propio_x, pos_racman_propio_y, 0, 0);

		}else{ //no se mueve para ningún lado
			//creo que no debería hacer nada aquí
		}


	}

	if(tipo_juego == 25){
		comproar_mov_fantasma();
	}
	if(tipo_juego == 12){

		//todo mandar y recibir información de la uart
		Uart_SendByte(key);

		char str[1];
		char *pt_str = str;
		while(1){
			*pt_str = Uart_Getch(); // leer caracter
			if (*pt_str == 'a'){
				leds_off();
				led1_on();
			}
			if (*pt_str == 'b'){
				leds_off();
				led2_on();
			}
			if (((*pt_str-'0') >= 0) && ((*pt_str-'0') < 16)){
				D8Led_symbol(*pt_str-'0');
			}
			pt_str = str;
		}
	}

	dibujar_racman(pos_racman_enemigo_x, pos_racman_enemigo_y, 1, 0);
	lanzarTimer(0);

}


int comprobar_mov(int direccion){

	int mover = 0;
	switch (direccion){
		case 0: //mover arriba
			// comprobar si es legal el movimiento
			if(pos_racman_propio_y - 1 >= 0 && mapa[pos_racman_propio_y - 1][pos_racman_propio_x] != -1){

				//todo añadir comprbante de si había bolita o no para sumar al contador
				if(mapa[pos_racman_propio_y][pos_racman_propio_x] > 3 || mapa[pos_racman_propio_y][pos_racman_propio_x] < 6){ //se lleva puntos
					puntos_jugador_1 += mapa[pos_racman_propio_y][pos_racman_propio_x] - 3;
				}

				mapa[pos_racman_propio_y][pos_racman_propio_x] = 0;
				pos_racman_propio_y -= 1;

				mapa[pos_racman_propio_y][pos_racman_propio_x] += 3;

				mover = 1;
			}
			break;

		case 1: //mover izquierda
			// comprobar si es legal el movimiento
			if(pos_racman_propio_x - 1 >= 0 && mapa[pos_racman_propio_y][pos_racman_propio_x - 1] != -1){

				//todo añadir comprbante de si había bolita o no para sumar al contador
				if(mapa[pos_racman_propio_y][pos_racman_propio_x] > 3 || mapa[pos_racman_propio_y][pos_racman_propio_x] < 6){ //se lleva puntos
					puntos_jugador_1 += mapa[pos_racman_propio_y][pos_racman_propio_x] - 3;
				}

				mapa[pos_racman_propio_y][pos_racman_propio_x] = 0;

				pos_racman_propio_x -= 1;

				mapa[pos_racman_propio_y][pos_racman_propio_x] += 3;

				mover = 1;

			}
			break;

		case 2: //mover derecha
			// comprobar si es legal el movimiento
			if(pos_racman_propio_x + 1 <= 19 && mapa[pos_racman_propio_y][pos_racman_propio_x + 1] != -1){

				//todo añadir comprbante de si había bolita o no para sumar al contador
				if(mapa[pos_racman_propio_y][pos_racman_propio_x] > 3 || mapa[pos_racman_propio_y][pos_racman_propio_x] < 6){ //se lleva puntos
					puntos_jugador_1 += mapa[pos_racman_propio_y][pos_racman_propio_x] - 3;
				}

				mapa[pos_racman_propio_y][pos_racman_propio_x] = 0;

				pos_racman_propio_x += 1;

				mapa[pos_racman_propio_y][pos_racman_propio_x] += 3;

				mover = 1;

			}
			break;

		case 3: //mover abajo
			// comprobar si es legal el movimiento
			if(pos_racman_propio_y + 1 <= 15 && mapa[pos_racman_propio_y + 1][pos_racman_propio_x] != -1){

				//todo añadir comprbante de si había bolita o no para sumar al contador
				if(mapa[pos_racman_propio_y][pos_racman_propio_x] > 3 || mapa[pos_racman_propio_y][pos_racman_propio_x] < 6){ //se lleva puntos
					puntos_jugador_1 += mapa[pos_racman_propio_y][pos_racman_propio_x] - 3;
				}

				mapa[pos_racman_propio_y][pos_racman_propio_x] = 0;

				pos_racman_propio_y += 1;

				mapa[pos_racman_propio_y][pos_racman_propio_x] += 3;

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
				int aux[2] = {pos_racman_propio_x - i, pos_racman_propio_y - j};
				int movido = 0; //1 si se ha movido

				if(fabs(aux[0]) > fabs(aux[1])){ //movimiento horizontal
					if(aux[0] > 0){ //intentar mover a la derecha
						if(mapa[j][i+1] > -1 && mapa[j][i+1] < 3){
							pos_fantasmas = mover_fantasma(i, j, 2, fantasma, pos_fantasmas);
							movido = 1;
						}
					}else{ //intentar mover a la izquierda

						if(mapa[j][i-1] > -1 && mapa[j][i-1] < 3){
							pos_fantasmas = mover_fantasma(i, j, 1, fantasma, pos_fantasmas);
							movido = 1;
						}
					}
				}else{
					if(aux[1] > 0){ //intentar mover abajo
						if(mapa[j+1][i] > -1 && mapa[j+1][i] < 3){
							pos_fantasmas = mover_fantasma(i, j, 3, fantasma, pos_fantasmas);
							movido = 1;
						}
					}else{ //intentar mover arriba
						if(mapa[j-1][i] > -1 && mapa[j-1][i] < 3){
							pos_fantasmas = mover_fantasma(i, j, 0, fantasma, pos_fantasmas);
							movido = 1;
						}
					}

				}

				if(movido == 0){ //mover a sitio posible aleatorio
					if(mapa[j+1][i] > -1 && mapa[j+1][i] < 3){
						pos_fantasmas = mover_fantasma(i, j, 3, fantasma, pos_fantasmas);

					}else if(mapa[j-1][i] > -1 && mapa[j-1][i] < 3){
						pos_fantasmas = mover_fantasma(i, j, 0, fantasma, pos_fantasmas);


					}else if(mapa[j][i+1] > -1 && mapa[j][i+1] < 3){
						pos_fantasmas = mover_fantasma(i, j, 2, fantasma, pos_fantasmas);


					}else if(mapa[j][i-1] > -1 && mapa[j][i-1] < 3){
						pos_fantasmas = mover_fantasma(i, j, 1, fantasma, pos_fantasmas);

					}
				}

				fantasma++;
			}

		}
	}

}


int* mover_fantasma(int x, int y, int direccion, int f, int movs[]){

	if(mapa[y][x] == 9 ){
		limpiar_pixels(x, y);
	}else if(mapa[y][x] == 10){
		poner_punto(x, y, 0);
	}else{
		poner_punto(x, y, 1);
	}
	mapa[y][x] -= 9;

	switch (direccion){
		case 0: //mover arriba

			dibujar_coco(x, y-1);
			mapa[y-1][x] += 9;

			movs[f*2] = y-1;
			movs[f*2 +1] = x;

			break;

		case 1: //mover izquierda

			dibujar_coco(x-1, y);
			mapa[y][x-1] += 9;

			movs[f*2] = y;
			movs[f*2 +1] = x-1;

			break;

		case 2: //mover derecha

			dibujar_coco(x+1, y);
			mapa[y][x+1] += 9;

			movs[f*2] = y;
			movs[f*2 +1] = x+1;

			break;

		case 3: //mover abajo

			dibujar_coco(x, y+1);
			mapa[y+1][x] += 9;

			movs[f*2] = y+1;
			movs[f*2 +1] = x;

			break;

		default:
			break;

	}
	return movs;

}


int comprobarFantasmaMovido(int pos_fantasmas[], int j, int i){
	int k;
    int q,w,e,r,t,y,u,o;
    q = *(pos_fantasmas+0);
    w = *(pos_fantasmas+1);
    e = *(pos_fantasmas+2);
    r = *(pos_fantasmas+3);
    t = *(pos_fantasmas+4);
    y = *(pos_fantasmas+5);
    u = *(pos_fantasmas+6);
    o = *(pos_fantasmas+7);
	for(k = 0; k < 8; k+=2){
		if(*(pos_fantasmas+k) == j && *(pos_fantasmas+k+1) == i)
			return 0;
	}
	return 1;
}






