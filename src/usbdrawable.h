#ifndef _USBDRAWABLE__H_
#define _USBDRAWABLE__H_

#include "usbcheck.h"
#include "lcd-display.h"

class BaseDrawable : public USBDrawable {
  protected:
   LCD_DISPLAY *tft;
  public:
    BaseDrawable(LCD_DISPLAY &tft);    
    void drawMeAtDefaultPosition();
    virtual void drawMeAtDefaultPosition(bool highlight) = 0;
    void drawMeAt(int x, int y);
    virtual void drawMeAt(int x, int y, bool highlight) =0;
};

class CLeftDrawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition(bool highlight);
    void drawMeAt(int x, int y, bool highlight);
};

class CRightDrawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition(bool highlight);
    void drawMeAt(int x, int y, bool highlight);
};

class A2Drawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition(bool highlight);
    void drawMeAt(int x, int y, bool highlight);
};

class A3Drawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition(bool highlight);
    void drawMeAt(int x, int y, bool highlight);
};

class MiniDrawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition(bool highlight);
    void drawMeAt(int x, int y, bool highlight);
};

class MicroDrawable : public BaseDrawable {
  using BaseDrawable::BaseDrawable;
  public:
    void drawMeAtDefaultPosition(bool highlight);
    void drawMeAt(int x, int y, bool highlight);
};
#endif
