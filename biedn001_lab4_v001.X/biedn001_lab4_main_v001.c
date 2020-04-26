#include "xc.h"
#include "Servo.h"

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

void setServo(double);
unsigned volatile short int state = 0;

volatile unsigned int overflow = 0;
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    overflow++;
    _T2IF = 0;
}

volatile unsigned long int curPeriod = 0;
void __attribute__((interrupt, auto_psv)) _IC1Interrupt(void) {
    unsigned long int curEdge;
    
    _IC1IF = 0;
    
    curEdge = (unsigned long int)((unsigned long int)IC1BUF + (unsigned long int)overflow*PR2);
    if (curEdge > 500) {
        //real click
        TMR2 = 0; //also reset tmr2
        overflow = 0;
        curPeriod = curEdge;
        
        if (!state && (curPeriod < 15625)) {
            //double click
            state = 1;
            setServo(1.8);
        }
    }
}

void initPushButton(void) {
    //The IC1 module
    //should be set up and configured to use Timer 2 and capture falling edges.
    
    T2CON = 0;
    PR2 = 0xffff;
    TMR2 = 0;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1; //enable t2 interrupt
    IPC1bits.T2IP = 3; //interrupt priority
    T2CONbits.TCKPS = 0b11;
    
    CNPU2bits.CN22PUE = 1; //Pull up on RB8 (button input))
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR7bits.IC1R = 8;  // IC1 on RP8
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    
    IC1CON = 0;
    IC1CONbits.ICTMR = 1; //timer 2 for ic1
    IEC0bits.IC1IE = 1; //enable ic1 interrupt
    IC1CONbits.ICM = 0b010; //falling edge capture also turn on
    IC1CONbits.ICI = 0b00; //interrupt every capture
    IPC0bits.IC1IP = 4; //interrupt prio
    _IC1IF = 0;
    _T2IF = 0;
    
    T2CONbits.TON = 1; //timer 2 enabled
}

void delay(unsigned int ms) {
    int i;
    for (i = 0; i < ms; i++) {
        asm("repeat #15993");
        asm("nop");
    }
    return;
}

void setup(void) {
    CLKDIVbits.RCDIV = 0; //clock setup thing
    AD1PCFG = 0x9fff; //sets all pins to digital I/O
    TRISBbits.TRISB6 = 0; //servo pin output
    TRISBbits.TRISB8 = 1; //button pin input;
    
    initServo();
    initPushButton();
}

int main(void) {
    setup();
    setServo(1.5);\
    
    while(1) {
        //asdkjnapsfn
    }
    
    return 0;
}
