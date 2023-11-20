#include "mbed.h"
#include "HTU21D.h"

HTU21D senzor(PB_9, PB_8);
Serial pc(USBRX, USBTX);

float sample_ftemp;
float sample_ctemp;
float sample_ktemp;
float sample_humid;

int main() {
    
    while(1) {
        sample_ftemp = senzor.sample_ftemp();
        sample_ctemp = senzor.sample_ctemp();
        sample_ktemp = senzor.sample_ktemp();
        sample_humid = senzor.sample_humid();
        //pc.printf("Hello world! \n\r");
        pc.printf("Temperatura: %.1f F\n\r", sample_ftemp);
        pc.printf("Temperatura: %.2f C\n\r", sample_ctemp);
        pc.printf("Temperatura: %.2f K\n\r", sample_ktemp);
        pc.printf("Vlaga: %.2f %%\n\r", sample_humid);
    wait_us(1000000);
    }
    
}