#ifndef _USBDRAWABLE__H_
#define _USBDRAWABLE__H_

#include "usbcheck.h"
#include "lcd-display.h"

class BaseDrawable : public USBDrawable {
  protected:
   LCD_DISPLAY *tft;
  public:
    BaseDrawable(LCD_DISPLAY &tft);
};

class CLeftDrawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition();
    void drawMeAt(int x, int y);
};

class CRightDrawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition();
    void drawMeAt(int x, int y);
};

class A2Drawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition();
    void drawMeAt(int x, int y);
};

class A3Drawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition();
    void drawMeAt(int x, int y);
};

class MiniDrawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition();
    void drawMeAt(int x, int y);
};

class MicroDrawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition();
    void drawMeAt(int x, int y);
};
#endif
