//Daniel Vaughn
//functions.c
//
//Developed at University of Maine
//Fall 2014
//
//This file contains the implementation of the functions used to initialize
// the modules, such as the Analog to Digital Converter(ADC), Timer1, and Timer2.
//It also contains various stages of functions from the development process/ programs
// that were used to test different parts of the code throughout the development.

#include "functions.h"

extern int SLT[180];

//Function to test if we could adjuct the PWM duty cycle on the fly
void dutycycle_fluc(void){
		int dc=0;
		while(dc<24040){
			PDC1 = dc;
			SDC1 = dc;
			PDC2 = dc;
			SDC2 = dc;
			PDC3 = dc;
			SDC3 = dc;
			dc++;
         	__delay_ms(10); // wait 100 ms
		}
}
//Function primarily used in testing interrupt code.
//Takes an int that is the number of times for the led to blink.
void blink_led(int numblinks){
    int i; 
      for(i=0;i<numblinks;i++) {
         LATA = 0x0001; // turn LED on
         __delay_ms(100); // wait 100 ms
         LATA = 0x0000; // turn LED OFF
         __delay_ms(100); // wait 100 ms
     }
}
//Function primarily used in testing interrupt code.
//Takes an int that is the number of times for the led to blink.
void blink_led2(int numblinks){
    int i; 
      for(i=0;i<numblinks;i++) {
         LATB = 0x8000; // turn LED on
         __delay_ms(100); // wait 100 ms
         LATB = 0x0000; // turn LED OFF
         __delay_ms(100); // wait 100 ms
     }
}

//This function initializes each of the 3 PWM modules. 
void init_pwm(void){
    PTCONbits.PTEN = 0;						/* Disable PWM */

	PTCONbits.PTSIDL = 0;					/* PWM runs in idle mode */
	PTCON2bits.PCLKDIV = 0;					/* PWM Input Clock Prescaler = 1*/
	//MDC = 0x00FF;								/* Set Duty Cycle = 50% */


/*									SETUP PWM MOD 1				*/
	PWMCON1bits.ITB = 1;					/* PHASEx/SPHASEx provides time base period for x PWM gen */
	PWMCON1bits.MDCS = 0;					/* PDC/SDC register provides duty cycle for x PWM generator */
	PWMCON1bits.CAM = 0;					/* Enable center-aligned mode */
	PWMCON1bits.XPRES = 0;					/* External pins do not affect PWM time base */
	PWMCON1bits.IUE = 1;					/*Updates to the active MDC/PDCx/SDCx registers are immediate*/
    IOCON1bits.PENH = 1;   					/* PWM1H is controlled by PWM module */
    IOCON1bits.PENL = 1;   					/* PWM1L is controlled by PWM module */
    IOCON1bits.PMOD = 0;   					/* Select Output PWM mode
												11 = PWM I/O pin pair is in the True Independent Output mode
												10 = PWM I/O pin pair is in the Push-Pull Output mode
												01 = PWM I/O pin pair is in the Redundant Output mode
												00 = PWM I/O pin pair is in the Complementary Output mode */
              
	PWMCON1bits.DTC = 0;					// Deadtime Setting
												//00 = Positive dead time actively applied for all output modes
												//01 = Negative dead time actively applied for all output modes
												//10 = Dead-time function is disabled
	
	DTR1 = 1000;								// Unsigned 14-Bit Dead-Time Value for PWM1 Dead-Time Unit bits							
	ALTDTR1 = 1000;									

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
                                           
    PDC1 = 24040;					   			/* 100% Duty cycle for PWM1H */ 
//	SDC1 = 24040;								/* 100% Duty cycle for PWM1L */
    
/*									SETUP PWM MOD 2				*/
	PWMCON2bits.ITB = 1;					/* PHASEx/SPHASEx provides time base period for x PWM gen */
	PWMCON2bits.MDCS = 0;					/* PDC/SDC register provides duty cycle for x PWM generator */
	PWMCON2bits.CAM = 0;					/* Enable center-aligned mode */
	PWMCON2bits.XPRES = 0;					/* External pins do not affect PWM time base */
	PWMCON2bits.IUE = 1;					/*Updates to the active MDC/PDCx/SDCx registers are immediate*/
    IOCON2bits.PENH = 1;   					/* PWM1H is controlled by PWM module */
    IOCON2bits.PENL = 1;   					/* PWM1L is controlled by PWM module */
    IOCON2bits.PMOD = 0;   					/* Select Output PWM mode
												11 = PWM I/O pin pair is in the True Independent Output mode
												10 = PWM I/O pin pair is in the Push-Pull Output mode
												01 = PWM I/O pin pair is in the Redundant Output mode
												00 = PWM I/O pin pair is in the Complementary Output mode */
              
	PWMCON2bits.DTC = 0;					/* Disable Deadtime */
												//00 = Positive dead time actively applied for all output modes
												//01 = Negative dead time actively applied for all output modes
												//10 = Dead-time function is disabled

	DTR2 = 1000;								// Unsigned 14-Bit Dead-Time Value for PWM2 Dead-Time Unit bits							
	ALTDTR2 = 1000;
	
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
                                 
    PDC2 = 24040;					   			/* 100% Duty cycle for PWM1H */ 
//	SDC2 = 24040;								/* 100% Duty cycle for PWM1L */
    
/*									SETUP PWM MOD 3				*/
	PWMCON3bits.ITB = 1;					/* PHASEx/SPHASEx provides time base period for x PWM gen */
	PWMCON3bits.MDCS = 0;					/* PDC/SDC register provides duty cycle for x PWM generator */
	PWMCON3bits.CAM = 0;					/* Enable center-aligned mode */
	PWMCON3bits.XPRES = 0;					/* External pins do not affect PWM time base */
	PWMCON3bits.IUE = 1;					/*Updates to the active MDC/PDCx/SDCx registers are immediate*/
    IOCON3bits.PENH = 1;   					/* PWM1H is controlled by PWM module */
    IOCON3bits.PENL = 1;   					/* PWM1L is controlled by PWM module */
    IOCON3bits.PMOD = 0;   					/* Select Output PWM mode
												11 = PWM I/O pin pair is in the True Independent Output mode
												10 = PWM I/O pin pair is in the Push-Pull Output mode
												01 = PWM I/O pin pair is in the Redundant Output mode
												00 = PWM I/O pin pair is in the Complementary Output mode */
              
	PWMCON3bits.DTC = 0;					/* Disable Deadtime */
												//00 = Positive dead time actively applied for all output modes
												//01 = Negative dead time actively applied for all output modes
												//10 = Dead-time function is disabled

	DTR3 = 1000;								// Unsigned 14-Bit Dead-Time Value for PWM3 Dead-Time Unit bits							
	ALTDTR3 = 1000;
	
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
                                               
    PDC3 = 24040;					   			/* 100% Duty cycle for PWM1H */ 
//	SDC3 = 24020;								/* 100% Duty cycle for PWM1L */
    


	PTCONbits.PTEN = 1;						/*  Enable PWM   */	



}


