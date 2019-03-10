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

void delay(unsigned int ms) {
    int i;
    for (i = 0; i < ms; i++) {
        asm("repeat #15993");
        asm("nop");
    }
    return;
}

void setServo(int val) {
    OC1RS = val;
}

void initServo(void) {
    //timer 3 to 20ms delay
    T3CON = 0;
    PR3 = 40000;
    TMR3 = 0;
    IFS0bits.T3IF = 0;
    T3CONbits.TCKPS0 = 1;
    T3CONbits.TCKPS1 = 0; //pre-scaler of 1:8
    
    T3CONbits.TON = 1; //Let's go!
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR3bits.RP6R = 18;  // Use Pin RP6 for Output Compare 1 = "18" (Table 10-3)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    OC1CON = 0;
    OC1R = 1234;
    OC1RS = 1234;
    OC1CONbits.OCM = 0b110;
    OC1CONbits.OCTSEL = 1;
}

void setup(void) {
    CLKDIVbits.RCDIV = 0; //clock setup thing
    AD1PCFG = 0x9fff; //sets all pins to digital I/O
    TRISBbits.TRISB6 = 0; //servo pin output
    TRISBbits.TRISB8 = 1; //button pin input;
    
    initServo();
}

int main(void) {
    setup();
    
    while(1) {
        setServo(10000); //25%
        delay(2000);
        setServo(30000); //75%;
        delay(2000);
    }
    return 0;
}
