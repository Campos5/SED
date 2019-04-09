/*-----------------------------------------------------------------
**
**	Fichero:
**		s3c44b0x.h  2/2/2013
**
**		(c) J.M. Mendias
**		Programación de Sistemas y Dispositivos
**		Facultad de Informática. Universidad Complutense de Madrid
**
**	Propósito:
**		Creación de nemotécnicos para los registros de los
**		controladores de dispositivos internos del chip S3C44B0X
**
**	Notas de diseño:
**		Las direcciones usadas asumen un alineamiento little-endian
**
**---------------------------------------------------------------*/

#ifndef __S3C44B0X_H__
#define __S3C44B0X_H__

/* Controlador de memoria */
#define BWSCON		(*(volatile unsigned *)0x1c80000)
#define BANKCON0	(*(volatile unsigned *)0x1c80004)
#define BANKCON1	(*(volatile unsigned *)0x1c80008)
#define BANKCON2	(*(volatile unsigned *)0x1c8000c)
#define BANKCON3	(*(volatile unsigned *)0x1c80010)
#define BANKCON4	(*(volatile unsigned *)0x1c80014)
#define BANKCON5	(*(volatile unsigned *)0x1c80018)
#define BANKCON6	(*(volatile unsigned *)0x1c8001c)
#define BANKCON7	(*(volatile unsigned *)0x1c80020)
#define REFRESH		(*(volatile unsigned *)0x1c80024)
#define BANKSIZE	(*(volatile unsigned *)0x1c80028)
#define MRSRB6		(*(volatile unsigned *)0x1c8002c)
#define MRSRB7		(*(volatile unsigned *)0x1c80030)

/* Gestor de reloj y energía */
#define PLLCON		(*(volatile unsigned *)0x1d80000)
#define CLKCON		(*(volatile unsigned *)0x1d80004)
#define CLKSLOW		(*(volatile unsigned *)0x1d80008)
#define LOCKTIME	(*(volatile unsigned *)0x1d8000c)

/* Controlador de cache */
#define SYSCFG		(*(volatile unsigned *)0x1c00000)
#define NCACHBE0	(*(volatile unsigned *)0x1c00004)
#define NCACHBE1	(*(volatile unsigned *)0x1c00008)

/* Árbitro de bus */
#define SBUSCON		(*(volatile unsigned *)0x1c40000)
 
/* Controlador de DMA */ 
#define ZDCON0		(*(volatile unsigned *)0x1e80000) /* canal ZDMA 0 */
#define ZDISRC0		(*(volatile unsigned *)0x1e80004)
#define ZDIDES0		(*(volatile unsigned *)0x1e80008)
#define ZDICNT0		(*(volatile unsigned *)0x1e8000c)
#define ZDCSRC0		(*(volatile unsigned *)0x1e80010)
#define ZDCDES0		(*(volatile unsigned *)0x1e80014)
#define ZDCCNT0		(*(volatile unsigned *)0x1e80018)
#define ZDCON1		(*(volatile unsigned *)0x1e80020) /* canal ZDMA 1 */
#define ZDISRC1		(*(volatile unsigned *)0x1e80024)
#define ZDIDES1		(*(volatile unsigned *)0x1e80028)
#define ZDICNT1		(*(volatile unsigned *)0x1e8002c)
#define ZDCSRC1		(*(volatile unsigned *)0x1e80030)
#define ZDCDES1		(*(volatile unsigned *)0x1e80034)
#define ZDCCNT1		(*(volatile unsigned *)0x1e80038)
#define BDCON0		(*(volatile unsigned *)0x1f80000) /* canal BDMA 0 */
#define BDISRC0		(*(volatile unsigned *)0x1f80004)
#define BDIDES0		(*(volatile unsigned *)0x1f80008)
#define BDICNT0		(*(volatile unsigned *)0x1f8000c)
#define BDCSRC0		(*(volatile unsigned *)0x1f80010)
#define BDCDES0		(*(volatile unsigned *)0x1f80014)
#define BDCCNT0		(*(volatile unsigned *)0x1f80018)
#define BDCON1		(*(volatile unsigned *)0x1f80020) /* canal BDMA 1 */
#define BDISRC1		(*(volatile unsigned *)0x1f80024)
#define BDIDES1		(*(volatile unsigned *)0x1f80028)
#define BDICNT1		(*(volatile unsigned *)0x1f8002c)
#define BDCSRC1		(*(volatile unsigned *)0x1f80030)
#define BDCDES1		(*(volatile unsigned *)0x1f80034)
#define BDCCNT1		(*(volatile unsigned *)0x1f80038)

