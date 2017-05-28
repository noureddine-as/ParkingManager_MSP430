#include "nMSPDriver.h"


#define 	VEHICLE_ENTER	BIT1
#define		VEHICLE_EXIT	BIT1
#define		MOTOR_CMD		BIT0

#define		LED1			BIT5
#define		LED2			BIT7

#define		SECOND			1000000

int nbr_vehicles = 0;

void configLEDS(void);
void actionBarrier(void);
void initEnterSensor(void);
void initExitSensor(void);
void initMotor(void)
;

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; // watchdog timer setup

	initEnterSensor();
	initExitSensor();
	initMotor();

	__enable_interrupt();


	while(1)
	{

	}

}

void configLEDS(void)
{
	P1DIR |= LED1;
	P1OUT &= ~LED1;

	P4DIR |= LED2;
	P4OUT &= ~LED2;
}

void initMotor(void)
{
	// Config MOTOR_CMD  (output, init to 0)
	P1DIR |= MOTOR_CMD;
	P1OUT &= ~MOTOR_CMD;
}

void initEnterSensor(void)
{
	// Configure VEHICLE_ENTER
	P1DIR &= ~VEHICLE_ENTER;
	P1REN |= VEHICLE_ENTER; // Enable Pullup/Pulldown
	P1OUT = VEHICLE_ENTER; // pullup
	P1IE |= VEHICLE_ENTER; // interrupt enabled
	P1IES |= VEHICLE_ENTER; // High to low falling edge
	P1IFG &= ~VEHICLE_ENTER; // IFG cleared just in case
}

void initExitSensor(void)
{
	// Configure VEHICLE_EXIT
	P2DIR &= ~VEHICLE_EXIT;
	P2REN |= VEHICLE_EXIT; // Enable Pullup/Pulldown
	P2OUT = VEHICLE_EXIT; // pullup
	P2IE |= VEHICLE_EXIT; // interrupt enabled
	P2IES |= VEHICLE_EXIT; // High to low falling edge
	P2IFG &= ~VEHICLE_EXIT; // IFG cleared just in case
}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	nbr_vehicles++;

	// action the barrier
	actionBarrier();  // WARNING

	P1IFG &= ~VEHICLE_ENTER; // P1.1 IFG cleared
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	nbr_vehicles--;

	// Action the barrier
  	actionBarrier();  // WARNING

	P2IFG &= ~VEHICLE_EXIT; // P1.1 IFG cleared
}


/*
 *   WARNING : NOT TO BE USED IN AN INTERRUPT HANDLER
 */
void actionBarrier(void)
{
	P1OUT |= MOTOR_CMD;
	__delay_cycles(SECOND);
	P1OUT &= ~MOTOR_CMD;

}

