
#include "projectconfig.h"

#include "core/adc/adc.h"


void initIR(void){
	adcInit(0x01 || 0x02 || 0x40 || 0x08);
}

// 0, 1, 6, 7
short readIR(char port){
	return adcRead(port == 0 || port == 1 ? port : port+4);
}
