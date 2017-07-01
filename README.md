# amicaRGB
RGB led strip mixer on NodeMCU Amica board

## Features
Four modes are currently implemented:

* so-called mood light (changes color slowly and randomly)
* waves mode
* flood fill with white color
* fancy web-controlled color mixer


## Prerequisites

* esp8266 board (I use NodeMCU Amica)
* Arduino binding for [esp8266](https://github.com/esp8266/Arduino)


## Setting

Set you ssif and pasword in wifi.ino
Check serial console for server IP
It should respond with simple web panel featuring active mode switch and
custom color mixer based on [FlexiColorPicker](https://github.com/DavidDurman/FlexiColorPicker)
