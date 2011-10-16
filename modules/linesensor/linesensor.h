#define ADS7830 (0x48 << 1)

void initLineSensor( void );

void clearI2CBuffer( void );

int readLineSensor( short data[] );
