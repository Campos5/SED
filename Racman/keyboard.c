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
void D8Led_symbol(int value);

extern int mapa[(240/16)][(320/16)];

extern int pos_racman_propio_x;
extern int pos_racman_propio_y;

extern int direccion_racman_propio;
extern int direccion_defecto_propio;

extern int jugador;

extern int puntos_jugador_1;


/*--- Declaracion de funciones ---*/
void keyboard_init();
void KeyboardInt(void) __attribute__ ((interrupt ("IRQ")));



void realizar_movimiento();



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
	rI_ISPC = ~0x0;
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
	rI_ISPC = ~0x0;
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
		dibujar_racman(pos_racman_propio_x, pos_racman_propio_y, 0);

	}else{ //se mueve, o lo intenta, en la direccion que llevaba antes

		if(comprobar_mov(direccion_defecto_propio) == 1){

			//limpiar la casilla donde se encuentra racman
			limpiar_pixels(x_ant, y_ant);


			//poner a racman en la nueva posicion
			dibujar_racman(pos_racman_propio_x, pos_racman_propio_y, 0);

		}else{ //no se mueve para ningún lado
			//creo que no debería hacer nada aquí
		}


	}


	//todo mandar y recibir información de la uart
	D8Led_symbol(puntos_jugador_1 % 15);

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

				mapa[pos_racman_propio_y][pos_racman_propio_x] = 0;;

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
