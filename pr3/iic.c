#include "44b.h"
#include "s3c44b0x.h"
#include "s3cev40.h"
#include "iic.h"

extern uint32 mclk;			   // Frecuencia actual del reloj (Hz)

extern void DelayMs(int ms_time);

void iic_init( void )
{
	// Enable IIC & GPIO & BDMA blocks (si no se activa BDMA, el controlador IIC no es accesible)
	rCLKCON = rCLKCON | (0x1 << 13);
	rCLKCON = rCLKCON | (0x1 << 7);
	rCLKCON = rCLKCON | (0x1 << 10);

	// PF[1] = IICSDA, PF[0] = IICSCL
	rPCONF = rPCONF & ~(0x1 << 0) &  ~(0x1 << 2);
	rPCONF = rPCONF | (0x1 << 1) | (0x1 << 3);

	// Pull-up enable
	rPUPF = 0x0;

    //Configurar la direcci�n del slave
	rIICADD = S3C44B0X_SLAVE_ADDRESS;

    //Generaci�n ACK habilitada, interrupciones habilitadas
	rIICCON = rIICCON | (0x1 << 7) | (0x1 << 5);
    rIICCON = rIICCON | ((mclk / 4000000 - 1) & 0xf); 	//Valor de preescalado, PREESCALER = mclk/16/250000 -1

    // Activa Tx/Rx
    //rIICSTAT = rIICSTAT | (0x1 << 4);
    rIICSTAT = 0x1 << 4;


}

void iic_putByte_start( uint8 byte )
{
	// Escribe el dato
	rIICDS = byte;

	// M�ster Tx, start condition, Tx/Rx habilitada
	//11,1,1 -> 11110000
	rIICSTAT = 0xF0;

	// Comienza la transmisi�n (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1 << 4);

	// Espera la recepci�n de ACK
	while((rIICCON & (0x1<<4))==0);

}

void iic_putByte( uint8 byte )
{
    // Escribe el dato
	rIICDS = byte;

	// Comienza la transmisi�n del dato (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1 << 4);

    // Espera la recepci�n de ACK  
	while((rIICCON & (0x1<<4))==0);
};

void iic_putByte_stop( uint8 byte )
{
    // Escribe el dato
	rIICDS = byte;

	// Comienza la trasmisi�n del dato (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1 << 4);

    // Espera la recepci�n de ACK  
	while((rIICCON & (0x1<<4))==0);

    // M�ster Tx, stop condition, Tx/Rx habilitada
	//11,0,1 -> 11010000
	rIICSTAT = 0xD0;

    // Comienza la trasmisi�n de STOP (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1 << 4);

    // Espera a que la stop condition tenga efecto (5 ms para la at24c04)
	DelayMs(5);
}


void iic_getByte_start( uint8 byte )
{
	// Escribe el dato
	rIICDS = byte;

    // M�ster Rx, start condition, Tx/Rx habilitada
	//11,1,1 -> 10110000
	rIICSTAT = 0xB0;

    // Comienza la transmisi�n (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1 << 4);

    // Espera la rececpi�n de ACK
	while((rIICCON & (0x1<<4))==0);

}

uint8 iic_getByte( void )
{
    // Reanuda la recepci�n (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1 << 4);
	// Espera la recepci�n del dato
	while((rIICCON & (0x1<<4))==0);

    return IICDS;// Lee el dato
}

uint8 iic_getByte_stop( int8 ack )
{
	uint8 byte;

    IICCON = (IICCON & ~(1 << 7)) | (ack << 7); // Habilita/deshabilita la generaci�n de ACK

    // Reanuda la recepci�n (borrando pending bit del IICCON)
    rIICCON = rIICCON & ~(0x1 << 4);

	// Espera la recepci�n del dato
    while((rIICCON & (0x1<<4))==0);

    byte = IICDS;	// Lee el dato

   	// M�ster Rx, stop condition, Tx/Rx habilitada
    //11,0,1 -> 10010000
	rIICSTAT = 0x90;

   	// Comienza la trasmisi�n de STOP (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1 << 4);

   	// Espera a que la stop condition tenga efecto (5 ms para la at24c04)
	DelayMs(5);

	IICCON |= (1<<7); // Habilita la generaci�n de ACK
   	return byte;
}
