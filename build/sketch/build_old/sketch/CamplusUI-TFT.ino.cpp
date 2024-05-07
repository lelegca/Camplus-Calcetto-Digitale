#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\build_old\\sketch\\CamplusUI-TFT.ino.cpp"
#line 1 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
/***************************

    CAMPLUS TORINO BERNINI
    CamplusUI-TFT
    All rights reserved

****************************/

/* MAIN CLASS */

/* Usage of this class is test--only. It should be ignored when the library is not used in standalone mode */

/* This library is meant to be used with Adafruit_ILI9341 library */

#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "src/Button.h"
#include "src/Event.h"
#include "src/Container.h"

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define TFT_DC 53
#define TFT_CS 10

Adafruit_ILI9341 myLCD = Adafruit_ILI9341(TFT_CS, TFT_DC, 51, 52, 4, 50); // Current LCD for simulation

#line 36 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
void setup();
#line 82 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
void toBeCalled();
#line 87 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
void listener1();
#line 92 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
void newListener1();
#line 96 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
void listener3();
#line 101 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
void test1(int (*funct)());
#line 106 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
void loop();
#line 36 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myLCD.begin();
  myLCD.fillScreen(RED);

  LargeEvent render;
  //render.addListener(&listener3);

  Container mainContainer(myLCD, render);

  Button button1;
  button1.append(mainContainer);
  button1.container = mainContainer; //temp
  button1.setX(100);
  button1.setY(100);

/*
  mainContainer.getRender().addListener(&listener3);
  mainContainer.getRender().raise();
  */

 //mainContainer.render.addListener(&listener3);
 mainContainer.render.raise();

 button1.setX(200);
  
  //temp code
  test1(&toBeCalled);

  Serial.println("Approaching Event class");

  Event event;
  event.addListener(&listener1);
  event.removeListener(&listener1);
  event.raise();
  event.addListener(&newListener1);
  event.addListener(&listener1);
  event.raise();
  //end of temp code

  //TODO: delete rendermanager class and create a container class which stores the LCD and renderEvent for the lcd, container is passed to every control instead of myLCD so that everyone can subscribe to render
}

//temp void
void toBeCalled() {
  Serial.println("DAJE");
}

//temp void
void listener1() {
  Serial.println("OLEEEEE");
}

//temp void
void newListener1() {
  Serial.println("I'm the new listener1.");
}

void listener3() {
  Serial.println("I'm the new listener3.");
}

//temp void
void test1(int (*funct)())
{
  (*funct)();
}

void loop() {
  // put your main code here, to run repeatedly:

}

