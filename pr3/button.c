/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "at24c04.h"
#include "def.h"
/*--- variables globales ---*/
int state;
int which_int;
/*--- funciones externas ---*/
//extern void D8Led_Symbol(int value);
/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
void Eint4567_init(void);
extern uint16 dir;
extern uint8 data;

extern void D8Led_symbol(int value);
extern void DelayMs(int ms_time);

void init_buttons();
int pulsa();

/*--- codigo de funciones ---*/
void Eint4567_init(void)
{
	/* Configuracion del controlador de interrupciones */
	// Borra EXTINTPND escribiendo 1s en el propio registro
	rEXTINTPND = 0xF;

	// Borra INTPND escribiendo 1s en I_ISPC
	rI_ISPC = BIT_EINT4567;

	// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0;

	// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON = 0x1;

	// Enmascara todas las lineas excepto Eint4567 y el bit global (INTMSK)
	rINTMSK = rINTMSK & ~(BIT_EINT4567 | BIT_GLOBAL);

	// Establecer la rutina de servicio para Eint4567
	pISR_EINT4567 = (unsigned)Eint4567_ISR;

	/* Configuracion del puerto G */
	// Establece la funcion interrupción en botones 6 y 7
	rPCONG = rPCONG | (1 << 12);
	rPCONG = rPCONG | (1 << 13);
	rPCONG = rPCONG | (1 << 14);
	rPCONG = rPCONG | (1 << 15);

	//Habilita las resistencias de pull-up
	rPUPG = 0x0;

	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	rEXTINT = rEXTINT & ~(1 << 26);
	rEXTINT = rEXTINT | (1 << 25);
	rEXTINT = rEXTINT & ~(1 << 24);

	rEXTINT = rEXTINT & ~(1 << 30);
	rEXTINT = rEXTINT | (1 << 29);
	rEXTINT = rEXTINT & ~(1 << 28);

	/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	rEXTINTPND = 0xF;
	rI_ISPC = BIT_EINT4567;
	state = 0;
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

void Eint4567_ISR(void)
{
	/*Identificar la interrupcion*/
	which_int = rEXTINTPND;

	/* Actualizar simbolo*/
	switch (which_int) {
		case 0x04: //izquierdo
			if(state == 6){
				state = 0;
			}else{
				state += 1;
			}

			while(pulsa() == 0);

			D8Led_symbol(state);
			break;

		case 0x08: //derecho
			at24c04_byteread(dir, &data);
			break;


		default:   //never
			break;
	}

	// espera 100ms para evitar rebotes
	DelayMs(100);

	/*Atendemos interrupciones*/
	//Borramos EXTINTPND ambas lï¿½neas EINT7 y EINT6
	rEXTINTPND = 0xC;

	//Borramos INTPND usando ISPC
	rI_ISPC = 0x3FFFFFF;
}

