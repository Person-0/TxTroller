# Sbus Test
This is sample code that utilizes the sbus parser logic to log current values of all channels.

It logs the values to the serial console in `2500`ms intervals, which can be changed by editing the `LOG_INTERVAL` macro in [sbus_test.c](./sbus_test.c).

This is extremely helpful for figuring out the values which are actually being received instead of hit-n-trial-ing everyting.

# Channel Map

Channel map for reference that I tested on my transmitter.
```
1 -> right stick, x axis,   (  right  -> 1800, left   -> 200              )
2 -> right stick, y axis,   (  bottom -> 1800, top    -> 200              )
3 -> left  stick, y axis,   (  bottom -> 200 , top    -> 1800             )
4 -> left  stick, x axis,   (  right  -> 1800, left   -> 200              )
5 -> top right switch       (  l      -> 200 , mid    -> 1000, h -> 1800  )
6 -> top right rotary       (  left   -> 200 , right  -> 1800             )
7 -> top left switch        (  h      -> 1800, l      -> 200              )
8 -> top left rotary        (  left   -> 200 , right  -> 1800             )
```

### For compiling / flashing, please refer to the main firmware's compiling / flashing guide.