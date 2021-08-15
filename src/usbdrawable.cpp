#include "usbdrawable.h"

BaseDrawable::BaseDrawable(LCD_DISPLAY &tft) {
  Serial.println("Created class");
  this->tft = &tft;
};

//CLeftDrawable::CLeftDrawable(LCD_DISPLAY &tft): BaseDrawable(tft) {
//};

void USBC_template(LCD_DISPLAY *tft, int x, int y, bool highlight = false)
{
  int x2 = x+2;
  int x3 = x+20;

  if (highlight) 
    tft->fillRoundRect(x, y, 26, 137, 10, tft->WHITE);

  for (int yp=0; yp < 120; yp += 10) {
    tft->fillRect(x2, y+11+yp, 4, 6, tft->YELLOW);  
    tft->fillRect(x3, y+11+yp, 4, 6, tft->YELLOW);  
  }

  tft->drawRoundRect(x, y, 26, 137, 10, tft->GREEN);
  tft->drawRoundRect(x2, y+2, 22, 133, 10, tft->GREEN);

  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);
}

void CLeftDrawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");
  //this->tft->USBC_Left_template();
  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);

  tft->setCursor(20, 15);
  tft->println("USB C");
  tft->setCursor(20, 25);
  tft->println(" v3.0");

  USBC_template(tft, 22, 52);
};

void CLeftDrawable::drawMeAt(int x, int y, bool highlight = false) {
  USBC_template(tft, x, y);
};

void CRightDrawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");
  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);

  tft->setCursor(270, 15);
  tft->println("USB C");
  tft->setCursor(270, 25);
  tft->println(" v3.0");

  USBC_template(tft, 275, 52);
};

void CRightDrawable::drawMeAt(int x, int y, bool highlight = false) {
  USBC_template(tft, x, y);
};

void A2Drawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");

  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);
  tft->setCursor(20, 15);
  tft->println("USB A");
  tft->setCursor(20, 25);
  tft->println(" v2.0");

  drawMeAt(18, 53);

};

void A2Drawable::drawMeAt(int x, int y, bool highlight = false) {
  int x2 = x + 15;

  if (highlight) {
    tft->fillRoundRect(x, y, 34, 135, 3, tft->WHITE);
  }

  tft->fillRect(x2, y+15, 4, 14, tft->YELLOW);
  tft->fillRect(x2, y+45, 4, 14, tft->YELLOW);
  tft->fillRect(x2, y+75, 4, 14, tft->YELLOW);
  tft->fillRect(x2, y+105, 4, 14, tft->YELLOW);

  tft->fillRect(x+3, y+3, 13, 129, tft->WHITE);
  tft->drawRect(x+3, y+3, 13, 129, tft->BLUE);
  tft->drawRoundRect(x, y, 34, 135, 3, tft->GREEN);
  tft->drawRect(x+1, y+1, 32, 133, tft->GREEN);

};

void A3Drawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");

  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);
  tft->setCursor(20, 15);
  tft->println("USB A");
  tft->setCursor(20, 25);
  tft->println(" v3.0");

  drawMeAt(18,53);
};

void A3Drawable::drawMeAt(int x, int y, bool highlight = false) {

  if (highlight) {
    tft->fillRoundRect(x, y, 34, 135, 3, tft->WHITE);
  }

  tft->fillRect(x + 16, y+12, 7, 7, tft->CYAN);
  tft->fillRect(x + 16, y+34, 7, 7, tft->CYAN);
  tft->fillRect(x + 16, y+63, 7, 7, tft->CYAN);
  tft->fillRect(x + 16, y+92, 7, 7, tft->CYAN);
  tft->fillRect(x + 16, y+114, 7, 7, tft->CYAN);
  tft->fillRect(x + 15, y+15, 4, 14, tft->YELLOW);
  tft->fillRect(x + 15, y+45, 4, 14, tft->YELLOW);
  tft->fillRect(x + 15, y+75, 4, 14, tft->YELLOW);
  tft->fillRect(x + 15, y+105, 4, 14, tft->YELLOW);

  tft->fillRect(x+3, y+3, 13, 129, tft->BLUE);
  tft->drawRect(x+3, y+3, 13, 129, tft->BLACK);
  tft->drawRoundRect(x, y, 34, 135, 3, tft->GREEN);
  tft->drawRect(x+1, y+1, 32, 133, tft->GREEN);      
};

void MiniDrawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");
  this->tft->USB_mini_template();
};

void MiniDrawable::drawMeAt(int x, int y, bool highlight = false) {
  this->tft->USB_mini_template(x,y);
};

void MicroDrawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");
  this->tft->USB_micro_template();
};

void MicroDrawable::drawMeAt(int x, int y, bool highlight = false) {
  this->tft->USB_micro_template(x,y);
};