#include "xc.h"
#include "Keypad.h"

int tryCols(int rowInd) {
    //test every column for a hit
    //left to right
    unsigned int mask = 0x0008;
    int i;
    
    for (i = 0; i < 4; i++) {
        if ((PORTA & mask) > 0) {
            return i;
        }
        mask = (mask >> 1);
    }
    return -1;
}

int readKey(void) {
    unsigned int mask = 0x8000;
    int i;
    int result;
    int lastState = -1;
    
    delay(1);
    
    //bottom to top
    for(i = 0; i < 4; i++) {
        LATB |= mask;
        result = tryCols(i);
        
        if (result != lastState) {
            //if there's a hit, wait 40ms and read again
            delay(40);
            result = tryCols(i);
            if (result >= 0) {
                LATB &= 0x0FFF;
                return result;
            }
        }
        
        lastState = result;
        LATB &= 0x0FFF;
        mask = (mask >> 1);
    }
    return -1;
}

void initKeyPad(void) {
    TRISA |= 0x000F; //ra3-ra0 input
    TRISB &= 0x0FFF; //rb15-rb12 output
    CNPU1 |= 0xC; //cn2-cn3
    CNPU2 |= 0xC000; //cn29-cn30
}
