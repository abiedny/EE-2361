#ifndef BIEDN001_LAB6_CIRCULARBUFFER_V001_H
#define	BIEDN001_LAB6_CIRCULARBUFFER_V001_H

#include "xc.h"

#ifdef	__cplusplus
extern "C" {
#endif

    #define BUFFERSIZE 1024
    static int buffer[BUFFERSIZE];
    static int buffInd = 0;
    
    void putVal(int);
    int getAvg(void);
    void initBuffer(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BIEDN001_LAB6_CIRCULARBUFFER_V001_H */

