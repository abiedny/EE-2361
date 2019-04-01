#include "biedn001_lab5_lcdLib_v001.h"
#include "xc.h"

void lcd_printChar(char toPrint) {
    lcd_cmd(toPrint, RSONE);
}

void lcd_setCursor(char x, char y) {
    lcd_cmd(((0x40*x)+y) + 0b10000000, RSZERO);
}

void lcd_cmd(char command, enum ControlBits cntrl) {
    I2C2CONbits.SEN = 1;
    //wait for sen = 0
    I2C2TRN = 0b01111100; //Check slave address?
    //wait for ack
    I2C2TRN = cntrl;
    //wait for ack
    I2C2TRN = command;
    //wait for ack
    I2C2CONbits.PEN = 1;
    //wait for pen = 0
}

void lcd_init(void) {
    //wait 50ms
    lcd_cmd(0b00111000, RSZERO);
    lcd_cmd(0b00111001, RSZERO);
    lcd_cmd(0b00010100, RSZERO);
    
    lcd_cmd(0b01110000 | (CONTRAST & 0b001111), RSZERO); //contrast c3-c0
    lcd_cmd(0b01010100 | ((CONTRAST & 0b110000) >> 4), RSZERO); //uhh this prblsy ain't right
    
    lcd_cmd(0b01101100, RSZERO);
    //wait 200ms
    lcd_cmd(0b00111000, RSZERO);
    lcd_cmd(0b00001100, RSZERO);
    lcd_cmd(0b00000001, RSZERO);
    //wait 2ms
}
