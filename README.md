![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Graphic/Cad2Arduino-logo.png?raw=true)

# Cad2Arduino
> Arduino core to allow Cad software to interact with hardware devices and IoT systems.

Have you ever imagined of drawing something and making your device to move in the same way? Or letting people know which parts have to subtitute on site by just clicking on your drawings? These and many other possibilities are now possible thanks to Cad2Arduino, which enables interaction between Cad drawings graphically and IoT devices. 

## Table of Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [Wiring](#wiring)
- [Team](#team)
- [FAQ](#faq)
- [Support](#support)
- [License](#license)


# Requirements
**Software**

- Arduino IDE. Download for free at https://www.arduino.cc/
- Windows OS (Tested on Windows 8 and higher versions).
- Powershell ISE.
- Cad software compatible with AutoLISP scripting. To choose in the market:
  - Autocad or any of its verticals (Tested on Autocad 2019 and Civil 3D 2019).
  - BricsCad.
  - BabaCad.
  - Archicad.

**Hardware**

Cad2Arduino is an extensible core designed to allow more devices than the suggested here. However, the default version is assemblied with the following hardware:
- Arduino Mega 2560. Arduino Nano or Uno are suitable.
- 0.96 Inch Oled display.
- 8x8 Led Matrix Module MAX7219.
- SG90 Microservo.
- 3V-12V Passive buzzer.
- 5mm LED.
- 220Ω resistor.
- Wire jumpers.
- Mini breadboard.

# Setup

1. Do the wiring of your Arduino device. 
> If not having the Arduino Mega 2506 you can test Cad2Arduino in different boards by respecting the I/O pins.
> No need to have all components to run Cad2Arduino. The library can be extended.
2. Start Arduino IDE and install the following libraries:
  - Adafruit GFX.
  - Adafruit SSD1306.
  - Pitches. By Brett Hagman.
  - Servo. By Michael Margolis.
  - Ledcontrol. By Eberhard Fahle.
3. Run Cad2Arduino in Arduino IDE and upload it into your board.
4. From now on you will be able to test it into Arduino Serial Monitor or Powershell `HandyCommandLine-ed01.ps1`*.
5. Run your Cad software and upload the AutoLISP* tools. 
6. Call AutoLISP functions by your Cad command line.
> *To succesfully run AutoLISP and HandyCommandLine you shall modify the Port Name in the code.

# Wiring Diagram

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Graphic/Cad2Arduino-WiringDiagram.png?raw=true)

# Arduino IDE & Serial Monitor

Once the wiring is done and the program uploaded to the board, the Serial Monitor can be started to test the core and try some commands with the board.


# Commands

The Cad2Arduino library contains the following commands:

* **text** - Specify strings on newlines at the OLED display. Enter empty string to exit.
* **point** - Specify point coordinates at the OLED display. Separate values by comma. Enter empty value to exit.
* **line** - Specify line (x1,y1,x2,y2) at the OLED display. Separate values by comma. Enter empty value to exit.
* **circle** - Specify circle (x1,y1,rad) at the OLED display. Separate values by comma. Enter empty value to exit.
* **fcircle** - Specify fill circle (x1,y1,rad) at the OLED display. Separate values by comma. Enter empty value to exit.
* **rectangle** - Specify rectangle (x1,y1,dx,dy) at the OLED display. Separate values by comma. Enter empty value to exit.
* **frectangle** - Specify fill rectangle (x1,y1,dx,dy) at the OLED display. Separate values by comma. Enter empty value to exit.
* **invert** - Create negative graphics at OLED display. Invert again to return to previous visual state.
* **clear** - Erase all graphics at OLED display.
* **matrix** - Specify command (line/pline/circle/ellipse/point/block/text/solid/surface/mesh/all/none)*
* **servo** - Specify new position for the micro servo. Non int will be considered as 0.
* **sound** - Make Buzzer beep.
* **12on** - Turn on Pin 12.
* **12off** - Turn off Pin 12.

*Besides these Cad graphics, other Matrix display were added: (skull/alien/tv/heart/wrong/right/creep/house/smile/neutral/sad).



# HandyCommandLine setup

Before running it, make sure to modify the second line PortName ("COM7" by default) to the one assigned to your board.
Also, note the BaudRate should be "9600" as per the Arduino Serial Monitor.

```powershell
$port = New-Object System.IO.Ports.SerialPort
$port.PortName = "COM7" #RENAME TO YOUR CURRENT PORT.
$port.BaudRate = "9600"
```

# HandyCommandLine example

```shell
$ brew update
$ brew install fvcproductions
```

# How it works

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Graphic/Cad2Arduino-HowItWorks.png?raw=true)

# Test samples

**Led Matrix:**
- The Led Matrix shows the Cad Object Entity as a common symbol.
- `EntityToMatrix_ETM.lsp` was used in this case.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/LedMatrix.gif?raw=true)

**Oled Display:**
- Property data of selected object is shown in the Oled Display.
- `PropertyToOled_PTO.lsp` was used in this case.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/Oled.gif?raw=true)

**Servo:**
- Block orientation property is assimilated by the servo.
- `BlockAngleToServo_ATS.lsp` was used in this case.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/Servo.gif?raw=true)

# Potential uses

- AAA
- eeeee
- iiii