/* Controlador de puertos de E/S */
#define SPUCR		(*(volatile unsigned *)0x1d2004c)
#define PCONA		(*(volatile unsigned *)0x1d20000) /* puerto A */
#define PDATA		(*(volatile unsigned *)0x1d20004)
#define PCONB		(*(volatile unsigned *)0x1d20008) /* puerto B */
#define PDATB		(*(volatile unsigned *)0x1d2000c)
#define PCONC		(*(volatile unsigned *)0x1d20010) /* puerto C */
#define PDATC		(*(volatile unsigned *)0x1d20014)
#define PUPC		(*(volatile unsigned *)0x1d20018)
#define PCOND		(*(volatile unsigned *)0x1d2001c) /* puerto D */
#define PDATD		(*(volatile unsigned *)0x1d20020)
#define PUPD		(*(volatile unsigned *)0x1d20024)
#define PCONE		(*(volatile unsigned *)0x1d20028) /* puerto E */
#define PDATE		(*(volatile unsigned *)0x1d2002c)
#define PUPE		(*(volatile unsigned *)0x1d20030)
#define PCONF		(*(volatile unsigned *)0x1d20034) /* puerto F */
#define PDATF		(*(volatile unsigned *)0x1d20038)
#define PUPF		(*(volatile unsigned *)0x1d2003c)
#define PCONG		(*(volatile unsigned *)0x1d20040) /* puerto G */
#define PDATG		(*(volatile unsigned *)0x1d20044)
#define PUPG		(*(volatile unsigned *)0x1d20048)
#define EXTINT		(*(volatile unsigned *)0x1d20050)
#define EXTINTPND	(*(volatile unsigned *)0x1d20054)
 
/* Bits de EXTINTPND */
#define BIT_EINT4	(0x1)
#define BIT_EINT5	(0x1<<1)
#define BIT_EINT6	(0x1<<2)
#define BIT_EINT7	(0x1<<3)

/* Temporizadores */
#define TCFG0		(*(volatile unsigned *)0x1d50000) 
#define TCFG1		(*(volatile unsigned *)0x1d50004)
#define TCON		(*(volatile unsigned *)0x1d50008)
#define TCNTB0		(*(volatile unsigned *)0x1d5000c) /* temporizador 0 */
#define TCMPB0		(*(volatile unsigned *)0x1d50010)
#define TCNTO0		(*(volatile unsigned *)0x1d50014)
#define TCNTB1		(*(volatile unsigned *)0x1d50018) /* temporizador 1 */
#define TCMPB1		(*(volatile unsigned *)0x1d5001c)
#define TCNTO1		(*(volatile unsigned *)0x1d50020)
#define TCNTB2		(*(volatile unsigned *)0x1d50024) /* temporizador 2 */
#define TCMPB2		(*(volatile unsigned *)0x1d50028)
#define TCNTO2		(*(volatile unsigned *)0x1d5002c)
#define TCNTB3		(*(volatile unsigned *)0x1d50030) /* temporizador 3 */
#define TCMPB3		(*(volatile unsigned *)0x1d50034)
#define TCNTO3		(*(volatile unsigned *)0x1d50038)
#define TCNTB4		(*(volatile unsigned *)0x1d5003c) /* temporizador 4 */
#define TCMPB4		(*(volatile unsigned *)0x1d50040)
#define TCNTO4		(*(volatile unsigned *)0x1d50044)
#define TCNTB5		(*(volatile unsigned *)0x1d50048) /* temporizador 5 */
#define TCNTO5		(*(volatile unsigned *)0x1d5004c)
 
