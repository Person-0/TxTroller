#include <stdio.h>
#include "pico/stdlib.h"

#include "../sbus.h"

#define LOG_INTERVAL 2500

uint32_t tstamp = 0;
uint32_t current_ms() {
    return to_ms_since_boot(get_absolute_time());
}

uint16_t channels[8];
void displayChannels() {
    printf("\n\n");
    for(uint8_t i = 0; i < 8; i++) {
        printf("CHANNEL [%d]: %d\n", i+1, channels[i]);
    }
}

void receiver_callback(uint8_t channel, uint16_t data) {
    if (channel < 1 || channel > 8) {
        printf("ERROR! CHANNEL OUT OF RANGE: %d\n", channel);
        return;
    }
    channels[channel-1] = data;
}

int main() {
    stdio_init_all();
    printf("hello world!!\n");
    setup_sbus();
    register_channel_callback(receiver_callback);
    while(1) {
        if (current_ms() - tstamp >= LOG_INTERVAL) {
            displayChannels();
            tstamp = current_ms();
        }
    };
}
