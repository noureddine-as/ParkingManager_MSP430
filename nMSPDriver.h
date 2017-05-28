#ifndef __N_MSP_DRIVER__
#define __N_MSP_DRIVER__


#ifdef __cplusplus
extern "C" {
#endif

#include <msp430.h>
#include <stdint.h>

typedef enum
{
	false = 0x00,
	true = 0x01
}bool;

typedef enum
{
	INPUT  = 0x00,
	OUTPUT = 0x01
}Direction;

typedef enum
{
	PORT1	= 1,
	PORT2   = 2
}Port;

typedef enum
{
	LOW = 0x00,
	HIGH = 0x01
}PIN_State;

typedef uint8_t Pin;


//typedef int Port;

/*
 * 16 Mhz at MCLK
 * DCOCLK -> as MCLK
 * Only MCLK specified,  if u need SMCLK u need to specify it
 */
//void initClockDefaultMax(void);

/*
 * Disables Interruption because it also sets the PxSEL and PxSEL2 registers
 */
//void SetDirection(Port port, Pin pin, Direction dir);
void PinStateWrite(Port port, Pin pin, PIN_State state);
PIN_State PinStateRead(Port port, Pin pin);

uint8_t bset(uint8_t reg, Pin pin);
uint8_t bclr(uint8_t reg, Pin pin);

int sum(int A, int B);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __N_MSP_DRIVER__ */
