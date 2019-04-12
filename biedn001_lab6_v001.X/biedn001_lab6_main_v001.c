#include "xc.h"
#include "biedn001_lab6_circularBuffer_v001.h"

void setup(void) {
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff; //all digital inputs and outputs
    initBuffer();
}

int main(void) {
    setup();
    
    while(1) {
        
    }
}
