#include <stdio.h>
#include "pico/stdlib.h"

// Definindo os pinos
const uint LED_GREEN_PIN = 11;
const uint LED_BLUE_PIN = 12;
const uint LED_RED_PIN= 13;



int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
