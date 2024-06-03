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

#include <DFRobotDFPlayerMini.h>
 
/***************************************

    CAMPLUS TORINO BERNINI
    Calcetto Digitale Camplus
    Academic Free License 3.0 (AFL-3.0)

****************************************/

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

// Audio Numbers Scheme

#define AUDIO_GAME_START 15
#define AUDIO_GAME_END_1 16
#define AUDIO_GAME_END_2 17
#define AUDIO_GOAL_FIRST 1
#define AUDIO_GOAL_LAST 14

/* CUSTOM LIBRARY SECTION */

// DEBUG MODE
/*  
*   0: No debugging (NOTE: External libraries and UI-TFT library debug will still be present)
*   1: Minimal debugging
*   2: Full debugging
*/

#define DEBUG_MODE 2 

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
bool audioAvailable = true;

/* DISPLAY */
Button rosso, blu;
LargeEvent render;
Container mainContainer(&myLCD, &render);

/* GOAL */
Event goalEvent;
int goalRosso = 0;
int goalBlu = 0;
void onGoal();
enum TEAM {TEAM_RED, TEAM_BLUE};
TEAM winnerTeam = TEAM_RED;

/* METHODS */

/* SETUP */

void setup() {
  Serial.begin(9600);

  initDisplay();

  initSpeakers();

  initSensors();

  goalEvent.addListener(&onGoal);

  randomSeed(analogRead(A5));

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
  myLCD.Set_Text_colour(WHITE);
  myLCD.Set_Text_Size(10);
  myLCD.Print("Camplus", 35, 135);
  game_GUI();
}

void game_GUI() {
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
    audioAvailable = false;
  }
  
  if(audioAvailable) {
    Serial.println(F("DFPlayer Mini online."));
  } else {
    Serial.println("Audio will not be enabled in this game");
  }
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
          break;Serial.println(F("DFPlayer Mini online."));
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
  if(DEBUG_MODE > 1) {
    Serial.print("Goal Rosso: ");
    Serial.print(goalRosso);
    Serial.print(" | Goal Blu: ");
    Serial.println(goalBlu);
  }
  // A prescindere cambia e ri-renderizza entrambi
  if(goalRosso < 11 && goalBlu < 11 && !((goalRosso == 10 || goalBlu == 10) && goalRosso == goalBlu)) { // Just need to check if goalRosso is equal to 10 as there is already a control of the equality of both
    rosso.setText((String) goalRosso);
    blu.setText((String) goalBlu);
    mainContainer.render->raise();
  } else if (goalRosso == goalBlu) {
    // DEUCE
    rosso.setText("DEUCE");
    blu.setText("DEUCE");
    mainContainer.render->raise();
  } else if (goalRosso > goalBlu + 1) {
    // WIN RED
    winnerTeam = TEAM_RED;
    endGame();
  } else if (goalBlu > goalRosso + 1) {
    // WIN BLUE
    winnerTeam = TEAM_BLUE;
    endGame();
  } else if (goalRosso > goalBlu) {
    // ADVANTAGE RED
    rosso.setText("AD");
    blu.setText("");
    mainContainer.render->raise();
  } else if (goalBlu > goalRosso) {
    // ADVANTAGE BLU
    rosso.setText("");
    blu.setText("AD");
    mainContainer.render->raise();
  } else if (goalRosso == 11) {
    // WIN RED
    winnerTeam = TEAM_RED;
    endGame();
  } else if (goalBlu == 11) {
    // WIN BLUE
    winnerTeam = TEAM_BLUE;
    endGame();
  } else {
    // ERROR
    Serial.println("[MAIN LOOP] [ERROR] Unknown game situation.");
    Serial.print("Goal Rosso: ");
    Serial.print(goalRosso);
    Serial.print(" | Goal Blu: ");
    Serial.println(goalBlu);
  }
}

void endGame() {
  if (winnerTeam == TEAM_RED) {
    rosso.setText("WIN");
    blu.setText("LOSS");
  } else {
    blu.setText("WIN");
    rosso.setText("LOSS");
  }

  mainContainer.render->raise();

  if(audioAvailable) {
    myDFPlayer.play(random(AUDIO_GAME_END_1, AUDIO_GAME_END_2));
  }

  // Reset

  goalBlu = 0;
  goalRosso = 0;

  delay(5000);

  rosso.setText("0");
  blu.setText("0");

  mainContainer.render->raise();
}

void playGoalSound() {
  int audioNumber = random(AUDIO_GOAL_FIRST, AUDIO_GOAL_LAST);

  if(audioAvailable) {
    myDFPlayer.play(audioNumber);
  }
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

  if (DEBUG_MODE == 2) {
    Serial.print("Tensione letta rosso: ");
    Serial.print(tensioneLettaRosso);
    Serial.print(" | Tensione letta blu: ");
    Serial.print(tensioneLettaBlu);  // Stampa il messaggio di debug
    //Serial.print(tensioneLettaRedButton);
  }

  // Controlla un passaggio per il sensore rosso
  if(tensioneLettaRosso>tensBaseRosso+0.5&& giPassataRosso==0) {
    if(DEBUG_MODE >= 1) Serial.print("----->passata rosso\n"); // Stampa il messaggio di debug
    goalRosso++; // Da incrementare in base a chi segna
    goalEvent.raise();
    playGoalSound();
    giPassataRosso=1;
    delay(2000);
  } else {
    giPassataRosso=0;
  }

  // Controlla un passaggio per il sensore blu
  if(tensioneLettaBlu>tensBaseBlu+0.5&& giPassataBlu==0) {
    if(DEBUG_MODE >= 1) Serial.print("----->passata blu\n"); // Stampa il messaggio di debug
    goalBlu++; // Da incrementare in base a chi segna
    goalEvent.raise();
    playGoalSound();
    giPassataBlu=1;
    delay(2000);
  } else {
    giPassataBlu=0;
  }

  // Controlla un passaggio per il bottone blu
  if(tensioneLettaBluButton<tensSogliaButton) {
    if (DEBUG_MODE >= 1) Serial.print("----->premuto blu\n"); // Stampa il messaggio di debug
    if(goalBlu != 0) goalBlu--; // Da incrementare in base a chi segna
    goalEvent.raise();
    delay(500);
  }
  // Controlla un passaggio per il bottone rosso
  if(tensioneLettaRedButton<tensSogliaButton) {
    if (DEBUG_MODE >= 1) Serial.print("----->premuto rosso\n"); // Stampa il messaggio di debug
    if(goalRosso != 0) goalRosso--; // Da incrementare in base a chi segna
    goalEvent.raise();
    delay(500);
  }

  //Print the detail message from DFPlayer to handle different errors and states.
  if (DEBUG_MODE == 1) {
    if (audioAvailable) {
      if (myDFPlayer.available()) {
        printDetail(myDFPlayer.readType(), myDFPlayer.read());
      }
    }
  }
  
  //simulaPartita(); // Simula una partita per motivi di debugging. De-commentare per procedere!

  // Chiude il print dell'attuale loop con un \n per passare al prossimo
  Serial.print("\n");
}

void simulaPartita() {
  delay(1000);
  goalBlu++; // Da incrementare in base a chi segna
  goalEvent.raise();
  if(goalRosso == 15) {
    goalRosso++;
    goalEvent.raise();
    delay(1000);
    goalRosso++;
    goalEvent.raise();
  }
  delay(1000);
  goalRosso++;
  goalEvent.raise();
}