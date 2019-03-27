/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "uart.h"
#include <stdarg.h>
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
	/* Configure las ISRs de env�o y recepci�n */
	//
	//
	
	/* Inicialice el estado del buffer de recepci�n 
	//(establece los punteros de lectura y escritura al comienzo de este) */
	//
	//
	
	/* Borrar interrupciones y configurar la l�nea INT_URXD0 como IRQ y desenmascararla */ 
	//
	//
	//
	
}

inline void Uart_TxEmpty(void)
{
	while (!(rUTRSTAT0 & 0x4)); // esperar a que el shifter de TX se vacie
}
	
char Uart_Getch(void)
{
	
	//Esperar mientras que los punteros de lectura y escritura sean iguales
	//Almacenar en data1 el valor apuntado por el puntero de lectura
	//Mover el puntero de lectura a la siguiente posici�n del buffer
	
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
	//Desenmascarar la l�nea de interrupci�n INT_UTXD0.
	//Esperar a que Uart0_TxInt() haya recorrido todo el buffer.
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
	if(keyBufWrPt < KEY_BUFLEN && keyBufRdPt!=keyBufWrPt_new){
		//Leer el dato de la UART con la macro y asign�rselo a data2
		data2 = RdURXH0();
		//Almacenar data2 en el buffer
		keyBuf[keyBufWrPt];
		//Actualizar el puntero de escritura del buffer
		keyBufWrPt = keyBufWrPt_new;
	}
	else{
		Uart_Printf(str_error2);
	}
	//Borrar interrupci�n pendiente
	//TODO
}

void Uart0_TxInt(){

	//Escribir el car�cter correspondiente del buffer de env�o en la UART a trav�s de la macro
	//Actualizar el puntero al buffer de env�o
	
	if(*uart0TxStr=='\0')
		//Enmascarar linea INT_UTXD0
	
	//Borrar interrupci�n pendiente

}

int siguiente(int keyPt){
	return (keyPt +1)%KEY_BUFLEN;
}
