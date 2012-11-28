// Bubble bot code for Midsouth Makers and Artist Ghetto
// Thanks for the members insperation and helping in debugging!

#include <Servo.h>  // Sevro library

// Physical Hardware   
int trayButtonHigh = 0; // Button located on top of tray   used
int trayButtonLow = 0;  // Button locate below tray        used
int ledPin = 13;        // Led pin for feed back           used
 
// Ez Driver Lines
int dirPin = 3;         // Direction pin for EZ-Driver
int motionPin = 4;      // Motion pin for EZ-Driver
 
// Software Globals
// int travel = 1;         // Timer 1 Global      obsolete 
int timer2 = 0;            // Timer 2 Global      used
// int timer3 = 0;         // Timer 3 Global      obsolete
int dirct = 0;             // Direction Global    used
int pos = 140;             // Position Global     used
int DirButton = 0;         // Dirc Button Global  used

// Servro global
Servo myServo;    

//set Digital Pins use
void setup() { 
  pinMode(2, INPUT);    // High Button #2
  pinMode(3, OUTPUT);   // Direction Pin #3 
  pinMode(4, OUTPUT);   // Motion Pin #4
  pinMode(5, INPUT);    // Low Button #5
  pinMode(6, INPUT);    // Low Button #6 
  pinMode(12, INPUT);   // Spare Pin
  pinMode(13, OUTPUT);  // LED Pin #13
  {
  myServo.attach(7);    // Servo pin #7
  }
  
// open serial port for debug
Serial.begin(9600);      // Open serial port

// set pins
  digitalWrite(2, HIGH); // trayButtonHigh fuse set
  digitalWrite(3, LOW);  // Dirct set
  digitalWrite(4, LOW);  // Motion pin reset
  digitalWrite(5, HIGH); // trayButtonLow fuse set
  digitalWrite(6, HIGH); // DirButton fuse set
  digitalWrite(13, LOW); // LED is turned off
}

void loop() 
{
  
timer2 = (timer2 + 1);               // Timer to jumpstart the motion ater button event
trayButtonHigh = digitalRead(2);     // Check the trayButtonHigh 
trayButtonLow = digitalRead(5);      // Check the trayButtonLow
DirButton = digitalRead(6);          // Check the DirButton
dirct = digitalRead(3);              // Check the dirct

if (timer2 % 100 == 0)               // Debug code - pulls ever 100th pass
{                                    // Debug code 
  Serial.print("High B = ");         // Debug code
  Serial.print(trayButtonHigh);      // Debug code
  Serial.print(" . dirct = ");       // Debug code
  Serial.print(dirct );              // Debug code
  Serial.print(" . DirButton = ");   // Debug code
  Serial.print(DirButton );          // Debug code
                                     // Debug code
  }                                  // Debug code
  
  if (DirButton == 0)                //Wrong direction reset button code
    {                                //
       timer2 = (10001);             // Advance the timer
       trayButtonLow = (0);          // trigger low tray return
    }
  
  
  if (timer2 > 1000 )                // The global that allows movement
  {                                  // while button is down
    if ( trayButtonHigh == 0)        //
      {
        digitalWrite(3,LOW);         // write direction low
        while (pos < 140)            // tell servo to move to 140 
        {
          (pos = pos + 1);           // move + 1
          delay (100);               // go slow as to not pop the bubble film
           myServo.write(pos);       // move the servo
        }
       
        delay(5000);                 // wait to blow bubble
        while (pos > 100)            // reset move servo to 100
        {
          (pos = pos - 1);           // move - 1    
          delay (100);               //go slow keep strings untangle
          myServo.write(pos);        // move the servo
        }
        timer2 = (0);                // set global so we can move while
      }                              // button is down
  
    if ( trayButtonLow == 0)         // completed drip
      {
        digitalWrite(3,HIGH);        // change direction
        delay (1000);                // let the string soak 1 sec
        timer2 = (0);                // set global so we can move while
      }                              // button is down
  }
  

   digitalWrite(4, HIGH);            // move stepper
   digitalWrite(13, HIGH);           // light LED
  delay(1);                          // delay
   digitalWrite(4, LOW);             // move stepper
   digitalWrite(13, LOW);            // dim LED
  delay(1);                          // delay


}  