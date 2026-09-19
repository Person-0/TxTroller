# TxTroller Firmware

> Modified from TinyUSB's [hid_composite example](https://github.com/hathach/tinyusb/tree/master/examples/device/hid_composite)

### Current mappings

These are the mappings I did for my T8FB transmitter.

---

| Gamepad                  | Transmitter                   |
| ------------------------ | ----------------------------- |
| Right Joystick, X axis   | Right stick, X axis           |
| Right Joystick, Y axis   | Right stick, Y axis           |
| Left Joystick, X axis    | Left stick, X axis            |
| Left Joystick, Y axis    | Left stick, Y axis            |
| Axis `4`                 | Top right rotary              |
| Axis `5`                 | Top left rotary               |
| Button `A`               | Top right switch (L position) |
| Button `B`               | Top right switch (H position) |
| Button `X`               | Top left switch  (L position) |
| Button `Y`               | —                             |
---

`Button Y` can be included by making the ABXY buttons a combination of Top left and right switches but that would make it too complicated and also force that only a single button can be pressed at a time.


## Firmware Compiling / Flashing
- Install the [Raspberry Pi Pico VS Code extension](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)
- Clone this repository
- Open this folder (/firmware) in VS Code
- The extension will automatically detect your workspace and install necessary toolchains that will be used to compile the firmware
- Edit files if required
- Press `Compile` at the bottom bar to test whether the firmware compiles successfully
- Hold the boot tactile switch on the XIAO-RP040 while plugging it into your PC, this will allow us to flash the firmware
- Use the `Run` button next to the Compile button at the bottom bar to compile, flash the firmware to the Pico. After the firmware is flashed, the Pico will auto reboot and you will see the results directly.

## Special Notes

- Use the official Raspberry Pi Pico VS Code extension to build or flash the firmware as it will save you lots of time and config messes.

## Pin Reference
- GP00 - SBUS_LED_PIN
- GP01 - SBUS_PIN