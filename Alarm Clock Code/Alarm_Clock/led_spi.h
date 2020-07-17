#ifndef USCI_LED_SPI_H
#define USCI_LED_SPI_H

#include <msp430.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI A0 Master-In-Slave-Out (MISO) 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.1
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIA0_MISO_BIT1					BIT6 //P1.6
#define USCIA0_MISO_PORT1					P1IN
#define USCIA0_MISO_DDR1					P1DIR
#define SET_USCIA0_MISO_AS_AN_INPUT1		USCIA0_MISO_DDR1 &= ~USCIA0_MISO_BIT1
#define SET_MISO1							USCIA0_MISO_PORT1 |= USCIA0_MISO_BIT1
#define RESET_MISO1							USCIA0_MISO_PORT1 &= ~USCIA0_MISO_BIT1
#define MISO_VALUE1							(USCIA0_MISO_PORT1 & USCIA0_MISO_BIT1) >> 1

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI A0 Master-Out-Slave-In (MOSI) 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.2
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIA0_MOSI_BIT1					BIT7
#define USCIA0_MOSI_PORT1				P1OUT
#define USCIA0_MOSI_DDR1 				P1DIR
#define SET_USCIA0_MOSI_AS_AN_OUTPUT1	USCIA0_MOSI_DDR1 |= USCIA0_MOSI_BIT1
#define SET_MOSI1						USCIA0_MOSI_PORT1 |= USCIA0_MOSI_BIT1
#define RESET_MOSI1						USCIA0_MOSI_PORT1 &= ~USCIA0_MOSI_BIT1

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Slave Clock for GPIO Flash Memory Board
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.4
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define SPI_SCK_BIT1					BIT2
#define SPI_SCK_PORT1					P2OUT // SPI Slave Clock output
#define SPI_SCK_DDR1					P2DIR // SPI Slave Clock direction
#define SET_SPI_SCK_AS_AN_OUTPUT1		SPI_SCK_DDR1 |= SPI_SCK_BIT1
#define TOGGLE_SPI_SCK1					SPI_SCK_PORT1 ^= SPI_SCK_BIT1


/*
 * This function initializes all hardware and port pins to support SPI.
 */
void InitializeLEDSPI();

/*
 * This function sends the byte, SendValue, using SPI.
 */
void LEDSPISendByte(unsigned char SendValue);

/*
 * This function receives a byte using SPI.
 *
 * Return Value: The byte that is received over SPI.
 */
unsigned char LEDSPIReceiveByte();

#endif
