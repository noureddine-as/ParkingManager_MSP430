#include "nMSPDriver.h"


#define 	VEHICLE_ENTER	BIT3
#define		VEHICLE_EXIT	BIT1
#define		MOTOR_CMD		BIT0
/*
//// parameters for msp430 F5529
 *
#define		LED1			BIT5
#define		LED2			BIT7
*/

// parameters for msp430 G2553
#define		LED1			BIT0
#define		LED2			BIT6

#define		SECOND			1000000

int nbr_vehicles = 0;

void actionBarrier(void);
void initEnterSensor(void);
void initExitSensor(void);
void initMotor(void);

void ConfigTimerA2(void);

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; // watchdog timer setup

	initEnterSensor();
	initExitSensor();
	initMotor();

	// enable general interruptions GIE (the 2 buttons with the Timers also)
	__enable_interrupt();


	while(1)
	{

	}

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
	P1OUT |= MOTOR_CMD;
	ConfigTimerA2(); // Launch the timer A2

	P1IFG &= ~VEHICLE_ENTER; // P1.1 IFG cleared
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	nbr_vehicles--;

	// Action the barrier
	P1OUT |= MOTOR_CMD;
	ConfigTimerA2(); // Launch the timer A2

	P2IFG &= ~VEHICLE_EXIT; // P1.1 IFG cleared
}


/*
 * Sets Up the Timer A2
 */
void ConfigTimerA2(void) {
	//This enables the counter/compare register 0 interrupt in the CCTL0 capture/compare
	CCTL0 = CCIE;
	CCR0 = 12000; // cz w're working with the VLO = 12kHz frequency
	TACTL = TASSEL_1 + MC_1; // select ACLK auxiliary clock (VLO) in Continuous mode: the timer counts up to 0FFFFh.
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
	P1OUT &= ~MOTOR_CMD;
	CCTL0 = ~CCIE;
}


