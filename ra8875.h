#ifndef RA8875_H
#define RA8875_H

//ra8875.h
//
//RA8875 TFT LCD Touchscreen library
//
//by Michael F. Cloutier
//developed at the University Of Maine
//Spring 2014
//
//contains all RA8875 functions for PIC24, 
//specifically for use with electronic lock system

//RA8875 registers, prefixed with "RA8875" so that we don't start accidentally
//writing to the PIC24 registers, there's a bit of overlap with the PIC24's
//header file, so we'll ere (is that how you spell that?) on the side of caution
#define RA8875_SYSR             0x10
#define RA8875_PCSR             0x04
#define RA8875_HDWR             0x14
#define RA8875_HNDR             0x16
#define RA8875_HSTR             0x17
#define RA8875_HPWR             0x18
#define RA8875_VDHR0            0x19
#define RA8875_VDHR1            0x1A
#define RA8875_VNDR0            0x1B
#define RA8875_VNDR1            0x1C
#define RA8875_VSTR0            0x1D
#define RA8875_VSTR1            0x1E
#define RA8875_VPWR             0x1F
#define RA8875_HSAW0            0x30
#define RA8875_HSAW1            0x31
#define RA8875_VSAW0            0x32
#define RA8875_VSAW1            0x33
#define RA8875_HEAW0            0x34
#define RA8875_HEAW1            0x35
#define RA8875_VEAW0            0x36
#define RA8875_VEAW1            0x37
#define RA8875_MCLR             0x8E
#define RA8875_PWRR             0x01
#define RA8875_GPIOX		0xC7
#define RA8875_P1CR 		0x8A
#define RA8875_P1DCR		0x8B
#define RA8875_DCR		0x90
#define RA8875_INTC1		0xF0
#define RA8875_INTC2		0xF1
#define RA8875_CURH0		0x2A
#define RA8875_CURH1		0x2B
#define RA8875_CURV0		0x2C
#define RA8875_CURV1		0x2D
#define RA8875_SROC		0x05
#define RA8875_SSAR0		0xB0
#define RA8875_SSAR1		0xB1
#define RA8875_SSAR2		0xB2
#define RA8875_DTNR0		0xB4
#define RA8875_DTNR1		0xB6
#define RA8875_DTNR2		0xB8
#define RA8875_DMACR		0xBF

//a few known colors so that we can draw stuff
#define	BLACK	0x0000
#define	BLUE	0x001F
#define	RED	    0xF800
#define	GREEN  	0x07E0
#define YELLOW	0xFFE0  
#define WHITE  	0xFFFF

//RA8875 touchscreen registers
#define TOUCH_TPCR0	0x70
#define TOUCH_TPCR1	0x71
#define TOUCH_TPXH	0x72
#define TOUCH_TPYH	0x73
#define TOUCH_TPXYL	0x74

//text sizes
#define TEXT_SIZE_SMALL	  55
#define TEXT_SIZE_NORMAL  56
#define TEXT_SIZE_LARGE   57

//these are values written to the RA8875 by the PIC24 (through SPI)
//so that we can write to and read from RA8875 register
#define WRITECOMMAND 0x80
#define READCOMMAND  0xC0
#define WRITEDATA    0x00
#define READDATA     0x40

void continue_int(int value, int size, unsigned int color);
void continue_text(char *text, int length, int size, unsigned int color);
void draw_circle(int x_center, int y_center, int radius, unsigned int color);
void display_text(char *text, int length, unsigned int start_x, unsigned int start_y, int size, unsigned int color);
void enable_touchscreen();
void disable_touchscreen();
void set_text_location(unsigned int x, unsigned int y);
void set_text_color(unsigned int foreground, unsigned int background);
void set_text_mode(void);
void set_background(unsigned int color);
void draw_rectangle(int x_start, int y_start, int x_end,  int y_end, unsigned int color, int fill_shape);
void setup_screen(void);
void reset_RA8875(void);
void write_command(unsigned char command);
void write_data(unsigned char data);
unsigned int read_register(unsigned int regnum);
void write_register(unsigned int regnum, unsigned int data);
void delay(int time);

