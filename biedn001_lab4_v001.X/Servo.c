#include <p24FJ64GA002.h>

#include "Servo.h"
#include "xc.h"

void setServo(double dutyMS) {
    OC1RS = (dutyMS/20)*PR3;
    OC2RS = (dutyMS/20)*PR3;
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
    RPOR3bits.RP7R = 19; //pin rp7 for oc2
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    
    OC2CON = 0;
    OC2R = 1234;
    OC2RS = 1234;
    OC2CONbits.OCM = 0b110;
    OC2CONbits.OCTSEL = 1;
    
    OC1CON = 0;
    OC1R = 1234;
    OC1RS = 1234;
    OC1CONbits.OCM = 0b110;
    OC1CONbits.OCTSEL = 1;
}
