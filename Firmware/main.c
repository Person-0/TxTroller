#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "pico/stdlib.h"
#include "sbus.h"
#include "tusb.h"
#include "usb_descriptors.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum {
	BLINK_NOT_MOUNTED = 250,
	BLINK_MOUNTED = 1000,
	BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

void led_blinking_task(void);
void hid_task(void);

/*------------- UTIL Fns -------------*/

#define board_millis() to_ms_since_boot(get_absolute_time())

void onboard_led_write(bool val) {
	gpio_put(ONBOARD_LED, 1 - val);  // led is active low
}

uint32_t wakeup_button_read() {
	return 0;  // todo: make it return 1 if tx btn was pressed
}

hid_gamepad_report_t LATEST_GAMEPAD_REPORT = {
	.x = 0,
	.y = 0,
	.z = 0,
	.rz = 0,
	.rx = 0,
	.ry = 0,
	.hat = GAMEPAD_HAT_CENTERED,
	.buttons = 0
};

void receiver_callback(uint8_t channel, uint16_t data) {
	// todo: map channels to gamepad btns / jsticks
}

/*------------- MAIN -------------*/
int main(void) {
	stdio_init_all();

	// setup onboard led
	gpio_init(ONBOARD_LED);
	gpio_set_dir(ONBOARD_LED, GPIO_OUT);
	gpio_put(ONBOARD_LED, 1);  // off

	// setup sbus
	setup_sbus_uart();
	register_channel_callback(receiver_callback);

	// init device stack on configured roothub port
	tud_init(0);

	while (1) {
		tud_task();  // tinyusb device task
		led_blinking_task();

		hid_task();
	}
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void) { blink_interval_ms = BLINK_MOUNTED; }

// Invoked when device is unmounted
void tud_umount_cb(void) { blink_interval_ms = BLINK_NOT_MOUNTED; }

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
	(void)remote_wakeup_en;
	blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
	blink_interval_ms = tud_mounted() ? BLINK_MOUNTED : BLINK_NOT_MOUNTED;
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

static void send_hid_report(void) {
	if (!tud_hid_ready()) return;
	tud_hid_report(REPORT_ID_GAMEPAD, &LATEST_GAMEPAD_REPORT, sizeof(LATEST_GAMEPAD_REPORT));
}

void hid_task(void) {
	// Poll every 10ms
	const uint32_t interval_ms = 10;
	static uint32_t start_ms = 0;
	if (board_millis() - start_ms < interval_ms) return;
	start_ms += interval_ms;
	if (!tud_hid_ready()) return;
	tud_hid_report(REPORT_ID_GAMEPAD, &LATEST_GAMEPAD_REPORT, sizeof(LATEST_GAMEPAD_REPORT));
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(
	uint8_t instance, uint8_t report_id,
	hid_report_type_t report_type, uint8_t* buffer,
	uint16_t reqlen
) {
	(void)instance;
	(void)report_id;
	(void)report_type;
	(void)buffer;
	(void)reqlen;
	return 0;
}

void tud_hid_set_report_cb(
	uint8_t instance, uint8_t report_id,
	hid_report_type_t report_type, uint8_t const* buffer,
	uint16_t bufsize
) {
	(void)instance;
	(void)report_id;
	(void)report_type;
	(void)buffer;
	(void)bufsize;
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void) {
	static uint32_t start_ms = 0;
	static bool led_state = false;

	// blink is disabled
	if (!blink_interval_ms) return;

	// Blink every interval ms
	if (board_millis() - start_ms < blink_interval_ms) return;  // not enough time
	start_ms += blink_interval_ms;

	onboard_led_write(led_state);
	led_state = 1 - led_state;  // toggle
}
