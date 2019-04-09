/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "uart.h"
#include <stdarg.h>
#include <stdio.h>

/*--- definicion de constantes ---*/
#define KEY_BUFLEN 100
/*--- variables globales ---*/
static unsigned char keyBuf[KEY_BUFLEN]; // buffer de recepcion
volatile static int keyBufRdPt=0; // puntero de lectura
volatile static int keyBufWrPt=0; // puntero de escritura
static char *uart0TxStr; // puntero al buffer de envio

char str_error2[50] = "\nBuffer completo!\n\0";
/*--- prototipos de funciones ---*/
void Uart0_RxInt(void) __attribute__ ((interrupt ("IRQ")));
void Uart0_TxInt(void) __attribute__ ((interrupt ("IRQ")));


char data1;
char data2;
int keyBufWrPt_new;	


/*--- implementacion de las funciones ---*/
void Uart_Init(int baud)
{

	/* UART0 */
	rULCON0=0x3; // modo normal, sin paridad, stop=1b, char=8b
	rUCON0=0x205; // tx=level, rx=edge, no timeout/error, normal, int/polling
	rUBRDIV0=( (int)(MCLK/16./baud + 0.5) -1 ); // formula div. frecuencia
	rUFCON0=0x0; // desactivar FIFO
	rUMCON0=0x0; // desactivar control de flujo

}

void Uart_Config(void)
{
	/* Configure las ISRs de envío y recepción */
	pISR_URXD0 = (unsigned)Uart0_RxInt;
	pISR_UTXD0 = (unsigned)Uart0_TxInt;

	/* Inicialice el estado del buffer de recepción
	//(establece los punteros de lectura y escritura al comienzo de este) */
	keyBufRdPt = 0;
	keyBufWrPt = 0;

	/* Borrar interrupciones y configurar la línea INT_URXD0 como IRQ y desenmascararla */
	rI_ISPC = ~0x0;
	rINTCON &= ~(0x1 << 2);
	rINTMOD &= ~(0x1 << 7);
	rINTMSK = rINTMSK & ~(BIT_URXD0 | BIT_GLOBAL);

}

inline void Uart_TxEmpty(void)
{
	while (!(rUTRSTAT0 & 0x4)); // esperar a que el shifter de TX se vacie
}
	
char Uart_Getch(void)
{

	//Esperar mientras que los punteros de lectura y escritura sean iguales
	while(keyBufRdPt == keyBufWrPt);

	//Almacenar en data1 el valor apuntado por el puntero de lectura
	data1 = keyBuf[keyBufRdPt];

	//Mover el puntero de lectura a la siguiente posición del buffer
	keyBufRdPt = siguiente(keyBufRdPt);
	
	return data1;

}

void Uart_SendByte(int data)
{
	char localBuf[2] ={'\0','\0'};
	if(data == '\n')
	{
	while (!(rUTRSTAT0 & 0x2)); // esperar a que THR se vacie
	WrUTXH0('\r'); // escribir retorno de carro (macro definida en 44b.h)
	}
	while (!(rUTRSTAT0 & 0x2)); // esperar a que THR se vacie
	WrUTXH0(data); // escribir data (macro definida en 44b.h)
}

void Uart_SendString(char *pt)
{
	//Actualizar uart0TxStr para que apunte al comienzo del string que queremos enviar
	uart0TxStr = pt;

	//Desenmascarar la línea de interrupción INT_UTXD0.
	rINTMSK = rINTMSK & ~(BIT_UTXD0);

	//Esperar a que Uart0_TxInt() haya recorrido todo el buffer.
	Uart_TxEmpty();
}

void Uart_Printf(char *fmt,...)
{
	va_list ap;
	char string[256];
	va_start(ap,fmt);
	vsprintf(string,fmt,ap);
	Uart_SendString(string);
	va_end(ap);
}

void Uart0_RxInt(){

	keyBufWrPt_new = siguiente(keyBufWrPt);
	if(keyBufRdPt!=keyBufWrPt_new){
		//Leer el dato de la UART con la macro y asignárselo a data2
		data2 = RdURXH0();

		//Almacenar data2 en el buffer
		keyBuf[keyBufWrPt] = data2;

		//Actualizar el puntero de escritura del buffer
		keyBufWrPt = siguiente(keyBufWrPt);
	}
	else{
		Uart_Printf(str_error2);
	}
	//Borrar interrupción pendiente
	rI_ISPC = rI_ISPC | (0x1 << 7);
}

void Uart0_TxInt(){

	//Escribir el carácter correspondiente del buffer de envío en la UART a través de la macro
	WrUTXH0(data1);

	//Actualizar el puntero al buffer de envío
	uart0TxStr = siguiente(uart0TxStr);


	if(*uart0TxStr=='\0'){
		//Enmascarar linea INT_UTXD0
		rINTMSK = rINTMSK | (BIT_UTXD0);
	}

	//Borrar interrupción pendiente
	rI_ISPC = rI_ISPC | (0x1 << 3);

}

int siguiente(int keyPt){
	return (keyPt +1)%KEY_BUFLEN;
}
