//Daniel Vaughn
//Harrison Goodhue

#include <p33FJ16GS502.h>
#include <math.h>
#include <stddef.h>
#include <float.h>
#include <stdlib.h>

 //Select internal FRC at POR
 _FOSCSEL(FNOSC_FRC);
 //Enable clock switching
 _FOSC(FCKSM_CSECMD & OSCIOFNC_OFF); 	//Clock switching mode enabled and fail safe clock monitor disabled & OSCO is general purpose IO pin
 _FWDT(FWDTEN_OFF); //Watchdog timer disabled
 _FPOR(FPWRT_PWR128); //Power-on reset timer is set to 128ms
 _FICD(ICS_PGD2 & JTAGEN_OFF); //Use PGD2 and PGC2 for ICS & JTAG disabled
 //Main function
 int main(void){
 	//Tune FRC frequency to 7.48MHz, i.e. 7.37*(1 + 0.00375*4)
 	OSCTUNbits.TUN = 4;

//Configure PLL divisor (M), PLL prescaler (N1) and PLL postscaler (N2) respectively
 	PLLFBDbits.PLLDIV = 212; 			     // M = PLLDIV + 2 = 214
 	CLKDIVbits.PLLPRE = 8;                   // N1 = PLLPRE + 2 = 10 
 	CLKDIVbits.PLLPOST = 0;                  // N2 = 2(PLLPOST + 1) = 2
    
// Change oscillator to (FRC+PLL)
    __builtin_write_OSCCONH(0b001);			// New Oscillator FRC with PLL
    __builtin_write_OSCCONL(0b00000001);  	// Enable Clock Switch 
    while(OSCCONbits.COSC != 0b001);		// Wait for new Oscillator to become FRC with PLL    
 	while(OSCCONbits.LOCK != 1);			// Wait for Pll to Lock

/* This part configures the auxiliary clock to be used by the PWM and ADC modules*/
 	//now configuring auxilliary clock for PWM and ADC modules
 	//Auxiliary clock = (selected_oscillator)*16/APSTSCLR = 120MHz
 	ACLKCONbits.FRCSEL = 1; //FRC is input to auxiliary PLL
 	ACLKCONbits.SELACLK = 1; //Auxiliary oscillator provides the clock source
 	ACLKCONbits.APSTSCLR = 7; //Divide Auxiliary clock by 1
 	ACLKCONbits.ENAPLL = 1; //Enable auxiliary PLL
 	while(ACLKCONbits.APLLCK !=1); //wait for auxiliary PLL to lock

/*This part initialises the PWM modules*/
 	PTCONbits.PTSIDL = 0; //PWM time base runs in cpu idle mode
 	PTCONbits.EIPU = 1; //Active period register is updated immediately (requirement from Errata)
 	PTCON2bits.PCLKDIV = 0b000; //Divide by 1. Maximum PWM timing resolution is therefore 1.04ns
 	PTPER = 5674; //Master time base frequency is desired to be 172kHz
 	//PWM module 1&2 initializations.
 	//PWM module 1 is used for flyback 1. PWM1_high for main switch and PWM1_low for complementary switch
	//MDC = 0; //Initial duty cycle in Master duty cycle register is 0;
 	PWMCON1bits.FLTSTAT = 0; //Clear fault interrupt status
 	PWMCON2bits.FLTSTAT = 0;
 	PWMCON1bits.TRGSTAT = 0; //No trigger interrupt pending
	PWMCON2bits.TRGSTAT = 0;
 	PWMCON1bits.FLTIEN = 0; //Enable Fault interrupt ***Change to 1***
 	PWMCON2bits.FLTIEN = 0;
 	PWMCON1bits.CLIEN = 0; //Current limit interrupt disabled because we are not interested in current-limiting function at this point
 	PWMCON2bits.CLIEN = 0; 
 	PWMCON1bits.TRGIEN = 0; //Trigger interrupt disabledChange to 1***
 	PWMCON2bits.TRGIEN = 0; //PWM1 only is sufficient for generating the interrupt to the ADC.
 	PWMCON1bits.ITB = 0; //PTPER register provides timing for the 1st and 2nd PWM generators
 	PWMCON2bits.ITB = 0;
 	PWMCON1bits.MDCS = 0; //PDC1 and SDC1 registers provide the duty cycle information for this PWM generator.
 	PWMCON2bits.MDCS = 0; //PDC2 and SDC2 registers provide the duty cycle information for this PWM generator.
 	PWMCON1bits.DTC = 0b00; //Positive dead time actively applied for all output modes
 	PWMCON2bits.DTC = 0b00;
 	PWMCON1bits.CAM = 0; //Enable edge-aligned mode for PWM 1
 	PWMCON2bits.CAM = 0; //Enable edge-aligned mode for PWM 2
 	PWMCON1bits.XPRES = 0; //External pins do not affect PWM time base
 	PWMCON2bits.XPRES = 0;
 	PWMCON1bits.IUE = 1; //Immediate updates to MDC/PDCx/SDCx registers
 	PWMCON2bits.IUE = 1;
 	PDC1 = 2837; //PWM1 generator duty cycle is initialized to 50%;
 	PDC2 = 2837; //PWM2 generator duty cycle is initialized to 50%;
 	//SDCx (for PWM1Low and PWM2Low) are not concerned here because in complementary mode, SDCx is not used
 	PHASE2 = 2837; //Phase shift of half a period (i.e. 2.91us)
 	DTR1 = 0; //High-side dead time. For now, let dead time be 0. We shall fine-tune this value later
	 DTR2 = 0;
 	ALTDTR1 = 0; //Low-side dead time. For now, let this be 0.
 	ALTDTR2 = 0;
 	TRGCON1bits.TRGDIV = 1; //Trigger PWM1 output for every 2nd trigger event.
 	//Is it necessary to trigger PWM2 output as well?
 	TRGCON1bits.TRGSTRT = 0; //Wait 0 PWM cycles before generating the first trigger event after PWM is enabled.
 	TRGCON1bits.DTM = 0; //Datasheet says secondary trigger event will not be combined will not be combined to create PWM trigger. Not so sure here????
 	IOCON1bits.PENH = 1; //PWM module controls PWM1High pin
 	IOCON2bits.PENH = 1; //PWM module controls PWM2High pin
 	IOCON1bits.PENL = 1; //PWM module controls PWM1Low pin
 	IOCON2bits.PENL = 1;
 	IOCON1bits.POLH = 0; //PWMxH is active high
 	IOCON2bits.POLH = 0;
 	IOCON1bits.PMOD = 0b00; //PWM I/O pin is in the complementary output mode
 	IOCON2bits.PMOD = 0b00;
 	//De-comment this section to improve safety. Don't forget to disable over-ride in code, in order to turn-on PWM
 	/*	IOCON1bits.OVRDAT = 0; //Over-ride data on PWM output pin. In this case, output is off when overriden. At start-up, PWM will be off.
 I	OCON2bits.OVRDAT = 0;
 	IOCON3bits.OVRDAT = 0;
 	IOCON1bits.OVRENH = 1; //Enable over-ride (at start-up. Need to disable in order to run PWM
 	IOCON1bits.OVRENL = 1;
 	IOCON2bits.OVRENH = 1;
 	IOCON2bits.OVRENL = 1;
 	IOCON3bits.OVRENH = 1;
 	IOCON3bits.OVRENL = 1;
	 */
	 TRIG1bits.TRGCMP = 0; //Trigger ADC module immediately PWM starts without any delay. ***This value might need to be fine-tuned***
 
/*This sub-section configures the PWM pins as digital outputs*/
 	TRISAbits.TRISA3 = 0;	//PWM1L
 	TRISAbits.TRISA4 = 0; 	//PWM1H
 	TRISBbits.TRISB14 = 0;	//PWM2L
 	TRISBbits.TRISB13 = 0;	//PWM2H
/*End of sub-section*/

//Now we activate the PWM module
 	PTCONbits.PTEN = 1; //PWM activated
 	while(1){ //Dead loop.
 	}
 }