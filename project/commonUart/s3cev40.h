/*-------------------------------------------------------------------
**
**  Fichero:
**    s3cev40.h  2/2/2013
**
**    (c) J.M. Mendias
**    Programación de Sistemas y Dispositivos
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Creación de nemotécnicos para acceso a distintos elementos
**    de la placa de prototipado Embest S3CEV40
**
**  Notas de diseño:
**    Las direcciones usadas asumen un alineamiento little-endian
**
**-----------------------------------------------------------------*/

#ifndef __S3CEV40_H__
#define __S3CEV40_H__

#include "common_types.h"

#define CPU   ("S3C44B0X")
#define CLKIN (8000000U)    // Frecuencia base del oscilador (Hz)

/* Mapa de memoria */

#define ROM_START_ADDRESS (0x00000000)
#define ROM_END_ADDRESS   (0x001fffff)

#define NON_CACHE_START   (0x02000000)
#define NON_CACHE_END     (0x0bffffff)

#define RAM_START_ADDRESS (0x0c000000)
#define RAM_END_ADDRESS   (0x0c7fffff)

#define SP_START_ADDRESS  (0x10000000)
#define SP_END_ADDRESS    (0x100001ff)

/* Tiempos de rebote en ms */

#define KEYPAD_KEYDOWN_DELAY  (30)
#define KEYPAD_KEYUP_DELAY   (100)
#define PB_KEYDOWN_DELAY      (30)
#define PB_KEYUP_DELAY       (100)

/* Tabla virtual de vectores de excepción */
#define pISR_PB       (*(volatile uint32 *)0xc7fff74) // EINT4567
#define pISR_ETHERNET (*(volatile uint32 *)0xc7fff78) // EINT3
#define pISR_TOUCHPAD (*(volatile uint32 *)0xc7fff7c) // EINT2
#define pISR_KEYPAD   (*(volatile uint32 *)0xc7fff80) // EINT1
#define pISR_USB      (*(volatile uint32 *)0xc7fff84) // EINT0

/* Bits de INTMASK, I_ISPC/F_ISPC y I_ISPR */
#define BIT_PB        (1<<21) // EINT4567
#define BIT_ETHERNET  (1<<22) // EINT3
#define BIT_KEYPAD    (1<<24) // EINT1
#define BIT_USB       (1<<25) // EINT2

/* Bits de EXTINTPND */
#define BIT_RIGHTPB   (1<<3)
#define BIT_LEFTPB    (1<<2)
#define BIT_IDE_INTRQ (1<<1)
#define BIT_IDE_DMACK (1<<0)

#endif 
