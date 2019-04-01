#ifndef BIEDN001_LAB5_LCDLIB_V001_H
#define	BIEDN001_LAB5_LCDLIB_V001_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

const static char CONTRAST = 0b100000;
const static enum ControlBits {
    RSONE = 0b01000000,
    RSZERO = 0b00000000
};

void lcd_printChar(char);
void lcd_setCursor(char, char);
void lcd_cmd(char, enum ControlBits);
void lcd_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BIEDN001_LAB5_LCDLIB_V001_H */

