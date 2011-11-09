#include "projectconfig.h"
#include "core/i2c/i2c.h"

#include "linesensor.h"

void initLineSensor()
{
	i2cInit(I2CMASTER);
	clearI2CBuffer();
}

void clearI2CBuffer()
{
	int i;
	for(i=0; i<I2C_BUFSIZE; i++)
	{
		I2CMasterBuffer[i] = 0;
		I2CSlaveBuffer[i] = 0;
	}
}

// Grabs line sensor data using i2c and dumps into LineSensor array. 
// Returns 1 if successful, 0 if encountered a timeout error 
//	(timeout probably means the line sensor isn't connected correctly)
int readLineSensor(char data[])
{
	int i;
	char cmd = 0x84; //1 CH# 01 XX for request conversion. e.g 1 000 01 00 is for channel 2
	
	for(i=0; i<I2C_BUFSIZE; i++)
	{
		I2CWriteLength = 2;
		I2CReadLength = 1;
		I2CMasterBuffer[0] = ADS7830;
		I2CMasterBuffer[1] = cmd; 
		I2CMasterBuffer[2] = ADS7830 | 1;
		
		cmd += 0x10;	// Increment Channel to read
		
		if (i2cEngine() > MAX_TIMEOUT)	// Run I2C sensor
		{	
			return 0;
		}
		data[i] = I2CSlaveBuffer[0]; //sadly after each transaction the RdIndex is returned to 0, could change i2c driver...
	} 
	
	// Clean the buffer after use
	clearI2CBuffer();
	
	return 1;
}