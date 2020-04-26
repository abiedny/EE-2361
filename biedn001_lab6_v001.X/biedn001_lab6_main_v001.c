#include <p24FJ64GA002.h>

#include "xc.h"
#include <stdio.h>
#include "biedn001_lab6_circularBuffer_v001.h"
#include "biedn001_lab5_lcdLib_v001.h"
void __attribute__ ((__interrupt__)) _AD1C1Interrupt(void) {
    _AD1IF = 0;
    
    int adValue = ADC1BUF0;
    putVal(adValue);
}


void setup(void) {
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff; //all digital inputs and outputs
    initBuffer();
    lcd_init();
    lcd_setCursor(0, 0);
    
    //every 62.5ms
    T3CON = 0;
    _T3IF = 0;
    T3CONbits.TCKPS = 0b10;
    PR3 = 15625;
    
    AD1CON1bits.SSRC = 0b010;
    
    AD1CON2 = 0;
    AD1CON3bits.SAMC = 0b101;
    AD1CHS = 0;
    AD1CSSL = 0;
    AD1PCFGbits.PCFG0 = 0;
    TRISAbits.TRISA0 = 1;
    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 1;
    AD1CON1bits.ADON = 1; //turn it on
}

int main(void) {
    setup();
    
    while(1) {
        
    }
}
