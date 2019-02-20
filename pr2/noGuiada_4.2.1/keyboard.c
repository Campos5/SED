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
/*--- Declaracion de funciones ---*/
void keyboard_init();
void KeyboardInt(void) __attribute__ ((interrupt ("IRQ")));
/*--- Codigo de las funciones ---*/
void keyboard_init()
{
	/* Configurar el puerto G (si no lo estuviese ya) */	
		// Establece la funcion de los pines (EINT0-7)
		// Habilita el "pull up" del puerto
		// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	/* Establece la rutina de servicio para EINT1 */
		//
	/* Configurar controlador de interrupciones */
		// Borra INTPND escribiendo 1s en I_ISPC
		// Configura las lineas como de tipo IRQ mediante INTMOD
		// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	/* Habilitar linea EINT1 */
		//
	/* Por precaucion, se vuelven a borrar los bits de INTPND correspondientes*/
		//
}
void KeyboardInt(void)
{
	/* Esperar trp mediante la funcion DelayMs()*/
	//
	/* Identificar la tecla */
	//
	/* Si la tecla se ha identificado, visualizarla en el 8SEG*/
	if(key > -1)
	{
		//
	}
	/* Esperar a se libere la tecla: consultar bit 1 del registro de datos del puerto G */
	while (){
		//NOTHING
	}
	/* Esperar trd mediante la funcion Delay() */
	//
	/* Borrar interrupción de teclado */
	//
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
		case 0x7:  value = ; break;
		case 0xB:  value = ; break;
		case 0xD:  value = ; break;
		case 0xE:  value = ; break;
	}
	
	/*
	* ESCRIBIR EL CÓDIGO CORRESPONDIENTE A LAS OTRAS FILAS Y COLUMNAS
	*/

	return value;

}
