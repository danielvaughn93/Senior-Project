//Daniel Vaughn
//Harrison Goodhue



#include "functions.h"
#include "spi.h"
#include "ra8875.h"

//Select internal FRC at POR
 _FOSCSEL(FNOSC_FRC);
 //Enable clock switching
 _FOSC(FCKSM_CSECMD & OSCIOFNC_OFF); 	//Clock switching mode enabled and fail safe clock monitor disabled & OSCO is general purpose IO pin
 _FWDT(FWDTEN_OFF); //Watchdog timer disabled
 _FPOR(FPWRT_PWR128); //Power-on reset timer is set to 128ms 
 _FICD(ICS_PGD2 & JTAGEN_OFF); //Use PGD2 and PGC2 for ICS & JTAG disabled

 //Main function
int main(void){
	int SLT[360];
	unsigned int regval = 0;
	float angle;
	int i;
	for(i=0;i<360;i++){
		angle = ((float)i);
		SLT[i]=nearestint((100+99*sin(angle*(PI/180))));
	}

	TRISA = 0x0004; //Set Porta[2] to input
	TRISB = 0b0000000000010000; //Set PortB to output, except RB4
	blink_led(5);

//SCREEN CODE!////
	_RA0 = 0; 	//error LED off
	_RB3 = 1;	//start with SS1 high, RA8875 disabled as slave
	spi_init();	//set up the SPI1 module on the DSPIC33

	//check to see if we can communicate with the RA8875
	while (1)
	{	
		regval = read_register(0);	
		if (regval != 0x75)	//something's wrong, we can't read from the RA8875
			_RA0 = 1;	//light up RA8875 communication error LED
		else if (regval == 0x75)
		{
			break;
		}
	}

	setup_screen();		//RA8875 is on, initialize everything

	set_background(BLUE);

	display_text("I just want these goddamn interrupts to work", 44, 100, 100, TEXT_SIZE_SMALL, WHITE);

//END SCREEN CODE!


 /* Configure Oscillator to operate the device at 40Mhz
	   Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
 	   Fosc= 7.37*(43)/(2*2)=80Mhz for Fosc, Fcy = 40Mhz */
/* Configure PLL prescaler, PLL postscaler, PLL divisor */
	PLLFBD=41; 				/* M = PLLFBD + 2 */
	CLKDIVbits.PLLPOST=0;   /* N1 = 2 */
	CLKDIVbits.PLLPRE=0;    /* N2 = 2 */
	__builtin_write_OSCCONH(0x01);			/* New Oscillator FRC w/ PLL */
	__builtin_write_OSCCONL(0x01);  		/* Enable Switch */
	while(OSCCONbits.COSC != 0b001);		/* Wait for new Oscillator to become FRC w/ PLL */ 
	while(OSCCONbits.LOCK != 1);			/* Wait for Pll to Lock */
	/* Now setup the ADC and PWM clock for 120MHz
	   ((FRC * 16) / APSTSCLR ) = (7.37 * 16) / 1 = ~ 120MHz*/

	ACLKCONbits.FRCSEL = 1;					/* FRC provides input for Auxiliary PLL (x16) */
	ACLKCONbits.SELACLK = 1;				/* Auxiliary Oscillator provides clock source for PWM & ADC */
	ACLKCONbits.APSTSCLR = 7;				/* Divide Auxiliary clock by 1 */
	ACLKCONbits.ENAPLL = 1;					/* Enable Auxiliary PLL */
	
	while(ACLKCONbits.APLLCK != 1);			/* Wait for Auxiliary PLL to Lock */

	init_timer1();
	init_timer2();
	enableInterrupts();
	initInterrupts();

	while(1);

	init_pwm();
	IOCON1bits.PENL = 0;
	IOCON1bits.PENH = 0;
	IOCON2bits.PENL = 0;
	IOCON2bits.PENH = 0;
	IOCON3bits.PENL = 0;
	IOCON3bits.PENH = 0;
	__delay_us(100);

	while(1){
	//	blink_led(5);
		//IOCON1bits.PENH = 0;
		IOCON2bits.PENL = 1;
		//IOCON3bits.PENH = 1;	
		__delay_us(166);
		IOCON2bits.PENL = 0;		
		//IOCON1bits.PENL = 1;
		__delay_us(166);
		//IOCON3bits.PENH = 0;		
		IOCON2bits.PENH = 1;
		__delay_us(166);
		//IOCON3bits.PENL = 1;		
		//IOCON1bits.PENL = 0;
		__delay_us(166);
		IOCON2bits.PENH = 0;		
		//IOCON1bits.PENH = 1;
		__delay_us(166);
		IOCON2bits.PENL = 1;		
		//IOCON3bits.PENL = 0;
		__delay_us(166);
	}

}
