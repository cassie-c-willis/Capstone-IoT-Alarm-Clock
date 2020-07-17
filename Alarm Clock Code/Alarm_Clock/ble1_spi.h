#ifndef USCI_BLE_SPI_H
#define USCI_BLE_SPI_H

#include <msp430.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI A0 Master-In-Slave-Out (MISO) 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.1
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIA0_MISO_BIT					BIT6 //P2.6
#define USCIA0_MISO_PORT				P2IN
#define USCIA0_MISO_DDR					P2DIR
#define SET_USCIA0_MISO_AS_AN_INPUT		USCIA0_MISO_DDR &= ~USCIA0_MISO_BIT
#define SET_MISO						USCIA0_MISO_PORT |= USCIA0_MISO_BIT
#define RESET_MISO						USCIA0_MISO_PORT &= ~USCIA0_MISO_BIT
#define MISO_VALUE						(USCIA0_MISO_PORT & USCIA0_MISO_BIT) >> 1

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI A0 Master-Out-Slave-In (MOSI) 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.2
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIA0_MOSI_BIT					BIT5
#define USCIA0_MOSI_PORT				P2OUT
#define USCIA0_MOSI_DDR 				P2DIR
#define SET_USCIA0_MOSI_AS_AN_OUTPUT	USCIA0_MOSI_DDR |= USCIA0_MOSI_BIT
#define SET_MOSI						USCIA0_MOSI_PORT |= USCIA0_MOSI_BIT
#define RESET_MOSI						USCIA0_MOSI_PORT &= ~USCIA0_MOSI_BIT

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Slave Clock for GPIO Flash Memory Board
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.4
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define SPI_SCK_BIT					BIT4
#define SPI_SCK_PORT				P2OUT // SPI Slave Clock output
#define SPI_SCK_DDR					P2DIR // SPI Slave Clock direction
#define SET_SPI_SCK_AS_AN_OUTPUT	SPI_SCK_DDR |= SPI_SCK_BIT
#define TOGGLE_SPI_SCK				SPI_SCK_PORT ^= SPI_SCK_BIT


/*
 * This function initializes all hardware and port pins to support SPI.
 */
void InitializeBLE1SPI();

/*
 * This function sends the byte, SendValue, using SPI.
 */
void BLE1SPISendByte(unsigned char SendValue);

/*
 * This function receives a byte using SPI.
 *
 * Return Value: The byte that is received over SPI.
 */
unsigned char BLE1SPIReceiveByte();

#endif
