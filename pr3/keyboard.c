/*--- Ficheros de cabecera ---*/
#include "44b.h"
#include "at24c04.h"
#include "def.h"
/*--- Definición de macros ---*/
#define KEY_VALUE_MASK 0xF
/*--- Variables globales ---*/
volatile UCHAR *keyboard_base = (UCHAR *)0x06000000;
int key;
uint16 dir;
uint8 data;

/*--- Funciones externas ---*/
extern void D8Led_symbol(int value);

/*--- Declaracion de funciones ---*/
void keyboard_init();
int key_read();
uint16 get_dir();
uint8 get_data();
void KeyboardInt(void) __attribute__ ((interrupt ("IRQ")));

extern void DelayMs(int ms_time);
extern void at24c04_bytewrite( uint16 addr, uint8 data );
extern void at24c04_byteread( uint16 addr, uint8 *data );

extern int get_state();
/*--- Codigo de las funciones ---*/
uint16 get_dir(){
	return dir;
}


uint8 get_data(){
	return data;
}




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
	rINTMSK = rINTMSK & ~(BIT_EINT1 | BIT_GLOBAL);

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
	//
	/* Si la tecla se ha identificado, visualizarla en el 8SEG*/
	if(key > -1)
	{

		switch(get_state()) {

			case 1:
				dir = key << (0x04);

				break;
			case 2:
				dir = key >> (0x04);

				break;
			case 3:


				break;
			case 4:


				break;
			case 5:
				at24c04_bytewrite(dir, data);

				break;
		}
		D8Led_symbol(key);

	}
	/* Esperar a se libere la tecla: consultar bit 1 del registro de datos del puerto G */
	while ( (rPDATG & (1 << 1) ) == 0){
		//NOTHING
	}
	/* Esperar trd mediante la funcion Delay() */
	//
	DelayMs(100);
	/* Borrar interrupción de teclado */
	//
	rI_ISPC = BIT_EINT1;

	//rTCON = rTCON | (0x01<<8);// iniciar timer1
}
int key_read()
{
	int value = -1;
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

