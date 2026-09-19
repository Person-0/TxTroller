#include <stdio.h>
#include "pico/stdlib.h"
#include "config.h"

/*
=============  
=============
 RECEIVER
 SBUS (already externally inverted)
=============
*/

// SBUS settings
#define SBUS_UART_IRQ   (SBUS_UART_ID == uart0) ? UART0_IRQ : UART1_IRQ
#define SBUS_BAUD_RATE  100000
#define SBUS_DATA_BITS  8
#define SBUS_STOP_BITS  2
#define SBUS_PARITY     UART_PARITY_EVEN

// SBUS parsing
volatile uint8_t sbus_index = 0;
volatile uint8_t sbus_byteCache[25];
volatile uint8_t sbus_bitStore[11];
static void (*channel_callback)(uint8_t, uint16_t) = NULL;

void set_sbus_led(bool status) {
    gpio_put(SBUS_LED_PIN, status);
}

static void parse_sbus_bytes() {
    channel_callback(1, (sbus_byteCache[1]       | sbus_byteCache[2]  << 8) & 0x07FF);
    channel_callback(2, (sbus_byteCache[2]  >> 3 | sbus_byteCache[3]  << 5) & 0x07FF);
    channel_callback(3, (sbus_byteCache[3]  >> 6 | sbus_byteCache[4]  << 2  | sbus_byteCache[5] << 10) & 0x07FF);
    channel_callback(4, (sbus_byteCache[5]  >> 1 | sbus_byteCache[6]  << 7) & 0x07FF);
    channel_callback(5, (sbus_byteCache[6]  >> 4 | sbus_byteCache[7]  << 4) & 0x07FF);
    channel_callback(6, (sbus_byteCache[7]  >> 7 | sbus_byteCache[8]  << 1  | sbus_byteCache[9] <<  9) & 0x07FF);
    channel_callback(7, (sbus_byteCache[9]  >> 2 | sbus_byteCache[10] << 6) & 0x07FF);
    channel_callback(8, (sbus_byteCache[10] >> 5 | sbus_byteCache[11] << 3) & 0x07FF);
}

static void on_uart_rx() {
    while (uart_is_readable(SBUS_UART_ID)) {
        set_sbus_led(1);
        uint8_t byte = uart_getc(SBUS_UART_ID);
        if (sbus_index == 0) {
            if (byte != 0x0F) {
                continue;
            }
        }
        sbus_byteCache[sbus_index] = byte;
        sbus_index++;
        if (sbus_index == 25) {
            parse_sbus_bytes();
            sbus_index = 0;
        }
    }
    set_sbus_led(0);
}

int setup_sbus() {
	gpio_init(SBUS_LED_PIN);
	gpio_set_dir(SBUS_LED_PIN, GPIO_OUT);
	gpio_put(SBUS_LED_PIN, 0);  // off

    uart_init(SBUS_UART_ID, SBUS_BAUD_RATE);
    gpio_set_function(SBUS_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(SBUS_UART_ID, false, false);
    uart_set_format(
        SBUS_UART_ID,
        SBUS_DATA_BITS,
        SBUS_STOP_BITS,
        SBUS_PARITY
    );
    uart_set_fifo_enabled(SBUS_UART_ID, true);
    irq_set_exclusive_handler(SBUS_UART_IRQ, on_uart_rx);
    irq_set_enabled(SBUS_UART_IRQ, true);
    uart_set_irq_enables(SBUS_UART_ID,true,false); // RX only

    printf("SBUS setup correctly\n");

    return 0;
}

void register_channel_callback(void (*callback)(uint8_t, uint16_t)) {
    channel_callback = callback;
    printf("receiver: channel callback registered\n");
}

void inject_sbus_bytes(uint8_t data[25]) {
    for (int i = 0; i < 25; i++) {
        sbus_byteCache[i] = data[i];
    }
    parse_sbus_bytes();
}
