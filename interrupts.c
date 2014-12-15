#include "interrupts.h"

static int Count=0;
static int Count2=0;
// ISR ROUTINE FOR THE TIMER1 INTERRUPT 
void __attribute__((__interrupt__)) _T1Interrupt(void){
	/* Insert ISR Code Here*/
    T1CONbits.TON = 0;
   	Count++;
//	display_text("THAT", 4, 122, 150, TEXT_SIZE_NORMAL, WHITE);
	if(Count == 1000){
		    Count = 0;  
			blink_led(3);		    
	}

    TMR1 = 0;
	/* Clear Timer1 interrupt */
	IFS0bits.T1IF = 0;
	//Turn Timer Back on
	T1CONbits.TON = 1;
}
// ISR ROUTINE FOR THE TIMER2 INTERRUPT
void __attribute__((__interrupt__)) _T2Interrupt(void){
	/* Insert ISR Code Here*/
    T2CONbits.TON = 0;
   	Count2++;
//	display_text("THIS", 4, 100, 150, TEXT_SIZE_NORMAL, WHITE);
	if(Count2 == 5500){
		    Count2 = 0;  
			blink_led2(3);		    
	}

    TMR2 = 0;
	/* Clear Timer2 interrupt */
	IFS0bits.T2IF = 0;
	//Turn Timer Back on
	T2CONbits.TON = 1;
}

// ISR ROUTINE FOR THE TIMER3 INTERRUPT
void __attribute__((__interrupt__)) _T3Interrupt(void){
	/* Insert ISR Code Here*/
	/* Clear Timer3 interrupt */
	IFS0bits.T3IF = 0;
}

// ISR ROUTINE FOR THE CN INTERRUPT
void __attribute__((__interrupt__)) _CNInterrupt(void){
	/* Insert ISR Code Here*/
	/* Clear CN interrupt */
	IFS1bits.CNIF = 0;
}