Data Collection
==
Detailed instruction and explanation is at our [wiki](https://github.com/Real-time-embedded10/Magic-Music-Player/wiki/Data-Collection).<br>
<br>
Since it is more convenient to collect data by python than C++ (every time changing the stored file name, you don't need to re-run `make` and then `./main`), this file was written by python.<br>
[Here](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/DATABASE/Original%20Data) is the original DATABASE collected. <br>

Requirement
--
Install I2C library.<br>
```
sudo apt-get install i2c-tools
```

Detect whether I2C device is successfully connected and find the corresponding address.
```
sudo i2cdetect -y 1
```
