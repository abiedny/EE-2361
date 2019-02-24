#include "xc.h"

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

//Which digit to display
const enum Digit {
    RIGHT = 0b0000100000000000,
    LEFT = 0b0000010000000000
};

const unsigned int Characters[] = {
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
};

void showChar7seg(char toShow, enum Digit digit) {
    LATB &= 0xF003;
    
    //convert char from ascii codes to array key
    switch (toShow) {
        case 'b':
        case 'd':
            //lowercase
            LATB |= digit | Characters[toShow - 87];
            break;
        case 'A':
        case 'C':
        case 'E':
        case 'F':
            //uppercase
            LATB |= digit | Characters[toShow - 55];
            break;
        default:
            //number
            LATB |= digit | Characters[toShow - 48];
    }
    
    return;
}

void init7seg(void) {
    //rb9 - rb2 = 0
    TRISB &= 0xF003; //RB 11:2 to output(0)
    LATB |= 0x0FFC; //RB 9:2 to high(off)
}

void delay(unsigned int ms) {
    int i;
    for (i = 0; i < ms; i++) {
        asm("repeat #15993");
        asm("nop");
    }
    return;
}

void test(void) {
    showChar7seg('0', RIGHT);
    delay(250);
    showChar7seg('1', LEFT);
    delay(250);
    showChar7seg('2', RIGHT);
    delay(250);
    showChar7seg('3', LEFT);
    delay(250);
    showChar7seg('4', RIGHT);
    delay(250);
    showChar7seg('5', LEFT);
    delay(250);
    showChar7seg('6', RIGHT);
    delay(250);
    showChar7seg('7', LEFT);
    delay(250);
    showChar7seg('8', RIGHT);
    delay(250);
    showChar7seg('9', LEFT);
    delay(250);
    showChar7seg('A', RIGHT);
    delay(250);
    showChar7seg('b', LEFT);
    delay(250);
    showChar7seg('C', RIGHT);
    delay(250);
    showChar7seg('d', LEFT);
    delay(250);
    showChar7seg('E', RIGHT);
    delay(250);
    showChar7seg('F', LEFT);
    return;
}

void setup(void) {
    CLKDIVbits.RCDIV = 0;   
    AD1PCFG = 0x9fff; //sets all pins to digital I/O
    init7seg();
}

int main(void) {
    setup();
    test();
    
    while(1) {
        
    }
}
