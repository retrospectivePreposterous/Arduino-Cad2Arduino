# Cad2Arduino
> Core to allow Cad software to interact with Arduino.

# Installation
> include terms/tags that can be searched

**Badges will go here**
- build status
- issues (waffle.io maybe)
- devDependencies

# Wiring Diagram
> include terms/tags that can be searched

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Autocad2Arduino-WiringDiagram.png?raw=true)

# Setup
> include terms/tags that can be searched



# HandyCommandLine setup

```powershell
$port = New-Object System.IO.Ports.SerialPort
$port.PortName = "COM7" #RENAME TO YOUR CURRENT PORT.
$port.BaudRate = "9600"
$port.open() 

Start-Sleep -Milliseconds 500
Write-Host " [HandyCommandLine 1.0 -- by retrospectivePreposterous]"
Write-Host " Enter EXIT to close. Readlines are disabled in this feature"
Write-Host "----------------------------------------------------------------"
do {
$codeline = Read-Host 
if ($codeline -ne "exit") {
$port.Write("$codeline`r") 
Start-Sleep -Milliseconds 500
}
} until ( $codeline -eq "exit" ) 

$port.close() 
```

# HandyCommandLine example

```shell
$ brew update
$ brew install fvcproductions
```

# Test samples
> include terms/tags that can be searched

- Led Matrix:
The Matrix shows the Cad Object Entity as a common symbol.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/LedMatrix.gif?raw=true)

- Oled Display:

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/Oled.gif?raw=true)

- Servo:

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/Servo.gif?raw=true)

