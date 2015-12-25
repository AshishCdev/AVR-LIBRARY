#ifndef AVR_ADC_H
#define AVR_ADC_H

/*
 * AVR_ADC.h
 *
 * Created: 4/1/2015 5:17:49 AM
 *  Author: Ashish kushwaha
 * Email: Ashish_kushwaha@outlook.com
 * Website:arm-tutorials.com
 */ 

// Channel selection
#define			A0			0
#define			A1			1
#define			A2			2
#define			A3			3
#define			A4			4
#define			A5			5
#define			A6			6
#define			A7			7
// ADC prescaler
#define			XTAl_2		1
#define			XTAl_4		2
#define			XTAl_8		3
#define			XTAl_16		4
#define			XTAl_32		5
#define			XTAl_64		6 
#define			XTAl_128	7
// Voltage reference
#define			Ext_pin		0
#define			AVCC_pin	1
#define			Intnl_2p56	3

//function definition
extern void ADC_ini(char chnl,char prscal,char V_ref); //Initializing for manual config

extern unsigned int Get_adc_auto(char chnl);  //Returns the ADC converted digital value with scaling factor of 128 from selected channel  

extern unsigned int Get_adc();	//Returns the digital value of configured ADC channel  

#endif //AVR_ADC.h