#include "Visualizar.h"
#include "44blib.h"
#include "44b.h"
#include "def.h"
#include <stdio.h>
#include <stdlib.h>



extern void DelayMs(int ms_time);

extern int pos_racman_propio_x;
extern int pos_racman_propio_y;

extern int pos_racman_enemigo_x;
extern int pos_racman_enemigo_y;

int direccion_racman_propio; //0 - arriba; 1 - izquierda; 2 - derecha; 3 - abajo; -1 - no se mueve
int direccion_defecto_propio;

extern int jugador;
extern int tipo_juego;

extern int puntos_jugador_1;
extern int puntos_jugador_2;

int mapa[(240/16)][(320/16)] = {
	{ -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 },
	{ -1,	1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,  -1 },
	{ -1, 	2,  -1,  -1,   1,  -1,  -1,  -1,   1,  -1,  -1,  -1,   1,  -1,  -1,  -1,   1,  -1,   2,  -1 },
	{ -1,	1,  -1,  -1,   1,  -1,   1,   1,   1,   1,  -1,   1,   1,   1,   1,  -1,   1,  -1,   1,  -1 },
	{ -1,	1,   1,   1,   1,  -1,   1,  -1,  -1,   1,  -1,   1,  -1,  -1,   1,  -1,   1,   1,   1,  -1 },
	{ -1,	1,  -1,  -1,   1,  -1,   1,  -1,  -1,   1,   1,   1,  -1,  -1,   1,  -1,   1,  -1,   1,  -1 },
	{ -1,	1,  -1,  -1,   1,   1,   1,  -1,  -1,  -1,   1,  -1,  -1,  -1,   1,   1,   1,  -1,   1,  -1 },
	{ -1,	1,   1,   1,   1,  -1,   1,   1,   1,   1,   1,   1,   1,   1,   1,  -1,   1,   1,   1,  -1 },
	{ -1,  -1,  -1,  -1,   1,  -1,   1,  -1,  -1,  -1,   0,  -1,  -1,  -1,   1,  -1,   1,  -1,  -1,  -1 },
	{ -1,  -1,  -1,  -1,   1,   1,   1,  -1,  -1,   9,   0,   9,  -1,  -1,   1,   1,   1,  -1,  -1,  -1 },
	{  1,	1,   1,   1,   1,  -1,   1,   1,  -1,   9,   0,   9,  -1,   1,   1,  -1,   1,   1,   1,   1 },
	{ -1,  -1,  -1,  -1,   1,  -1,  -1,   1,  -1,  -1,  -1,  -1,  -1,   1,  -1,  -1,   1,  -1,  -1,  -1 },
	{ -1,  -1,  -1,  -1,   1,  -1,  -1,   1,   6,   1,   1,   1,   3,   1,  -1,  -1,   1,  -1,  -1,  -1 },
	{ -1,	1,   1,   1,   1,   1,   1,   1,  -1,   1,  -1,   1,  -1,   1,   1,   1,   1,  -1,   2,  -1 },
	{ -1,	2,  -1,  -1,   1,  -1,  -1,   1,   1,   1,   1,   1,   1,   1,  -1,  -1,   1,   1,   1,  -1 }
};

uint8 negro[16*16] = {
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
		0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,
};


