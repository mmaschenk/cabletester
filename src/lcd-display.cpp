#include "lcd-display.h"

void LCD_DISPLAY::USB_micro_template(int x, int y, bool highlight = false) {
  fillRoundRect(x+22, y+1, 12, 109, 8, BLUE);
  fillRect(x+22, y+1, 6, 4, BLUE); 
  fillRect(x+22, y+105, 6, 4, BLUE); 

  drawRoundRect(x+9, y, 27, 111, 10, GREEN);
  drawRoundRect(x+10, y+1, 25, 109, 8, GREEN);
  fillRect(x+9, y, 6, 111, BLACK);
  drawLine(x, y+15, x+15, y, GREEN); 
  drawLine(x+1, y+15, x+16, y, GREEN);
  drawLine(x, y+94, x+15, y+109, GREEN);
  drawLine(x+1, y+94, x+16, y+109, GREEN);
  drawLine(x, y+15, x, y+94, GREEN);
  drawLine(x+1, y+15, x+1, y+94, GREEN);

  if (highlight) {
    fillRect(x+2, y+15, 20, 80, RED);
    fillTriangle(x+3, y+14, x+15, y+14, x+15, y+2, RED );
    fillRect(x+16, y+2, 6, 13, RED);

    fillTriangle(x+3, y+95, x+15, y+107, x+15, y+95, RED );
    fillRect(x+16, y+95, 6, 14, RED);
  }

  for (int yc = 0; yc <= 80; yc += 20) {
    fillRect(x+21, y+12+yc, 4, 8, YELLOW);
  }
}

void LCD_DISPLAY::USB_micro_template()
{
  // Draws the connector and pins for USB Micro-b on RHS of screen

  setTextColor(WHITE);
  setTextSize(0);
  setCursor(255, 15);
  println("USB Micro");
  setCursor(260, 25);
  println(" v2.0");

  USB_micro_template(264, 70);

}


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
