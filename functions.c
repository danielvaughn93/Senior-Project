#include "functions.h"
extern void enSecOsc();

void dutycycle_fluc(void){
		int dc=0;
		while(dc<1224){
			PDC1 = dc;
			SDC1 = dc;
			PDC2 = dc;
			SDC2 = dc;
			PDC3 = dc;
			SDC3 = dc;
			dc++;
         	__delay_ms(100); // wait 100 ms
		}
}

void blink_led(int numblinks){
    int i; 
      for(i=0;i<numblinks;i++) {
         LATA = 0x0001; // turn LED on
         __delay_ms(100); // wait 100 ms
         LATA = 0x0000; // turn LED OFF
         __delay_ms(100); // wait 100 ms
     }
}
void blink_led2(int numblinks){
    int i; 
      for(i=0;i<numblinks;i++) {
         LATB = 0x8000; // turn LED on
         __delay_ms(100); // wait 100 ms
         LATB = 0x0000; // turn LED OFF
         __delay_ms(100); // wait 100 ms
     }
}

void init_pwm(void){
    PTCONbits.PTEN = 0;						/* Disable PWM */

	PTCONbits.PTSIDL = 0;					/* PWM runs in idle mode */
	PTCON2bits.PCLKDIV = 0;					/* PWM Input Clock Prescaler = 1*/
	//MDC = 0x00FF;								/* Set Duty Cycle = 50% */


/*									SETUP PWM MOD 1				*/
	PWMCON1bits.ITB = 1;					/* PHASEx/SPHASEx provides time base period for x PWM gen */
	PWMCON1bits.MDCS = 0;					/* PDC/SDC register provides duty cycle for x PWM generator */
	PWMCON1bits.CAM = 1;					/* Enable center-aligned mode */
	PWMCON1bits.XPRES = 0;					/* External pins do not affect PWM time base */
	PWMCON1bits.IUE = 1;					/*Updates to the active MDC/PDCx/SDCx registers are immediate*/
    IOCON1bits.PENH = 1;   					/* PWM1H is controlled by PWM module */
    IOCON1bits.PENL = 1;   					/* PWM1L is controlled by PWM module */
    IOCON1bits.PMOD = 3;   					/* Select Output PWM mode */
              
	PWMCON1bits.DTC = 3;					/* Disable Deadtime */
											  /* Select Independent timebase mode (required for
                                               center-aligned mode) */
	
    PHASE1 = 24040;             			
											/* In Center-aligned mode the effective period of 
                                               the PWM signal is twice of the value in the 
                                               PHASEx register. So to obtain signal of 40kHz
                                               (or 25us period), the PHASE1 register should be
                                               configured for a period of 1.25us.
                                               PHASE1 = ((12.5us) / 1.04ns) = 12020. So effective
                                               period is 25us. */

    SPHASE1 = 24040;             			
												/* In Center-aligned mode the effective period of 
                                               the PWM signal is twice of the value in the 
                                               SPHASEx register. So to obtain signal of 400kHz
                                               (or 2.5us period), the SPHASE1 register should be
                                               configured for a period of 1.25us.
                                               SPHASE1 = ((1.25us) / 1.04ns) = 1202. So effective
                                               period is 2.5us. */
                                           
    PDC1 = 24020;					   			/* 50% Duty cycle for PWM1H */ 
	SDC1 = 24020;								/* 50% Duty cycle for PWM1L */
    
/*									SETUP PWM MOD 2				*/
	PWMCON2bits.ITB = 1;					/* PHASEx/SPHASEx provides time base period for x PWM gen */
	PWMCON2bits.MDCS = 0;					/* PDC/SDC register provides duty cycle for x PWM generator */
	PWMCON2bits.CAM = 1;					/* Enable center-aligned mode */
	PWMCON2bits.XPRES = 0;					/* External pins do not affect PWM time base */
	PWMCON2bits.IUE = 1;					/*Updates to the active MDC/PDCx/SDCx registers are immediate*/
    IOCON2bits.PENH = 1;   					/* PWM1H is controlled by PWM module */
    IOCON2bits.PENL = 1;   					/* PWM1L is controlled by PWM module */
    IOCON2bits.PMOD = 3;   					/* Select complimentary Output PWM mode */
              
	PWMCON2bits.DTC = 2;					/* Disable Deadtime */
											  /* Select Independent timebase mode (required for
                                               center-aligned mode) */
	
    PHASE2 = 24040;             			
											/* In Center-aligned mode the effective period of 
                                               the PWM signal is twice of the value in the 
                                               PHASEx register. So to obtain signal of 400kHz
                                               (or 2.5us period), the PHASE1 register should be
                                               configured for a period of 1.25us.
                                               PHASE1 = ((1.25us) / 1.04ns) = 1202. So effective
                                               period is 2.5us. */

    SPHASE2 = 24040;             			
												/* In Center-aligned mode the effective period of 
                                               the PWM signal is twice of the value in the 
                                               SPHASEx register. So to obtain signal of 400kHz
                                               (or 2.5us period), the SPHASE1 register should be
                                               configured for a period of 1.25us.
                                               SPHASE1 = ((1.25us) / 1.04ns) = 1202. So effective
                                               period is 2.5us. */
                                 
    PDC2 = 24020;					   			/* 50% Duty cycle for PWM1H */ 
	SDC2 = 24020;								/* 50% Duty cycle for PWM1L */
    
/*									SETUP PWM MOD 3				*/
	PWMCON3bits.ITB = 1;					/* PHASEx/SPHASEx provides time base period for x PWM gen */
	PWMCON3bits.MDCS = 0;					/* PDC/SDC register provides duty cycle for x PWM generator */
	PWMCON3bits.CAM = 1;					/* Enable center-aligned mode */
	PWMCON3bits.XPRES = 0;					/* External pins do not affect PWM time base */
	PWMCON3bits.IUE = 1;					/*Updates to the active MDC/PDCx/SDCx registers are immediate*/
    IOCON3bits.PENH = 1;   					/* PWM1H is controlled by PWM module */
    IOCON3bits.PENL = 1;   					/* PWM1L is controlled by PWM module */
    IOCON3bits.PMOD = 3;   					/* Select complimentary Output PWM mode */
              
	PWMCON3bits.DTC = 2;					/* Disable Deadtime */
											  /* Select Independent timebase mode (required for
                                               center-aligned mode) */
	
    PHASE3 = 24040;             			
											/* In Center-aligned mode the effective period of 
                                               the PWM signal is twice of the value in the 
                                               PHASEx register. So to obtain signal of 400kHz
                                               (or 2.5us period), the PHASE1 register should be
                                               configured for a period of 1.25us.
                                               PHASE1 = ((1.25us) / 1.04ns) = 1202. So effective
                                               period is 2.5us. */

    SPHASE3 = 24040;             			
												/* In Center-aligned mode the effective period of 
                                               the PWM signal is twice of the value in the 
                                               SPHASEx register. So to obtain signal of 400kHz
                                               (or 2.5us period), the SPHASE1 register should be
                                               configured for a period of 1.25us.
                                               SPHASE1 = ((1.25us) / 1.04ns) = 1202. So effective
                                               period is 2.5us. */
                                               
    PDC3 = 24020;					   			/* 50% Duty cycle for PWM1H */ 
	SDC3 = 24020;								/* 50% Duty cycle for PWM1L */
    


	PTCONbits.PTEN = 1;						/*  Enable PWM   */	



}

