#include "biedn001_lab5_lcdLib_v001.h"
#include "xc.h"

void delay(unsigned int ms) {
    int i;
    for (i = 0; i < ms; i++) {
        asm("repeat #15993");
        asm("nop");
    }
    return;
}

void lcd_printChar(char toPrint) {
    lcd_cmd(toPrint, RSONE);
}

void lcd_setCursor(char x, char y) {
    lcd_cmd(((0x40*x)+y) + 0b10000000, RSZERO);
}

void lcd_cmd(char command, enum ControlBits cntrl) {
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF=0;
    I2C2TRN= 0b01111100;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    I2C2TRN = cntrl;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    I2C2TRN = command;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
}

void lcd_init(void) {
    delay(50);
    lcd_cmd(0b00111000, RSZERO);
    lcd_cmd(0b00111001, RSZERO);
    lcd_cmd(0b00010100, RSZERO);
    
    lcd_cmd(0b01110000 | (CONTRAST & 0b001111), RSZERO); //contrast c3-c0
    lcd_cmd(0b01010100 | (((CONTRAST & 0b110000) >> 4) & 3), RSZERO); //uhh this prblsy ain't right
    
    lcd_cmd(0b01101100, RSZERO);
    delay(200);
    lcd_cmd(0b00111000, RSZERO);
    lcd_cmd(0b00001100, RSZERO);
    lcd_cmd(0b00000001, RSZERO);
    delay(2);
}
