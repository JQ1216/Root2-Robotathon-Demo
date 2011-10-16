
/* begin encoder code */
/* Move typedefs into header when sorting code 
 * Also recommending same typedef style for all other aspects of this project */
typedef enum { ENCODER_0, ENCODER_1 } encoder_t;	// encoder data type
typedef signed long encoder_count_t;				// encoder count type
typedef enum { s_0, s_1, s_2, s_3 }  encoder_state_t;
const int enc_Machine[4][4] = { { 0 , 1 , -1 , 0 } , {-1 , 0 , 0 , 1 } , { 1 , 0 , 0 , -1 } , { 0 , -1 , 1 , 0 } }; 
volatile static encoder_count_t enc_0, enc_1;
volatile static encoder_state_t enc_state[2];
          
void initEncoders(void);

void encoderDrive( encoder_t enc );

void encoderIntHandler(void);

signed long getEncoderValue(encoder_t enc);