void start_PWM(void){

    PHASE1 = 1920;                          /* PWM1H, PHASEx = ((1 / 500kHz) / 1.04ns) = 1923, where 500kHz 
											 is the desired switching frequency and 1.04ns is PWM resolution. */

    SPHASE1 = 3840;                         /* PWM1L, SPHASEx = ((1 / 250kHz) / 1.04ns) = 3846, where 250kHz 
											 is the desired switching frequency and 1.04ns is PWM resolution. */

	PWMCON1bits.ITB = 1;					/* Use Phasex and SPHASEx registers for Independent time base */
	PWMCON1bits.DTC = 2;					/* Disable Deadtime */

   
    IOCON1bits.PENH = 1;      				/* PWM1H is controlled by PWM module */ 
    IOCON1bits.PENL = 1;      				/* PWM1L is controlled by PWM module */
    IOCON1bits.PMOD = 0;      				/* Select True Independent Output PWM mode */

    PDC1 = 960;					   			/* 50% Duty cycle for PWM1H */ 
	SDC1 = 1920;							/* 50% Duty cycle for PWM1L */
    
    PTCONbits.PTEN       = 1;      			/* Enable the PWM Module */
}

void init_adc(void){
	ADCONbits.ADON = 0;
	ADCONbits.ADSIDL = 0;
	ADCONbits.SLOWCLK = 0;
	ADCONbits.FORM = 0;

	ADCONbits.ADCS = 0;
	ADCONbits.ADON = 1;
}
void init_timer1(void){

    T1CON = 0;              // Timer reset
//	IFS0bits.T1IF = 0;      // Reset Timer1 interrupt flag
//	IPC0bits.T1IP = 4;      // Timer1 Interrupt priority level=4
 //	IEC0bits.T1IE = 1;      // Enable Timer1 interrupt
 	TMR1 = 0x0000;		
	PR1 = 0x8000;           // Timer1 period register = 32768
	T1CONbits.TCS = 0;      // Timer1 Clock= internal
  	T1CONbits.TON = 1;      // Enable Timer1 and start the counter

}
void init_timer2(void){
    T2CON = 0;              // Timer reset
//	IFS0bits.T1IF = 0;      // Reset Timer1 interrupt flag
//	IPC0bits.T1IP = 4;      // Timer2 Interrupt priority level=4
 //	IEC0bits.T1IE = 1;      // Enable Timer2 interrupt
 	TMR2 = 0x0000;		
	PR2 = 0x8000;           // Timer2 period register = 32768
	T2CONbits.TCS = 0;      // Timer2 Clock= internal
  	T2CONbits.TON = 1;      // Enable Timer2 and start the counter
}

