#include <LiquidCrystal.h>
#include "pitches.h"

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int button = 13; //input for the button
int y = 1; //position where the character starts
int down = 0; //prevent button multiclick
int enemy, yspawn, alive = 0; //enemy information
float xspawn = 12; //enemy spawn position and movement
int score = 0; //score display
float fast = 0.3; //enemy speed
void(* resetFunc) (void) = 0;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
} 
void loop()
{
  lcd.setCursor(13,0);
  lcd.print(score); //these two lines will display the score on the right
  if(digitalRead(button) == LOW && down == 0)
  {//button press to change the position of the character
    if(y == 1)
    {
      y = 0;
    }
    else
    {
      y = 1;
    }
    down = 1;
  }

  if(digitalRead(button) == HIGH && down == 1) 
  {//prevent holding button multiclick
    down = 0;
  }

  if(y == 0)
  {//move the character to 1st line
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.setCursor(0,0);
    lcd.print("<");
  }

  if(y == 1)
  {//move the character to 2nd line
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print("<");
  }

  if(alive == 0)
  {//randomly create the enemy
    enemy = random(2); //X or Y
    yspawn = random(2); //line 1 or 2
    alive = 1;
  }

  if(alive == 1)
  {
    lcd.setCursor(xspawn,yspawn);
    if(enemy == 0)
    {
      lcd.print("X");
      if(y != yspawn && xspawn < 1)
      {//when character successfully dodges the X
        tone(6,NOTE_C5,100);
        score += 1;
        alive = 0;
        xspawn = 12;
      }
      else if(y == yspawn && xspawn < 1)
      {//when character fails to dodge the X
        lcd.clear(); //empty the screen
        lcd.setCursor(3,0);
        lcd.print("Game Over");
        lcd.setCursor(7,1);
        lcd.print(score); //game over screen with score
        tone(6,NOTE_E4,300);
        delay(300);
        tone(6,NOTE_C3,600);
        delay(3000);
        resetFunc(); //automatically restart the game
      }
    }
    if(enemy == 1)
    {
      lcd.print("O");
      if(y == yspawn && xspawn < 1)
      {//when character successfully collects the O
        tone(6,NOTE_C5,100);
        score += 1;
        alive = 0;
        xspawn = 12;
      }
      else if(y != yspawn && xspawn < 1)
      {//when character fails to dodge the O
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Game Over");
        lcd.setCursor(7,1);
        lcd.print(score);
        tone(6,NOTE_E4,300);
        delay(300);
        tone(6,NOTE_C3,600);
        delay(3000);
        resetFunc();
      }
   
    }
    xspawn -= fast;
    if(fast < 1)
    {
      //subsequently increase the speed of enemy
      fast *= 1.005;
    }
    lcd.print(" ");
  }

  delay(50);
} 
