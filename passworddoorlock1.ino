#include <Servo.h>

#include <LiquidCrystal_I2C.h>

#include <Keypad.h>


#ifndef PASSWORD_H

#define PASSWORD_H

 

#define MAX_PASSWORD_LENGTH (20)



#define STRING_TERMINATOR '\0'



class Password {

public:


	Password(char* pass);


	void set(char* pass);


	bool is(char* pass);


	bool append(char character);

	void reset();


	bool evaluate();



	Password &operator=(char* pass);


	bool operator==(char* pass);


	bool operator!=(char* pass);


	Password &operator<<(char character);

	

private:

	char* target;

	char guess[ MAX_PASSWORD_LENGTH ];

	byte currentIndex;

};



#endif




Password::Password(char* pass) {

  set(pass);

  reset();

}



void Password::set(char* pass) { target = pass; }



bool Password::is(char* pass) {

  byte i = 0;

  while (*pass && i < MAX_PASSWORD_LENGTH) {

    guess[i] = pass[i];

    i++;

  }

  return evaluate();

}



bool Password::append(char character) {

  if (currentIndex + 1 == MAX_PASSWORD_LENGTH) {

    return false;

  } else {

    guess[currentIndex++] = character;

    guess[currentIndex] = STRING_TERMINATOR; 

  }

  return true;

}



void Password::reset() {

  currentIndex = 0;

  guess[currentIndex] = STRING_TERMINATOR;

}



bool Password::evaluate() {

  char pass = target[0];

  char guessed = guess[0];

  for (byte i = 1; i < MAX_PASSWORD_LENGTH; ++i) {


    if ((STRING_TERMINATOR == pass) && (STRING_TERMINATOR == guessed)) {

      return true;  

    } else if ((pass != guessed) || (STRING_TERMINATOR == pass) ||

               (STRING_TERMINATOR == guessed)) {

      return false; 

    }


    pass = target[i];

    guessed = guess[i];

  }

  return false;

}



Password& Password::operator=(char* pass) {

  set(pass);

  return *this;

}


bool Password::operator==(char* pass) { return is(pass); }



bool Password::operator!=(char* pass) { return !is(pass); }



Password& Password::operator<<(char character) {

  append(character);

  return *this;

}

#define buzzer 11



Servo servo;

LiquidCrystal_I2C lcd(0x27, 16, 2);



String newPasswordString; 

char newPassword[6]; 

byte a = 5;

bool value = true;



Password password = Password("1234"); //Enter your password



byte maxPasswordLength = 6;

byte currentPasswordLength = 0;

const byte ROWS = 4; 

const byte COLS = 4; 



char keys[ROWS][COLS] = {

  {'D', 'C', 'B', 'A'},

  {'#', '9', '6', '3'},

  {'0', '8', '5', '2'},

  {'*', '7', '4', '1'},

};



byte rowPins[ROWS] = {2, 3, 4, 5};

byte colPins[COLS] = {6, 7, 8, 9};



Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void setup() {
 

  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);

  servo.attach(10);

  servo.write(50);

  lcd.init();

  lcd.backlight();

  lcd.setCursor(3, 0);

  lcd.print("WELCOME TO");

  lcd.setCursor(0, 1);

  lcd.print("DOOR LOCK SYSTEM");

  delay(3000);

  lcd.clear();

}



void loop() {

  lcd.setCursor(1, 0);

  lcd.print("ENTER PASSWORD");


  char key = keypad.getKey();

  if (key != NO_KEY) {

    delay(60);

    if (key == 'C') {

      resetPassword();

    } else if (key == 'D') {

      if (value == true) {

        doorlocked();

        value = false;

      } else if (value == false) {

        dooropen();
        dooropenf();

        value = true;

      }

    } else {

      processNumberKey(key);

    }

  }

}


void processNumberKey(char key) {

  lcd.setCursor(a, 1);

  lcd.print("*");

  a++;

  if (a == 11) {

    a = 5;

  }

  currentPasswordLength++;

  password.append(key);



  if (currentPasswordLength == maxPasswordLength) {

    doorlocked();

    dooropen();



  }

}


void dooropen() {

  if (password.evaluate()) {

    digitalWrite(buzzer, HIGH);

    delay(300);

    digitalWrite(buzzer, LOW);

    servo.write(50);

    delay(100);

    lcd.setCursor(0, 0);

    lcd.print("CORRECT PASSWORD");

    lcd.setCursor(0, 1);

    lcd.print("DOOR OPENED");

    delay(2000);

    lcd.clear();

    a = 5;

  } else {

    digitalWrite(buzzer, HIGH);

    delay(200);

    digitalWrite(buzzer, LOW);

    delay(200);

    digitalWrite(buzzer, HIGH);

    delay(200);

    digitalWrite(buzzer, LOW);

    delay(200);

    digitalWrite(buzzer, HIGH);

    delay(200);

    digitalWrite(buzzer, LOW);

    delay(200);

    lcd.setCursor(0, 0);

    lcd.print("WRONG PASSWORD!");

    lcd.setCursor(0, 1);

    lcd.print("PLEASE TRY AGAIN");

    delay(2000);

    lcd.clear();

    a = 5;

  }

  resetPassword();

}


void resetPassword() {

  password.reset();

  currentPasswordLength = 0;

  lcd.clear();

  a = 5;

}



void doorlocked() {

  if (password.evaluate()) {

    digitalWrite(buzzer, HIGH);

    delay(300);

    digitalWrite(buzzer, LOW);

    servo.write(110);

    delay(100);

    lcd.setCursor(0, 0);

    lcd.print("CORRECT PASSWORD");

    lcd.setCursor(2, 1);

    lcd.print("DOOR UNLOCKED");

    delay(2000);

    lcd.clear();

    a = 5;

  } else {

    digitalWrite(buzzer, HIGH);

    delay(200);

    digitalWrite(buzzer, LOW);

    delay(200);

    digitalWrite(buzzer, HIGH);

    delay(200);

    digitalWrite(buzzer, LOW);

    delay(200);

    digitalWrite(buzzer, HIGH);

    delay(200);

    digitalWrite(buzzer, LOW);

    delay(200);

    digitalWrite(buzzer, HIGH);

    delay(200);

    digitalWrite(buzzer, LOW);

    delay(200);

    lcd.setCursor(0, 0);

    lcd.print("WRONG PASSWORD!");

    lcd.setCursor(0, 1);

    lcd.print("PLEASE TRY AGAIN");

    delay(2000);

    lcd.clear();

    a = 5;

  }

  resetPassword();

}

const int ledPin = 10; // Define the pin connected to the LED

void dooropenf() {
  if (password.evaluate()) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH); // Turn on the green LED
    delay(300);
    digitalWrite(buzzer, LOW);
    servo.write(50);
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("CORRECT PASSWORD");
    lcd.setCursor(0, 1);
    lcd.print("DOOR OPENED");
    delay(2000);
    lcd.clear();
    digitalWrite(ledPin, LOW); // Turn off the LED
    a = 5;
  } else {
    // If the password is incorrect, handle it here
  }
  resetPassword();
}