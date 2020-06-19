![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Graphic/Cad2Arduino-logo.png?raw=true)

# Cad2Arduino
> Arduino core to allow Cad software to interact with hardware devices and IoT systems.

Have you ever imagined of drawing something and making your device to move in the same way? Or letting people know which parts have to subtitute on site by just clicking on your drawings? These and many other possibilities are now possible thanks to Cad2Arduino, which enables graphical interaction between Cad drawings and IoT devices. 

# Table of Contents

- [Requirements](#requirements)
- [Setup](#setup)
- [Wiring Diagram](#wiring-diagram)
- [Arduino IDE & Serial Monitor](#arduino-ide--serial-monitor)
- [Commands](#commands)
- [Powershell HandyCommandLine setup](#powershell-handycommandline-setup)
- [How it works](#how-it-works)
- [Testing in CAD - AutoLISP samples](#testing-in-cad---autolisp-samples)
- [Potential uses](#potential-uses)
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
4. From now on you will be able to test it into Arduino Serial Monitor or Powershell `PS-HandyCommandLine-ed01.ps1`*.
5. Run your Cad software and upload the AutoLISP* tools. 
6. Call AutoLISP functions by your Cad command line.
> *To succesfully run AutoLISP and HandyCommandLine you shall modify the Port Name in the code.

# Wiring Diagram

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Graphic/Cad2Arduino-WiringDiagram.png?raw=true)

# Arduino IDE & Serial Monitor

Once the wiring is done and the program uploaded to the board, the Serial Monitor can be started to test the core and try some commands with the board. Do not forget to set it up at 9600 Baud Rate.

If the connection is succesful the Serial Monitor shall prompt the HandyCommandLine, a short of REPL, which might look like this:

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/HandyCommandLine.gif?raw=true)

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

# Powershell HandyCommandLine setup

This small piece of script was designed to test the connection without Arduino IDE. Powershell can be instructed through CMD and Batch script making it suitable to be run "behind the curtain". Also, Powershell has serial port communication libraries and it is a Windows native program (which is perfect to run Cad2Arduino in computers with no need of installing Arduino IDE).

Before testing `PS-HandyCommandLine-ed01.ps1` open the file in Powershell ISE (right click - edit) and modify the second line PortName (subtitute "COM7" with your current port name). Also make sure the BaudRate is set to "9600".

```powershell
$port = New-Object System.IO.Ports.SerialPort
$port.PortName = "COM7" #RENAME TO YOUR CURRENT PORT.
$port.BaudRate = "9600"
```

`PS-HandyCommandLine-ed01.ps1` might look like this (note this script was not designed with reading-line properties as Arduino's Serial Monitor to enhance communication speed):

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/PS-HandyCommandLine.gif?raw=true)


# How it works

Before making our first Cad tests we shall understand how the core works:

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Graphic/Cad2Arduino-HowItWorks.png?raw=true)

The setup of the core goes in the opposite direction of its use, but once the setup is ready we only have to worry about the LISP branch.
With some AutoLISP knowledge we can program our own routines for our Cad2Arduino. AutoLISP will be able to recognise many drawing or object properties like rotation, length or name thanks to ActiveX VLA and VLAX enablers. Then AutoLISP calls Powershell through external shell and it sends the information to the board.

> *Putting it simple: **AutoLISP** is the reader, **PowerShell** the messager, **Arduino** the performer.*


# Testing in CAD - AutoLISP samples

Before testing the AutoLISP samples in our Cad Software, please make sure the PortName and BaudRate in the LISP are set up according your current ones:

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Graphic/AutoLISP-setup.png?raw=true)

**`EntityToMatrix_ETM.lsp`**
- The Led Matrix shows the Cad Object Entity as a common symbol.
- Once loaded in Cad run "ETM" command.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/LedMatrix.gif?raw=true)

**`PropertyToOled_PTO.lsp`**
- Property data of selected object is shown in the Oled Display.
- Once loaded in Cad run "PTO" command.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/Oled.gif?raw=true)

**`BlockAngleToServo_ATS.lsp`:**
- Block orientation property is assimilated by the servo.
- Once loaded in Cad run "ATS" command.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/Servo.gif?raw=true)

# Potential uses

- For BIM purposes, like maintenance or control of IoT systems physically located on site in 6D projects.
- For graphical paths or route instructions to robotic cars, by just entering a polyline drawing.
- For graphical movement instructions to robotic arms, by selecting block assemblies.
- For realtime communication with project team members.
- For any graphic to light, sound or movement translation, at any place not necessary next to our computer.
