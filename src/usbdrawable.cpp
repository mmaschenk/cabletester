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
  this->tft->USBC_Left_template();
};

void CLeftDrawable::drawMeAt(int x, int y) {
  this->tft->USBC_template(x, y);
};

void CRightDrawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");
  //tft->USBC_Right_template();
  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);

  tft->setCursor(270, 15);
  tft->println("USB C");
  tft->setCursor(270, 25);
  tft->println(" v3.0");

  USBC_template(this->tft, 275, 52);
};

void CRightDrawable::drawMeAt(int x, int y) {
  this->tft->USBC_template(x, y);
};

void A2Drawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");
  this->tft->USB2_A_template();
};

void A2Drawable::drawMeAt(int x, int y) {
  this->tft->USB2_A_template(x,y);
};

void A3Drawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");
  this->tft->USB3_A_template();
};

void A3Drawable::drawMeAt(int x, int y) {
  this->tft->USB3_A_template(x,y);
};

void MiniDrawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");
  this->tft->USB_mini_template();
};

void MiniDrawable::drawMeAt(int x, int y) {
  this->tft->USB_mini_template(x,y);
};

void MicroDrawable::drawMeAtDefaultPosition() {
  Serial.println("Drawing at default position");
  this->tft->USB_micro_template();
};

void MicroDrawable::drawMeAt(int x, int y) {
  this->tft->USB_micro_template(x,y);
};