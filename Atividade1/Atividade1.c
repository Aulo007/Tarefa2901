#include <stdio.h>
#include "pico/stdlib.h"    // Inclui a biblioteca padrão para funcionalidades básicas como GPIO.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

// Declaração dos pinos

const uint LED_RED_PIN = 11;
const uint LED_YELLOW_PIN = 12;
const uint LED_BLUE_PIN = 13;

volatile bool acionador[3] = {true, false, false};

// Declarando função de callback que será chamada pelo temporizador, ela é do tipo bool
// ou seja, se retornar true ela continua o temporizador, se falso ela para.

bool repeating_timer_callback(struct repeating_timer *t);

int main()
{
    stdio_init_all(); // Inicializa comunicação serial

    // Inicializa os Leds
    gpio_init(LED_RED_PIN);
    gpio_init(LED_YELLOW_PIN);
    gpio_init(LED_BLUE_PIN);

    // Seta direçao dos leds
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);

    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 3 segundos, conforme pedido na tarefa.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true)
    {
        printf("Olá, mundo!\n");
        sleep_ms(1000);
    }
}

bool repeating_timer_callback(struct repeating_timer *t)
{
    if (acionador[0] == true && nand(acionador[1], acionador[2]) == true)
    {
        gpio_put(LED_RED_PIN, true);
        acionador[0] = false;
        acionador[1] = true;
    }

    else if (acionador[1] == true && nand(acionador[0], acionador[2]) == true)
    {
        gpio_put(LED_YELLOW_PIN, true);
        acionador[1] = false;
        acionador[2] = true;
    }
    else
    {
        gpio_put(LED_BLUE_PIN, true);
        acionador[2] = false;
        acionador[0] = true;
    }

    return true;
}
