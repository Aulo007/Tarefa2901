#include <stdio.h>
#include "pico/stdlib.h"

// Definindo os pinos
const uint LED_GREEN_PIN = 11;
const uint LED_BLUE_PIN = 12;
const uint LED_RED_PIN = 13;
const uint BUTTON1_PIN = 5;

int main()
{
    // Inicia comunicação serial
    stdio_init_all();

    // Inicializa os pinos

    gpio_init(LED_GREEN_PIN);
    gpio_init(LED_BLUE_PIN);
    gpio_init(LED_RED_PIN);
    gpio_init(BUTTON1_PIN);

    // Seta a direção dos pinos
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(BUTTON1_PIN, GPIO_IN);

    // Configura pull-up interno para evitar problemas com leituras incertas(flutuantes)
    gpio_pull_up(BUTTON1_PIN);

    

    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
