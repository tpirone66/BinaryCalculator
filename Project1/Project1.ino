/*
 * Trevor Pirone
 * CMPT 422
 * Project 1: Binary Calculator and Digital Screen Contrast
 * 4/7/2018
 * 
 * The project has an LCD display that cycles through screens on user
 * input with switch buttons. To go to the next screen, press both 
 * buttons at the same time.
 * 
 * Screens:
 * 0 = Welcome Screen
 * 1 = Byte 1
 * 2 = Byte 2
 * 3 = Solution
 * 4 = Adjust Contrast
 * 
 * Pressing the left or right button on screen 0 and 3 have no effect.
 * However, on screens 1, 2, and 4, the effect is as follows:
 * 
 * Left Button:
 * 1 and 2 = Move the cursor right
 * 4 = Increase the contrast value
 * 
 * Right Button:
 * 1 and 2 = Change the bit value
 * 4 = Decrease the contrast value
 * 
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// set up a constant for the contrast pin
const int switchPin = 6;

// variables to hold the value of the switch pins
int switch1State = 0;
int switch2State = 0;

// variables to hold previous value of the switch pins
int prevSwitch1State = 0;
int prevSwitch2State = 0;

// default value of screen contrast
int contrast = 0;

// initialize the starting screen
int screen = 0;

// default binary number value
int binaryNum = 0;

// initial cursor and text position
int column = 0;

/*
 * The values below represent the corresponding values for each bit.
 * The format is as follows:
 * x_screen_x_column 
 * where screen is the number screen and column is the column number
 * on the LCD plus the place value holder.
 * 
 * Ex. x1x7 on the LCD screen is at position (0, 1) on the LCD since 
 * counting begins with 0.
 * 
 */
int x1x7 = 0;
int x1x6 = 0;
int x1x5 = 0;
int x1x4 = 0;
int x1x3 = 0;
int x1x2 = 0;
int x1x1 = 0;
int x1x0 = 0;
int x2x7 = 0;
int x2x6 = 0;
int x2x5 = 0;
int x2x4 = 0;
int x2x3 = 0;
int x2x2 = 0;
int x2x1 = 0;
int x2x0 = 0;
int x3x8 = 0;
int x3x7 = 0;
int x3x6 = 0;
int x3x5 = 0;
int x3x4 = 0;
int x3x3 = 0;
int x3x2 = 0;
int x3x1 = 0;
int x3x0 = 0;


void setup() {
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  // set up the switch pin as an input
  analogWrite(switchPin, contrast);

  // print a message to the LCD
  lcd.print("Hello! Press");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("Both Buttons!");
}

void loop() {
  switch1State = digitalRead(8);
  switch2State = digitalRead(9);

  // change screens if both buttons are pressed
  if (switch1State == HIGH && switch2State == HIGH) {
    delay(200);
    screen++;

    // reset to the welcome screen if we reach last screen
    if (screen > 4) {
      lcd.clear();
      screen = 0;
      setup();
    }

    /*
     * If we are not the last screen, go through the switch statement.
     * The screen numbers are as follows:
     * 0 = Welcome Screen
     * 1 = Byte 1
     * 2 = Byte 2
     * 3 = Solution
     * 4 = Adjust Contrast
     * 
     */
    switch (screen) {
      case 1: {
        byte1Screen(); 
        break; 
      }

      case 2: {
        byte2Screen(); 
        break; 
      }

      case 3: {
        solutionScreen(); 
        break; 
      }
      
      case 4: {
        adjustContrast();
        break;
      }
    }
  }

  // Byte 1 Screen
  if (screen == 1) {
    // left button is pressed
    if (switch1State == HIGH && switch2State == LOW) {
      if (column < 7) {
        moveCursor(); 
      }
    }
    // right button is pressed
    if (switch2State == HIGH && switch1State == LOW) {
      byteOneZeroOrOne();                          
    }
    lcd.setCursor(column, 1);
    lcd.cursor();
  }

  // Byte 2 Screen
  if (screen == 2) {
    // left button is pressed
    if (switch1State == HIGH && switch2State == LOW) {
      if (column < 7) {
        moveCursor();
      }
    }
    // right button is pressed
    if (switch2State == HIGH && switch1State == LOW) {
      byteTwoZeroOrOne();
    }
    lcd.setCursor(column, 1);
    lcd.cursor();
  }

  // Adjust Contrast Screen
  if (screen == 4) {
    // left button is pressed
    if (switch1State == HIGH && switch2State == LOW) {
      increaseContrast();
    }
    // right button is pressed
    if (switch2State == HIGH && switch1State == LOW) {
      decreaseContrast();
    }
  }

  // set the previous state of the button to the current
  prevSwitch2State = switch2State;
  prevSwitch1State = switch1State;
  
}

