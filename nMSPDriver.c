/*
 * nMSPDriver.c
 *
 *  Created on: 21 mai 2017
 *      Author: AIT SAID
 */

#include "nMSPDriver.h"

uint16_t bit[] = { BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, BIT8, BIT9,
		BITA, BITB, BITC, BITD, BITE, BITF };
/*
void initClockDefaultMax(void) {
	if (CALBC1_16MHZ == 0xFF || CALDCO_16MHZ == 0xFF) {
		while (1)
			; // If cal constants erased,
	} // trap CPU!!

	// BCSCTL1 reg of DCO Calibration
	BCSCTL1 = CALBC1_16MHZ; // Set range
	DCOCTL = CALDCO_16MHZ; // Set DCO step + modulation

	BCSCTL3 |= LFXT1S_2; // clock system setup
	IFG1 &= ~OFIFG;
	// _bis_SR_register(SCG1 + SCG0);

	// Only MCLK specified,  if u need SMCLK u need to specify it
	BCSCTL2 |= SELM_0 + DIVM_0;   // DCOCLCK  +  DIV=1
}

void SetDirection(Port port, Pin pin, Direction dir) {
	if (port == PORT1) {
		P1SEL = bclr(P1SEL, pin);
		P1SEL2 = bclr(P1SEL2, pin);
		if (dir == INPUT) {
			P1DIR = bclr(P1DIR, pin);
			P1OUT = bset(P1OUT, pin);
			// PULL-UP
			P1REN = bset(P1REN, pin);
			// PULL_DOWN
			//P1REN = bclr(P1REN, pin);
		} else {
			P1DIR = bset(P1DIR, pin);

		}
	} else if (port == PORT2) {
		P2SEL = bclr(P2SEL, pin);
		P2SEL2 = bclr(P2SEL2, pin);
		if (dir == INPUT) {
			P2DIR = bclr(P2DIR, pin);
			P2OUT = bset(P2OUT, pin);
			// PULL-UP
			P2REN = bset(P2REN, pin);
			// PULL_DOWN
			//P2REN = bclr(P2REN, pin);
		} else {
			P2DIR = bset(P2DIR, pin);
		}

	}
}
*/
void PinStateWrite(Port port, Pin pin, PIN_State state) {
	if (port == PORT1) {
		if (state == HIGH)
			P1OUT = bset(P1OUT, pin);
		else
			P1OUT = bclr(P1OUT, pin);
	} else if (port == PORT2)
		if (state == HIGH)
			P2OUT = bset(P2OUT, pin);
		else
			P2OUT = bclr(P2OUT, pin);

}

PIN_State PinStateRead(Port port, Pin pin) {
	if (port == PORT1)
		return (P1IN & bit[pin] ? HIGH : LOW);
	else
		return (P2IN & bit[pin] ? HIGH : LOW);
}

uint8_t bset(uint8_t reg, Pin pin) {
	return (reg |= bit[pin]);

}

uint8_t bclr(uint8_t reg, Pin pin) {
	return (reg &= ~bit[pin]);
}

int sum(int A, int B)
{
	return (A+B);
}


/*void setBit(int reg, int bit, int state)
 {

 }
 */
