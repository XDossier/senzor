#include "mbed.h"
#include "HTU2X.h"

#define HTU2X_ADDRESS 0x40 << 1

Serial pc(USBRX, USBTX);
InterruptIn button(PA_8);
Timer timer;
PwmOut buzzer(PB_5);


bool global_var = false;
bool alarm_activated = false;

void switcher() {
    auto ms = timer.read_ms(); // Use read_ms() to get the elapsed time in milliseconds
    if (ms > 250) {
        global_var = !global_var;
        timer.reset();
    }
}

void stop_alarm() {
    buzzer = 0;
    alarm_activated = false;
    button.fall(NULL);
    wait_us(10000000);
}

void resetiraj_mjerenje() {
    buzzer = 0;
    alarm_activated = false;
    button.fall(NULL);
    button.rise(&switcher);  // Use rise instead of fall for the button rising edge
}

void mjeri_vlagu(float vlaga) {
    if (vlaga < 25) {
        buzzer = 0;
        alarm_activated = false;
        button.fall(NULL);
    } else {
        buzzer.period(1.0 / 500.0);
        buzzer = 0.5;
        alarm_activated = true;
        if(!button){
            stop_alarm();
        }
    }
}

void mjeri_temperaturu(float temperatura) {
    if (temperatura > 24 && !alarm_activated) {
        buzzer.period(1.0 / 500.0);
        buzzer = 0.5;
        alarm_activated = true;
        if(!button){
            stop_alarm();
        }
    }
}

int main() {
    timer.start();
    button.mode(PullUp);
    button.fall(&resetiraj_mjerenje);
    button.fall(&stop_alarm);

    HTU2X htu2x;
    htu2x.init();

    float temperatura, vlaga;

    while (1) {
        temperatura = htu2x.tempc();
        vlaga = htu2x.get_humidity();
        mjeri_vlagu(vlaga);
        mjeri_temperaturu(temperatura);

        pc.clear_break();
        pc.printf("Temperatura iznosi: %.1fC\n Vlaga iznosi: %.2f%%", temperatura, vlaga);

        wait_us(1000000);
    }
}
