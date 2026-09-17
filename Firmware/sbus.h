int setup_sbus_uart();
void inject_sbus_bytes(uint8_t data[25]);
void register_channel_callback(void (*callback)(uint8_t, uint16_t));