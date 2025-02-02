#include <stdio.h>
#include "pico/stdlib.h"

// Definindo os pinos
const uint LED_GREEN_PIN = 11;
const uint LED_BLUE_PIN = 12;
const uint LED_RED_PIN = 13;
const uint BUTTON1_PIN = 5;

// Variáveis globais
static volatile bool BUTTON_PRESSED = true;
static volatile int contador = 0;
static volatile uint32_t last_time = 0; // Variável de debounce

static int64_t turn_off_callback(alarm_id_t, void *user_data)
{
    contador++;

    if (contador == 1)
    {
        gpio_put(LED_GREEN_PIN, false);
        return 3000 * 1000; // Chama novamente a função em 3 segundos
    }

    if (contador == 2)
    {
        gpio_put(LED_BLUE_PIN, false);
        return 3000 * 1000;
    }

    if (contador == 3)
    {
        gpio_put(LED_RED_PIN, false);
        BUTTON_PRESSED = true; // Permite nova ativação pelo botão
        return 0;              // Não agendará mais chamadas
    }

    return 0;
}

int main()
{
    stdio_init_all();

    // Inicializa e configura os pinos
    gpio_init(LED_GREEN_PIN);
    gpio_init(LED_BLUE_PIN);
    gpio_init(LED_RED_PIN);
    gpio_init(BUTTON1_PIN);

    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(BUTTON1_PIN, GPIO_IN);

    gpio_pull_up(BUTTON1_PIN); // Pull-up para evitar leituras flutuantes

    while (true)
    {
        uint32_t current_time_in_us = to_us_since_boot(get_absolute_time());

        if (current_time_in_us - last_time > 50000)
        {
            if (!gpio_get(BUTTON1_PIN) && BUTTON_PRESSED) // Entra aqui quando o botão for pressionando e enquanto a flag for true
            {
                last_time = current_time_in_us; // Atualiza tempo do último clique
                BUTTON_PRESSED = false;
                contador = 0;

                // Liga todos os LEDs
                gpio_put(LED_GREEN_PIN, true);
                gpio_put(LED_BLUE_PIN, true);
                gpio_put(LED_RED_PIN, true);

                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }

        sleep_ms(10); // Reduz o uso de CPU
    }
}