void continue_int(int value, int size, unsigned int color)
{
	int digits;
	int i;
	char digit;

	digits = 10;
	//figure out how many digits are in the integer value
	for (i = 1000000000; i > 1; i = i / 10)
	{
		if ((value / i) >= 1)
			break;
		digits--; 
	}

	//display value to screen, one digit at a time
	for (i = 0; i < digits; i++)
	{
		//extract single digit from int value
		digit = (char) ((value / pow(10, (digits - i - 1))) + 48);
		continue_text(&digit, 1, size, color);
		//erase the digit from the int value, preparing for next extraction
		value = value - (((int) digit - 48) * pow(10, (digits - i -1)));
	}
}

void continue_text(char *text, int length, int size, unsigned int color)
{
	int i;
	unsigned int regval;

	set_text_mode();		  //let's go to text mode!
	set_text_color(color, BLACK);	  //set the color for our text
	if (size == TEXT_SIZE_SMALL)
		write_register(0x22, 0b00000001); //set the font small
	else if (size == TEXT_SIZE_NORMAL)
		write_register(0x22, 0b00000101); //set the font normal
	else if (size == TEXT_SIZE_LARGE)
		write_register(0x22, 0b00001010); //set the font large

	//draw the text
	for (i = 0; i < length; i++)
	{
		//draw a character
		write_register(0x02, text[i]);
	}

	regval = read_register(0x40);	  //get out of text mode
	write_register(0x40, regval & 0b01111111);
}

/* -function to draw an unfilled circle on the screeen using the RA8875's geometric pattern
 * drawing engine
 * -parameters are x and y coordinates of the circle's center, circle's radius, and its color,
 *  return nothing
 */
void draw_circle(int x_center, int y_center, int radius, unsigned int color)
{
	write_register(0x99, x_center);		//circle horizontal center point
	write_register(0x9A, x_center >> 8);	//(two register)
	write_register(0x9B, y_center);		//circle vertical center point
	write_register(0x9C, y_center >> 8);	//(two registers)
	write_register(0x9D, radius);		//circle radius
	write_register(0x63, (color & RED) >> 11);	//controls how much red the color has
	write_register(0x64, (color & GREEN) >> 5);	//controls how much green the color has
	write_register(0x65, color & BLUE);		//controls how much blue the color has
	write_register(RA8875_DCR, 0b01000000);	//now draw the circle, no fill

	//wait for drawing to finish
	/*while (1)
	{
		reg_return = read_register(RA8875_DCR);
		if ((reg_return & 0x40) == 0);
			break;
	}*/
	delay(25);
}

void display_text(char *text, int length, unsigned int start_x, unsigned int start_y, int size, unsigned int color)
{
	int i;
	unsigned int regval;

	set_text_mode();		  //let's go to text mode!
	set_text_color(color, BLACK);	  //set the color for our text
	set_text_location(start_x, start_y);      //set the cursor location for our text
	if (size == TEXT_SIZE_SMALL)
		write_register(0x22, 0b00000001); //set the font small
	else if (size == TEXT_SIZE_NORMAL)
		write_register(0x22, 0b00000101); //set the font normal
	else if (size == TEXT_SIZE_LARGE)
		write_register(0x22, 0b00001010); //set the font large

	//draw the text
	for (i = 0; i < length; i++)
	{
		//draw a character
		write_register(0x02, text[i]);
		delay(25);
	}

	regval = read_register(0x40);	  //get out of text mode
	write_register(0x40, regval & 0b01111111);
}

void enable_touchscreen(void)
{
	unsigned int regval;

	write_register(TOUCH_TPCR0, 0b10110010); //enable touchscreen, wait = 4096 clock cycles
	write_register(TOUCH_TPCR1, 0b00000100); //enable auto mode, enable debounce
	regval = read_register(RA8875_INTC1);
	write_register(RA8875_INTC1, regval | 0b00000100); //enable touch interrupt
}

void disable_touchscreen(void)
{
	unsigned int regval;

	write_register(TOUCH_TPCR0, 0b00000000); //disable touchscreen
	regval = read_register(RA8875_INTC1);
	write_register(RA8875_INTC1, regval & 0b11111011); //disable touch interrupt
}

void set_text_location(unsigned int x, unsigned int y)
{
	write_register(RA8875_CURH0, x);
	write_register(RA8875_CURH1, x >> 8);
	write_register(RA8875_CURV0, y);
	write_register(RA8875_CURV1, y >> 8);	
}

