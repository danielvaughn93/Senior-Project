//Daniel Vaughn
//funtions.h
// File to declare the functions to be used in the motor control project
//
//
//Developed at the University of Maine
//Fall 2014
//
//This file contains the declarations of the functions to initialize
// the modules, such as the Analog to Digital Converter(ADC), Timer1, and Timer2.
//It also contains various stages of functions from the development process/ programs
// that were used to test different parts of the code throughout the development.

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <p33FJ16GS502.h>
#include <math.h>
#include <stddef.h>
#include <float.h>
#include <stdlib.h>
#include <delay.h>
#include <stdio.h>
#include <xc.h>
#define FCY (3685000UL) // for delay routines
#define PI 3.14159265359
#include <libpic30.h>



void blink_led(int numblinks);
void blink_led2(int numblinks);

void sin_pwm(int period);

void init_pwm(void);
void init_adc(void);
void start_PWM(void);
void dutycycle_fluc(void);
void init_timer1(void);
void init_timer2(void);
void init_comp(void);
void cycle_pwm(void);
void enable_interrupts(void);
void disable_interrupts(void);
void init_interrupts(void);
int nearestint(float i);
void square_pwm(int freq);
void test_dcmotor(void);

#endif