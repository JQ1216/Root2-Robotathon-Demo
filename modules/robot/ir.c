
#include "projectconfig.h"
#include "sysinit.h"

#include "core/timer32/timer32.h"
#include "core/usbcdc/cdcuser.h"
#include "core/i2c/i2c.h"
#include "core/adc/adc.h"


void initIR(void){
	adcInit();
}

// 0, 1, 6, 7
short readIR(char port){
	return readAdc(port == 0 || port == 1 ? port : port+4);
}
