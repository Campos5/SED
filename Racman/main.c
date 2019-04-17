/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "uart.h"
#include "Visualizar.h"
#include "lcd.h"

int pos_racman_propio_x;
int pos_racman_propio_y;

int jugador;

int puntos_jugador_1;

extern void Eint4567_init();
extern void keyboard_init();
extern void timer_init();

/*--- declaracion de funciones ---*/
void Main(void);


/*--- codigo de la funcion ---*/
void Main(void){

	sys_init(); // inicializacion de la placa, interrupciones, puertos

	Eint4567_init(); // inicializacion de los botones
	keyboard_init();
	timer_init();

	init_visualizacion();

	dibujar_mapa();

	lanzarTimer(0);

	while(1);
	//Uart_Init(115200); // inicializacion de la Uart
	//Uart_Config(); // configuración de interrupciones y buffers

	// Por ahora este main espera que le llegue un entero por el serie
	// y cuando le llega hace un led switch
/*
	D8Led_symbol(0);

	char* mensajeRecibido = "";
	char c[60];
	int numeroLeido = 0;

	lcd_on();

	lcd_draw_vline( 240, 0, 150, BLACK, 4);

	lcd_printf(40, 16, BLACK, "OUTBOX");

	lcd_printf(210, 16, BLACK, "INBOX");*/
}