/* UART */
#define ULCON0		(*(volatile unsigned *)0x1d00000) /* canal 0 */
#define UCON0		(*(volatile unsigned *)0x1d00004)
#define UFCON0		(*(volatile unsigned *)0x1d00008)
#define UMCON0		(*(volatile unsigned *)0x1d0000c)
#define UTRSTAT0	(*(volatile unsigned *)0x1d00010)
#define UERSTAT0	(*(volatile unsigned *)0x1d00014)
#define UFSTAT0		(*(volatile unsigned *)0x1d00018)
#define UMSTAT0		(*(volatile unsigned *)0x1d0001c)
#define UBRDIV0		(*(volatile unsigned *)0x1d00028)
#define ULCON1		(*(volatile unsigned *)0x1d04000) /* canal 1 */
#define UCON1		(*(volatile unsigned *)0x1d04004)
#define UFCON1		(*(volatile unsigned *)0x1d04008)
#define UMCON1		(*(volatile unsigned *)0x1d0400c)
#define UTRSTAT1	(*(volatile unsigned *)0x1d04010)
#define UERSTAT1	(*(volatile unsigned *)0x1d04014)
#define UFSTAT1		(*(volatile unsigned *)0x1d04018)
#define UMSTAT1		(*(volatile unsigned *)0x1d0401c)
#define UBRDIV1		(*(volatile unsigned *)0x1d04028)

/* Controlador de interrupciones */
#define INTCON		(*(volatile unsigned *)0x1e00000)
#define INTPND		(*(volatile unsigned *)0x1e00004)
#define INTMOD		(*(volatile unsigned *)0x1e00008)
#define INTMSK		(*(volatile unsigned *)0x1e0000c)
#define I_PSLV		(*(volatile unsigned *)0x1e00010)
#define I_PMST		(*(volatile unsigned *)0x1e00014)
#define I_CSLV		(*(volatile unsigned *)0x1e00018)
#define I_CMST		(*(volatile unsigned *)0x1e0001c)
#define I_ISPR		(*(volatile unsigned *)0x1e00020)
#define I_ISPC		(*(volatile unsigned *)0x1e00024)
#define F_ISPR		(*(volatile unsigned *)0x1e00038)
#define F_ISPC		(*(volatile unsigned *)0x1e0003c)

/* Bits de INTMASK, I_ISPC/F_ISPC y I_ISPR */
#define BIT_ADC		(0x1)
#define BIT_RTC		(0x1<<1)
#define BIT_UTXD1	(0x1<<2)
#define BIT_UTXD0	(0x1<<3)
#define BIT_SIO		(0x1<<4)
#define BIT_IIC		(0x1<<5)
#define BIT_URXD1	(0x1<<6)
#define BIT_URXD0	(0x1<<7)
#define BIT_TIMER5	(0x1<<8)
#define BIT_TIMER4	(0x1<<9)
#define BIT_TIMER3	(0x1<<10)
#define BIT_TIMER2	(0x1<<11)
#define BIT_TIMER1	(0x1<<12)
#define BIT_TIMER0	(0x1<<13)
#define BIT_UERR01	(0x1<<14)
#define BIT_WDT		(0x1<<15)
#define BIT_BDMA1	(0x1<<16)
#define BIT_BDMA0	(0x1<<17)
#define BIT_ZDMA1	(0x1<<18)
#define BIT_ZDMA0	(0x1<<19)
#define BIT_TICK	(0x1<<20)
#define BIT_EINT4567	(0x1<<21)
#define BIT_EINT3	(0x1<<22)
#define BIT_EINT2	(0x1<<23)
#define BIT_EINT1	(0x1<<24)
#define BIT_EINT0	(0x1<<25)
#define BIT_GLOBAL	(0x1<<26)

