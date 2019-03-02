/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
/*--- funciones externas ---*/
extern void leds_switch();
extern void leds_off();
extern void led1_on();
extern void led2_on();
extern void D8Led_symbol(int value);
extern void jugadorPierde();
extern void keyboard_init();
extern void Eint4567_init();
/*--- declaracion de funciones ---*/
void timer_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer_ISR_1(void) __attribute__ ((interrupt ("IRQ")));
void timer_ISR_2(void) __attribute__ ((interrupt ("IRQ")));
void timer_init(void);
void lanzarTimer(int timer);
void pararTimer(int timer);

/*--- codigo de las funciones ---*/

/*--- Timers globales ---*/
int timer0;
int timer1;
int timer2;



void timer_init(void)
{
	timer0 = 0;
	timer1 = 0;
	timer2 = 0;

	/* Configuracion del controlador de interrupciones */	
	rINTMOD = 0x0;// Configurar las lineas como de tipo IRQ
	rINTCON = 0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)
	rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global

	rINTMSK = rINTMSK & ~(BIT_TIMER1 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer1 y el bit global

	rINTMSK = rINTMSK & ~(BIT_TIMER2 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer2 y el bit global


	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER0 = (unsigned)timer_ISR;

	pISR_TIMER1 = (unsigned)timer_ISR_1;

	pISR_TIMER2 = (unsigned)timer_ISR_2;

	/* Configurar el Timer0 (el resto de los timers se dejan a la
	configuración por defecto) */
	rTCFG0 = 0xFF;// pre-escalado = 255

	rTCFG1 &= 0xFFFFF0;// divisor = 1/2 Timer0
	rTCFG1 &= 0xFFFF0F;// divisor = 1/2 Timer1
	rTCFG1 &= 0xFFF3FF;// divisor = 1/2 Timer2

	rTCNTB0 = 65535;
	rTCMPB0 = 12800;
	
	rTCNTB1 = 65535;
	rTCMPB1 = 12800;

	rTCNTB2 = 65535;
	rTCMPB2 = 12800;

	rTCON = rTCON | (0x01<<1);// establecer manual_update timer0
	rTCON = rTCON | (0x01<<9);// establecer manual_update timer1
	rTCON = rTCON | (0x01<<13);// establecer manual_update timer2

	rTCON = rTCON & ~(0x01<<1);// DESACTIVA manual_update timer0
	rTCON = rTCON & ~(0x01<<9);// DESACTIVA manual_update timer1
	rTCON = rTCON | (0x01<<13);// establecer manual_update timer2


	rTCON = rTCON | (0x01<<3);//activar modo auto-reload timer0
	rTCON = rTCON | (0x01<<11);//activar modo auto-reload timer1
	rTCON = rTCON | (0x01<<15);//activar modo auto-reload timer1

	rTCON = rTCON | (0x01<<0);// iniciar timer0


}

void timer_ISR(void){
	timer0 += 1;

	if (timer0 == 10)
	{
		pararTimer(0);
		leds_off();
		led1_on();
		keyboard_init();
		Eint4567_init();

	}
	D8Led_symbol(10 - timer0);

	rI_ISPC = BIT_TIMER0;

}

void timer_ISR_1(void){

	timer1 += 1;

	if (timer1 == 15)
	{
		pararTimer(1);
		jugadorPierde();

	}
	D8Led_symbol(15 - timer1);

	rI_ISPC = BIT_TIMER1;
}


void timer_ISR_2(void){

	timer2 += 1;

	if(timer2 == 60){
		pararTimer(2);
		terminarPartida(1);
	}
	rI_ISPC = BIT_TIMER2;

}

void lanzarTimer(int timer) {
	switch(timer)
		{
		case 0:
			rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_GLOBAL); // Enmascarar todas las lineas excepto Timer0 y el bit global
			rTCON = rTCON | (0x01<<3);//activar modo auto-reload timer0
			rTCON = rTCON | (0x01<<1);// establecer manual_update timer0
			rTCON = rTCON & ~(0x01<<1);// DESACTIVA manual_update timer0
			rTCON = rTCON | (0x01<<0);// iniciar timer0
			break;
		case 1:
			rINTMSK = rINTMSK & ~(BIT_TIMER1 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer1 y el bit global
			rTCON = rTCON | (0x01<<9);// establecer manual_update timer1
			rTCON = rTCON & ~(0x01<<9);// DESACTIVA manual_update timer1
			rTCON = rTCON | (0x01<<11);//activar modo auto-reload timer1
			rTCON = rTCON | (0x01<<8);// iniciar timer1
			break;
		case 2:
			rINTMSK = rINTMSK & ~(BIT_TIMER2 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer1 y el bit global
			rTCON = rTCON | (0x01<<13);// establecer manual_update timer1
			rTCON = rTCON & ~(0x01<<13);// DESACTIVA manual_update timer1
			rTCON = rTCON | (0x01<<15);//activar modo auto-reload timer1
			rTCON = rTCON | (0x01<<12);// iniciar timer1
			break;
		}
}

void pararTimer(int timer){
	switch(timer)
	{
	case 0:
		rINTMSK = rINTMSK | (BIT_TIMER0);
		rTCON=rTCON & ~(0x01<<3); //desactivar modo auto-reload
		timer0 = 0;
		break;
	case 1:
		rINTMSK = rINTMSK | (BIT_TIMER1);// Enmascarar todas las lineas excepto Timer1 y el bit global
		rTCON=rTCON & ~(0x01<<11); //desactivar modo auto-reload
		timer1 = 0;
		break;
	case 2:
		rINTMSK = rINTMSK | (BIT_TIMER2);// Enmascarar todas las lineas excepto Timer2 y el bit global
		rTCON=rTCON & ~(0x01<<15); //desactivar modo auto-reload
		timer2 = 0;
		break;
	}
}
