#include "xc.h"
#include "biedn001_lab2b_asmLib_v001.h"
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
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
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    TRISA = 0xFFFE;
    LATA = 0x0000;
}

int main(void) {
    //setup
    setup();
    
    //write to LED
    delay_100_micro();

    //red
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    
    //green
    write_0();
    write_1();
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    
    //blue
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    write_0();
    
    delay_100_micro();
    
    while(1) {
        //loop
    }
}
