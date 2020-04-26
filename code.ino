#define FanAP  0 
#define FanBP  1 
#define FanAM  A4 
#define FanBM  A5 
#define Motor1AP  8
#define Motor1BP  9
#define Motor1AM  10
#define Motor1BM  11
#define Motor2AP  4
#define Motor2BP  5
#define Motor2AM  6
#define Motor2BM  7 
#define led  12 
#define trigPin  A3
#define Ech1Pin  A2
#define Ech2Pin  A1
#define Ech3Pin  A0
#define ledSwt  2
#define fanSwt  3
#define motorSpeed     60                  
#define stepRevolution 200        
bool ledState = true ;
int previous = 0 ;
float duration;
float distance;
bool FanFire = false;
#include <Stepper.h>
Stepper Motor1 (stepRevolution ,Motor1BP ,Motor1BM ,Motor1AP , Motor1AM);
Stepper Motor2 (stepRevolution,Motor2BP ,Motor2BM ,Motor2AP , Motor2AM);
Stepper Fan    (stepRevolution,FanBP ,FanBM ,FanAP , FanAM);
void setup()
{Serial.begin (9600);
Motor1.setSpeed(motorSpeed);
Motor2.setSpeed(motorSpeed);
Fan.setSpeed(motorSpeed);
pinMode(FanAP ,OUTPUT);
pinMode(FanBP,OUTPUT);
pinMode(FanAM ,OUTPUT);
pinMode(FanBM ,OUTPUT);
pinMode(Motor1AP ,OUTPUT);
pinMode(Motor1BP ,OUTPUT);
pinMode(Motor1AM ,OUTPUT);
pinMode(Motor1BM ,OUTPUT);
pinMode(Motor2AP ,OUTPUT);
pinMode(Motor2BP ,OUTPUT);
pinMode(Motor2AM ,OUTPUT);
pinMode(Motor2BM ,OUTPUT);
pinMode(led, OUTPUT);
pinMode(ledSwt, INPUT);
pinMode(trigPin, OUTPUT);
pinMode(Ech1Pin, INPUT);
pinMode(Ech2Pin, INPUT);
pinMode(Ech3Pin, INPUT);
pinMode(fanSwt, INPUT);
attachInterrupt(digitalPinToInterrupt(fanSwt), ActivateFan, RISING);
}
void loop()
{ if (digitalRead(ledSwt) == HIGH)
  {Motor();} 
  while(FanFire)
  { Fan.step(10);
    Serial.println("Fire");
    blink1();}blink1();
}
void blink1(){
  if(millis() - previous > 1000){
     digitalWrite(led, ledState);
     previous = millis();
     ledState = !ledState;}
}

void Motor(){
  if(Forword()){
    Motor1.step(5);
    Motor2.step(5);}
  else {
      if(Right()){
      Motor2.step(5);}
    else {
      if(Left()){
        Motor1.step(-5);}
      else
      {Motor1.step(-5);
       Motor2.step(-5);}}}
}

bool Forword(){
  digitalWrite( trigPin, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( trigPin, LOW );
  duration = pulseIn(Ech2Pin,HIGH);
  distance = ( duration/2 ) * 0.0344;
  Serial.print("Distance: ");
  Serial.println( distance );
  if(distance < 10)
  {return false;}
  return true;
}
bool Right(){
  digitalWrite( trigPin, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( trigPin, LOW );
  duration = pulseIn(Ech3Pin,HIGH);
  distance = ( duration/2 ) * 0.0344;
  Serial.print("DistantrigPince: ");
  Serial.println( distance );
  if(distance < 10)
  {return false;}
  return true;
}
bool Left(){
  digitalWrite( trigPin, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( trigPin, LOW );
  duration = pulseIn(Ech1Pin,HIGH);
  distance = ( duration/2 ) * 0.0344;
  Serial.print("Distance: ");
  Serial.println( distance );
  if(distance < 10)
  {return false;}
  return true;
}
void ActivateFan()
{FanFire = !FanFire;}
