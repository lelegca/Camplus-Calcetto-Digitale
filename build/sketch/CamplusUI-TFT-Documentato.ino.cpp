#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
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

#line 36 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
void setup();
#line 124 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
void toBeCalled();
#line 129 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
void listener1(void* args);
#line 134 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
void newListener1(void* args);
#line 138 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
void listener3(void* args);
#line 143 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
void test1(int (*funct)());
#line 148 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
void loop();
#line 36 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myLCD.begin();
  myLCD.setRotation(1);
  myLCD.fillScreen(RED);

  LargeEvent render;
  //render.addListener(&listener3);

  Container mainContainer(&myLCD, &render);

  Serial.println("This is a new build");

/*
  Button button1;
  button1.append(&mainContainer);
  button1.setX(100);
  button1.setY(100);
  button1.setWidth(100);
  button1.setHeight(100);
  button1.setTextColor(GREEN);
  button1.setText("Hello!");
  button1.setTextSize(3);

  Button button2;
  button2.append(&mainContainer);
  button2.setX(0);
  button2.setY(0);
  button2.setWidth(100);
  button2.setHeight(100);
  button2.setTextColor(YELLOW);
  button2.setText("World!");
  button2.setTextSize(2);
  button2.setShape(Button::Shape::Circular);

  Button button3;
  button3.append(&mainContainer);
  button3.setX(0);
  button3.setY(200);
  button3.setWidth(300);
  button3.setHeight(100);
  button3.setTextColor(BLUE);
  button3.setColor(GREEN);
  button3.setText("How are you?");
  button3.setTextSize(1);
*/

Button rosso;
rosso.append(&mainContainer);
rosso.setX(0);
rosso.setY(0);
rosso.setWidth(480);
rosso.setHeight(160);
rosso.setTextColor(WHITE);
rosso.setColor(RED);
rosso.setText("Rosso");
rosso.setTextSize(3);

/*
  mainContainer.getRender().addListener(&listener3);
  mainContainer.getRender().raise();
  */

 //mainContainer.render.addListener(&listener3);
 mainContainer.render->raise();

 //button1.setX(200);
  
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
void listener1(void* args) {
  Serial.println("OLEEEEE");
}

//temp void
void newListener1(void* args) {
  Serial.println("I'm the new listener1.");
}

void listener3(void* args) {
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