// method called if screen is 1
void byte1Screen() {
  // reset position of cursor
  if (column > 0) {
    column = 0;
  }
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Byte 1:");
  lcd.setCursor(column, 1);   
  lcd.print("00000000");
}

// method called if screen is 2
void byte2Screen() {
  // reset position of cursor
  if (column > 0) {
    column = 0;
  }
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Byte 2:");
  lcd.setCursor(column, 1);   
  lcd.print("00000000");
}

// method is called if we click left button
// only call it if we are not at the last bit
void moveCursor() {
  binaryNum = 0;
  delay(500);
  column = column + 1;
  lcd.setCursor(column, 1);
}

/*
 * This method determines the value for each bit in 
 * byte 1. The method is called when the right button
 * is hit and changes the values between 0 and 1. That 
 * value is then assigned to that bit depending on the 
 * column.
 * 
 */
void byteOneZeroOrOne() {
  if (binaryNum == 0) {
    binaryNum = 1;
  }
  else {
    binaryNum = 0;
  }
  if (column == 0) {
    x1x7 = binaryNum;
  }
  if (column == 1) {
    x1x6 = binaryNum;
  }
  if (column == 2) {
    x1x5 = binaryNum;
  }
  if (column == 3) {
    x1x4 = binaryNum;
  }
  if (column == 4) {
    x1x3 = binaryNum;
  }
  if (column == 5) {
    x1x2 = binaryNum;
  }
  if (column == 6) {
    x1x1 = binaryNum;
  }
  if (column == 7) {
    x1x0 = binaryNum;
  } 
  lcd.print(binaryNum);
}

/*
 * This method determines the value for each bit in 
 * byte 2. The method is called when the right button
 * is hit and changes the values between 0 and 1. That 
 * value is then assigned to that bit depending on the 
 * column.
 * 
 */
void byteTwoZeroOrOne() {
  if (binaryNum == 0) {
    binaryNum = 1;
  }
  else {
    binaryNum = 0;
  }
  if (column == 0) {
    x2x7 = binaryNum;
  }
  if (column == 1) {
    x2x6 = binaryNum;
  }
  if (column == 2) {
    x2x5 = binaryNum;
  }
  if (column == 3) {
    x2x4 = binaryNum;
  }
  if (column == 4) {
    x2x3 = binaryNum;
  }
  if (column == 5) {
    x2x2 = binaryNum;
  }
  if (column == 6) {
    x2x1 = binaryNum;
  }
  if (column == 7) {
    x2x0 = binaryNum;
  } 
  lcd.print(binaryNum);
}

/*
 * This method contains all of the math that is calculated then 
 * outputted onto the solution screen. When adding binary, we deal
 * with two values: 0 and 1.
 * 
 * In binary 0+0=0, 1+0=0, 1+1=0, but you have to carry 1, so 1+1=10.
 * 1+1+1=1 carry 1 which is 11.
 * 
 * To account for the carry, we can use mod 2 because we are only dealing
 * with 0 and 1, two values.
 * 
 * The caluclator is programmed to handle 8-bit values, but if there is a
 * value greater, then there's overflow. To handle the overflow, we do the
 * same thing for a carry, but now we add an additional column onto the
 * solution screen to account for it.
 * 
 */
