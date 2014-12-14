#include "functions.h"

void __attribute__((__interrupt__)) _T1Interrupt(void);
void __attribute__((__interrupt__)) _T2Interrupt(void);
void __attribute__((__interrupt__)) _T3Interrupt(void);
void __attribute__((__interrupt__)) _CNInterrupt(void);