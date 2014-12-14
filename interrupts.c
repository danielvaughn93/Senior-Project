#include "interrupts.h"

int Count=0;

void __attribute__((__interrupt__)) _T1Interrupt(void){
	/* Insert ISR Code Here*/
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 0;
   	Count++;
	if(Count == 5)
	{
		    Count		   = 0;  
			blink_led(3);		    
	}

    TMR1          = 0;
	/* Clear Timer1 interrupt */
	IFS0bits.T1IF = 0;
}
void __attribute__((__interrupt__)) _T2Interrupt(void){
	/* Insert ISR Code Here*/
	/* Clear Timer2 interrupt */
	IFS0bits.T2IF = 0;
}
void __attribute__((__interrupt__)) _T3Interrupt(void){
	/* Insert ISR Code Here*/
	/* Clear Timer3 interrupt */
	IFS0bits.T3IF = 0;
}
void __attribute__((__interrupt__)) _CNInterrupt(void){
	/* Insert ISR Code Here*/
	/* Clear CN interrupt */
	IFS1bits.CNIF = 0;
}