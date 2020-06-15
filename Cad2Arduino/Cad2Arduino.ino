
// Buzzer
#include <pitches.h>

// Micro Servo
#include <Servo.h>
Servo myservo; 
int pos = 0;

// OLED display 
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C   // OLED display TWI address
Adafruit_SSD1306 display(-1);
String pointx = "0";
String pointy = "0";
String linex1 = "0";
String liney1 = "0";
String linex2 = "0";
String liney2 = "0";
String rectx1 = "0";
String recty1 = "0";
String rectx2 = "0";
String recty2 = "0";
String rad = "0";
int inverse = 0;

// 8X8 Led Matrix:
#include <LedControl.h>
int DIN = 10;
int CS =  9;
int CLK = 8;
LedControl lc=LedControl(DIN,CLK,CS,0);

// Serial Monitor
String linetext = "ContentToBeOverwritten";
String type = "Type a command_";
 
void setup()
{

  // Micro Servo
  myservo.attach(11);
  myservo.write(pos);
  
  // OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // 8X8 Led Matrix:
  lc.shutdown(0,false);       
  lc.setIntensity(0,1);      //Adjust the brightness maximum is 15
  lc.clearDisplay(0);  

  // Serial Monitor
  Serial.begin(9600);
  Serial.println("[HandyCommandLine 1.0 -- by retrospectivePreposterous]");
  Serial.println("------------------------------------------------------");
  Serial.println(type);
}

// This void is specific for 8X8 Led Matrix:
void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}

