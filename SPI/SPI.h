/*
 * SPI.h
 *
 * Created: 7/25/2015 8:51:52 AM
 *  Author: Ashish Kushwaha
 * Email: ashish_kushwaha@outlook.com
 * Website: arm-tutorials.com
 */ 


#ifndef SPI_H_
#define SPI_H_

#define DD_MOSI DDB5
#define DDR_SPI DDRB
#define DD_MISO	DDB6
#define DD_SCK  DDB7

extern void SPI_MasterInit(void); //initializes master mode
extern void SPI_MasterTransmit(char cData);//transmits data in slave mode 
extern void SPI_SlaveInit(void);//initializes in slave mode
extern char SPI_SlaveReceive(void);//slave receives 1 byte at once 

#endif /* SPI_H_ */