
#include "projectconfig.h"
#include "sysinit.h"

#include "core/timer32/timer32.h"
#include "core/usbcdc/cdcuser.h"
#include "core/i2c/i2c.h"
#include "core/adc/adc.h"


/* begin encoder code */
/* Move typedefs into header when sorting code 
 * Also recommending same typedef style for all other aspects of this project */
typedef enum { ENCODER_0, ENCODER_1 } encoder_t;	// encoder data type
typedef signed long encoder_count_t;				// encoder count type
typedef enum { s_0, s_1, s_2, s_3 }  encoder_state_t;
const int enc_Machine[4][4] = { { 0 , 1 , -1 , 0 } , {-1 , 0 , 0 , 1 } , { 1 , 0 , 0 , -1 } , { 0 , -1 , 1 , 0 } }; 
volatile static encoder_count_t enc_0, enc_1;
volatile static encoder_state_t enc_state[2];
          
void initEncoders(void) {
	/*written as psedocode until actual values can be set*/
	/* Configure Encoder Pins 3 block (4 pins) as input */
	
	/***  <THIS CODE IS STALLING THE uC!>  ***/
	enc_state[0] = s_0 ;
	enc_state[1] = s_0 ;
	enc_0 = 0;
	enc_1 = 0;
	/***  </THIS CODE IS STALLING THE uC!>  ***/
	
	//gpioInit();	// Already initialized in cpuInit() (yeah, strange.)
	gpioSetDir(3, 0, gpioDirection_Input);
	gpioSetDir(3, 1, gpioDirection_Input);
	gpioSetDir(3, 2, gpioDirection_Input);
	gpioSetDir(3, 3, gpioDirection_Input);
	
	// Disable Internal pullups
	gpioSetPullup(&IOCON_PIO3_0, gpioPullupMode_Inactive);
	gpioSetPullup(&IOCON_PIO3_1, gpioPullupMode_Inactive);
	gpioSetPullup(&IOCON_PIO3_2, gpioPullupMode_Inactive);
	gpioSetPullup(&IOCON_PIO3_3, gpioPullupMode_Inactive);
	
	// Enable interupts on A pins
	gpioSetInterrupt(3, 0, gpioInterruptSense_Edge, gpioInterruptEdge_Double, gpioInterruptEvent_ActiveHigh);
	gpioSetInterrupt(3, 1, gpioInterruptSense_Edge, gpioInterruptEdge_Double, gpioInterruptEvent_ActiveHigh);
	gpioSetInterrupt(3, 2, gpioInterruptSense_Edge, gpioInterruptEdge_Double, gpioInterruptEvent_ActiveHigh);
	gpioSetInterrupt(3, 3, gpioInterruptSense_Edge, gpioInterruptEdge_Double, gpioInterruptEvent_ActiveHigh);
	
	// Enable Interrupts
	gpioIntEnable(3, 0);
	gpioIntEnable(3, 1);	
	gpioIntEnable(3, 2);
	gpioIntEnable(3, 3);
}

void encoderDrive( encoder_t enc )
{
	int nextState;
	if (enc == ENCODER_0)
	{
		nextState = (((gpioGetValue(3,0) != 0) << 1 ) + (gpioGetValue(3,1) != 0));
		enc_0 += enc_Machine[enc_state[0]][ nextState ];
		enc_state[0] = nextState;
	} 
	else if (enc == ENCODER_1)
	{
		nextState = (((gpioGetValue(3,2) != 0) << 1 ) + (gpioGetValue(3,3) != 0));
		enc_1 += enc_Machine[enc_state[1]][ nextState ];
		enc_state[1] = nextState;
	} 
}

void encoderIntHandler(void){
	//printf("interrupt fire!");
  if ( gpioIntStatus(3, 0) ){
	  encoderDrive( ENCODER_0 );
	  gpioIntClear(3, 0);
  }else if ( gpioIntStatus(3, 1) ){
	  encoderDrive( ENCODER_0 );
	  gpioIntClear(3, 1);
  }else if ( gpioIntStatus(3, 2) ){
	  encoderDrive( ENCODER_1 );
	  gpioIntClear(3, 2);
  }else if ( gpioIntStatus(3, 3) ){
	  encoderDrive( ENCODER_1 );
	  gpioIntClear(3, 3);
  }
  return;
}

signed long getEncoderValue(encoder_t enc){	return enc ? enc_1 : enc_0; }