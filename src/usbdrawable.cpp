#include "usbdrawable.h"

BaseDrawable::BaseDrawable(LCD_DISPLAY &tft) {
  Serial.println("Created class");
  this->tft = &tft;
};

void BaseDrawable::drawMeAtDefaultPosition() {
  drawMeAtDefaultPosition(false);
};

void BaseDrawable::drawMeAt(int x, int y) {
  drawMeAt(x, y, false);
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

void CLeftDrawable::drawMeAtDefaultPosition(bool highlight) {
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

void CRightDrawable::drawMeAtDefaultPosition(bool highlight) {
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

void A2Drawable::drawMeAtDefaultPosition(bool highlight) {
  Serial.println("Drawing at default position");

  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);
  tft->setCursor(20, 15);
  tft->println("USB A");
  tft->setCursor(20, 25);
  tft->println(" v2.0");

  drawMeAt(18, 53, highlight);

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

void A3Drawable::drawMeAtDefaultPosition(bool highlight) {
  Serial.println("Drawing at default position");

  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);
  tft->setCursor(20, 15);
  tft->println("USB A");
  tft->setCursor(20, 25);
  tft->println(" v3.0");

  drawMeAt(18,53,highlight);
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

void MiniDrawable::drawMeAtDefaultPosition(bool highlight) {
  Serial.println("Drawing at default position");

  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);
  tft->setCursor(255, 15);
  tft->println("USB Mini");
  tft->setCursor(260, 25);
  tft->println(" v2.0");

  drawMeAt(254, 70, highlight);
};

void MiniDrawable::drawMeAt(int x, int y, bool highlight = false) {

  tft->fillRoundRect(x+32, y+1, 12, 109, 4, tft->BLUE);
  tft->drawRoundRect(x+19, y, 27, 111, 10, tft->GREEN);
  tft->drawRoundRect(x+20, y+1, 25, 109, 8, tft->GREEN);
  tft->drawRoundRect(x, y+15, 27, 81, 8, tft->GREEN);
  tft->drawRoundRect(x+1, y+16, 25, 79, 6, tft->GREEN);
  tft->fillRect(x+11, y+17, 20, 77, tft->BLACK);
  tft->fillRect(x+19, y+9, 10, 93, tft->BLACK);
  tft->fillRect(x+12, y+15, 20, 81, tft->BLACK);

  tft->drawLine(x+10, y+15, x+20, y+5, tft->GREEN);
  tft->drawLine(x+11, y+15, x+21, y+5, tft->GREEN);
  tft->drawLine(x+10, y+17, x+25, y+2, tft->BLACK);
  tft->drawLine(x+10, y+18, x+25, y+3, tft->BLACK);

  tft->drawLine(x+10, y+95, x+20, y+105, tft->GREEN);
  tft->drawLine(x+11, y+95, x+21, y+105, tft->GREEN);
  tft->drawLine(x+10, y+93, x+25, y+108, tft->BLACK);
  tft->drawLine(x+10, y+92, x+25, y+107, tft->BLACK);

  if (highlight) {
    tft->fillRect(x+2, y + 21, 30, 69, tft->RED);
    tft->fillCircle(x+7, y + 22, 5, tft->RED);
    tft->fillCircle(x+7, y + 88, 5, tft->RED);
    tft->fillTriangle(x+6, y+20, x+25, y+2, x+25, y+20, tft->RED);
    tft->fillRect(x+26, y+2, 6, 19, tft->RED);
    tft->fillTriangle(x+7, y+90, x+25, y+108, x+25, y+90, tft->RED);
    tft->fillRect(x+26, y+90, 6, 19, tft->RED);
  }

  for (int yc=0; yc < 100; yc+=20) {
    tft->fillRect(x+31, y+12+yc, 4, 8, tft->YELLOW);
  }
};

void MicroDrawable::drawMeAtDefaultPosition(bool highlight) {
  Serial.println("Drawing at default position");

  tft->setTextColor(tft->WHITE);
  tft->setTextSize(0);
  tft->setCursor(255, 15);
  tft->println("USB Micro");
  tft->setCursor(260, 25);
  tft->println(" v2.0");

  drawMeAt(264, 70, highlight);
};

void MicroDrawable::drawMeAt(int x, int y, bool highlight = false) {

  tft->fillRoundRect(x+22, y+1, 12, 109, 8, tft->BLUE);
  tft->fillRect(x+22, y+1, 6, 4, tft->BLUE); 
  tft->fillRect(x+22, y+105, 6, 4, tft->BLUE); 

  tft->drawRoundRect(x+9, y, 27, 111, 10, tft->GREEN);
  tft->drawRoundRect(x+10, y+1, 25, 109, 8, tft->GREEN);
  tft->fillRect(x+9, y, 6, 111, tft->BLACK);
  tft->drawLine(x, y+15, x+15, y, tft->GREEN); 
  tft->drawLine(x+1, y+15, x+16, y, tft->GREEN);
  tft->drawLine(x, y+94, x+15, y+109, tft->GREEN);
  tft->drawLine(x+1, y+94, x+16, y+109, tft->GREEN);
  tft->drawLine(x, y+15, x, y+94, tft->GREEN);
  tft->drawLine(x+1, y+15, x+1, y+94, tft->GREEN);

  if (highlight) {
    tft->fillRect(x+2, y+15, 20, 80, tft->RED);
    tft->fillTriangle(x+3, y+14, x+15, y+14, x+15, y+2, tft->RED );
    tft->fillRect(x+16, y+2, 6, 13, tft->RED);

    tft->fillTriangle(x+3, y+95, x+15, y+107, x+15, y+95, tft->RED );
    tft->fillRect(x+16, y+95, 6, 14, tft->RED);
  }

  for (int yc = 0; yc <= 80; yc += 20) {
    tft->fillRect(x+21, y+12+yc, 4, 8, tft->YELLOW);
  }
};