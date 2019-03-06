#include "s3c44b0x.h"
#include "s3cev40.h"
#include "iic.h"

extern uint32 mclk;			   // Frecuencia actual del reloj (Hz)

extern void DelayMs(int ms_time);

void iic_init( void )
{
	// Enable IIC & GPIO & BDMA blocks (si no se activa BDMA, el controlador IIC no es accesible)
	
	// PF[1] = IICSDA, PF[0] = IICSCL
	// Pull-up enable
	
    //Configurar la direcci�n del slave

    //Generaci�n ACK habilitada, interrupciones habilitadas
    IICCON = IICCON | ((mclk / 4000000 - 1) & 0xf); 	//Valor de preescalado, PREESCALER = mclk/16/250000 -1
    // Activa Tx/Rx
}

void iic_putByte_start( uint8 byte )
{
	// Escribe el dato
	// M�ster Tx, start condition, Tx/Rx habilitada
	// Comienza la transmisi�n (borrando pending bit del IICCON)
    // Espera la recepci�n de ACK  
}

void iic_putByte( uint8 byte )
{
    // Escribe el dato
	// Comienza la transmisi�n del dato (borrando pending bit del IICCON)
    // Espera la recepci�n de ACK  
};

void iic_putByte_stop( uint8 byte )
{
    // Escribe el dato
	// Comienza la trasmisi�n del dato (borrando pending bit del IICCON)
    // Espera la recepci�n de ACK  
    
    // M�ster Tx, stop condition, Tx/Rx habilitada
    // Comienza la trasmisi�n de STOP (borrando pending bit del IICCON)
    // Espera a que la stop condition tenga efecto (5 ms para la at24c04)
}

void iic_getByte_start( uint8 byte )
{
	// Escribe el dato
    // M�ster Rx, start condition, Tx/Rx habilitada
    // Comienza la transmisi�n (borrando pending bit del IICCON)
    // Espera la rececpi�n de ACK
}

uint8 iic_getByte( void )
{
    // Reanuda la recepci�n (borrando pending bit del IICCON)
	// Espera la recepci�n del dato
    return IICDS;// Lee el dato
}

uint8 iic_getByte_stop( int8 ack )
{
	uint8 byte;

    IICCON = (IICCON & ~(1 << 7)) | (ack << 7); // Habilita/deshabilita la generaci�n de ACK

    // Reanuda la recepci�n (borrando pending bit del IICCON)
	// Espera la recepci�n del dato
    byte = IICDS;	// Lee el dato

   	// M�ster Rx, stop condition, Tx/Rx habilitada
   	// Comienza la trasmisi�n de STOP (borrando pending bit del IICCON)
   	// Espera a que la stop condition tenga efecto (5 ms para la at24c04)

	IICCON |= (1<<7); // Habilita la generaci�n de ACK
   	return byte;
}
