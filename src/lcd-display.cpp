#include "lcd-display.h"


void LCD_DISPLAY::splashscreen()
{

  // **** Splash Screen

  //  tft.drawRoundRect(0, 0, 320, 240, 10, WHITE);

  byte g = 70;

  // First row of text

  drawCircle(28, g - 40, 20, GREEN);
  setTextColor(GREEN);
  setTextSize(3);
  setCursor(21, g - 50);
  println("U");
  drawCircle(81, g - 40, 20, GREEN);
  setTextColor(GREEN);
  setTextSize(3);
  setCursor(74, g - 50);
  println("S");
  drawCircle(134, g - 40, 20, GREEN);
  setTextColor(GREEN);
  setTextSize(3);
  setCursor(127, g - 50);
  println("B");

  // Second row of text

  drawCircle(28, g + 12, 20, RED);
  setTextColor(RED);
  setTextSize(3);
  setCursor(21, g + 2);
  println("C");
  drawCircle(81, g + 12, 20, RED);
  setTextColor(RED);
  setTextSize(3);
  setCursor(74, g + 2);
  println("A");
  drawCircle(134, g + 12, 20, RED);
  setTextColor(RED);
  setTextSize(3);
  setCursor(127, g + 2);
  println("B");
  drawCircle(187, g + 12, 20, RED);
  setTextColor(RED);
  setTextSize(3);
  setCursor(180, g + 2);
  println("L");
  drawCircle(239, g + 12, 20, RED);
  setTextColor(RED);
  setTextSize(3);
  setCursor(232, g + 2);
  println("E");

  // 3rd row of text

  drawCircle(28, g + 64, 20, YELLOW);
  setTextColor(YELLOW);
  setTextSize(3);
  setCursor(21, g + 54);
  println("T");
  drawCircle(81, g + 64, 20, YELLOW);
  setTextColor(YELLOW);
  setTextSize(3);
  setCursor(74, g + 54);
  println("R");
  drawCircle(134, g + 64, 20, YELLOW);
  setTextColor(YELLOW);
  setTextSize(3);
  setCursor(127, g + 54);
  println("A");
  drawCircle(187, g + 64, 20, YELLOW);
  setTextColor(YELLOW);
  setTextSize(3);
  setCursor(180, g + 54);
  println("C");
  drawCircle(239, g + 64, 20, YELLOW);
  setTextColor(YELLOW);
  setTextSize(3);
  setCursor(232, g + 54);
  println("E");
  drawCircle(292, g + 64, 20, YELLOW);
  setTextColor(YELLOW);
  setTextSize(3);
  setCursor(285, g + 54);
  println("R");
  setTextColor(WHITE);
  setTextSize(2);
  setCursor(10, 170);
  println("Test, Diagnose, Repair");
  setTextColor(WHITE);
  setTextSize(1);
  setCursor(10, 200);
  println("By TechKiwiGadgets 2021");

  // Arduino logo

  drawCircle(20, 225, 9, WHITE);
  drawCircle(37, 225, 9, WHITE);
  drawCircle(20, 225, 8, WHITE);
  drawCircle(37, 225, 8, WHITE);
  setTextColor(WHITE);
  setTextSize(2);
  setCursor(16, 218);
  println("-");
  setCursor(33, 218);
  println("+");

  //       tft.setTextColor(WHITE);  tft.setTextSize(1);
  //       tft.setCursor(10, 220);   tft.println("Arduino");

  delay(2000);

  setTextColor(WHITE);
  setTextSize(0);
  fillScreen(BLACK);
}

void LCD_DISPLAY::splashscreen2()
{
  // **** Splash Screen

  //  tft.drawRoundRect(0, 0, 320, 240, 10, WHITE);

  byte g = 70;

  // First row of text

  drawCircle(28, g - 40, 20, GREEN);
  fillCircle(28, g - 40, 17, GREEN);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(21, g - 50);
  println("U");
  drawCircle(81, g - 40, 20, GREEN);
  fillCircle(81, g - 40, 17, GREEN);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(74, g - 50);
  println("S");
  drawCircle(134, g - 40, 20, GREEN);
  fillCircle(134, g - 40, 17, GREEN);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(127, g - 50);
  println("B");

  // Second row of text

  drawCircle(28, g + 12, 20, RED);
  fillCircle(28, g + 12, 17, RED);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(21, g + 2);
  println("C");
  drawCircle(81, g + 12, 20, RED);
  fillCircle(81, g + 12, 17, RED);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(74, g + 2);
  println("A");
  drawCircle(134, g + 12, 20, RED);
  fillCircle(134, g + 12, 17, RED);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(127, g + 2);
  println("B");
  drawCircle(187, g + 12, 20, RED);
  fillCircle(187, g + 12, 17, RED);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(180, g + 2);
  println("L");
  drawCircle(239, g + 12, 20, RED);
  fillCircle(239, g + 12, 17, RED);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(232, g + 2);
  println("E");

  // 3rd row of text

  drawCircle(28, g + 64, 20, YELLOW);
  fillCircle(28, g + 64, 17, YELLOW);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(21, g + 54);
  println("T");
  drawCircle(81, g + 64, 20, YELLOW);
  fillCircle(81, g + 64, 17, YELLOW);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(74, g + 54);
  println("R");
  drawCircle(134, g + 64, 20, YELLOW);
  fillCircle(134, g + 64, 17, YELLOW);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(127, g + 54);
  println("A");
  drawCircle(187, g + 64, 20, YELLOW);
  fillCircle(187, g + 64, 17, YELLOW);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(180, g + 54);
  println("C");
  drawCircle(239, g + 64, 20, YELLOW);
  fillCircle(239, g + 64, 17, YELLOW);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(232, g + 54);
  println("E");
  drawCircle(292, g + 64, 20, YELLOW);
  fillCircle(292, g + 64, 17, YELLOW);
  setTextColor(BLACK);
  setTextSize(3);
  setCursor(285, g + 54);
  println("R");
  setTextColor(WHITE);
  setTextSize(2);
  setCursor(10, 170);
  println("Test, Diagnose, Repair");
  setTextColor(WHITE);
  setTextSize(1);
  setCursor(10, 200);
  println("By TechKiwiGadgets 2021");
  // Arduino logo

  drawCircle(20, 225, 9, WHITE);
  drawCircle(37, 225, 9, WHITE);
  drawCircle(20, 225, 8, WHITE);
  drawCircle(37, 225, 8, WHITE);
  setTextColor(WHITE);
  setTextSize(2);
  setCursor(16, 218);
  println("-");
  setCursor(33, 218);
  println("+");

  //       tft.setTextColor(WHITE);  tft.setTextSize(1);
  //       tft.setCursor(10, 220);   tft.println("Arduino");

  delay(1000);

  setTextColor(WHITE);
  setTextSize(0);
  fillScreen(BLACK);
}
