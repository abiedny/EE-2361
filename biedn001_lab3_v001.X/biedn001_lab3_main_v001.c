#include "xc.h"
#include "Display.h"
#include "Keypad.h"

#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup(void) {
    CLKDIVbits.RCDIV = 0;   
    AD1PCFG = 0x9fff; //sets all pins to digital I/O
    init7seg();
    initKeyPad();
    
    T1CON = 0;
    PR1 = 15999;
    TMR1 = 0;
    IFS0bits.T1IF = 0; //alternatively, _T1IF = 0;
    T1CONbits.TON = 1; // alternatively, T1CON = 0x8000;
}

int main(void) {
    setup();
    char Translation[4][4] = {
        {'E', '7', '4', '1'},
        {'0', '8', '5', '2'},
        {'F', '9', '6', '3'},
        {'d', 'C', 'b', 'A'}
    };
    
    char leftChar = '\0';
    char rightChar = '\0';
    int lastKey = -1;
    while(1) {
        int key = readKey();
        if (key >= 0) { //either -1 or coordinates in form xy (packed integer)
            if (key != lastKey) {
            
                //display the key
                rightChar = Translation[(key / 10) % 10][key % 10];
                if (lastKey >= 0) {
                    leftChar = Translation[(lastKey / 10) % 10][lastKey % 10];
                }
                lastKey = key;
                }
        }
        
        if (rightChar != '\0') {
            showChar7seg(rightChar, RIGHT);
            delay(5);
        }
        if (leftChar != '\0') {
            showChar7seg(leftChar, LEFT);
            delay(5);
        }
    }
}
