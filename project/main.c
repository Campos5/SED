/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "uart.h"
#include "lcd.h"
/*--- declaracion de funciones ---*/
int Main(void);

/*--- variables globales ---*/
char str_send[10] = "\nSED-P4 >\0";
char str_error[50] = "\nSe ha producido un desbordamiento!\n\0";
char str[256];

/*--- codigo de la funcion ---*/
void Main(void){


	sys_init(); // inicializacion de la placa, interrupciones, puertos
	Eint4567_init(); // inicializacion de los botones
	lcd_init();
	keyboard_init();
	Uart_Init(115200); // inicializacion de la Uart
	Uart_Config(); // configuración de interrupciones y buffers

	// Por ahora este main espera que le llegue un entero por el serie
	// y cuando le llega hace un led switch

	D8Led_symbol(0);

	char* mensajeRecibido = "";
	char c[60];
	int numeroLeido = 0;

	lcd_on();

	lcd_draw_vline( 240, 0, 150, BLACK, 4);

	lcd_printf(40, 16, BLACK, "OUTBOX");

	lcd_printf(210, 16, BLACK, "INBOX");
}