void init_comp(void){
	PMD3bits.CMPMD=0;
	PMD7bits.CMP1MD=0;

	CMPCON1bits.CMPSIDL=0;
	CMPCON1bits.INSEL=2;
	CMPCON1bits.EXTREF=0;
	CMPCON1bits.CMPPOL=0;
	CMPCON1bits.RANGE=1;
	CMPCON1bits.DACOE=0;
	CMPCON1bits.CMPON=1;
}

void cyle_pwm(void){

}

void enableInterrupts(void){
	/* Set CPU IPL to 0, enable level 1-7 interrupts */
	/* No restoring of previous CPU IPL state performed here */
	SRbits.IPL = 0;
	return;
}
void disableInterrupts(void){
	/* Set CPU IPL to 7, disable level 1-7 interrupts */
	/* No saving of current CPU IPL setting performed here */
	SRbits.IPL = 7;
	return;
}

void initInterrupts(void){
	// Interrupt nesting enabled here
	INTCON1bits.NSTDIS = 0;
	
	// Set Timer3 interrupt priority to 6 (level 7 is highest) 
//	IPC2bits.T3IP = 6;
	// Set Timer2 interrupt priority to 6 
	IPC1bits.T2IP = 6;
	// Set Change Notice interrupt priority to 4
//	IPC4bits.CNIP = 4;
	// Set Timer1 interrupt priority to 6 
	IPC0bits.T1IP = 6;
	//Set Analog Comparator interrupt priority to 6
	IPC4bits.AC1IP = 6;
	// Reset Timer1 interrupt flag 
	IFS0bits.T1IF = 0;
	// Reset Timer2 interrupt flag 
	IFS0bits.T2IF = 0;
	// Reset Timer3 interrupt flag 
//	IFS0bits.T3IF = 0;
	// Reset Comparator interrupt flag
	IFS1bits.AC1IF=0;
	// Enable CN interrupts
//	IEC1bits.CNIE = 1;
	// Enable Timer1 interrupt 
	IEC0bits.T1IE = 1;
	/* Enable Timer2 interrupt (PWM time base) */
	IEC0bits.T2IE = 1;
	// Enable Timer3 interrupt 
//	IEC0bits.T3IE = 1;
	//Enable Analog comparator 1 Interrupt
	IEC1bits.AC1IE;
	/* Reset change notice interrupt flag */
//	IFS1bits.CNIF = 0;
	
	return;
}
int nearestint(float i){
	int rounded;
	if(i<0){
		rounded = ((int)(i-0.5));
	}
	else{
		rounded = ((int)(i+0.5));
	}
	return rounded;
}