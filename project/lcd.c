#include "lcd.h"
#include "font8x16.h"
#include <stdarg.h>
#include <stdio.h>

extern const uint8 font[256*16];

static uint8 status_lcd;
static uint32 buffer[320*240/8] __attribute__ ((section (".lcdbuffer"))); // Como hacer que referencia la zona de memoria reservada en el linker_script.ld??
/*
** Configura el controlador de lcd según los siguientes parámetros
**   Resolución: 320x240
**   Modo de barrido: 4 bit single scan
**   Modo del lcd: 16 niveles de gris
**   Paletas de color: no
**   Frecuencia de refresco: 120 Hz
**   Self-refresh: desactivado
**   Polaridad de señales de sincronismo: normal
**   Conmutación de VM: en cada frame
**   Anchura del blanking horizontal: mínima
**   Retardo y anchura de pulso de sincronismo horizontal: mínimos
**   Valores de dithering: por defecto
** Inicializa el estado del lcd y lo apaga
*/
void lcd_init( void ){
	LCDCON1 	= 0x0000D021;//
	LCDCON2 	= 0x00013CEF;//
	LCDSADDR1 	= 0x16180000;
	LCDSADDR2 	= 0x00184B00;
	LCDSADDR3 	= 0x00050;
	REDLUT 		= 0x0;
	BLUELUT 	= 0x0;
	GREENLUT 	= 0x0;
	DITHMODE 	= 0x12210;
	DP1_2 		= 0xA5A5;
	DP4_7 		= 0xBA5DA65;
	DP3_5 		= 0xA5A5F;
	DP2_3 		= 0xD6B;
	DP5_7 		= 0xEB7B5ED;
	DP3_4 		= 0x77DBE;//
	DP4_5 		= 0x7EBDF;
	DP6_7 		= 0x7FDFBFE;

	status_lcd = LCD_OFF;
}

/*
** Enciende el lcd
*/
void lcd_on( void ){
	LCDCON1 |= 0x00000001; // ????
	status_lcd = LCD_ON;
}

/*
** Apaga el lcd
*/
void lcd_off( void ){
	LCDCON1 &= ~(0x00000001); // ????
	status_lcd = LCD_OFF;
}

/*
** Devuelve el estado (LCD_ON/LCD_OFF) del lcd
*/
uint8 lcd_status( void ){
	return status_lcd;
}

/*
** Borra el lcd
*/
void lcd_clear( void ){
	int i;
	int j;
	for(i = 0; i < 320; i++)
		for(j = 0; j < 240; j++)
			lcd_putpixel(i, j, WHITE);
}

/*
** Borra medio el lcd
*/
void lcd_half_clear( void ){
	int i;
	int j;
	for(i = 0; i < 160; i++)
		for(j = 0; j < 240; j++)
			lcd_putpixel(i, j, WHITE);
}

/*
** Borra la parte izquierda del lcd
*/
void lcd_left_clear( void ){
	int i;
	int j;
	for(i = 0; i < 150; i++)
			for(j = 40; j < 240; j++)
				lcd_putpixel(i, j, WHITE);
}

/*
** Borra la parte derecha del lcd
*/
void lcd_right_clear( void ){
	int i;
	int j;
	for(i = 154; i < 320; i++)
		for(j = 40; j < 240; j++)
			lcd_putpixel(i, j, WHITE);
}

/*
** Borra parte el lcd
*/
void lcd_mini_clear( void ){
	int i;
	int j;
	for(i = 0; i < 80; i++)
		for(j = 0; j < 240; j++)
			lcd_putpixel(i, j, WHITE);
}


/*
** Borra parte de abajo el lcd
*/
void lcd_mini_down_clear( void ){
	int i;
	int j;
	for(i = 220; i < 320; i++)
		for(j = 0; j < 240; j++)
			lcd_putpixel(i, j, WHITE);
}


/*
** Pone el pixel (x,y) en el color indicado
*/
void lcd_putpixel( uint16 x, uint16 y, uint8 color){
	uint32 word;
	word = buffer[x/8 + y*(320/8)];
	word &= ~(0xf0000000 >> (x%8)*4);
	word |= (uint32) color << (7 - x%8)*4;
	buffer[x/8 + y*(320/8)] = word;
}

/*
** Devuelve el color al que está el pixel (x,y)
*/
uint8 lcd_getpixel( uint16 x, uint16 y ){
	uint8 color;
	uint32 word;
	word = buffer[x/8 + y*(320/8)];
	word &= (0xf0000000 >> (x%8)*4);
	color = (uint32) word >> (7 - x%8)*4; // ver cuanto calcular

	return color;
}

