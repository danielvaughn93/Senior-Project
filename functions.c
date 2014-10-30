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
    IOCON1bits.PMOD = 0;   					/* Select Complimentary Output PWM mode */
              
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
    PDC1 = 24040;
	SDC1 = 24040;                                           
    //PDC1 = 12000;					   			/* 50% Duty cycle for PWM1H */ 
	//SDC1 = 12000;								/* 50% Duty cycle for PWM1L */
    
/*									SETUP PWM MOD 2				*/
	PWMCON2bits.ITB = 1;					/* PHASEx/SPHASEx provides time base period for x PWM gen */
	PWMCON2bits.MDCS = 0;					/* PDC/SDC register provides duty cycle for x PWM generator */
	PWMCON2bits.CAM = 1;					/* Enable center-aligned mode */
	PWMCON2bits.XPRES = 0;					/* External pins do not affect PWM time base */
	PWMCON2bits.IUE = 1;					/*Updates to the active MDC/PDCx/SDCx registers are immediate*/
    IOCON2bits.PENH = 1;   					/* PWM1H is controlled by PWM module */
    IOCON2bits.PENL = 1;   					/* PWM1L is controlled by PWM module */
    IOCON2bits.PMOD = 0;   					/* Select complimentary Output PWM mode */
              
	PWMCON2bits.DTC = 0;					/* Negaive Deadtime */
											  /* Select Independent timebase mode (required for
                                               center-aligned mode) */
	
	DTR2 = 2730;							//Dead Time Register
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
    PDC2 = 24040;
	SDC2 = 24040;                                  
    //PDC2 = 12000;					   			/* 50% Duty cycle for PWM1H */ 
	//SDC2 = 12000;								/* 50% Duty cycle for PWM1L */
    
/*									SETUP PWM MOD 3				*/
	PWMCON3bits.ITB = 1;					/* PHASEx/SPHASEx provides time base period for x PWM gen */
	PWMCON3bits.MDCS = 0;					/* PDC/SDC register provides duty cycle for x PWM generator */
	PWMCON3bits.CAM = 1;					/* Enable center-aligned mode */
	PWMCON3bits.XPRES = 0;					/* External pins do not affect PWM time base */
	PWMCON3bits.IUE = 1;					/*Updates to the active MDC/PDCx/SDCx registers are immediate*/
    IOCON3bits.PENH = 1;   					/* PWM1H is controlled by PWM module */
    IOCON3bits.PENL = 1;   					/* PWM1L is controlled by PWM module */
    IOCON3bits.PMOD = 0;   					/* Select complimentary Output PWM mode */
              
	PWMCON3bits.DTC = 2;					/* Disable Deadtime */
											  /* Select Independent timebase mode (required for
                                               center-aligned mode) */
	
    PHASE3 = 1202;             			
											/* In Center-aligned mode the effective period of 
                                               the PWM signal is twice of the value in the 
                                               PHASEx register. So to obtain signal of 400kHz
                                               (or 2.5us period), the PHASE1 register should be
                                               configured for a period of 1.25us.
                                               PHASE1 = ((1.25us) / 1.04ns) = 1202. So effective
                                               period is 2.5us. */

    SPHASE3 = 1202;             			
												/* In Center-aligned mode the effective period of 
                                               the PWM signal is twice of the value in the 
                                               SPHASEx register. So to obtain signal of 400kHz
                                               (or 2.5us period), the SPHASE1 register should be
                                               configured for a period of 1.25us.
                                               SPHASE1 = ((1.25us) / 1.04ns) = 1202. So effective
                                               period is 2.5us. */
                                               
    PDC3 = 667;					   			/* 50% Duty cycle for PWM1H */ 
	SDC3 = 667;								/* 50% Duty cycle for PWM1L */
    


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
void init_timer1( void )
{

    T1CON = 0;              // Timer reset
 	IFS0bits.T1IF = 0;      // Reset Timer1 interrupt flag
	IPC0bits.T1IP = 4;      // Timer1 Interrupt priority level=4
 	IEC0bits.T1IE = 1;      // Enable Timer1 interrupt
 	  	
	PR1 = 0x8000;           // Timer1 period register = 32768
	T1CONbits.TCS = 1;      // Timer1 Clock= External
    enSecOsc();             // Enable Secondary Osc
	T1CONbits.TON = 0;      // Enable Timer1 and start the counter
	
}

void init_comp(void){


}

void cyle_pwm(void){

}