#include <Arduino.h>

//Define frequency for Tones A to G
#define Tone_D 294
#define Tone_E 330
#define Tone_F 349
#define Tone_G 392
#define Tone_A 440
#define Tone_B 493

bool Ser_Out = true;       //Set to true for serial output

bool buttonPressed = false;
const int D = 17; //D
const int E = 16; //E
const int F = 4;  //F
const int G = 0;  //G
const int A = 2;  //A
const int B = 15; //B
const int Relay = 5; //Relay
const int Buzz = 12; //Speaker Output
const int Passcode = 5555;  //Current Passcode
int code = 0;
int buttonUpdate = 0;
int runloop = 1;

unsigned long buttonTime = 0;

void setup()
{
  ledcWriteTone(0, 2000); //Affect PWM settings for Tone()???

  pinMode(D, INPUT);
  digitalWrite(D,HIGH);
  
  pinMode(E, INPUT);
  digitalWrite(E,HIGH);
  
  pinMode(F, INPUT);
  digitalWrite(F,HIGH);
  
  pinMode(G, INPUT);
  digitalWrite(G,HIGH);
  
  pinMode(A, INPUT);
  digitalWrite(A,HIGH);
  
  pinMode(B, INPUT);
  digitalWrite(B,HIGH);

  pinMode(Relay, OUTPUT);
  digitalWrite(Relay,HIGH);

  if(Ser_Out == true) {
  Serial.begin(9600);}

  delay(100);
}

void Open_Door()
    {
      if(Ser_Out == true) {
      Serial.println("              CORRECT! Door Opens!");
            Serial.print('\n');}
            // Insert code to activate door
            digitalWrite(Relay,LOW);
            code = 0;
            delay(300);
            tone(Buzz,Tone_D);
            delay(300);
            tone(Buzz,Tone_E);
            delay(300);
            tone(Buzz,Tone_A);
            delay(300);
            tone(Buzz,Tone_D);
            delay(300);
            tone(Buzz,Tone_E);
            delay(300);
            tone(Buzz,Tone_A);
            delay(300);
            noTone(Buzz);
            delay(10000);
            digitalWrite(Relay,HIGH);
            buttonPressed = false;
            runloop = 1;
    }

void loop()
 {
  if(code > 999) {
      if(code == Passcode) {runloop = 0;}
      switch(runloop) {
        case 0: 
            Open_Door();
            break;
  
        case 1:
            code = 0;
            if(Ser_Out == true) {
            Serial.print("          - Incorrect, Please Try Again -");   
            Serial.print('\n');}
            tone(Buzz,Tone_A);
            delay(100);
            tone(Buzz,Tone_E);
            delay(100);
            tone(Buzz,Tone_D);
            delay(100);
            buttonPressed = false;
            break;  }
  }


  
  if (((buttonTime + 2000) < millis()) && buttonPressed)
    {
    code = 0;
    if(Ser_Out == true) {
    Serial.print("Too slow. Try again.");
    Serial.print('\n');}
    tone(Buzz,Tone_D);
    delay(100);
    tone(Buzz,Tone_E);
    delay(100);
   tone(Buzz,Tone_A);
    delay(100);
    buttonPressed = false;
  }
  while(digitalRead(D) == HIGH)
  {
    tone(Buzz,Tone_D);
    buttonTime = millis();
    buttonPressed = true;
    buttonUpdate = 1;
  } 
  while(digitalRead(E) == HIGH)
  {
    tone(Buzz,Tone_E);
    buttonTime = millis();
    buttonPressed = true;
    buttonUpdate = 2;
  }

  while(digitalRead(F) == HIGH)
  {
    tone(Buzz,Tone_F);
    buttonTime = millis();
    buttonPressed = true;
    buttonUpdate = 3;
  }

  while(digitalRead(G) == HIGH)
  {
    tone(Buzz,Tone_G);
    buttonTime = millis();
    buttonPressed = true;
    buttonUpdate = 4;
  }

  while(digitalRead(A) == HIGH)
  {
    tone(Buzz,Tone_A);
    buttonTime = millis();
    buttonPressed = true;
    buttonUpdate = 5;
  }

  while(digitalRead(B) == HIGH)
  {
    tone(Buzz,Tone_B);
    buttonTime = millis();
    buttonPressed = true;
    buttonUpdate = 6;
  }

  if (buttonUpdate != 0){
    code = code * 10 + buttonUpdate;
    buttonUpdate = 0;
    if(Ser_Out == true) {Serial.println(code);}
  }
  delay(60);

  noTone(Buzz);
  
  }

  

