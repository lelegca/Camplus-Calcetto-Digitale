# 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
/***************************



    CAMPLUS TORINO BERNINI

    CamplusUI-TFT

    All rights reserved



****************************/
# 9 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
/* MAIN CLASS */

/* Usage of this class is test--only. It should be ignored when the library is not used in standalone mode */

/* This library is meant to be used with Adafruit_ILI9341 library */

# 16 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino" 2
# 17 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino" 2

# 19 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino" 2
# 20 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino" 2
# 21 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino" 2
# 34 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
Adafruit_ILI9341 myLCD = Adafruit_ILI9341(10, 53, 51, 52, 4, 50); // Current LCD for simulation

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myLCD.begin();
  myLCD.setRotation(1);
  myLCD.fillScreen(0xF800);

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
# 85 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
Button rosso;
rosso.append(&mainContainer);
rosso.setX(0);
rosso.setY(0);
rosso.setWidth(480);
rosso.setHeight(160);
rosso.setTextColor(0xFFFF);
rosso.setColor(0xF800);
rosso.setText("Rosso");
rosso.setTextSize(3);

/*

  mainContainer.getRender().addListener(&listener3);

  mainContainer.getRender().raise();

  */
# 101 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\CamplusUI-TFT-Documentato.ino"
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
