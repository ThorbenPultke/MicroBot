//Display Class to easy access the 16x2 LCD
#include <Wire.h>
#include <hd44780.h>            // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h>  // i2c expander i/o class header
#include "Arduino.h"
class LCD_Display {
  private:
    const int __LCD_COLS = 16;
    const int __LCD_ROWS = 2;
    hd44780_I2Cexp lcd;
  public:
    LCD_Display() {}

    void writeText(String Text) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(Text);
    }

    void setupLCD() {
      int status;
      status = lcd.begin(__LCD_COLS, __LCD_ROWS);
      if (status) // non zero status means it was unsuccesful
      {
        // begin() failed
        // blink error code using the onboard LED if possible
        hd44780::fatalError(status); // does not return
      }
      lcd.lineWrap();
    }
};
