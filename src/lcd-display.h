#ifndef _LCD_DISPLAY__H_
#define _LCD_DISPLAY__H_

#include <Adafruit_TFTLCD.h> 

class LCD_DISPLAY : public Adafruit_TFTLCD {
  public:
    LCD_DISPLAY(uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t rst) {
      Serial.println("Instantiated");
    };
};




#endif