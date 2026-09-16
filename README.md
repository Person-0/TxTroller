# **TxTroller**
*A Radio Receiver-to-USB HID Gamepad Adapter.*

# The Plan
This is a simple adapter that will allow older-style Radio transmitter / receiver combos to be used as video-game controllers using the USB HID Gamepad device class.

### **Hardware**
For the initial stages, this is being developed for the [`Radiolink R8EF`](https://www.radiolink.com/r8ef) receiver, which is an 8-channel receiver operating on the 2.4GHz frequency band.

As for the transmitter that will be the actual gamepad, It will be the [`Radiolink T8FB`](https://www.radiolink.com/t8fb) transmitter, which is a 2.4GHz 8 Channels RC Remote Transmitter.

The microcontroller that will be responsible for translating the SBUS signals from the receiver to the USB device class will be an [`XIAO RP2040`](https://wiki.seeedstudio.com/XIAO-RP2040/) due to it's small footprint and easy-to-use C/C++ SDK.

## 😼💖