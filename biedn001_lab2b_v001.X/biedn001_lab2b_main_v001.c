#include "xc.h"
#include "stdint.h"
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

#define PERIOD 5

uint32_t packColor(unsigned char, unsigned char, unsigned char);
void writePackedColor(uint32_t);
void writeColor(int, int, int);

uint32_t Wheel(unsigned char WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
        return packColor(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return packColor(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return packColor(WheelPos * 3, 255 - WheelPos * 3, 0);
}


uint32_t packColor(unsigned char r, unsigned char g, unsigned char b) {
    return ((long) r << 16) | ((long) g << 8) | ((long) b);
}

unsigned char getR(uint32_t RGBval) {
    return (unsigned char) (RGBval >> 16);
}

unsigned char getG(uint32_t RGBval) {
    return (unsigned char) (RGBval >> 8 );
}

unsigned char getB(uint32_t RGBval) {
    return (unsigned char) (RGBval >> 0 );
}

void delay(int ms) {
    int i;
    for (i = 0; i < ms; i++) {
        delay_1_milli();
    }
    return;
}

void writePackedColor(uint32_t color) {
    int red = (int) getR(color);
    int green = (int) getG(color);
    int blue = (int) getB(color);
    
    writeColor(red, green, blue);
}

void writeColor(int r, int g, int b) {
    delay_100_micro();
    
    //get the nth bit
    int n;
    for (n = 7; n >= 0; n--) {
        if ((r >> n) & 1) {
            //lsb to msb
            write_1();
        }
        else write_0();
    }
    for (n = 7; n >= 0; n--) {
        if ((g >> n) & 1) {
            //lsb to msb
            write_1();
        }
        else write_0();
    }
    for (n = 7; n >= 0; n--) {
        if ((b >> n) & 1) {
            //lsb to msb
            write_1();
        }
        else write_0();
    }
    
    delay_100_micro();
    return;
}

void setup(void) {
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    TRISA = 0xFFFE;
    LATA = 0x0000;
}

int main(void) {
    //setup
    setup();
    
    unsigned int frame = 255;
    int up = 0;
    uint32_t color;
    
    while(1) {
        color = Wheel(frame);
        writePackedColor(color);
        
        if (up) frame++;
        else frame--;
        
        if (frame == 255) up = 0;
        else if (frame == 0) up = 1;
           
        delay(PERIOD);
    }
}
