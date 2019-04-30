/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "uart.h"
#include "Visualizar.h"
#include "lcd.h"

int pos_racman_propio_x;
int pos_racman_propio_y;


int pos_racman_enemigo_x;
int pos_racman_enemigo_y;

int jugador;


int tipo_juego;
int salir_juego;

int puntos_jugador_1;
int puntos_jugador_2;

extern void Eint4567_init();
extern void keyboard_init();
extern void timer_init();
extern void cargar_pantalla_carga();

/*--- declaracion de funciones ---*/
void Main(void);

char str[1];

/*--- codigo de la funcion ---*/
void Main(void){

	jugador = -1;
	sys_init(); // inicializacion de la placa, interrupciones, puertos

	Uart_Init(115200); // inicializacion de la Uart
	keyboard_init();

	Eint4567_init(); // inicializacion de los botones
	timer_init();

	init_visualizacion();

	//Uart_Config(); // configuración de interrupciones y buffers

	char *pt_str = str;
	while(1){
		*pt_str = Uart_Getch(); // leer caracter
		if (*pt_str == 'i'){ //el otro jugador a iniciado juego
			jugador = 2;
			//todo cambiar lcd
			cargar_pantalla_carga();
			break;
		}
		pt_str = str;
	}

	while(salir_juego == 0);

}
