//Daniel Vaughn
//spi.h
//dsPIC33fj16GS502
//
//This file contains functions that interact over SPI lines

#ifndef SPI_H_
#define SPI_H_

volatile unsigned int spi_write(unsigned int data){
	SPI1BUF = data;	//transmit data on SPI
	while (SPI1STATbits.SPIRBF == 0);	//wait for transmit to finish
	return SPI1BUF;	//return whatever was sent back to us
}

void spi_init(void){
	//unlock registers so that we can map SDI, SDO, SCK, and SS to RP pins
	OSCCON = OSCCON & 0b1111111101000110;
	OSCCON = OSCCON & 0b1111111101010111;
	OSCCON = OSCCON & 0b1111111110111111;	//clear IOLOCK
	RPINR20bits.SDI1R = 4;			//configure SDI1 as RP4
	RPOR0bits.RP1R = 7;			//configure SDO1 as RP1
	RPOR2bits.RP5R = 8;			//configure SCK1 as RP5
	RPOR1bits.RP3R = 9;			//configure SS1 as RP3	
	//lock registers
	OSCCON = OSCCON & 0b1111111101000110;
	OSCCON = OSCCON & 0b1111111101010111;
	//set IOLOCK
	OSCCON = OSCCON | 0b0000000001000000;

	SPI1BUF = 0;	//clear the SPI buffer

	IFS0bits.SPI1IF = 0;	//clear SPI interrupt flag
	IEC0bits.SPI1IE = 0;	//Disable SPI interrupts

	//congigure SPICON1
	SPI1CON1bits.DISSCK = 0;	//enable internal serial clock
	SPI1CON1bits.DISSDO = 0;	//SDO1 pin is controlled by SPI module
	SPI1CON1bits.MODE16 = 0;	//communication is 8 bits wide
	SPI1CON1bits.SMP = 0;		//input data sampled at middle of data output
	SPI1CON1bits.CKE = 0;		//serial output data changes on transition
	SPI1CON1bits.CKP = 0;		//clock is active high
	SPI1CON1bits.MSTEN = 1;		//master mode enabled
/*	
	//sck frequency = 125kHz
	SPI1CON1bits.SPRE2 = 0; 	//secondary prescale 1:1
	SPI1CON1bits.SPRE1 = 0;
	SPI1CON1bits.SPRE0 = 0;
	SPI1CON1bits.PPRE1 = 0;		//primary prescale 4:1
	SPI1CON1bits.PPRE0 = 1;
*/
	SPI1STATbits.SPIROV = 0;	//clear SPIROV bit
	SPI1STATbits.SPIEN = 1;		//enable SPI module, let's do this!!!
}	

#endif