/* Controlador de LCD */
#define LCDCON1		(*(volatile unsigned *)0x1f00000)
#define LCDCON2		(*(volatile unsigned *)0x1f00004)
#define LCDCON3		(*(volatile unsigned *)0x1f00040)
#define LCDSADDR1	(*(volatile unsigned *)0x1f00008)
#define LCDSADDR2	(*(volatile unsigned *)0x1f0000c)
#define LCDSADDR3	(*(volatile unsigned *)0x1f00010)
#define REDLUT		(*(volatile unsigned *)0x1f00014)
#define GREENLUT	(*(volatile unsigned *)0x1f00018)
#define BLUELUT		(*(volatile unsigned *)0x1f0001c)
#define DP1_2		(*(volatile unsigned *)0x1f00020)
#define DP4_7		(*(volatile unsigned *)0x1f00024)
#define DP3_5		(*(volatile unsigned *)0x1f00028)
#define DP2_3		(*(volatile unsigned *)0x1f0002c)
#define DP5_7		(*(volatile unsigned *)0x1f00030)
#define DP3_4		(*(volatile unsigned *)0x1f00034)
#define DP4_5		(*(volatile unsigned *)0x1f00038)
#define DP6_7		(*(volatile unsigned *)0x1f0003c)
#define DITHMODE	(*(volatile unsigned *)0x1f00044)

/* Conversor analógico digital */
#define ADCCON		(*(volatile unsigned *)0x1d40000)
#define ADCPSR		(*(volatile unsigned *)0x1d40004)
#define ADCDAT		(*(volatile unsigned *)0x1d40008)

/* Reloj de tiempo real */
#define RTCCON		(*(volatile unsigned *)0x1d70040)
#define RTCALM		(*(volatile unsigned *)0x1d70050)
#define ALMSEC		(*(volatile unsigned *)0x1d70054)
#define ALMMIN		(*(volatile unsigned *)0x1d70058)
#define ALMHOUR		(*(volatile unsigned *)0x1d7005c)
#define ALMDAY		(*(volatile unsigned *)0x1d70060)
#define ALMMON		(*(volatile unsigned *)0x1d70064)
#define ALMYEAR		(*(volatile unsigned *)0x1d70068)
#define RTCRST		(*(volatile unsigned *)0x1d7006c)
#define BCDSEC		(*(volatile unsigned *)0x1d70070)
#define BCDMIN		(*(volatile unsigned *)0x1d70074)
#define BCDHOUR		(*(volatile unsigned *)0x1d70078)
#define BCDDAY		(*(volatile unsigned *)0x1d7007c)
#define BCDDATE		(*(volatile unsigned *)0x1d70080)
#define BCDMON		(*(volatile unsigned *)0x1d70084)
#define BCDYEAR		(*(volatile unsigned *)0x1d70088)
#define TICNT		(*(volatile unsigned *)0x1d7008c)

/* Watchdog timer */
#define WTCON		(*(volatile unsigned *)0x1d30000)
#define WTDAT		(*(volatile unsigned *)0x1d30004)
#define WTCNT		(*(volatile unsigned *)0x1d30008)

/* Controlador de IIC */
#define IICCON     (*(volatile unsigned *)0x1d60000)
#define IICSTAT    (*(volatile unsigned *)0x1d60004)
#define IICADD     (*(volatile unsigned *)0x1d60008)
#define IICDS      (*(volatile unsigned *)0x1d6000c)

/* Controlador de IIS */
#define IISCON		(*(volatile unsigned *)0x1d18000)
#define IISMOD		(*(volatile unsigned *)0x1d18004)
#define IISPSR		(*(volatile unsigned *)0x1d18008)
#define IISFCON		(*(volatile unsigned *)0x1d1800c)

/* Controlador de SIO */
#define SIOCON		(*(volatile unsigned *)0x1d14000)
#define SIODAT		(*(volatile unsigned *)0x1d14004)
#define SBRDR		(*(volatile unsigned *)0x1d14008)
#define IVTCNT		(*(volatile unsigned *)0x1d1400c)
#define DCNTZ		(*(volatile unsigned *)0x1d14010)

#endif 

