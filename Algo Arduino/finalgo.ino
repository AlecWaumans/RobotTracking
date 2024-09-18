
#include <Servo.h>

#define numOfValsRec 5 
#define digitsPerValRec 1

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1; //$00000
int counter = 0;

bool counterStart = false;
String receivedString;

Servo Servo1;  // create servo object to control a servo
Servo Servo2;  // create servo object to control a servo
Servo Servo3;  // create servo object to control a servo
Servo Servo4;  // create servo object to control a servo
Servo Servo5;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;


void setup() {
  Serial.begin(9600);
  
  Servo1.attach(2);  // attaches the servo on pin 9 to the servo object
  Servo2.attach(3);  // attaches the servo on pin 9 to the servo object
  Servo3.attach(4);  // attaches the servo on pin 9 to the servo object
  Servo4.attach(5);  // attaches the servo on pin 9 to the servo object
  Servo5.attach(6);  // attaches the servo on pin 9 to the servo object
  
  Servo1.write(15);
  Servo2.write(15);
  Servo3.write(15);
  Servo4.write(15); 
  Servo5.write(15);
}

void loop() {
  delay(1000); // Attente de 1 seconde
  receiveData(); // Appel de la fonction de réception de données
  
  // Assignation des valeurs reçues aux variables correspondantes
  val1 = valsRec[1];
  val2 = valsRec[1];
  val3 = valsRec[3];
  val4 = valsRec[3];
  val5 = valsRec[1];
  
  // Contrôle des servomoteurs en fonction des valeurs reçues
  // Si la valeur est 0, positionner le servo à 10 degrés, sinon à 140 degrés
  Servo1.write(val1 == 0 ? 10 : 140);
  Servo2.write(val2 == 0 ? 10 : 140);
  Servo3.write(val3 == 0 ? 10 : 140);
  Servo4.write(val4 == 0 ? 10 : 140);
  Servo5.write(val5 == 0 ? 10 : 140);
  
  delay(1000); // Attente de 1 seconde
}

void receiveData() {
  while (Serial.available()) {
    char c = Serial.read();
    //Serial.print(c);
    
    if (c == '$') {
      counterStart = true;
    }
    
    if (counterStart) {
      if (counter < stringLength) {
        receivedString += c;
        counter++;
      }
      
      if (counter >= stringLength) {
        //$00000
        for (int i = 0; i < numOfValsRec; i++) {
          int num = (i * digitsPerValRec) + 1;
          int val = receivedString.substring(num , num + digitsPerValRec).toInt();
          Serial.print(val);
          valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
        }
        /*
        for (int i = 0; i < numOfValsRec; i++) {
          Serial.print(valsRec[i]);
          if (i < numOfValsRec - 1) {
            Serial.print(" ");
          }
        }
        */
        Serial.println(); // Ajout d'un saut de ligne pour séparer les envois
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}


