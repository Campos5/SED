/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "def.h"
/*--- variables globales ---*/
int symbol;
/*--- funciones externas ---*/
//extern void D8Led_Symbol(int value);
/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
void Eint4567_init(void);
void init_buttons();
int pulsa();
extern void leds_switch ();
extern void D8Led_symbol(int value);

/*--- codigo de funciones ---*/
void Eint4567_init(void)
{
	/* Configuracion del controlador de interrupciones */
	// Borra EXTINTPND escribiendo 1s en el propio registro
	rEXTINTPND = 0xF;

	// Borra INTPND escribiendo 1s en I_ISPC
	rI_ISPC = 0x3FFFFFF;

	// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0;

	// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON = 0x1;

	// Enmascara todas las lineas excepto Eint4567 y el bit global (INTMSK)
	rINTMSK = ~(BIT_EINT4567 | BIT_GLOBAL);

	// Establecer la rutina de servicio para Eint4567
	pISR_EINT4567 = (unsigned)Eint4567_ISR;

	/* Configuracion del puerto G */
	// Establece la funcion de los pines (EINT7-EINT0)
	rPCONG = 0xFFFF;

	//Habilita las resistencias de pull-up
	rPUPG = 0x0;

	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	//0010 0010 0010 0010 0000
	rEXTINT = 0x22220000;

	/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	rEXTINTPND = 0xF;
	rI_ISPC = 0x3FFFFFF;
	symbol = 0;
}

void init_buttons(){
	rPCONG = rPCONG & ~(0x01<<12);
	rPCONG = rPCONG & ~(0x01<<13);
	rPCONG = rPCONG & ~(0x01<<14);
	rPCONG = rPCONG & ~(0x01<<15);
}


int pulsa(){
	int pulsado = rPDATG & (0x40);
	if(pulsado != 0){
		pulsado = rPDATG & (0x80);
	}
	return pulsado; //0-pulsado
}

/*COMENTAR PARA LA PARTE DEL 8-SEGMENTOS
DESCOMENTAR PARA LA PRIMERA PARTE CON INTERRUPCIONES
*/
//void Eint4567_ISR(void)
//{
//	//Conmutamos LEDs
//	while(1){
//		if(pulsa() != 0){
//			DelayMs(10);
//			leds_switch();
//			DelayMs(100);
//			break;
//		}
//	}
//
//
//	/*Atendemos interrupciones*/
//	//Borramos EXTINTPND ambas l�neas EINT7 y EINT6
//	rEXTINTPND = 0xC;
//
//	//Borramos INTPND usando ISPC
//	rI_ISPC = 0x3FFFFFF;
//
//}

/*
DESCOMENTAR PARA LA PARTE DEL 8-SEGMENTOS
COMENTAR PARA LA PRIMERA PARTE CON INTERRUPCIONES*/
int which_int;

void Eint4567_ISR(void)
{
	/*Identificar la interrupcion*/
	which_int = rEXTINTPND;

	/* Actualizar simbolo*/
	switch (which_int) {
		case 0x04: //izquierdo
			if(symbol == 0){
				symbol = 15;
			}else{
				symbol -= 1;
			}

			while(pulsa() == 0);

			D8Led_symbol(symbol);
			break;

		case 0x08: //derecho
			if(symbol == 15){
				symbol = 0;
			}else{
				symbol += 1;
			}

			while(pulsa() == 0);

			D8Led_symbol(symbol);
			break;


		default:   //never
			break;
	}
	// muestra el simbolo en el display


	// espera 100ms para evitar rebotes
	DelayMs(100);

	/*Atendemos interrupciones*/
	//Borramos EXTINTPND ambas l�neas EINT7 y EINT6
	rEXTINTPND = 0xC;

	//Borramos INTPND usando ISPC
	rI_ISPC = 0x3FFFFFF;
}