//This function initiallizes the ADC. The ADC will be used to take inupt
//From the Hall effect sensor and determine whether the wheel is spinning
//at the correct speed.
void init_adc(void){
	ADCONbits.ADON=0;	//turn off ADC module

	ADCONbits.FORM = 0; // Output in Integer Format
	ADCONbits.EIE = 0; // Enable Early Interrupt
	ADCONbits.ORDER = 0; // Normal Order of Conversion
	ADCONbits.SEQSAMP = 0; // Simultaneous Sampling 
	ADCONbits.ASYNCSAMP = 1; // Asynchronous Sampling
	ADCONbits.SLOWCLK = 0; // High Frequency Clock Input
	ADCONbits.ADCS = 5; // Clock Divider Selection

	ADCPC0bits.TRGSRC1=0b11111; // Timer 2 Period match trigger Selected
	ADCPC1bits.TRGSRC2=0b11111; // Timer 2 Period Match trigger Selected

	ADPCFGbits.PCFG3 = 0; // AN3 is configured as analog input
	ADPCFGbits.PCFG4 = 0; // AN4 is configured as analog input
	ADPCFGbits.PCFG5 = 0; // AN5 is configured as analog input

	IPC28bits.ADCP2IP = 0x04; // Set ADC Pair 2 Interrupt Priority (Level 4)
	IFS7bits.ADCP2IF = 0; // Clear ADC Pair 2 Interrupt Flag
	IEC7bits.ADCP2IE = 1; // Enable ADC Pair 2 Interrupt

	IPC27bits.ADCP1IP = 0x04; // Set ADC Pair 1 Interrupt Priority (Level 4)
	IFS6bits.ADCP1IF = 0; // Clear ADC Pair 1 Interrupt Flag
	IEC6bits.ADCP1IE = 1; // Enable ADC Pair 1 Interrupt

	ADCONbits.ADON = 1; // Enable ADC Module

}
//This function initializes Timer1. This timer is going to primarily
// be used to adjust the frequecy of the PWM emulated sine wave, and
// Emulate the sine wave in the Timer1 Interrupts
void init_timer1(void){

    T1CON = 0;              // Timer reset
//	IFS0bits.T1IF = 0;      // Reset Timer1 interrupt flag
//	IPC0bits.T1IP = 4;      // Timer1 Interrupt priority level=4
 //	IEC0bits.T1IE = 1;      // Enable Timer1 interrupt
 	TMR1 = 0x0000;		
	PR1 = 0x8000;           // Timer1 period register = 32768
	T1CONbits.TCS = 0;      // Timer1 Clock= internal

//Interrupt setup
	IPC0bits.T1IP = 6;		// Set Timer1 interrupt priority to 6 
	IFS0bits.T1IF = 0;		// Reset Timer1 interrupt flag 
	IEC0bits.T1IE = 1;  	// Enable Timer1 interrupt 

	T1CONbits.TON = 1;      // Enable Timer1 and start the counter

}