void set_text_color(unsigned int foreground, unsigned int background)
{
	write_register(0x63, (foreground & RED) >> 11);	//foreground color
	write_register(0x64, (foreground & GREEN) >> 5);
	write_register(0x65, foreground & BLUE);
	write_register(0x60, (background & RED) >> 11);	//background color
	write_register(0x61, (background & GREEN) >> 5);
	write_register(0x62, background & BLUE);
}

void set_text_mode(void)
{
	unsigned int regval;

	regval = read_register(0x40);		//text mode
	write_register(0x40, regval | 0b10000000);
	write_register(0x21, 0b00000000);	//CGROM selected, ISO/IEC 8859-1
}

/* -draws a filled rectangle covering the entire screen which acts as a "background"
 * for the current menu or text display
 * -paramter is the color of the filled rectangle, returns nothing
 */
void set_background(unsigned int color)
{
	//draw a filled rectangled of the desired color covering the entire screen
	draw_rectangle(1, 1, 799, 479, color, 1);
	delay(25);
}

/* -draws a rectange (either filled or unfilled) on the screen.  Makes used of
 * the RA8875's geometric pattern drawing engine
 * -parameters are x and y start coordinates (top left corner of rectangle), x and y
 *  end coordinateds (bottom right corner of rectangle), the color of the rectangle,
 *  and whether or not to fill it (1 to fill, anything else (0), to not fill)
 * -returns nothing
 */
void draw_rectangle(int x_start, int y_start, int x_end,  int y_end, unsigned int color, int fill_shape)
{
	//set the starting point of the rectangle
 	write_register(0x91, x_start);	//horizontal start
	write_register(0x92, x_start >> 8);
	write_register(0x93, y_start);	//vertical start
	write_register(0x94, y_start >> 8);
	//set the ending point of the rectangle
	write_register(0x95, x_end);	//horizontal end
	write_register(0x96, x_end >> 8);
	write_register(0x97, y_end);	//vertical end
	write_register(0x98, y_end >> 8);
	//set the color
	write_register(0x63, (color & RED) >> 11);	//controls how much red the color has
	write_register(0x64, (color & GREEN) >> 5);	//controls how much green the color has
	write_register(0x65, color & BLUE);		//controls how much blue the color has
	if (fill_shape == 1)
		write_register(RA8875_DCR, 0b10110000); //draw rectangle, fill on
	else
		write_register(RA8875_DCR, 0b10010000);	//draw rectangle, fill off

	delay(25);
}

/* -performs all necessary initializations for the RA8875.  This includes color depth,
 * horizontal and vertical settings, active window settings, pixel clock.  Most of the value
 * were chosen using suggestions from the datasheet.
 * -this function is usually called when SPI1 is running at a lower clock speed
 * -no parameters, returns nothing
 */
