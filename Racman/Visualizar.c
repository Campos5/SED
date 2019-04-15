#include "Visualizar.h"

int mapa[(240/16)][(320/16)] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
	{ 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 2, 0 },
	{ 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0 },
	{ 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0 },
	{ 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0 },
	{ 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 4, 4, 4, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 0, 1, 1, 0, 4, 4, 4, 0, 1, 1, 0, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 3, 1, 1, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 2, 0 },
	{ 0, 2, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0 }
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


uint8 racman[2][3][16*16] = {
	{
		{
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b1101,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b1110,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b1110,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0111,0b1101,0b0111,0b1110,0b1110,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0111,0b1110,0b1101,0b1110,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0111,0b1101,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0111,0b0011,0b1011,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0111,0b1011,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0111,0b0111,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b0101,0b1101,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,0b1110,0b1101,0b0111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0111,0b1111,0b0111,0b0111,0b0111,0b0000,0b0000,0b0000
		},
		{
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b1110,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,
				0b1110,0b1110,0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,0b1110,0b1110,
				0b1110,0b1110,0b1110,0b1110,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b1101,0b1110,0b1110,0b1110,0b1110,
				0b0000,0b1110,0b1110,0b1111,0b0011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b0011,0b1111,0b1110,0b1110,0b0000,
				0b0000,0b0000,0b1111,0b1111,0b0011,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0011,0b1111,0b1111,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b0100,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0100,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b1011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b1011,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1011,0b1011,0b1011,0b1011,0b1011,0b1011,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b0011,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1101,0b0011,0b1011,0b0100,0b0011,0b1101,0b1101,0b0011,0b1101,0b0011,0b0011,0b1101,0b0000,0b0000,
				0b0000,0b1101,0b0011,0b1011,0b1101,0b1011,0b0011,0b0011,0b0011,0b1011,0b1101,0b0011,0b0100,0b1101,0b0000,0b0000,
				0b0000,0b1101,0b0100,0b0011,0b1101,0b1011,0b1011,0b1011,0b1011,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1100,0b1100,0b1101,0b1101,0b1111,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b1110,0b1110,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b1111,0b1111,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000
		},
		{
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b1110,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b1110,
				0b1110,0b1110,0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,0b1110,0b1110,
				0b1110,0b1110,0b1110,0b1110,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b1101,0b1110,0b1110,0b1110,0b1110,
				0b0000,0b1110,0b1110,0b1111,0b0011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b0011,0b1111,0b1110,0b1110,0b0000,
				0b0000,0b0000,0b1111,0b1111,0b0011,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0011,0b1111,0b1111,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b0100,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0100,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b1011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b1011,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1011,0b1011,0b1011,0b1011,0b1011,0b1011,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0011,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1101,0b0011,0b0011,0b1101,0b0011,0b1101,0b1101,0b0011,0b0100,0b1011,0b0011,0b1101,0b0000,0b0000,
				0b0000,0b0000,0b1101,0b0100,0b0011,0b1101,0b0100,0b0100,0b0100,0b0100,0b1011,0b1101,0b1011,0b0011,0b1101,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1011,0b1011,0b1011,0b1011,0b1101,0b0100,0b0100,0b1101,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1111,0b1101,0b1101,0b1100,0b1100,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1110,0b1110,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b1111,0b1111,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000
		}
	},{
		{
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1111,0b0011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b0011,0b1111,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1111,0b1111,0b0011,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0011,0b1111,0b1111,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b0100,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0100,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b1011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b1011,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1011,0b1011,0b1011,0b1011,0b1011,0b1011,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b0011,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0011,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1101,0b0011,0b1011,0b0100,0b0011,0b1101,0b1101,0b0011,0b0100,0b1011,0b0011,0b1101,0b0000,0b0000,
				0b0000,0b1101,0b0011,0b1011,0b1101,0b1011,0b0100,0b0100,0b0100,0b0100,0b1011,0b1101,0b1011,0b0011,0b1101,0b0000,
				0b0000,0b1101,0b0100,0b0100,0b1101,0b1011,0b1011,0b1011,0b1011,0b1011,0b1011,0b1101,0b0100,0b0100,0b1101,0b0000,
				0b0000,0b0000,0b1101,0b1101,0b1101,0b1100,0b1100,0b1100,0b1100,0b1100,0b1100,0b1101,0b1101,0b1101,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b0101,0b1101,0b1101,0b0101,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1110,0b1110,0b1101,0b1101,0b1110,0b1110,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1111,0b1111,0b1101,0b1101,0b1111,0b1111,0b1101,0b0000,0b0000,0b0000,0b0000
		},
		{
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1111,0b0011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b0011,0b1111,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1111,0b1111,0b0011,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0011,0b1111,0b1111,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b0100,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0100,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b1011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b1011,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1011,0b1011,0b1011,0b1011,0b1011,0b1011,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b0011,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1101,0b0011,0b1011,0b0100,0b0011,0b1101,0b1101,0b0011,0b1101,0b0011,0b0011,0b1101,0b0000,0b0000,
				0b0000,0b1101,0b0011,0b1011,0b1101,0b1011,0b0011,0b0011,0b0011,0b1011,0b1101,0b0011,0b0100,0b1101,0b0000,0b0000,
				0b0000,0b1101,0b0100,0b0011,0b1101,0b1011,0b1011,0b1011,0b1011,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1100,0b1100,0b1101,0b1101,0b1111,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b1110,0b1110,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b1111,0b1111,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000
		},
		{
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b0011,0b0011,0b0011,0b0011,0b0011,0b0011,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1111,0b0011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b0011,0b1111,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1111,0b1111,0b0011,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0011,0b1111,0b1111,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b0100,0b0001,0b1110,0b0001,0b0001,0b1110,0b0001,0b0100,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b1011,0b0010,0b0001,0b0010,0b0010,0b0001,0b0010,0b1011,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1011,0b1011,0b1011,0b1011,0b1011,0b1011,0b1101,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b1101,0b0011,0b1101,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b1101,0b0011,0b0011,0b1101,0b0011,0b1101,0b1101,0b0011,0b0100,0b1011,0b0011,0b1101,0b0000,0b0000,
				0b0000,0b0000,0b1101,0b0100,0b0011,0b1101,0b0100,0b0100,0b0100,0b0100,0b1011,0b1101,0b1011,0b0011,0b1101,0b0000,
				0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1011,0b1011,0b1011,0b1011,0b1101,0b0100,0b0100,0b1101,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1111,0b1101,0b1101,0b1100,0b1100,0b1101,0b1101,0b1101,0b1101,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b1101,0b1101,0b1101,0b1101,0b1110,0b1110,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000,
				0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b0000,0b1101,0b1111,0b1111,0b1101,0b0000,0b0000,0b0000,0b0000,0b0000

		}
	}
};


void init_visualizacion(void){
	lcd_init();
	lcd_clear();
}


void mensaje_bienvenida(void){
	lcd_puts_x2( 0, 20, BLACK, "     RAC-MAN     " );
	lcd_puts( 0, 60, BLACK, "   Pulsa Boton Izquierdo para empezar   " );
}


void dibujar_mapa(void){
	int i, j;
	for (i = 0; i<320/16; i++)
		for (j = 0; j<240/16; j++){

			if(mapa[j][i] == 0)
				poner_muro(i, j);

			if(mapa[j][i] == 3)
				dibujar_racman(i, j, 0);
		}
}


void dibujar_racman(int posX, int posY, int aux){
	posX *=16;
	posY *=16;
	pintar_pixels(posX, posY, racman[0][aux]);
}


void poner_muro(int x, int y){
	x *=16;
	y *=16;
	pintar_pixels(x, y, muro);
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
	lcd_clear16x16(posX, posY);
}
