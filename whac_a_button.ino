
#include "TM1637.h"

const int CLK = 8; //Set the CLK pin connection to the display
const int DIO = 7; //Set the DIO pin connection to the display
TM1637 tm1637(CLK,DIO);  //set up the 4-Digit Display.
int ones = 0;
int tens = 0;
int hundreds = 0;
int thousands = 0;
int gameDelay = 1000; //This is the game speed
int hitButton = 1;
boolean playing = 1; //boolean flag that we'll use to determine where in the scoring cycle we are
int score = 0; //This is the score
void setup(){
  Serial.begin(9600);
  //set the button pins
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(2,HIGH);
  pinMode(3,HIGH);
  pinMode(4,HIGH);
  pinMode(5,HIGH);
  pinMode(6,HIGH);
  //set the led pins
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);  
  
  tm1637.init();
  tm1637.set(BRIGHTEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}


void loop(){

  while(keyPress()==0){ 
    
    //Serial.println("wait for input");
    } //Wait for a key press to start the game
  gameDelay = 1000;
  playing = 1; //Reset the flag from last game
  gameRunning(); //Start the Game
  
}

//This function will flash all buttons and wait for a button press to start the game.
//Speed will be set depending on which button is pressed
boolean keyPress(){
digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    delay(50);
  boolean pressed = 0;
  
  if(digitalRead(2)==LOW || digitalRead(3)==LOW || digitalRead(4)==LOW || digitalRead(5)==LOW || digitalRead(6)==LOW){
  pressed = 1; 
    }
          
  return pressed;
  
}


void gameRunning(){
score = 0; 
int newLED; //This is the the LED that we're goign to light next
randomSeed(analogRead(A0)); //Random Seed
delay(1000); 



while(playing == 1){ 

playing=0; //Assumed guilty until proven innocent 
      byte randomLed = random(9,14); // pick a random LED
while(newLED == randomLed){ //make sure it's not the same as the last one
        randomLed = random(9,14); 
      }
      newLED = randomLed; 
Serial.println(newLED); //Serial debug stuff
int newButton = getButton(newLED); //The getButton function returns the button number corresponding to the LED that's on.

digitalWrite(newLED, HIGH); //Light up the random LED.

for(int t=0; t<gameDelay; t++){ //Game cycles delay
  hitButton = digitalRead(newButton); //Grab the button status
  if(hitButton==0){
    playing=1;
    } //if button was pressed
  delay(1);
}
digitalWrite(newLED, LOW); //turn off the LED
score=score+1; //increase the score

gameDelay=(gameDelay-15); //Speed up the game after every button press
ones = score%10;
tens = (score/10)%10;
hundreds = (score/100)%10;
thousands = (score/1000)%10;
tm1637.display(3,ones);
tm1637.display(2,tens);
tm1637.display(1,hundreds);
tm1637.display(0,thousands);

} 


  
}

//This functio returns the corresponding button pin for a given LED pin.
int getButton(int newLED){ 

int Button; 
  
 switch (newLED) {
  
   case 9:
   Button = 2;
   break;
   case 10:
   Button = 3;   
   break;
   case 11:
   Button = 4;   
   break;
   case 12:
   Button = 5;   
   break;
   case 13:
   Button = 6;   
   break;
   
 } 
  
  return Button; 
  
}