void setup_screen(void)
{
	unsigned char pulse = 255;

  	//set the pixel clock, data fetched on falling edge
	//clock period is twice that of the system clock	
	write_register(RA8875_PCSR, 0b10000001);
	delay(1);	//give the pixel clock some time after configuration,
			//other things can happen too fast and the display gets fudged

	//system configuration register, 65K colors (WOW!) and MCU SPI is 8-bit	
	write_register(RA8875_SYSR, 0b00001000);

  	//set up the LCD screen, most instruction are written in the order in 
	//which the registers are listed in the RA8875 datasheet
 	//WE WILL CONTROL THE HORIZONTAL.  WE WILL CONTROL THE VERTICAL.....

 	//horizontal settings for LCD screen
	//set the size of the width, for our screen it's 800 pixels
	//total width is value in (HDWR + 1) * 8
  	write_register(RA8875_HDWR, 100);
	//set the horizontal starting position
  	write_register(RA8875_HSTR, 1);
       	//set the horizontal pulse width, for now give it a conservative value	
  	write_register(RA8875_HPWR, 11);
  
 	//vertical settings for LCD screen
	//set the vertical height (this is split up into two registers)
  	write_register(RA8875_VDHR0, (479 - 1) & 0xFF);
	//this one goes in the LSB of register VDHR1
  	write_register(RA8875_VDHR1, (479 - 1) >> 8);
	//set the vertical blanking, again it's split into two registers
  	write_register(RA8875_VNDR0, 31);
  	//this one goes in the LSB of register VDHR1
  	write_register(RA8875_VNDR1, 31 >> 8);
	//set the vertical starting position (two registers)
  	write_register(RA8875_VSTR0, 31);
  	write_register(RA8875_VSTR1, 32 >> 8);
  	//set the vertical pulse width
  	write_register(RA8875_VPWR, 1);

  	//set the horizontal start and end points for our active window
  	write_register(RA8875_HSAW0, 0);	//starting point (two registers)
  	write_register(RA8875_HSAW1, 0);
  	write_register(RA8875_HEAW0, (800 - 1) & 0xFF);	///end point (two registers)
  	write_register(RA8875_HEAW1, (800 - 1) >> 8);
  
 	//set the vertical start and end points for our active window
	write_register(RA8875_VSAW0, 0);	//starting point (two registers)
 	write_register(RA8875_VSAW1, 0);  
  	write_register(RA8875_VEAW0, (480 - 1) & 0xFF);  //end point (two registers)
  	write_register(RA8875_VEAW1, (480 - 1) >> 8);
  
  	//clear the entire window, we're done initializing!  YAY!!!!
  	write_register(RA8875_MCLR, 0b10000000);
  	delay(1);	//I don't know, it seemed like a good idea at the time
/*
  	//change SCK frequency to 1 MHz
  	SPI1STATbits.SPIEN = 0;	//clear SPIEN bit to modify SPI1CON1
  	SPI1CON1bits.SPRE2 = 1; //secondary prescale 4:1
  	SPI1CON1bits.SPRE1 = 0;
  	SPI1CON1bits.SPRE0 = 0;
  	SPI1CON1bits.PPRE1 = 1;	//primary prescale 4:1
  	SPI1CON1bits.PPRE0 = 0;
  	SPI1STATbits.SPIEN = 1;	//set SPIEN bit to enable SPI
*/
  	//give the PIC24 some time to reconfigure SCK before firing out data
	delay(1);

  	write_register(RA8875_PWRR, 0b10000000); //turn on LCD display
  	write_register(RA8875_GPIOX, 1);  	 //GPIOX on
  	write_register(RA8875_P1CR, 0x80 | (0x0A & 0x0F));	//PWM configuration
  	write_register(RA8875_P1DCR, pulse);
}

/* -reads a value from an RA8875 register
 * -parameter is the RA8875 register you want to read, returns whatever is in that
 *  register
 */
unsigned int read_register(unsigned int regnum)
{
	volatile unsigned int spi_return;

	//read data from register
	_RB3 = 0;			//set CS low, starting communication with slave
	spi_write(WRITECOMMAND);	//we are sending a command
	spi_write(regnum);		//register to command is 0x00
	_RB3 = 1;			//done with this communication

	_RB3 = 0;			//set CS low, starting communication with slave
	spi_write(READDATA);		//we are reading data
	spi_return = spi_write(0x00);	//dummy send to read data from register 0x00
	_RB3 = 1;			//done with this communication

	return spi_return;
}

/* -writes a value to an RA8875 register
 * -parameters are the RA8875 register to which you want to write, and what you want
 *  to write to that specific register, returns nothing
 */
void write_register(unsigned int regnum, unsigned int data)
{
	//write data to register
	_RB3 = 0;			//set CS low, starting communication with slave
	spi_write(WRITECOMMAND);	//we are sending a command
	spi_write(regnum);		//register to command
	_RB3 = 1;			//done with this communication

	_RB3 = 0;			//set CS low, starting communication with slave
	spi_write(WRITEDATA);		//we are writing data
	spi_write(data);		//write data to register
	_RB3 = 1;			//done with this communication
}

/* -sends a given command to an RA8875 register with no data.  Not used very often, it's
 * incorporated into write_register
 * -parameter is the command to send, returns nothing
 */
void write_command(unsigned char command)
{
	_RB3 = 0;			//set CS low, starting communication with slave
	spi_write(WRITECOMMAND);	//we are sending a command
	spi_write(command);		//send command
	_RB3 = 1;			//done with this communication
}

/* -writes given data to an RA8875 register, assuming you have already told the RA8875
 * that you want to write to a register (see write_command).  This isn't used very often,
 * it's incorporated into write_register
 * -paramter is the data to write, returns nothing
 */
void write_data(unsigned char data)
{
	_RB3 = 0;			//set CS low, starting communication with slave
	spi_write(WRITEDATA);		//we are writing data
	spi_write(data);		//write data
	_RB3 = 1;			//done with this communication
}

void delay(int time)
{
	__delay_ms(time);
}

#endif