void loop() {
  
        // 8x8 Matrix arrays. Visit http://xlr8.at/8x8hexbin/
          byte line[8]=   {0x0, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x0};
          byte pline[8]= {0x0, 0xc, 0x2, 0x1, 0x1, 0x2, 0xfc, 0x0};
          byte circle[8]= {0x18, 0x66, 0x42, 0x81, 0x81, 0x42, 0x66, 0x18};
          byte ellipse[8]= {0x0, 0x18, 0x66, 0x81, 0x81, 0x66, 0x18, 0x0};    
          byte point[8]=   {0x0, 0x0, 0x0, 0x18, 0x18, 0x0, 0x0, 0x0};
          byte block[8]= {0xfc, 0x84, 0x8c, 0x96, 0xed, 0x21, 0x12, 0xc};
          byte text[8]= {0x18, 0x3c, 0x24, 0x66, 0x42, 0x7e, 0xc3, 0x81};
          byte solid[8]= {0x3f, 0x63, 0xc7, 0xfd, 0x89, 0x8b, 0x8e, 0xfc};   
          byte surface[8]= {0x1f, 0x22, 0x44, 0x48, 0x24, 0x12, 0x22, 0x7c};   
          byte mesh[8]= {0xff, 0x89, 0x89, 0x89, 0xff, 0x89, 0x89, 0xff}; 
        // Others:
          byte all[8]= {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};         
          byte none[8]= {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};         
          byte skull[8]= {0x3c, 0x7e, 0xff, 0x99, 0x99, 0xff, 0x7e, 0x5a};         
          byte alien[8]= {0x3e, 0x36, 0x3e, 0x5d, 0x7f, 0x14, 0x14, 0x36};    
          byte tv[8]= {0x84, 0x48, 0x30, 0xff, 0x85, 0x87, 0x85, 0xff};
          byte heart[8]= {0x0, 0x66, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x18};
          byte wrong[8]= {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
          byte right[8]= {0x0, 0x1, 0x2, 0x44, 0x28, 0x10, 0x0, 0x0};
          byte creep[8]= {0x0, 0x0, 0x24, 0x0, 0x5a, 0x24, 0x0, 0x0}; 
          byte house[8]= {0x0, 0x18, 0x3c, 0x7e, 0x7a, 0x6e, 0x6e, 0x0};         
          byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
          byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};
          byte sad[8]=   {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};
                                    
LOOPSTART:


if (Serial.available() > 0) {
linetext = Serial.readString(); // read the command:
linetext.trim();

//-------- Command Text to OLED display --------

if (linetext == "text") {
  
Serial.println("   TEXT Specify strings on newlines at the OLED display. Enter empty string to exit."); 
TEXT: 
if (Serial.available() > 0) {
  linetext = Serial.readString(); // read the string:
  linetext.trim();
  if (linetext == "") {
  Serial.println(type);
  goto LOOPSTART;
  } else {
    Serial.print("   Input: ");
    Serial.println(linetext);
    display.println(linetext);
    display.display();
    goto TEXT;
  }
} else {
goto TEXT;
}
}

//-------- Command Point to OLED display --------

if (linetext == "point") {
  
Serial.println("   POINT Specify point coordinates at the OLED display. Separate values by comma. Enter empty value to exit."); 
POINT: 
if (Serial.available() > 0) {
pointx = Serial.readStringUntil(',');
  pointx.trim();
  if (pointx == "") {
  Serial.println(type);
  goto LOOPSTART;
  } else {
    pointy  = Serial.readStringUntil('\0');
      pointy.trim();
      if (pointy == "") {
      Serial.println(type);
      goto LOOPSTART;
      } else {
        Serial.print("   Input: " );
        Serial.println(pointx + "," + pointy);
        display.drawPixel(pointx.toInt(), pointy.toInt(), WHITE);
        display.display();
        goto POINT;
      }
  }
} else {
goto POINT;
}
}

//-------- Command Circle to OLED display --------

if (linetext == "circle") {
  
Serial.println("   CIRCLE Specify circle (x1,y1,rad) at the OLED display. Separate values by comma. Enter empty value to exit."); 
CIRCLE: 
if (Serial.available() > 0) {
pointx = Serial.readStringUntil(',');
  pointx.trim();
  if (pointx == "") {
  Serial.println(type);
  goto LOOPSTART;
  } else {
      pointy  = Serial.readStringUntil(',');
      pointy.trim();
      if (pointy == "") {
      Serial.println(type);
      goto LOOPSTART;
      } else {
          rad  = Serial.readStringUntil('\0');
          rad.trim();
          if (rad == "") {
          Serial.println(type);
          goto LOOPSTART;
          } else {
            Serial.print("   Input: " );
            Serial.println(pointx + "," + pointy + "," + rad);
            display.drawCircle(pointx.toInt(), pointy.toInt(), rad.toInt(), WHITE);
            display.display();
            goto CIRCLE;
          }
      }
  }
} else {
goto CIRCLE;
}
}

//-------- Command Fill Circle to OLED display --------

if (linetext == "fcircle") {
  
Serial.println("   FCIRCLE Specify fill circle (x1,y1,rad) at the OLED display. Separate values by comma. Enter empty value to exit."); 
FCIRCLE: 
if (Serial.available() > 0) {
pointx = Serial.readStringUntil(',');
  pointx.trim();
  if (pointx == "") {
  Serial.println(type);
  goto LOOPSTART;
  } else {
      pointy  = Serial.readStringUntil(',');
      pointy.trim();
      if (pointy == "") {
      Serial.println(type);
      goto LOOPSTART;
      } else {
          rad  = Serial.readStringUntil('\0');
          rad.trim();
          if (rad == "") {
          Serial.println(type);
          goto LOOPSTART;
          } else {
            Serial.print("   Input: " );
            Serial.println(pointx + "," + pointy + "," + rad);
            display.fillCircle(pointx.toInt(), pointy.toInt(), rad.toInt(), WHITE);
            display.display();
            goto FCIRCLE;
          }
      }
  }
} else {
goto FCIRCLE;
}
}

//-------- Command Line to OLED display --------

if (linetext == "line") {
  
Serial.println("   LINE Specify line (x1,y1,x2,y2) at the OLED display. Separate values by comma. Enter empty value to exit."); 
LINE: 
if (Serial.available() > 0) {
linex1 = Serial.readStringUntil(',');
  linex1.trim();
  if (linex1 == "") {
  Serial.println(type);
  goto LOOPSTART;
    } else {
    liney1  = Serial.readStringUntil(',');
      liney1.trim();
      if (liney1 == "") {
      Serial.println(type);
      goto LOOPSTART;
        } else {
          linex2  = Serial.readStringUntil(',');
            linex2.trim();
            if (linex2 == "") {
            Serial.println(type);
            goto LOOPSTART;
              } else {
                liney2  = Serial.readStringUntil('\0');
                  liney2.trim();
                  if (liney2 == "") {
                  Serial.println(type);
                  goto LOOPSTART;
      } else {
        Serial.print("   Input: " );
        Serial.println(linex1 + "," + liney1 + "," + linex2 + "," + liney2);
        display.drawLine(linex1.toInt(), liney1.toInt(), linex2.toInt(), liney2.toInt(), WHITE);
        display.display();
        goto LINE;
      }
    }
  }
}
} else {
goto LINE;
}
}

//-------- Command Rectangle to OLED display --------

if (linetext == "rectangle") {
  
Serial.println("   RECTANGLE Specify rectangle (x1,y1,distx,disty) at the OLED display. Separate values by comma. Enter empty value to exit."); 
RECTANGLE: 
if (Serial.available() > 0) {
rectx1 = Serial.readStringUntil(',');
  rectx1.trim();
  if (rectx1 == "") {
  Serial.println(type);
  goto LOOPSTART;
    } else {
    recty1  = Serial.readStringUntil(',');
      recty1.trim();
      if (recty1 == "") {
      Serial.println(type);
      goto LOOPSTART;
        } else {
          rectx2  = Serial.readStringUntil(',');
            rectx2.trim();
            if (rectx2 == "") {
            Serial.println(type);
            goto LOOPSTART;
              } else {
                recty2  = Serial.readStringUntil('\0');
                  recty2.trim();
                  if (recty2 == "") {
                  Serial.println(type);
                  goto LOOPSTART;
      } else {
        Serial.print("   Input: " );
        Serial.println(rectx1 + "," + recty1 + "," + rectx2 + "," + recty2);
        display.drawRect(rectx1.toInt(), recty1.toInt(), rectx2.toInt(), recty2.toInt(), WHITE);
        display.display();
        goto RECTANGLE;
      }
    }
  }
}
} else {
goto RECTANGLE;
}
}

//-------- Command Fill Rectangle to OLED display --------

if (linetext == "frectangle") {
  
Serial.println("   FRECTANGLE Specify fill rectangle (x1,y1,distx,disty) at the OLED display. Separate values by comma. Enter empty value to exit."); 
FRECTANGLE: 
if (Serial.available() > 0) {
rectx1 = Serial.readStringUntil(',');
  rectx1.trim();
  if (rectx1 == "") {
  Serial.println(type);
  goto LOOPSTART;
    } else {
    recty1  = Serial.readStringUntil(',');
      recty1.trim();
      if (recty1 == "") {
      Serial.println(type);
      goto LOOPSTART;
        } else {
          rectx2  = Serial.readStringUntil(',');
            rectx2.trim();
            if (rectx2 == "") {
            Serial.println(type);
            goto LOOPSTART;
              } else {
                recty2  = Serial.readStringUntil('\0');
                  recty2.trim();
                  if (recty2 == "") {
                  Serial.println(type);
                  goto LOOPSTART;
      } else {
        Serial.print("   Input: " );
        Serial.println(rectx1 + "," + recty1 + "," + rectx2 + "," + recty2);
        display.fillRect(rectx1.toInt(), recty1.toInt(), rectx2.toInt(), recty2.toInt(), WHITE);
        display.display();
        goto FRECTANGLE;
      }
    }
  }
}
} else {
goto FRECTANGLE;
}
}

//-------- Command Invert to OLED display --------

else if (linetext == "invert") {
  
Serial.println("   INVERT Create negative graphics at OLED display."); 
if (inverse == 0) {
display.invertDisplay(true);
inverse = 1;
display.display();
} else {
display.invertDisplay(false);
inverse = 0;
display.display();  
}
Serial.println(type);
goto LOOPSTART;
}


//-------- Command Clear to OLED display --------

else if (linetext == "clear") {
  
Serial.println("   CLEAR Erase all graphics at OLED display."); 
display.clearDisplay();
display.setCursor(0,0); 
display.display();
Serial.println(type);
goto LOOPSTART;
}

//-------- Command Matrix to 8x8 led array display --------

if (linetext == "matrix") {

Serial.println("   MATRIX Specify command [line/pline/circle/ellipse/point/block/text/solid/surface/mesh/all/none]:"); 
MATRIX: 
if (Serial.available() > 0) {
linetext = Serial.readString(); // read the command:
linetext.trim();
    if (linetext == "line") {
    printByte(line);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "pline") {
    printByte(pline);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "circle") {
    printByte(circle);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "ellipse") {
    printByte(ellipse);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "point") {
    printByte(point);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "block") {
    printByte(block);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "text") {
    printByte(text);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "solid") {
    printByte(solid);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "surface") {
    printByte(surface);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "mesh") {
    printByte(mesh);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "all") {
    printByte(all);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "none") {
    printByte(none);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "skull") {
    printByte(skull);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "alien") {
    printByte(alien);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "tv") {
    printByte(tv);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "heart") {
    printByte(heart);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "wrong") {
    printByte(wrong);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "right") {
    printByte(right);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "creep") {
    printByte(creep);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "house") {
    printByte(house);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "smile") {
    printByte(smile);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "neutral") {
    printByte(neutral);
    Serial.println(type);
    goto LOOPSTART; 
    }
    else if (linetext == "sad") {
    printByte(sad);
    Serial.println(type);
    goto LOOPSTART; 
    }
} else {
goto MATRIX;
}
}

//-------- Command Servo to add position --------

else if (linetext == "servo") {
  
Serial.println("   SERVO Specify new position for the micro servo. Non int will be considered as 0."); 
SERVO: 
if (Serial.available() > 0) {
int pos = Serial.parseInt(); // read the integer:
Serial.print("   Input: " );
Serial.println(String(pos));
myservo.write(pos);
Serial.println(type);
goto LOOPSTART;
} else {
goto SERVO;
}
}

//-------- Command Sound to BUZZER beep --------

else if (linetext == "sound") {
  
Serial.println("   SOUND make Buzzer beep."); 
tone(4, 200, 200); 
Serial.println(type);
goto LOOPSTART;
}

//-------- Command 12on --------

else if (linetext == "12on") {
  
Serial.println("   120N Turn on Pin 12."); 
pinMode(12, OUTPUT);
digitalWrite(12, HIGH);
Serial.println(type);
goto LOOPSTART;
}

//-------- Command 12off --------

else if (linetext == "12off") {
  
Serial.println("   120FF Turn off Pin 12."); 
pinMode(12, OUTPUT);
digitalWrite(12, LOW);
Serial.println(type);
goto LOOPSTART;
}

//-------- Command wrong --------

/*else {
Serial.println("   ***Unidentified command***"); 
Serial.println(type); 
}*/

}  // end of if serial available
} // end of void loop