//This function initializes Timer2. This timer is going to be
//used to trigger the ADC interrupts
void init_timer2(void){
    T2CON = 0;              // Timer reset
//	IFS0bits.T1IF = 0;      // Reset Timer1 interrupt flag
//	IPC0bits.T1IP = 4;      // Timer2 Interrupt priority level=4
 //	IEC0bits.T1IE = 1;      // Enable Timer2 interrupt
 	TMR2 = 0x0000;		
	PR2 = 0x8000;           // Timer2 period register = 32768
	T2CONbits.TCS = 0;      // Timer2 Clock= internal

//Interrupt Stuff
	IPC1bits.T2IP = 6;		// Set Timer2 interrupt priority to 6 
	IFS0bits.T2IF = 0;		// Reset Timer2 interrupt flag 
	IEC0bits.T2IE = 1;		// Enable Timer2 interrupt
  
	T2CONbits.TON = 1;      // Enable Timer2 and start the counter
}


//This function initiallizes the comparator module.
void init_comp(void){
	PMD3bits.CMPMD=0;
	PMD7bits.CMP1MD=0;

	CMPCON3bits.CMPSIDL=0;
	CMPCON3bits.INSEL=1;
	CMPCON3bits.EXTREF=1;
	CMPCON3bits.CMPPOL=0;
	CMPCON3bits.RANGE=1;
	CMPCON3bits.DACOE=0;
	CMPCON3bits.CMPON=1;
}

//Enables the use of interrupts
void enable_interrupts(void){
	/* Set CPU IPL to 0, enable level 1-7 interrupts */
	/* No restoring of previous CPU IPL state performed here */
	SRbits.IPL = 0;
	return;
}

//Disables all interrupts
void disable_interrupts(void){
	/* Set CPU IPL to 7, disable level 1-7 interrupts */
	/* No saving of current CPU IPL setting performed here */
	SRbits.IPL = 7;
	return;
}


//This was the first way I was going to initialize all the interrupts in one place
//Decided that it would be better to initialize them individually with the module 
//that they would be associated with
void init_interrupts(void){
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
	//Enable ADC Pair 0 Interrupt
	ADCPC0bits.IRQEN1=1;
	/* Reset change notice interrupt flag */
//	IFS1bits.CNIF = 0;
	
	return;
}

//This function rounds to the nearest int. I tried to use round and rint,
//But it was giving me some weird linker errors, even though I had included math.h

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

//This function was an attempt to use square pwm waves that were being turned on and off
// in a way that would control the H-bridge to turn the motor.
void square_pwm(int freq){
		int del=0;
		if(freq<1000){		//Frequency too low
			freq=1000;
		}
		del=freq/6;
		IOCON2bits.PENL = 1;
		IOCON3bits.PENH = 1;	
		__delay_us(del);
		IOCON2bits.PENL = 0;		
		IOCON1bits.PENL = 1;
		__delay_us(del);
		IOCON3bits.PENH = 0;		
		IOCON2bits.PENH = 1;
		__delay_us(del);
		IOCON3bits.PENL = 1;		
		IOCON1bits.PENL = 0;
		__delay_us(del);
		IOCON2bits.PENH = 0;		
		IOCON1bits.PENH = 1;
		__delay_us(del);
		IOCON2bits.PENL = 1;		
		IOCON3bits.PENL = 0;
		__delay_us(del);
}

void sin_pwm(int period){
//		int del=period/180;
		int i=0;
		while(1){
			for(i=0; i<180; i++){

				PDC1=(SLT[i]);
				PDC2=(SLT[((i+60)%180)]);
				PDC3=(SLT[((i+120)%180)]);
				__delay_us(72);
			}
		}
}

void test_dcmotor(void){
		PDC1=12020;

}