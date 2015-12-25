/*
 * SPI.c
 *
 * Created: 7/25/2015 8:51:52 AM
 *  Author: Ashish Kushwaha
 * Email: ashish_kushwaha@outlook.com
 * Website: arm-tutorials.com
 */

#include <avr/io.h>
#include "SPI.h"

void SPI_MasterInit(void)
{
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);//Set MOSI and SCK output, all others input 
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);// Enable SPI, Master, set clock rate fck/16 
	
}
void SPI_SlaveInit(void)
{
	DDR_SPI = (1<<DD_MISO);// Set MISO output, all others input 
	SPCR = (1<<SPE);// Enable SPI 
}

char SPI_SlaveReceive(void)
{
	while(!(SPSR & (1<<SPIF)));// Wait for reception complete 
	return SPDR;// Return data register 
}

void SPI_MasterTransmit(char cData)
{
	SPDR = cData;// Start transmission 
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete 
}
