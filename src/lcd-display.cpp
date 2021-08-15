#include "lcd-display.h"

void LCD_DISPLAY::USBC_template(int x, int y, bool highlight = false)
{
  int x2 = x+2;
  int x3 = x+20;

  if (highlight) 
    fillRoundRect(x, y, 26, 137, 10, WHITE);

  for (int yp=0; yp < 120; yp += 10) {
    fillRect(x2, y+11+yp, 4, 6, YELLOW);  
    fillRect(x3, y+11+yp, 4, 6, YELLOW);  
  }

  drawRoundRect(x, y, 26, 137, 10, GREEN);
  drawRoundRect(x2, y+2, 22, 133, 10, GREEN);

  setTextColor(WHITE);
  setTextSize(0);
}

/*void LCD_DISPLAY::USBC_Right_template()
{
  setTextColor(WHITE);
  setTextSize(0);

  setCursor(270, 15);
  println("USB C");
  setCursor(270, 25);
  println(" v3.0");

  USBC_template(275, 52);
}*/

void LCD_DISPLAY::USBC_Left_template()
{
  setTextColor(WHITE);
  setTextSize(0);

  setCursor(20, 15);
  println("USB C");
  setCursor(20, 25);
  println(" v3.0");

  USBC_template(22, 52);
}

void LCD_DISPLAY::USB2_A_template(int x, int y, bool highlight = false) {
  int x2 = x + 15;

  if (highlight) {
    fillRoundRect(x, y, 34, 135, 3, WHITE);
  }

  fillRect(x2, y+15, 4, 14, YELLOW);
  fillRect(x2, y+45, 4, 14, YELLOW);
  fillRect(x2, y+75, 4, 14, YELLOW);
  fillRect(x2, y+105, 4, 14, YELLOW);

  fillRect(x+3, y+3, 13, 129, WHITE);
  drawRect(x+3, y+3, 13, 129, BLUE);
  drawRoundRect(x, y, 34, 135, 3, GREEN);
  drawRect(x+1, y+1, 32, 133, GREEN);
}

void LCD_DISPLAY::USB2_A_template()
{
  setTextColor(WHITE);
  setTextSize(0);
  setCursor(20, 15);
  println("USB A");
  setCursor(20, 25);
  println(" v2.0");

  USB2_A_template(18, 53);
}

void LCD_DISPLAY::USB_mini_template(int x, int y, bool highlight = false) {
  fillRoundRect(x+32, y+1, 12, 109, 4, BLUE);
  drawRoundRect(x+19, y, 27, 111, 10, GREEN);
  drawRoundRect(x+20, y+1, 25, 109, 8, GREEN);
  drawRoundRect(x, y+15, 27, 81, 8, GREEN);
  drawRoundRect(x+1, y+16, 25, 79, 6, GREEN);
  fillRect(x+11, y+17, 20, 77, BLACK);
  fillRect(x+19, y+9, 10, 93, BLACK);
  fillRect(x+12, y+15, 20, 81, BLACK);

  drawLine(x+10, y+15, x+20, y+5, GREEN);
  drawLine(x+11, y+15, x+21, y+5, GREEN);
  drawLine(x+10, y+17, x+25, y+2, BLACK);
  drawLine(x+10, y+18, x+25, y+3, BLACK);

  drawLine(x+10, y+95, x+20, y+105, GREEN);
  drawLine(x+11, y+95, x+21, y+105, GREEN);
  drawLine(x+10, y+93, x+25, y+108, BLACK);
  drawLine(x+10, y+92, x+25, y+107, BLACK);

  if (highlight) {
    fillRect(x+2, y + 21, 30, 69, RED);
    fillCircle(x+7, y + 22, 5, RED);
    fillCircle(x+7, y + 88, 5, RED);
    fillTriangle(x+6, y+20, x+25, y+2, x+25, y+20, RED);
    fillRect(x+26, y+2, 6, 19, RED);
    fillTriangle(x+7, y+90, x+25, y+108, x+25, y+90, RED);
    fillRect(x+26, y+90, 6, 19, RED);
  }

  for (int yc=0; yc < 100; yc+=20) {
    fillRect(x+31, y+12+yc, 4, 8, YELLOW);
  }

}

void LCD_DISPLAY::USB_mini_template()
{
  // Draws the connector and pins for USB Mini on RHS of screen

  setTextColor(WHITE);
  setTextSize(0);
  setCursor(255, 15);
  println("USB Mini");
  setCursor(260, 25);
  println(" v2.0");

  USB_mini_template(254, 70);
}

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

void LCD_DISPLAY::USB3_A_template(int x, int y, bool highlight = false) {
  if (highlight) {
    fillRoundRect(x, y, 34, 135, 3, WHITE);
  }

  fillRect(x + 16, y+12, 7, 7, CYAN);
  fillRect(x + 16, y+34, 7, 7, CYAN);
  fillRect(x + 16, y+63, 7, 7, CYAN);
  fillRect(x + 16, y+92, 7, 7, CYAN);
  fillRect(x + 16, y+114, 7, 7, CYAN);
  fillRect(x + 15, y+15, 4, 14, YELLOW);
  fillRect(x + 15, y+45, 4, 14, YELLOW);
  fillRect(x + 15, y+75, 4, 14, YELLOW);
  fillRect(x + 15, y+105, 4, 14, YELLOW);

  fillRect(x+3, y+3, 13, 129, BLUE);
  drawRect(x+3, y+3, 13, 129, BLACK);
  drawRoundRect(x, y, 34, 135, 3, GREEN);
  drawRect(x+1, y+1, 32, 133, GREEN);      
}


void LCD_DISPLAY::USB3_A_template()
{
  // Draws the connector and pins for USB A V3.0 on LHS of screen
  setTextColor(WHITE);
  setTextSize(0);
  setCursor(20, 15);
  println("USB A");
  setCursor(20, 25);
  println(" v3.0");

  USB3_A_template(18,53);
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
