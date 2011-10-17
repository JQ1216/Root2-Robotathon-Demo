
#include "projectconfig.h"

#include "core/adc/adc.h"


void initIR(void){
	adcInit();
}

// 0, 1, 6, 7
short readIR(char port){
	return adcRead(port == 0 || port == 1 ? port : port+4);
}
