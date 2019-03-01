#ifndef DISPLAY_H
#define	DISPLAY_H

#include <xc.h>
#include "Utility.h"

#ifdef	__cplusplus
extern "C" {
#endif

    const static unsigned int Characters[] = {
    0b0000000000001100,
    0b0000001001111100,
    0b0000000010010100,
    0b0000000000110100,
    0b0000001001100100,
    0b0000000100100100,
    0b0000000100000100,
    0b0000000001111100,
    0b0000000000000100,
    0b0000000000100100,
    0b0000000001000100, //A
    0b0000001100000100, //b
    0b0000000110001100, //C
    0b0000001000010100, //d
    0b0000000110000100, //E
    0b0000000111000100, //F
    0b0000001111111000  //.
    };

    const static enum Digit {
        RIGHT = 0b0000100000000000,
        LEFT = 0b0000010000000000
    };
    
    void showChar7seg(char toShow, enum Digit digit);
    void init7seg(void);
    void test(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

