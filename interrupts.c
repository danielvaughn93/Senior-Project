//Daniel Vaughn
//interrupts.c
// File to write the Interrupt Serive Routines(ISR)
//for the dsPIC33fj16GS502
//
//Developed at the University of Maine
//Fall 2014
//
//This file contains the routine to be executed by the interrupts,
//these interrupts are to be used with the dsPIC33fj16GS502

#include "interrupts.h"

extern int SLT[360];
extern int per;
static int Count=0;
static int Count2=0;
static int del=1000;
static int ind=0;
static int an2=0;
static int an3=0;
static int an4=0;
static int an5=0;

// ISR ROUTINE FOR THE TIMER1 INTERRUPT 
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void){
    T1CONbits.TON = 0;
	if(Count >= del){
		    Count = 0;  
			blink_led(1);
/*
			//Sine wave generation of first sine wave
			PDC1=(24040*SLT[ind])/100;
			
			//Sine wave generation of second sine wave which is 120 degrees out of phase with the first
			PDC2=(24040*SLT[(ind+120)%360])/100;

			//Sine wave generation of third sine wave which is 120 degrees out of phase with the second
			PDC3=(24040*SLT[(ind+240)%360])/100;
			if(ind==360){
				ind=0;
			}
			else{
				ind++;
			}*/
	}
	Count++;
    TMR1 = 0;
	// Clear Timer1 interrupt
	IFS0bits.T1IF = 0;
	//Turn Timer Back on
	T1CONbits.TON = 1;
}

// ISR ROUTINE FOR THE TIMER2 INTERRUPT
void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void){
	// Insert ISR Code Here
    T2CONbits.TON = 0;
   	Count2++;
	if(Count2 == 5500){
		    Count2 = 0;  
			blink_led2(1);		    
	}

    TMR2 = 0;
	/* Clear Timer2 interrupt */
	IFS0bits.T2IF = 0;
	//Turn Timer Back on
	T2CONbits.TON = 1;
}

/*TIMER 3 IS UNUSED SO FAR IN THE CODE

// ISR ROUTINE FOR THE TIMER3 INTERRUPT
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void){
	IFS0bits.T3IF = 0;
}

*/

//ISR ROUTINE FOR THE ADC PAIR 1 INTERRUPT
void __attribute__((__interrupt__, __auto_psv__)) _ADCP1Interrupt (void){
	T2CONbits.TON = 0; //Timer2 is the trigger, turn it off while interrupt runs

	an2 = ADCBUF2; // Read AN2 conversion result
	an3 = ADCBUF3; // Read AN3 conversion result


    T2CONbits.TON = 1;	//Turn timer2 back on	
	IFS6bits.ADCP1IF = 0;  //Clear ADC Pair 1 Interrupt Flag
}

//ISR ROUTINE FOR THE ADC PAIR 2 INTERRUPT
void __attribute__((__interrupt__, __auto_psv__)) _ADCP2Interrupt (void){
	T2CONbits.TON = 0; //Timer2 is trigger, turn it off while interrupt runs

	an4 = ADCBUF0; // Read AN0 conversion result
	an5 = ADCBUF1; // Read AN1 conversion result

    T2CONbits.TON = 1;	//Turn timer2 back on
	IFS6bits.ADCP0IF = 0; // Clear ADC Pair 2 Interrupt Flag
}