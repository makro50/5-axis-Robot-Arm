/*

 5 Axis Robot Arm controlled by Sparkfun Joystick Shield and Arduino Mega.
Jan 11, 2016 
By David Leiva SPEED CONTROL 2
*/
#include <Servo.h>
//Create variables for each button on the Joystick Shield to assign the pin numbers
char button0 = 3, button1 = 4, button2 = 5, button3 = 6;
char sel = 2;
int armRot = 90;
int baseRot =90;
int clawstatus =  false;
int clawspinpos =90;
int clawudpos = 90;

Servo base;  
Servo arm; 
Servo ClawOpen; 
Servo ClawSpin;
Servo ClawUpDown; 

int valX;    // variable to read the value from the analog pin
int valY;

void setup(void)
{
  pinMode(sel, INPUT);      //Set the Joystick 'Select'button as an input
  digitalWrite(sel, HIGH);  //Enable the pull-up resistor on the select button

  pinMode(button0, INPUT);      //Set the Joystick button 0 as an input
  digitalWrite(button0, HIGH);  //Enable the pull-up resistor on button 0

  pinMode(button1, INPUT);      //Set the Joystick button 1 as an input
  digitalWrite(button1, HIGH);  //Enable the pull-up resistor on button 1

  pinMode(button2, INPUT);      //Set the Joystick button 2 as an input
  digitalWrite(button2, HIGH);  //Enable the pull-up resistor on button 2

  pinMode(button3, INPUT);      //Set the Joystick button 3 as an input
  digitalWrite(button3, HIGH);  //Enable the pull-up resistor on button 3
  
    base.attach(53);  // attaches the servo on pin 9 to the servo object
    arm.attach(51);  
    ClawOpen.attach(49);  
    ClawSpin.attach(47);  
    ClawUpDown.attach(45);  
    
    
    
  Serial.begin(9600);           //Turn on the Serial Port at 9600 bps
}

void loop(void)
{
 /*  Serial.print(digitalRead(sel));       //Read the value of the select button and print it on the serial port.
  Serial.print(digitalRead(button0));   //Read the value of the button 0 and print it on the serial port.
  Serial.print(digitalRead(button1));   //Read the value of the button 1 and print it on the serial port.
  Serial.print(digitalRead(button2));   //Read the value of the button 2 and print it on the serial port.
  Serial.print(digitalRead(button3)); //Read the value of the button 3 and print it on the serial port.
   Serial.print("\t"); */
   Serial.print(valX);
   Serial.print("\t");
   Serial.print(valY);
   Serial.println("");
  Serial.print(armRot);
  Serial.print("||");
  Serial.print(baseRot);
  Serial.print(clawstatus);

            // reads the value of the potentiometer (value between 0 and 1023) 
  valX =analogRead(0);
/*  valX = (map(valX, 0, 1023, 0, 18)*10);     // scale it to use it with the servo (value between 0 and 180) 
  ClawSpin.write(valX);          */
  // sets the servo position according to the scaled value 
 if (valX < 300) {
    clawspinpos =  clawspinpos + 1;
    clawspinpos = constrain(clawspinpos, 0 ,180);
     ClawSpin.write(clawspinpos);  
  } else if (valX > 700) {
   clawspinpos =  clawspinpos - 1;
    clawspinpos = constrain(clawspinpos, 0 ,180);
    ClawSpin.write(clawspinpos);  
  }
  
           // reads the value of the potentiometer (value between 0 and 1023) 
  valY = analogRead(1);         
  /* valY = (map(valY, 0, 1023, 0, 18)*10);     // scale it to use it with the servo (value between 0 and 180) 
  ClawUpDown.write(valY); */                 // sets the servo position according to the scaled value 
   if (valY < 300) {
    clawudpos =  clawudpos + 1;
    clawudpos = constrain(clawudpos, 0 ,180);
     ClawUpDown.write(clawudpos);  
  } else if (valY > 700) {
   clawudpos =  clawudpos - 1;
    clawudpos = constrain(clawudpos, 0 ,180);
    ClawUpDown.write(clawudpos);  
  }
  
  if (digitalRead(button0) == LOW) {
    baseRot = baseRot + 1;
    baseRot = constrain(baseRot, 0 ,180);
    base.write(baseRot); 
}
  if (digitalRead(button3) == LOW) {
        baseRot = baseRot - 1;
    baseRot = constrain(baseRot, 0 ,180);
    base.write(baseRot); 
}
  if (digitalRead(button2) == LOW) {
        armRot = armRot + 1;
    armRot = constrain(armRot, 0 ,180);
    arm.write(armRot); 
}
  if (digitalRead(button1) == LOW) {
        armRot = armRot - 1;
    armRot = constrain(armRot, 0 ,180);
    arm.write(armRot); 
}

  if (digitalRead(sel) == LOW) {
    ClawOpen.write(0); 
    clawstatus = true;
} else {
  if (clawstatus == true) {
     ClawOpen.write(138);
     clawstatus = false;
  }
  else {
    clawstatus = false;
  }

 
}
}
  //Wait for 100 ms, then go back to the beginning of 'loop' and repeat.
  