uint8 muro[16*16] ={
		0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0100,0b0100,0b0100,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0100,0b0100,0b0100,0b0100,0b0000,0b0000,0b1001,0b0100,0b0100,0b0100,0b0100,0b0100,0b0000,0b0000,
		0b0000,0b0000,0b0100,0b0100,0b0100,0b0100,0b1001,0b1001,0b1001,0b0100,0b0100,0b0100,0b0100,0b0100,0b0000,0b0000,
		0b0000,0b1001,0b0111,0b0100,0b0100,0b1001,0b1001,0b1001,0b1001,0b0100,0b0100,0b0100,0b0100,0b0100,0b0100,0b0000,
		0b0000,0b1001,0b0111,0b0111,0b1001,0b1001,0b1001,0b1001,0b1001,0b0100,0b0100,0b0100,0b0100,0b0100,0b0100,0b0000,
		0b0000,0b1001,0b1001,0b0111,0b0100,0b0100,0b0111,0b0111,0b0111,0b0100,0b0100,0b0100,0b0100,0b0100,0b0100,0b0000,
		0b0000,0b1001,0b1001,0b0111,0b0100,0b0100,0b0111,0b0111,0b0111,0b0100,0b0100,0b0100,0b0100,0b0100,0b0100,0b0000,
		0b0000,0b1001,0b1001,0b0111,0b0100,0b0100,0b0111,0b0111,0b0111,0b0100,0b0100,0b0100,0b0100,0b0100,0b0100,0b0000,
		0b0000,0b1001,0b1001,0b0100,0b0100,0b0100,0b0111,0b0111,0b0111,0b0111,0b0100,0b0100,0b0100,0b0100,0b1001,0b0000,
		0b0000,0b1001,0b1001,0b0100,0b0100,0b0100,0b0111,0b0111,0b0111,0b0111,0b1001,0b1001,0b1001,0b1001,0b1001,0b0000,
		0b0000,0b0000,0b1001,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b1001,0b1001,0b1001,0b1001,0b1001,0b1001,0b0000,
		0b0000,0b0000,0b1001,0b1001,0b0111,0b0111,0b1001,0b1001,0b1001,0b1001,0b1001,0b1001,0b1001,0b1001,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b1111,0b0111,0b0111,0b1001,0b1001,0b1001,0b1001,0b1001,0b1001,0b1111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0000,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b1111,0b0000,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000
};

//TODO pintar también las otras direcciones
uint8 racman[2][4][16*16] = {
	{
		{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b1101,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b1110,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1101,0b0111,0b1110,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1110,0b1101,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0011,0b1011,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1011,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b0101,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,0b1110,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b1111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000
		},
		{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b1101,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b1110,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1101,0b0111,0b1110,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1110,0b1101,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0011,0b1011,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1011,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b0101,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,0b1110,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b1111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000
		},
		{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b1101,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b1110,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1101,0b0111,0b1110,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1110,0b1101,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0011,0b1011,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1011,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b0101,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,0b1110,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b1111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000
		},
		{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b1101,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b1110,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1101,0b0111,0b1110,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1110,0b1101,0b1110,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0011,0b1011,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b1011,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b0101,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,0b1110,0b1101,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b1111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000
		}
	},{
		{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b1101,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b1110,0b0011,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1101,0b0011,0b1110,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1110,0b1101,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b1011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b0101,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,0b1110,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b1111,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000
		},
		{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b1101,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b1110,0b0011,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1101,0b0011,0b1110,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1110,0b1101,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b1011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b0101,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,0b1110,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b1111,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000
		},
		{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b1101,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b1110,0b0011,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1101,0b0011,0b1110,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1110,0b1101,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b1011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b0101,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,0b1110,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b1111,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000

		},
		{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b1101,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b1110,0b0011,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1101,0b0011,0b1110,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1110,0b1101,0b1110,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b1011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b1011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b0101,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,0b1110,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0011,0b1111,0b0011,0b0011,0b0011,0b0011,0b0011,0b0000
		}
	}
};

uint8 coco[16*16] = {
		0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0111,0b0000,0b0000,0b0111,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
		0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000
};

uint8 punto[2][16*16] ={
		{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000
		},{
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
			0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000

		}
};

void init_visualizacion(void){
	lcd_init();
	lcd_clear();

	lcd_puts_x2( 0, 20, BLACK, "     RAC-MAN     " );
	lcd_puts( 0, 60, BLACK, "   Pulsa Boton Izquierdo para 1 jugador   " );
	lcd_puts( 0, 100, BLACK, "   Pulsa Boton Derecho para 2 jugadores  " );

}


void cargar_pantalla_carga(void){

	lcd_clear();
	lcd_puts_x2( 0, 20, BLACK, " Listo para empezar " );
	lcd_puts( 0, 60, BLACK, "Pulsa Boton Derecho empezar");
}


