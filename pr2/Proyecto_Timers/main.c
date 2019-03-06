/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"
/*--- funciones externas ---*/
extern void leds_on();
extern void timer_init();
//Declarar funciones externas de inicializaci�n

/*--- declaracion de funciones ---*/
void Main(void);
/*--- codigo de funciones ---*/
void Main(void)
{
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	// Inicializacion del temporizador
	leds_on();
	timer_init();
	// Inicializaci�n del teclado matricial
	//keyboard_init();
	/*Inicializaci�n de los botones*/

	while (1); // esperar
}
