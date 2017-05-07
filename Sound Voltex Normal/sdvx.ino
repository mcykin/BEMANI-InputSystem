#include "Keyboard.h"
#include "Mouse.h"
#define DELAY            5 

enum PinAssignments
 {
  encoderPinA = 0,
  encoderPinB = 1,
  encoderPinC = 2,
  encoderPinD = 3,
 };

int encoderPos[] = {0,0};
 
 boolean A_set = false;              
 boolean B_set = false;
 boolean C_set = false;              
 boolean D_set = false;
 int i;
 
void setup()
{
  /* KEYBOARD PIN SETTING
   * PIN 13 START
   * PIN 04 TEST
   * PIN A0 BT-A
   * PIN A1 BT-B
   * PIN A2 BT-C
   * PIN A3 BT-D
   * PIN A4 FX-L
   * PIN A5 FX-R
   */
  pinMode(13, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  Keyboard.begin();


  /* KEYBOARD LED PIN SETTING
   * PIN 13(5) START
   * PIN 04(6) TEST
   * PIN A0(7) BT-A
   * PIN A1(8) BT-B
   * PIN A2(9) BT-C
   * PIN A3(10) BT-D
   * PIN A4(11) FX-L
   * PIN A5(12) FX-R
   * BT蓝光 FX红光
   */
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinC, INPUT_PULLUP);
  pinMode(encoderPinD, INPUT_PULLUP);

  Mouse.begin();
 
  attachInterrupt(0, doEncoderC, CHANGE);
  attachInterrupt(1, doEncoderD, CHANGE);
 
  attachInterrupt(2, doEncoderA, CHANGE);
  attachInterrupt(3, doEncoderB, CHANGE);
 
  Serial.begin(9600);
  
}

//按键模拟部分

void loop() {
  
  //SETTING
  if(digitalRead(13)==LOW){
    Keyboard.press('q');
    digitalWrite(5, HIGH);
  }
  if(digitalRead(13)==HIGH){
    Keyboard.release('q');
    digitalWrite(5, LOW);
  }
  if(digitalRead(4)==LOW){
    Keyboard.press('w');
    digitalWrite(6, HIGH);
  }
  if(digitalRead(4)==HIGH){
    Keyboard.release('w');
    digitalWrite(6, LOW);
  }
  
  //BT
  if(digitalRead(A0)==LOW){
    Keyboard.press('d');
    digitalWrite(7, HIGH);
  }
  if(digitalRead(A0)==HIGH){
    Keyboard.release('d');
    digitalWrite(7, LOW);
  }
  if(digitalRead(A1)==LOW){
    Keyboard.press('f');
    digitalWrite(8, HIGH);
  }
  if(digitalRead(A1)==HIGH){
    Keyboard.release('f');
    digitalWrite(8, LOW);
  }
  if(digitalRead(A2)==LOW){
    Keyboard.press('j');
    digitalWrite(9, HIGH);
  }
  if(digitalRead(A2)==HIGH){
    Keyboard.release('j');
    digitalWrite(9, LOW);
  }
  if(digitalRead(A3)==LOW){
    Keyboard.press('k');
    digitalWrite(10, HIGH);
  }
  if(digitalRead(A3)==HIGH){
    Keyboard.release('k');
    digitalWrite(10, LOW);
  }
  
  //FX
  if(digitalRead(A4)==LOW){
    Keyboard.press('c');
    digitalWrite(11, HIGH);
  }
  if(digitalRead(A4)==HIGH){
    Keyboard.release('c');
    digitalWrite(11, LOW);
  }
  if(digitalRead(A5)==LOW){
    Keyboard.press('m');
    digitalWrite(12, HIGH);
  }
  if(digitalRead(A5)==HIGH){
    Keyboard.release('m');
    digitalWrite(12, LOW);
  }

  for(i=0;i<=1;i++)
  {
    if (encoderPos[i] != 0)
    {
      if(i==0)  Mouse.move(encoderPos[i],0,0);
      if(i==1)  Mouse.move(0,encoderPos[i],0);
 
      encoderPos[i] = 0;
    }
  }
 
  delay(DELAY);
}

void doEncoderA()
{
 
  if( digitalRead(encoderPinA) != A_set )
  {  
    A_set = !A_set;
 
    if ( A_set && !B_set )
      encoderPos[0] += 1;
  }
}
 
void doEncoderB()
{
 
  if( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;
   
    if( B_set && !A_set )
      encoderPos[0] -= 1;
  }
}
 
void doEncoderC()
{
  if( digitalRead(encoderPinC) != C_set )
  {  
    C_set = !C_set;
 
    if ( C_set && !D_set )
      encoderPos[1] += 1;
  }
}
 
void doEncoderD()
{
  if( digitalRead(encoderPinD) != D_set ) {
    D_set = !D_set;
   
    if( D_set && !C_set )
      encoderPos[1] -= 1;
  }
}
