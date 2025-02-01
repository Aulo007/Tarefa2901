#include <stdio.h>
#include "pico/stdlib.h"

// Definindo os pinos
const uint LED_GREEN_PIN = 11;
const uint LED_BLUE_PIN = 12;
const uint LED_RED_PIN = 13;
const uint BUTTON1_PIN = 5;

// Definindo constantes globais
// Varíavel para indicar se deve ser realizada a sequência qd o botão for apertado
static volatile bool BUTTON_PRESSED = true;
static volatile int contador = 0;
static volatile int last_time = 0; // Variável global para amarzenar o tempo do último evento

static int64_t turn_off_callback(alarm_id_t, void *user_data)
{
    contador++;

    if (contador == 1)
    {
        gpio_put(LED_GREEN_PIN, false);
        return 3000 * 1000;
    }

    if (contador == 2)
    {
        gpio_put(LED_BLUE_PIN, false);
        return 3000 * 1000;
    }

    if (contador == 3)
    {
        gpio_put(LED_BLUE_PIN, false);
        BUTTON_PRESSED = true;
        return 3000 * 1000;
    }

    return 0;
}

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
        uint32_t current_time_in_us = to_us_since_boot(get_absolute_time());

        if (current_time_in_us - last_time > 50000)
        {
            if (!gpio_get(BUTTON1_PIN) && BUTTON_PRESSED) // Se o botão for pressionado e o botão pressed for verdadeiro...
            {
                BUTTON_PRESSED = false;
                contador = 0;

                // Liga todos os leds

                gpio_put(LED_GREEN_PIN, true);
                gpio_put(LED_BLUE_PIN, true);
                gpio_put(LED_RED_PIN, true);

                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }
    }
}
