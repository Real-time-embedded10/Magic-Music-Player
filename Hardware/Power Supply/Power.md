The recommended power supply for the Raspberry Pi 3B is 5V2.5A ~ 5V3A. It is generally considered that 5V ± 5% (that is, 4.75V ~ 5.25V) is an acceptable voltage range, but exceeding (or almost beyond) this range is prone to problems. Although the power adapters all output 5V nominally, as the current consumption increases, the voltage will gradually decrease. If the voltage drops to a certain level, the Raspberry Pi will be underpowered and cannot work properly.


When the power supply voltage or current does not reach 5V / 2A, the main symptoms of insufficient power supply of the Raspberry Pi are:

  -There are corresponding symbols in the upper right corner of the monitor linked to the HDMI interface or the upper right corner of the system desktop.
  
  -The main board's red indicator is blinking or off.
  
  -The display flickers frequently.
  
  -The system starts repeatedly.
  
When the above situations occur, although the Raspberry Pi will work, it will be unstable and even crash.


Several possible ways to power the Raspberry Pi:
  
  Method 1:
Power is supplied through the Micro USB interface, and 5V / 2A DC power is sufficient. This method is usually used when experimenting early in the design. Depending on the requirements of the final product, other mobile power may need to be provided for the Raspberry Pi.
  
  Method 2: 
Power is supplied through the GPIO interface. The Raspberry Pi's GPIO interface can also accept DC input, but it is different from the first method: the GPIO power supply has no fuse. When the voltage or current is too high, it is easy to burn the board directly. The wiring method is as follows: Connect the positive pole of 5v current to pin 2 and the negative pole to pin 6.
  
  Method 3: 
Direct power supply via USB interface. Directly use the USB interface to reverse power the Raspberry Pi. However, this method requires some changes to the Raspberry Pi's motherboard to supply power normally. Therefore, this method is generally not recommended.

