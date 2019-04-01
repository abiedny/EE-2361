#ifndef BIEDN001_LAB5_LCDLIB_V001_H
#define	BIEDN001_LAB5_LCDLIB_V001_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

const static char CONTRAST = 0b100000;
const static enum ControlBits {
    RSONE = 0b01000000,
    RSZERO = 0b00000000,
    ALLONE = 0b11000000
};
const static enum Direction {
    LEFT = 0b00011000,
    RIGHT = 0b00011100
};

void delay(unsigned int);
void lcd_printChar(char);
void lcd_setCursor(char, char);
void lcd_cmd(char, enum ControlBits);
void lcd_init(void);
void lcd_printStr(const char *s);
void lcd_cntrl(enum ControlBits, char);
void lcd_shiftScreen(enum Direction);

#ifdef	__cplusplus
}
#endif

#endif	/* BIEDN001_LAB5_LCDLIB_V001_H */

