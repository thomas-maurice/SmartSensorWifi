# util

These files are provided as 'helpers' to use/dev/debug the project.
They are not quite documented/re-usable because their sole purpose
is being used in the Smart Sensor WiFi project's developement.
Of course everything here is under the GPL License.

## pyserialcom.py
This script provides a simple user-friendly and swaggy alternative to
*minicom*. It enables you to communicate with the mictocontroller via
the serial port. The advantage is that if a character is not printable,
it won't result in a horrible and unprintable result. You can choose
between an ASCII output, a hex output and a mixed output.

To launch it just type :

    ./pyserialcom.py [serialport] [baudrate=9600]

and enjoy ;)
