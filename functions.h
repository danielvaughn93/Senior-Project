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

void init_pwm(void);
void init_adc(void);
void start_PWM(void);
void dutycycle_fluc(void);
void init_timer1(void);
void init_timer2(void);
void init_comp(void);
void cycle_pwm(void);
void enableInterrupts(void);
void disableInterrupts(void);
void initInterrupts(void);
int nearestint(float i);