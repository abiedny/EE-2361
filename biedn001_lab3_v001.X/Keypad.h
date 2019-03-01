#ifndef KEYPAD_H
#define	KEYPAD_H

#include <xc.h>
#include "Utility.h"

#ifdef	__cplusplus
extern "C" {
#endif

    int tryCols(int rowInd);
    int readKey(void);
    void initKeyPad(void);

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */

