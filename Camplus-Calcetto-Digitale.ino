/*
    ____      _          _   _          ____  _       _ _        _         ____                      _           
  / ___|__ _| | ___ ___| |_| |_ ___   |  _ \(_) __ _(_) |_ __ _| | ___   / ___|__ _ _ __ ___  _ __ | |_   _ ___ 
 | |   / _` | |/ __/ _ \ __| __/ _ \  | | | | |/ _` | | __/ _` | |/ _ \ | |   / _` | '_ ` _ \| '_ \| | | | / __|
 | |__| (_| | | (_|  __/ |_| || (_) | | |_| | | (_| | | || (_| | |  __/ | |__| (_| | | | | | | |_) | | |_| \__ \
  \____\__,_|_|\___\___|\__|\__\___/  |____/|_|\__, |_|\__\__,_|_|\___|  \____\__,_|_| |_| |_| .__/|_|\__,_|___/
                                               |___/                                         |_|                

*/

#include <LCDWIKI_GUI.h>

#include <LCDWIKI_KBV.h>
#include <lcd_mode.h>
#include <lcd_registers.h>
#include <mcu_16bit_magic.h>
#include <mcu_8bit_magic.h>

#include "DFRobotDFPlayerMini.h"
 
/***************************

    CAMPLUS TORINO BERNINI
    CamplusUI-TFT
    All rights reserved

****************************/

/* MAIN CLASS */

/* DECLARATIONS */

/* PRE-COMPILATION STANDARDS */

#include <Arduino.h>

#include <string.h>

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

LCDWIKI_KBV myLCD(ILI9486,A3,A2,A1,A0,A4);

/* CUSTOM LIBRARY SECTION */

/* SENSORS */

// Vartiabili comuni fotoresistenze
const float tensioneRiferimento = 5.0;  // Tensione di riferimento dell'ADC in volt
const int risoluzioneADC = 1023;  // Risoluzione dell'ADC

// Sensore squadra rossa
const int pinAnalogicoRosso = A7;  // Definisci il pin analogico da cui leggere la tensione
float tensBaseRosso = 0;
float tensioneLettaRosso;
int valoreLetturaRosso;
int giPassataRosso=0;

// Sensore squadra blu
const int pinAnalogicoBlu = A8;  // Definisci il pin analogico da cui leggere la tensione
float tensBaseBlu = 0;
float tensioneLettaBlu;
int valoreLetturaBlu;
int giPassataBlu=0;


/* BUTTONS */

float tensSogliaButton=1; // Tensione di soglia per il bottone

// Bottone squadra blu
const int pinAnalogicoBluButton= A14;  // Definisci il pin analogico da cui leggere la tensione
float tensioneLettaBluButton;
int valoreLetturaBluButton;

// Bottone squadra rossa
const int pinAnalogicoRedButton = A15;  // Definisci il pin analogico da cui leggere la tensione
float tensioneLettaRedButton;
int valoreLetturaRedButton;

/* SPEAKERS */
DFRobotDFPlayerMini myDFPlayer;

/* DISPLAY */
Button rosso, blu;
LargeEvent render;
Container mainContainer(&myLCD, &render);

/* GOAL */
Event goalEvent;
int goalRosso = 0;
int goalBlu = 0;
void onGoal();

/* METHODS */

/* SETUP */

void setup() {
  Serial.begin(9600);

  initDisplay();

  initSpeakers();

  initSensors();

  goalEvent.addListener(&onGoal);

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3 
}

/* SENSOR SECTION */

void initSensors() {
  valoreLetturaRosso = analogRead(pinAnalogicoRosso);  // Leggi il valore analogico dal pin
  tensBaseRosso = (valoreLetturaRosso * tensioneRiferimento) / risoluzioneADC;
  Serial.print("valore soglia: ");
  Serial.print( tensBaseRosso);
  Serial.print("\n");

  valoreLetturaBlu = analogRead(pinAnalogicoBlu);  // Leggi il valore analogico dal pin
  tensBaseBlu = (valoreLetturaBlu * tensioneRiferimento) / risoluzioneADC;
  Serial.print("valore soglia: ");
  Serial.print( tensBaseBlu);
  Serial.print("\n");
}

/* DISPLAY SECTION */

void initDisplay() {
  myLCD.Init_LCD();
  myLCD.Set_Rotation(1); // da cambiare a 1
  myLCD.Set_Text_Mode(1);
  myLCD.Fill_Screen(RED);

  // GUI Initialization

  rosso.append(&mainContainer);
  rosso.setX(0);
  rosso.setY(0);
  rosso.setWidth(240);
  rosso.setHeight(320);
  rosso.setTextColor(WHITE);
  rosso.setColor(RED);
  rosso.setText("0");
  rosso.setTextSize(6);

  blu.append(&mainContainer);
  blu.setX(240);
  blu.setY(0);
  blu.setWidth(240);
  blu.setHeight(320);
  blu.setTextColor(WHITE);
  blu.setColor(BLUE);
  blu.setText("0");
  blu.setTextSize(6);

  mainContainer.render->raise();

  delay(2000);
}

/* SPEAKER SECTION */

/* Init */

void initSpeakers() {
  Serial1.begin(9600);

  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }

  Serial.println(F("DFPlayer Mini online."));
}

/* Methods */

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}



/* LOOP SECTION */

/* Methods */

void onGoal() {
  // A prescindere cambia e ri-renderizza entrambi
  rosso.setText((String) goalRosso);
  blu.setText((String) goalBlu);

  mainContainer.render->raise();
}

void loop() {
  // Ottiene dati dal sensore rosso
  valoreLetturaRosso = analogRead(pinAnalogicoRosso);  // Leggi il valore analogico dal pin
  tensioneLettaRosso = (valoreLetturaRosso * tensioneRiferimento) / risoluzioneADC;  // Converti il valore letto in volt

  // Ottiene dati dal sensore blu
  valoreLetturaBlu = analogRead(pinAnalogicoBlu);  // Leggi il valore analogico dal pin
  tensioneLettaBlu = (valoreLetturaBlu * tensioneRiferimento) / risoluzioneADC;  // Converti il valore letto in volt

  // Ottieni dati dal bottone blu
  valoreLetturaBluButton = analogRead(pinAnalogicoBluButton);  // Leggi il valore analogico dal pin
  tensioneLettaBluButton = (valoreLetturaBluButton * tensioneRiferimento) / risoluzioneADC;  // Converti il valore letto in volt

  // Ottieni dati dal bottone rosso
  valoreLetturaRedButton = analogRead(pinAnalogicoRedButton);  // Leggi il valore analogico dal pin
  tensioneLettaRedButton = (valoreLetturaRedButton * tensioneRiferimento) / risoluzioneADC;  // Converti il valore letto in volt

  Serial.print("Tensione letta rosso: ");
  Serial.print(tensioneLettaRosso);
  Serial.print(" | Tensione letta blu: ");
  Serial.print(tensioneLettaBlu);  // Stampa il messaggio di debug
  //Serial.print(tensioneLettaRedButton);

  // Controlla un passaggio per il sensore rosso
  if(tensioneLettaRosso>tensBaseRosso+0.5&& giPassataRosso==0) {
    Serial.print("----->passata rosso\n"); // Stampa il messaggio di debug
    goalRosso++; // Da incrementare in base a chi segna
    goalEvent.raise();
    giPassataRosso=1;
    delay(2000);
  } else {
    giPassataRosso=0;
  }

  // Controlla un passaggio per il sensore blu
  if(tensioneLettaBlu>tensBaseBlu+0.5&& giPassataBlu==0) {
    Serial.print("----->passata blu\n"); // Stampa il messaggio di debug
    goalBlu++; // Da incrementare in base a chi segna
    goalEvent.raise();
    giPassataBlu=1;
    delay(2000);
  } else {
    giPassataBlu=0;
  }

  // Controlla un passaggio per il bottone blu
  if(tensioneLettaBluButton<tensSogliaButton) {
    //Serial.print("----->premuto blu\n"); // Stampa il messaggio di debug
    goalBlu--; // Da incrementare in base a chi segna
    goalEvent.raise();
    delay(500);
  }
  // Controlla un passaggio per il bottone rosso
  if(tensioneLettaRedButton<tensSogliaButton) {
    //Serial.print("----->premuto rosso\n"); // Stampa il messaggio di debug
    goalRosso--; // Da incrementare in base a chi segna
    goalEvent.raise();
    delay(500);
  }

  //Print the detail message from DFPlayer to handle different errors and states.
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read());
  }

  // Chiude il print dell'attuale loop con un \n per passare al prossimo
  Serial.print("\n");

}