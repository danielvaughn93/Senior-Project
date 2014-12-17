//Daniel Vaughn
//interrupts.h
// Header to declare the interrupts for the dsPIC33fj16GS502
//
//Developed at the University of Maine
//Fall 2014
//
//This file contains the declarations for the interrupts to 
//be used with the dsPIC33fj16GS502


#include "functions.h"

//Declaration for the Timer 1 Interrupt
void __attribute__((__interrupt__)) _T1Interrupt(void);
//Declaration for the Timer 2 Interrupt
void __attribute__((__interrupt__)) _T2Interrupt(void);
//Declaration for the Timer 3 Interrupt
void __attribute__((__interrupt__)) _T3Interrupt(void);
//Declaration for ADC pair 1 interrupt
void __attribute__((__interrupt__)) _ADCP0Interrupt (void);
//Declaration for ADC pair 2 Interrupt
void __attribute__((__interrupt__)) _ADCP2Interrupt (void);

