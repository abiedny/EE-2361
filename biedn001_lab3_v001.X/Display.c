#include "xc.h"
#include "Display.h"

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
    delay(250);
    showChar7seg('.', RIGHT);
    delay(250);
    return;
}

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
        case '.':
            LATB |= digit | Characters[toShow - 30];
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
