#include "biedn001_lab6_circularBuffer_v001.h"

void initBuffer(void) {
    int i;
    for (i = 0; i < BUFFERSIZE; i++) {
        buffer[i] = 0;
    }
}

void putVal(int newVal) {
    buffer[buffInd] = newVal;
    buffInd = (buffInd + 1) % BUFFERSIZE;
}

int getAvg(void) {
    unsigned long int sum = 0;
    
    int i;
    for (i = 0; i < BUFFERSIZE; i++) {
        sum += buffer[i];
    }
    return sum/BUFFERSIZE;
}