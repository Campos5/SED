
#ifndef __LCD_H__
#define __LCD_H__

#include "common_types.h"
#include "44b.h"

#define LCD_WIDTH   (320)
#define LCD_HEIGHT  (240)

#define LCD_BUFFER_SIZE    (LCD_WIDTH*LCD_HEIGHT/2) // en bytes con 2 pixels/byte

#define BLACK       (0xf)
#define WHITE       (0x0)
#define LIGHTGRAY   (0x5)
#define DARKGRAY    (0xa)
    
#define LCD_OFF     (1)
#define LCD_ON      (0)

void lcd_init( void );
void lcd_clear( void );
void lcd_putpixel( uint16 x, uint16 y, uint8 color);
void lcd_clear16x16(uint16 x, uint16 y);
void lcd_drawSprite16x16(uint16 x, uint16 y, uint8* sprite);
uint8 lcd_getpixel( uint16 x, uint16 y );
void lcd_draw_hline( uint16 xleft, uint16 xright, uint16 y, uint8 color, uint16 width );
void lcd_draw_vline( uint16 yup, uint16 ydown, uint16 x, uint8 color, uint16 width );
void lcd_draw_box( uint16 xleft, uint16 yup, uint16 xright, uint16 ydown, uint8 color, uint16 width );
void lcd_putchar( uint16 x, uint16 y, uint8 color, char ch );
void lcd_puts( uint16 x, uint16 y, uint8 color, char *s );
uint32 lcd_printf( uint16 x, uint16 y, uint8 color, const char *fmt, ... );
void lcd_putchar_x2( uint16 x, uint16 y, uint8 color, char ch );
void lcd_puts_x2( uint16 x, uint16 y, uint8 color, char *s );
uint32 lcd_printf_x2( uint16 x, uint16 y, uint8 color, const char *fmt, ... );

#endif 
