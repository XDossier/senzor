#include "HTU2X.h" 
#ifndef HTU2X_H
#define HTU2X_H
I2C i2c(PB_8, PB_9);

void HTU2X::init(){

char data_to_send[0]; i2c.frequency(400000);

wait_us(10000);

data_to_send[0]= HTU2X_SOFT_RESET; i2c.write((HTU2X_I2C_ADDRESS << 1) & 0xF3, data_to_send, 1); wait_us(10000);

}

float HTU2X::tempc(){ char data_to_send[1]; char data_to_read[2];

data_to_send[0] = HTU2X_TRIGGER_TEMP_MEASURE; i2c.write((HTU2X_I2C_ADDRESS << 1) & 0xF3, data_to_send, 1); wait_us(10000);

i2c.read((HTU2X_I2C_ADDRESS << 1) | 0x01, data_to_read, 2); wait_us(10000);

unsigned int rawTemperature = ((unsigned int) data_to_read[0] << 8) | (unsigned int) data_to_read[1]; //spajanje MSB i LSB da dobijemo raw podatak

rawTemperature &= 0xFFFC; //datasheet zadnja dva bita nula

float tem =175.72 * rawTemperature / 65536 - 46.85; return tem;

}

float HTU2X::tempf(){

int temptemp = tempc();

int ftemp = temptemp * 1.8 + 32; return ftemp;

}

float HTU2X::tempk(){

int temptemp = tempc();

int ktemp = temptemp + 274; return ktemp;

}

float HTU2X::get_humidity(){ char data_to_send[1]; char data_to_read[2];

data_to_send[0] = HTU2X_TRIGGER_HUMD_MEASURE; i2c.write((HTU2X_I2C_ADDRESS << 1) & 0xFE, data_to_send, 1); wait_us(10000);

i2c.read((HTU2X_I2C_ADDRESS << 1) | 0x01, data_to_read, 2);

//wait_us(10000);

unsigned int rawHumidity = ((unsigned int) data_to_read[0] << 8) | (unsigned int) data_to_read[1];

rawHumidity &= 0xFFFC;

float tempRH = rawHumidity / (float)65536;

float rh = -6 + (125 * tempRH);

return rh;

}

void HTU2X::soft_reset(){ char data_to_send[1];

wait_us(7000);

data_to_send[0]= HTU2X_SOFT_RESET;

i2c.write((HTU2X_I2C_ADDRESS << 1) & 0xFE, data_to_send, 1, false); wait_us(7000);

}
#endif // HTU2X_H