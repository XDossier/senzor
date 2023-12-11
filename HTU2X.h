#ifndef HTU2X_H 
#define HTU2X_H

#include "mbed.h"

//#include "HTU2X_registers.h"

class HTU2X {

public:

void init(); 
float tempc(); 
float tempf(); 
float tempk();

float get_humidity(); 
void soft_reset();

};

#endif