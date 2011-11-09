//#ifndef _ENCODER_H_
//#define _ENCODER_H_

#include "projectconfig.h"

typedef enum { ENCODER_0, ENCODER_1 } encoder_t;	// encoder data type
typedef signed long encoder_count_t;				// encoder count type
typedef enum { s_0, s_1, s_2, s_3 }  encoder_state_t;

void initEncoders( void );

void encoderDrive( encoder_t enc );

void encoderIntHandler( void );

signed long getEncoderValue( encoder_t enc );

//#endif
