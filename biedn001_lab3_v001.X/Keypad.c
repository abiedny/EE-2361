#include "xc.h"
#include "Keypad.h"

//Remeber 0 is a hit not 1...
int tryCols(int rowInd) {
    //test every column for a hit
    //left to right
    unsigned int mask = 0xFFF7;
    int i;
    
    for (i = 0; i < 4; i++) {
        if ((PORTA | mask) < 0xFFFF) {
            //there's a hit, but is it in the row?
            return i;
        }
        mask = (mask >> 1);
        mask += 0x8000;
    }
    return -1;
}

int readKey(void) {
    unsigned int mask = 0x7FFF;
    int i;
    int result;
    static int lastState = -1;
    
    //bottom to top
    for(i = 0; i < 4; i++) {
        LATB |= 0xF000;
        LATB &= mask;
        result = tryCols(i);
        
        if (result != lastState) {
            result = tryCols(i);
            if (result >= 0) {
                LATB &= 0x0FFF;
                return (result*10) + i;
            }
        }
        
        lastState = result;
        mask = (mask >> 1);
        mask += 0x8000;
        
        /*if (possibleRow != -1) {
            LATB &= 0x0FFF;
            break;
        }*/
    }
    return -1;
}

void initKeyPad(void) {
    TRISA |= 0x000F; //ra3-ra0 input
    TRISB &= 0x0FFF; //rb15-rb12 output
    CNPU1 |= 0xC; //cn2-cn3
    CNPU2 |= 0b0110000000000000; //cn29-cn30
}