/*
** Dibuja una línea horizontal desde el pixel (xleft,y) hasta el pixel (xright,y) del color y grosor indicados
*/
void lcd_draw_hline( uint16 xleft, uint16 xright, uint16 y, uint8 color, uint16 width ){
	int i;
	int tam;
	for(tam = 0; tam < width; tam++)
		for(i = xleft; i < xright; i++)
				lcd_putpixel(i, y + tam, color);
}

/*
** Dibuja una línea vertical desde el pixel (x,yup) hasta el pixel (x,ydown) del color y grosor indicados
*/
void lcd_draw_vline( uint16 yup, uint16 ydown, uint16 x, uint8 color, uint16 width ){
	int j;
	int tam;
	for(tam = 0; tam < width; tam++)
		for(j = ydown; j < yup; j++)
				lcd_putpixel(x + tam, j, color);
}

/*
** Dibuja un rectángulo cuya esquina superior izquierda está en el pixel (xleft,yup) y cuya esquina inferior está en el píxel (xright, ydown) del color y grosor indicados
*/
void lcd_draw_box( uint16 xleft, uint16 yup, uint16 xright, uint16 ydown, uint8 color, uint16 width ){
	lcd_draw_hline(xleft+width, xright+width, ydown, color, width);
	lcd_draw_vline(ydown, yup, xright, color, width);
	lcd_draw_hline(xleft, xright, yup, color, width);
	lcd_draw_vline(ydown+width, yup+width, xleft, color, width);
}

/*
** Usando una fuente 8x16, escribe un caracter a partir del pixel (x,y) en el color indicado
*/
void lcd_putchar( uint16 x, uint16 y, uint8 color, char ch ){
	uint8 row, line;
	uint8 *bitmap;
	bitmap = font + ch*16;
	for(line = 0; line < 16; line++){
		for(row = 0; row < 8; row++){
			if(bitmap[line] & (0x80>>row))
				lcd_putpixel(x+row, y+line, color);
			else
				lcd_putpixel(x+row, y+line, WHITE);
		}
	}
}

/*
** Usando una fuente 8x16, escribe una cadena a partir del pixel (x,y) en el color indicado
*/
void lcd_puts( uint16 x, uint16 y, uint8 color, char *s ){
	while(*s) {
		lcd_putchar(x, y, color, *s);
		s++;
		x = x + 8;
	}
}

/*
** Usando una fuente 8x16, escribe texto formateado a partir del pixel (x,y) en el color indicado
*/
uint32 lcd_printf( uint16 x, uint16 y, uint8 color, const char *fmt, ... ){
	va_list arg_p;

	char cadena[256];
	int32 charRetorno;

	va_start(arg_p, fmt);

	charRetorno = vsprintf(cadena, fmt, arg_p);

	va_end(arg_p);

	lcd_puts(x, y, color, cadena);

	return charRetorno;
}

/*
** Usando una fuente 8x16, escribe un caracter a doble tamaño a partir del pixel (x,y) en el color indicado
*/
void lcd_putchar_x2( uint16 x, uint16 y, uint8 color, char ch ){
	uint8 row, line;
	uint8 *bitmap;
	bitmap = font + ch*16;
	for(line = 0; line < 16; line++){
		for(row = 0; row < 8; row++){
			if(bitmap[line] & (0x80>>row)) {
				lcd_putpixel(2*(x+row)-18, 2*(y+line) - y, color);
				lcd_putpixel(2*(x+row)-1-18, 2*(y+line) - y, color);
				lcd_putpixel(2*(x+row)-18, 2*(y+line)+1 - y, color);
				lcd_putpixel(2*(x+row)-1-18, 2*(y+line)+1 - y, color);

			} else {
				lcd_putpixel(2*(x+row)-18, 2*(y+line) - y, WHITE);
				lcd_putpixel(2*(x+row)-1-18, 2*(y+line) - y, WHITE);
				lcd_putpixel(2*(x+row)-18, 2*(y+line)+1 - y, WHITE);
				lcd_putpixel(2*(x+row)-1-18, 2*(y+line)+1 - y, WHITE);
			}
		}
	}
}

/*
** Usando una fuente 8x16, escribe una cadena a doble tamaño a partir del pixel (x,y) en el color indicado
*/
void lcd_puts_x2( uint16 x, uint16 y, uint8 color, char *s ){
	while(*s) {
		lcd_putchar_x2(x, y, color, *s);
		s++;
		x = x + 8;
	}
}

/*
** Usando una fuente 8x16, escribe texto formateado a doble tamaño a partir del pixel (x,y) en el color indicado
*/
uint32 lcd_printf_x2( uint16 x, uint16 y, uint8 color, const char *fmt, ... ){
	va_list arg_p;

	char cadena[256];
	int32 charRetorno;

	va_start(arg_p, fmt);

	charRetorno = vsprintf(cadena, fmt, arg_p);

	va_end(arg_p);

	lcd_puts_x2(x, y, color, cadena);

	return charRetorno;
}