void addBinary() {
  x3x0 = x2x0 + x1x0;
  if (x3x0 >= 2) {
    // we need to carry
    // take modulus of byte 1 + byte 2
    x3x0 = x3x0 % 2;
    // carry over remainder to next bit
    x1x1 = x1x1 + 1;
  }
  x3x1 = x2x1 + x1x1;
  if (x3x1 >= 2) {
    x3x1 = x3x1 % 2;
    x1x2 = x1x2 + 1;
  }
  x3x2 = x2x2 + x1x2;
  if (x3x2 >= 2) {
    x3x2 = x3x2 % 2;
    x1x3 = x1x3 + 1;
  }
  x3x3 = x2x3 + x1x3;
  if (x3x3 >= 2) {
    x3x3 = x3x3 % 2;
    x1x4 = x1x4 + 1;
  }
  x3x4 = x2x4 + x1x4;
  if (x3x4 >= 2) {
    x3x4 = x3x4 % 2;
    x1x5 = x1x5 + 1;
  }
  x3x5 = x2x5 + x1x5;
  if (x3x5 >= 2) {
    x3x5 = x3x5 % 2;
    x1x6 = x1x6 + 1;
  }
  x3x6 = x2x6 + x1x6;
  if (x3x6 >= 2) {
    x3x6 = x3x6 % 2;
    x1x7 = x1x7 + 1;
  }
  x3x7 = x2x7 + x1x7;
  if (x3x7 >= 2) {
    // overflow carry
    // take modulus of byte 1 + byte 2
    x3x7 = x3x7 % 2;
    // carry remainder over to next bit
    x3x8 = x3x8 + 1;
    // print the last bit only if we have overflow
    lcd.print(x3x8);
  }
}

// method called if screen is 3
void solutionScreen() {
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Solution:");
  lcd.setCursor(0, 1); 
  
  // call our add binary calculator method 
  addBinary();

  // print solution
  lcd.print(x3x7);
  lcd.print(x3x6);
  lcd.print(x3x5);
  lcd.print(x3x4);
  lcd.print(x3x3);
  lcd.print(x3x2);
  lcd.print(x3x1);
  lcd.print(x3x0);
  lcd.noCursor();
}

/*
 * This method resets any existing bit values stored 
 * in memory to the default value of 0. That way a user 
 * does not need to reset the Arduino if they need to 
 * perform multiple calculations.
 * 
 */
void resetCalc() {
  x1x7 = 0;
  x1x6 = 0;
  x1x5 = 0;
  x1x4 = 0;
  x1x3 = 0;
  x1x2 = 0;
  x1x1 = 0;
  x1x0 = 0;
  x2x7 = 0;
  x2x6 = 0;
  x2x5 = 0;
  x2x4 = 0;
  x2x3 = 0;
  x2x2 = 0;
  x2x1 = 0;
  x2x0 = 0;
  x3x8 = 0;
  x3x7 = 0;
  x3x6 = 0;
  x3x5 = 0;
  x3x4 = 0;
  x3x3 = 0;
  x3x2 = 0;
  x3x1 = 0;
  x3x0 = 0;
}

// method called if screen is 4
void adjustContrast() {
  resetCalc();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Adjust Contrast");
  lcd.setCursor(0, 1);
  lcd.print("Left +   Right -");
}

// increase contrast on screen 4
void increaseContrast() {
  // left button is remained pressed or unpressed
  if (switch1State != prevSwitch1State) {
    // highest contrast possible
    if (contrast <= 0) {
      contrast = 0;
    }
    else {
      // lower contrast
      contrast = contrast - 10;
    }
    analogWrite(switchPin, contrast);
  }
}

// decrease contrast on screen 4
void decreaseContrast() {
  // right button is remained pressed or unpressed
  if (switch2State != prevSwitch2State) {
    // lowest contrast possible
    if (contrast >= 200) {
      contrast = 200;
    }
    else {
      // raise contrast
      contrast = contrast + 10;
    }
    analogWrite(switchPin, contrast);
  }
}

