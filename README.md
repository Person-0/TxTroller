# **TxTroller**
*A Radio Receiver-to-USB HID Gamepad Adapter.*

# The Plan
This is a simple adapter that will allow older-style Radio transmitter / receiver combos to be used as video-game controllers using the USB HID Gamepad device class.

## Hardware
For the initial stages, this is being developed for the [`Radiolink R8EF`](https://www.radiolink.com/r8ef) receiver, which is an 8-channel receiver operating on the 2.4GHz frequency band.

As for the transmitter that will be the actual gamepad, It will be the [`Radiolink T8FB`](https://www.radiolink.com/t8fb) transmitter, which is a 2.4GHz 8 Channels RC Remote Transmitter.

The microcontroller that will be responsible for translating the SBUS signals from the receiver to the USB device class will be an [`XIAO RP2040`](https://wiki.seeedstudio.com/XIAO-RP2040/) due to it's small footprint and easy-to-use C/C++ SDK.

## PCB

The PCB has been designed using KiCAD 9.0. It is a 2 layer PCB with both top and bottom having thick signal traces and a ground fill.

PCB Schematics:

<img src="./PCB/imgs/schematics.png" width="512px">

PCB layout:

<img src="./PCB/imgs/layout.png" height="512px">

PCB Preview:

<img src="./PCB/imgs/3d1.webp" height="512px">
<img src="./PCB/imgs/3d2.webp" height="512px">

## 3D Case

The case has been designed in Fusion 360, with the `.f3z` available in the [/CAD](./CAD/) directory, along with the exported `.step` files of the top and bottom parts of the case in [/CAD/exports](./CAD/exports).

The case looks like this:

<img src="./CAD/previews/1.webp" width="512px">
<img src="./CAD/previews/2.webp" width="512px">
<img src="./CAD/previews/3.webp" width="512px">
<img src="./CAD/previews/4.webp" width="512px">

The case has side extrusions for friction-fitting the top and bottom part of the case together.

## Firmware
*Originally modified from [raspberrypi/pico-examples/tree/master/usb/device/dev_hid_composite
](https://github.com/raspberrypi/pico-examples/tree/master/usb/device/dev_hid_composite).*

Checkout the [Firmware directory](./Firmware/).

## 😼💖