void pantalla_fin_juego_solitario(int gana, int puntos){
	lcd_clear();
	if(gana){
		lcd_puts_x2( 0, 20, BLACK, "      ENHORABUENA       " );

	}else{
		lcd_puts_x2( 0, 20, BLACK, "UNLUKY,OTRA VEZ SERA");

	}

	char strPuntos[80];
	sprintf(strPuntos, "Has obtenido %d puntos", puntos);
	lcd_puts( 0, 60, BLACK, strPuntos);
}

void pantalla_fin_juego_doble(int puntos1, int puntos2){

	lcd_clear();
	if(puntos1 > puntos2){
		lcd_puts_x2( 0, 20, BLACK, "EL JUGADOR 1 GANA!" );

	}else if (puntos1 < puntos2){
		lcd_puts_x2( 0, 20, BLACK, "EL JUGADOR 2 GANA!" );
	}else{
		lcd_puts_x2( 0, 20, BLACK, "HAY EMPATE, INCREIBLE" );
	}
	char strPuntos1[80];
	char strPuntos2[80];
	sprintf(strPuntos1, "Jugador 1: %d puntos", puntos1);
	sprintf(strPuntos2, "Jugador 2: %d puntos", puntos2);

	lcd_puts( 0, 60, BLACK, strPuntos1);
	lcd_puts( 0, 80, BLACK, strPuntos2);

}


void dibujar_mapa(void){
	lcd_clear();
	int i, j;

	for (i = 0; i<320/16; i++){
		for (j = 0; j<240/16; j++){

			if(mapa[j][i] == -1){
				poner_muro(i, j);
			}

			if(mapa[j][i] == 1){
				poner_punto(i, j, 0);
			}
			if(mapa[j][i] == 2){
				poner_punto(i, j, 1);
			}
			if(mapa[j][i] == 9){
				dibujar_coco(i, j, 1);
			}

			if(mapa[j][i] == 3*jugador){
				dibujar_racman(i, j, 0, 0);
				pos_racman_propio_x = i;
				pos_racman_propio_y = j;
				direccion_racman_propio = 1; //direccion inicial para la izquierda
				direccion_defecto_propio = 1;
				puntos_jugador_1 = 0;
			}
			int otro_jugador;
			if(jugador == 1)
				otro_jugador = 2;
			else
				otro_jugador = 1;
			if(mapa[j][i] == 3*otro_jugador){
				if(tipo_juego == 0){
					mapa[j][i] = 1;
					poner_punto(i, j, 0);
				}else{
					dibujar_racman(i, j, 1, 0);
					pos_racman_enemigo_x = i;
					pos_racman_enemigo_y = j;
					//direccion_racman_propio = 1; //direccion inicial para la izquierda
					//direccion_defecto_propio = 1;
					puntos_jugador_2 = 0;
				}
			}
		}
	}

}


void dibujar_racman(int posX, int posY, int jugador, int dir){
	posX *=16;
	posY *=16;
	pintar_pixels(posX, posY, racman[jugador][dir]);
}


void dibujar_coco(int posX, int posY){
	posX *=16;
	posY *=16;
	pintar_pixels(posX, posY, coco);
}



void poner_muro(int x, int y){
	x *=16;
	y *=16;
	pintar_pixels(x, y, muro);
}

void poner_punto(int x, int y, int z){
	x *=16;
	y *=16;
	pintar_pixels(x, y, punto[z]);
}

void poner_negro(int x, int y){
	x *=16;
	y *=16;
	pintar_pixels(x, y, negro);
}


void pintar_pixels(int posX, int posY,  uint8* sprite){
	int i,j;
	int count = 0;
	int currY;
	uint8 a = sprite[80];
	for (j = 0; j<16; j++){
		currY = posY + j;

		for (i = 0; i<16; i++){

			if(sprite[count] != 0b0000){
				lcd_putpixel(posX+i, currY, sprite[count]);
			}

			count +=1;
		}
	}
}


void limpiar_pixels(int posX, int posY){
	posX *=16;
	posY *=16;
	lcd_clear16x16(posX, posY);
}

void pantalla_en_negro(){
	int i, j;
	for (i = 0; i<320/16; i++){
		for (j = 0; j<240/16; j++){
				poner_negro(i, j);
				DelayMs(10);
		}
	}
}
