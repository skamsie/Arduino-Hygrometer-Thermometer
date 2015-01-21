# Arduino-Hygrometer-Thermometer

This repository includes the program and schematic for building a standalone temperature and humidity reading device with Arduino. You can check out a video with the final product <strong>[here](https://www.youtube.com/watch?v=i7G4gAmwFMo)</strong>.

<strong>Parts list:</strong>

- arduino uno
- temperature sensor MaxDetect RHT03
- arduino 1.8" TFT screen
- 2 mini breadboards
- a lot of cables
- 10 kOhm potentiometer
- 9V Energizer battery
- one 10k OHM resistor

<strong>Optional:</strong>

- silver knob
- the case is 'Box für Arduino' bought from a german company named Flikto

<strong>Schematics</strong> (created with [Fritzing](http://fritzing.org/home/)). It's kind of messy as I wanted to fit everything on two mini breadboards and a small plastic box.<br /><br />

<img src=https://github.com/skamsie/Arduino-Hygrometer-Thermometer/blob/master/schema_big_compressed.png></img>

<strong>Dependencies:</strong>

<pre>Adafruit_GFX.h    // Core graphics library
Adafruit_ST7735.h  // Hardware-specific library
DHT.h // Sensor library</pre>

<strong>Other:</strong>
<br />
I have used the Arduino 1.8" TFT display but the schematics shows an Adafruit ST7735R display as I could not find that Fritzing part for the schematic. They are almost the same, only the BL and VCC connectors are switched, but it does not really matter since they both go to 5V.

<br />
To sync the time with the computer (Mac, Linux):

- connect the Arduino to the computer with the cable
- while the device is turned on, open the serial communication via the Arduino IDE
- in the terminal input the following command <code>TZ_adjust=+2;  echo T$(($(date +%s)+60*60*$TZ_adjust)) > /dev/tty.usbmodem1421</code> 
- replace <code>usbmodem1421</code> with your port and <code>TZ_adjust</code> depending on the time zone

For Windows: http://mikmo.dk/gobetwino.html
