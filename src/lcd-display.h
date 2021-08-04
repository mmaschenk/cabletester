#ifndef _LCD_DISPLAY__H_
#define _LCD_DISPLAY__H_

#include <Adafruit_TFTLCD.h> 




class LCD_DISPLAY : public Adafruit_TFTLCD {
  public:
    LCD_DISPLAY(uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t rst) {
      Serial.println("Instantiated");
    };

    void USBC_Right_template();
    void USBC_Left_template();
    void USB2_A_template();
    void USB3_A_template();
    void USB_mini_template();
    void USB_micro_template();
    void splashscreen();
    void splashscreen2();

  private:
    int BLACK = 0x0000;
    int BLUE = 0x001F;
    int MAGENTA = 0xF800;
    int GREEN = 0x07E0;
    int CYAN = 0x07FF;
    int RED = 0xF81F;
    int YELLOW = 0xFFE0;
    int WHITE = 0xFFFF;
};




#endif