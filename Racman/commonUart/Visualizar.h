#ifndef VISUALIZAR_H_
#define VISUALIZAR_H_

#include "lcd.h"
#include <stdlib.h>

void init_visualizacion(void);
void mensaje_bienvenida(void);
void dibujar_mapa(void);
void dibujar_racman(int posX, int posY, int jugador, int dir);
void poner_muro(int x, int y);
void pintar_pixels(int posX, int posY,  uint8* sprite);
void limpiar_pixels(int posX, int posY);


#endif /* VISUALIZAR_H_ */
