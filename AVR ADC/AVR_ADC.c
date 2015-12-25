
/*
 * AVR_ADC.c
 *
 * Created: 4/1/2015 5:17:49 AM
 *  Author: Ashish kushwaha
 * Email: Ashish_kushwaha@outlook.com
 * Website:arm-tutorials.com
 */ 

#include <avr/io.h>
#include "AVR_ADC.h"

void ADC_ini(char chnl,char prscal,char V_ref){
	ADMUX=((prscal<<6)|chnl);
	ADCSRA=((1<<ADEN)|prscal);
}

unsigned int Get_adc_auto(char chnl){ 
	ADC_ini(chnl,XTAl_128,Intnl_2p56);
	ADCSRA|=(1<<ADSC);
	while ((ADCSRA&(1<<ADIF))==0);
	return ADC;
} 

unsigned int Get_adc(void){
	ADCSRA|=(1<<ADSC);
	while ((ADCSRA&(1<<ADIF))==0);
	return ADC;
}

	


