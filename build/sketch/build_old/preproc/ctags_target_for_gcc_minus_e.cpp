#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\build_old\\preproc\\ctags_target_for_gcc_minus_e.cpp"
# 1 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
/***************************



    CAMPLUS TORINO BERNINI

    CamplusUI-TFT

    All rights reserved



****************************/
# 9 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
/* MAIN CLASS */

/* Usage of this class is test--only. It should be ignored when the library is not used in standalone mode */

/* This library is meant to be used with Adafruit_ILI9341 library */

# 16 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino" 2
# 17 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino" 2

# 19 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino" 2
# 20 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino" 2
# 21 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino" 2
# 34 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
Adafruit_ILI9341 myLCD = Adafruit_ILI9341(10, 53, 51, 52, 4, 50); // Current LCD for simulation

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myLCD.begin();
  myLCD.fillScreen(0xF800);

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
# 59 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\CamplusUI-TFT.ino"
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
