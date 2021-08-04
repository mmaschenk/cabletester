#include "lcd-display.h"

void LCD_DISPLAY::USBC_Right_template()
{

  //  USB Type C v3.0

  // Right USB C Plug

  setTextColor(WHITE);
  setTextSize(0);

  setCursor(270, 15);
  println("USB C");
  setCursor(270, 25);
  println(" v3.0");

  // Pins USB 3 Pins right
  fillRect(295, 63, 4, 6, YELLOW);
  fillRect(295, 73, 4, 6, YELLOW);
  fillRect(295, 83, 4, 6, YELLOW);
  fillRect(295, 93, 4, 6, YELLOW);
  fillRect(295, 103, 4, 6, YELLOW);
  fillRect(295, 113, 4, 6, YELLOW);
  fillRect(295, 123, 4, 6, YELLOW);
  fillRect(295, 133, 4, 6, YELLOW);
  fillRect(295, 143, 4, 6, YELLOW);
  fillRect(295, 153, 4, 6, YELLOW);
  fillRect(295, 163, 4, 6, YELLOW);
  fillRect(295, 173, 4, 6, YELLOW);

  // Pins USB 3 Pins left
  fillRect(277, 63, 4, 6, YELLOW);
  fillRect(277, 73, 4, 6, YELLOW);
  fillRect(277, 83, 4, 6, YELLOW);
  fillRect(277, 93, 4, 6, YELLOW);
  fillRect(277, 103, 4, 6, YELLOW);
  fillRect(277, 113, 4, 6, YELLOW);
  fillRect(277, 123, 4, 6, YELLOW);
  fillRect(277, 133, 4, 6, YELLOW);
  fillRect(277, 143, 4, 6, YELLOW);
  fillRect(277, 153, 4, 6, YELLOW);
  fillRect(277, 163, 4, 6, YELLOW);
  fillRect(277, 173, 4, 6, YELLOW);

  // Outer Case USB C Right
  drawRoundRect(275, 52, 26, 137, 10, GREEN); // outer
  drawRoundRect(277, 54, 22, 133, 10, GREEN); // inner

  //  tft.drawRoundRect(273, 50, 30, 141, 12, MAGENTA);   // outer
  //  tft.drawRoundRect(277, 54, 22, 133, 10, MAGENTA);  // inner

  setTextColor(WHITE);
  setTextSize(0);

  /*
  // USB C pin outs
  setCursor(195, 2);     println("GND     A1");
  setCursor(195, 11);    println("GND    B12");
  setCursor(195, 20);    println("TX1+    A2");
  setCursor(195, 30);    println("RX1+   B11");
  setCursor(195, 40);    println("TX1-    A3");
  setCursor(195, 50);    println("RX1-   B10");
  setCursor(195, 60);    println("vBUS    A4");
  setCursor(195, 70);    println("vBUS    B9");
  setCursor(195, 80);    println("CC1     A5");
  setCursor(195, 90);    println("SBUS2   B8");
  setCursor(195, 100);   println("D+      A6");
  setCursor(195, 110);   println("D-      B7");
  setCursor(195, 120);   println("D-      A7");
  setCursor(195, 130);   println("D+      B6");
  setCursor(195, 140);   println("SBU1    A8");
  setCursor(195, 150);   println("CC2     B5");
  setCursor(195, 160);   println("vBUS    A9");
  setCursor(195, 170);   println("vBUS    B4");
  setCursor(195, 180);   println("RX2-   A10");
  setCursor(195, 190);   println("TX2-    B3");
  setCursor(195, 200);   println("RX2+   A11");
  setCursor(195, 210);   println("RX2-    B2");
  setCursor(195, 220);   println("GND    A12");
  setCursor(195, 230);   println("GND     B1");
  drawRoundRect(0, 0, 320, 240, 10, WHITE);
  */
}

void LCD_DISPLAY::USBC_Left_template()
{

  //  USB Type C Cable v3.0

  setTextColor(WHITE);
  setTextSize(0);

  setCursor(20, 15);
  println("USB C");
  setCursor(20, 25);
  println(" v3.0");

  // Pins USB 3 Pins right
  fillRect(42, 63, 4, 6, YELLOW);
  fillRect(42, 73, 4, 6, YELLOW);
  fillRect(42, 83, 4, 6, YELLOW);
  fillRect(42, 93, 4, 6, YELLOW);
  fillRect(42, 103, 4, 6, YELLOW);
  fillRect(42, 113, 4, 6, YELLOW);
  fillRect(42, 123, 4, 6, YELLOW);
  fillRect(42, 133, 4, 6, YELLOW);
  fillRect(42, 143, 4, 6, YELLOW);
  fillRect(42, 153, 4, 6, YELLOW);
  fillRect(42, 163, 4, 6, YELLOW);
  fillRect(42, 173, 4, 6, YELLOW);

  // Pins USB 3 Pins left
  fillRect(24, 63, 4, 6, YELLOW);
  fillRect(24, 73, 4, 6, YELLOW);
  fillRect(24, 83, 4, 6, YELLOW);
  fillRect(24, 93, 4, 6, YELLOW);
  fillRect(24, 103, 4, 6, YELLOW);
  fillRect(24, 113, 4, 6, YELLOW);
  fillRect(24, 123, 4, 6, YELLOW);
  fillRect(24, 133, 4, 6, YELLOW);
  fillRect(24, 143, 4, 6, YELLOW);
  fillRect(24, 153, 4, 6, YELLOW);
  fillRect(24, 163, 4, 6, YELLOW);
  fillRect(24, 173, 4, 6, YELLOW);

  // Outer Case USB C Left
  drawRoundRect(22, 52, 26, 137, 10, GREEN); // outer
  drawRoundRect(24, 54, 22, 133, 10, GREEN); // inner

  /*
  
 tft.setTextColor(WHITE);  tft.setTextSize(0);

  // USB C pin outs
  tft.setCursor(70, 2);    tft.println("A1    GND");
  tft.setCursor(70, 11);    tft.println("B12   GND");
  tft.setCursor(70, 20);    tft.println("A2    TX1+");
  tft.setCursor(70, 30);    tft.println("B11   RX1+");
  tft.setCursor(70, 40);    tft.println("A3    TX1-");
  tft.setCursor(70, 50);    tft.println("B10   RX1-");
  tft.setCursor(70, 60);    tft.println("A4    vBUS");
  tft.setCursor(70, 70);   tft.println("B9    vBUS");
  tft.setCursor(70, 80);   tft.println("A5     CC1");
  
  tft.setCursor(70, 90);    tft.println("B8   SBUS2");
  tft.setCursor(70, 100);   tft.println("A6      D+");
  tft.setCursor(70, 110);   tft.println("B7      D-");
  tft.setCursor(70, 120);   tft.println("A7      D-");
  tft.setCursor(70, 130);   tft.println("B6      D+");
  tft.setCursor(70, 140);   tft.println("A8    SBU1");
  tft.setCursor(70, 150);   tft.println("B5     CC2");
  tft.setCursor(70, 160);   tft.println("A9    vBUS");
  tft.setCursor(70, 170);   tft.println("B4    vBUS");
  tft.setCursor(70, 180);   tft.println("A10   RX2-");
  tft.setCursor(70, 190);   tft.println("B3    TX2-");
  tft.setCursor(70, 200);   tft.println("A11   RX2+");
  tft.setCursor(70, 210);   tft.println("B2    RX2-");
  tft.setCursor(70, 220);   tft.println("A12    GND");
  tft.setCursor(70, 230);   tft.println("B1     GND");

  tft.drawRoundRect(0, 0, 320, 240, 10, WHITE);
*/
}

void LCD_DISPLAY::USB2_A_template()
{

  // Draws the connector and pins for USB A V2.0 on LHS of screen

  // Left USB A Plug

  setTextColor(WHITE);
  setTextSize(0);
  setCursor(20, 15);
  println("USB A");
  setCursor(20, 25);
  println(" v2.0");

  // Pins USB A Pins left

  fillRect(33, 68, 4, 14, YELLOW);
  fillRect(33, 98, 4, 14, YELLOW);
  fillRect(33, 128, 4, 14, YELLOW);
  fillRect(33, 158, 4, 14, YELLOW);

  // Outer Case USB A Left
  fillRect(21, 56, 13, 129, WHITE);         // Contact Bar
  drawRect(21, 56, 13, 129, BLUE);          // Contact Bar
  drawRoundRect(18, 53, 34, 135, 3, GREEN); // outer
  drawRect(19, 54, 32, 133, GREEN);         // inner
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

  // Outer Case USB Mini Right

  fillRoundRect(286, 71, 12, 109, 4, BLUE);   // Connector Bar
  drawRoundRect(273, 70, 27, 111, 10, GREEN); // right outer
  drawRoundRect(274, 71, 25, 109, 8, GREEN);  // right inner
  drawRoundRect(254, 85, 27, 81, 8, GREEN);   // left outer
  drawRoundRect(255, 86, 25, 79, 6, GREEN);   // left inner
  fillRect(265, 87, 20, 77, BLACK);           // Delete overlap
  fillRect(273, 79, 10, 93, BLACK);           // Delete overlap
  fillRect(266, 85, 20, 81, BLACK);           // Delete overlap

  // Draw angled case

  drawLine(264, 85, 274, 75, GREEN);   // Upper angle
  drawLine(265, 85, 275, 75, GREEN);   // Upper angle
  drawLine(264, 87, 279, 72, BLACK);   // Upper Tidy Up 1
  drawLine(264, 88, 279, 73, BLACK);   // Upper Tidy Up 2
  drawLine(264, 165, 274, 175, GREEN); // Lower angle
  drawLine(265, 165, 275, 175, GREEN); // Lower angle
  drawLine(264, 163, 279, 178, BLACK); // Lower Tidy Up 1
  drawLine(264, 162, 279, 177, BLACK); // Lower Tidy Up 2

  // Draw contacts

  fillRect(285, 82, 4, 8, YELLOW);
  fillRect(285, 102, 4, 8, YELLOW);
  fillRect(285, 122, 4, 8, YELLOW);
  fillRect(285, 142, 4, 8, YELLOW);
  fillRect(285, 162, 4, 8, YELLOW);

  /*
  setCursor(195, 160);    tft.println("Vcc    1");
  setCursor(195, 140);    tft.println("Data-  2");
  setCursor(195, 120);    tft.println("Data+  3");
  setCursor(195, 100);    tft.println("ID     4");
  setCursor(195, 80);     tft.println("GND    5");
  drawRoundRect(0, 0, 320, 240, 10, WHITE);
*/

  /* Wires

  drawLine( 135, 80, 185, 80, WHITE);
  drawLine( 135, 100, 185, 100, WHITE);
  drawLine( 135, 120, 185, 120, WHITE);
  drawLine( 135, 140, 185, 140, WHITE);
  drawLine( 135, 160, 185, 160, WHITE);
*/
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

  // Outer Case USB Mini Right

  fillRoundRect(286, 71, 12, 109, 4, BLUE); // Connector Bar
drawRoundRect(273, 70, 27, 111, 10, GREEN); // right outer
  drawRoundRect(274, 71, 25, 109, 8, GREEN);  // right inner

  //  tft.drawRoundRect(254, 85, 27, 81, 8, WHITE);   // left outer
  //  tft.drawRoundRect(255, 86, 25, 79, 6, WHITE);  // left inner

  fillRect(265, 87, 20, 77, BLACK); // Delete overlap
  fillRect(273, 79, 10, 93, BLACK); // Delete overlap
  fillRect(266, 85, 20, 81, BLACK); // Delete overlap

  // Draw angled case

  drawLine(264, 85, 274, 75, GREEN); // Upper angle
  drawLine(265, 85, 275, 75, GREEN); // Upper angle
drawLine(264, 87, 279, 72, BLACK); // Upper Tidy Up 1
  drawLine(264, 88, 279, 73, BLACK); // Upper Tidy Up 2
drawLine(264, 165, 274, 175, GREEN); // Lower angle
  drawLine(265, 165, 275, 175, GREEN); // Lower angle
drawLine(264, 163, 279, 178, BLACK); // Lower Tidy Up 1
  drawLine(264, 162, 279, 177, BLACK); // Lower Tidy Up 2
drawLine(264, 164, 264, 86, GREEN); // COnnector line
  drawLine(265, 164, 265, 86, GREEN); // COnnector line

  // Draw contacts

  fillRect(285, 82, 4, 8, YELLOW);
  fillRect(285, 102, 4, 8, YELLOW);
  fillRect(285, 122, 4, 8, YELLOW);
  fillRect(285, 142, 4, 8, YELLOW);
  fillRect(285, 162, 4, 8, YELLOW);

  /*
  setCursor(195, 160);    tft.println("Vcc    1");
  setCursor(195, 140);    tft.println("Data-  2");
  setCursor(195, 120);    tft.println("Data+  3");
  setCursor(195, 100);    tft.println("ID     4");
  setCursor(195, 80);     tft.println("GND    5");

  drawRoundRect(0, 0, 320, 240, 10, WHITE);
*/
  /* Wires

  drawLine( 135, 80, 185, 80, WHITE);
  drawLine( 135, 100, 185, 100, WHITE);
  drawLine( 135, 120, 185, 120, WHITE);
  drawLine( 135, 140, 185, 140, WHITE);
  drawLine( 135, 160, 185, 160, WHITE);
*/
}


void LCD_DISPLAY::USB3_A_template()
{

  // Draws the connector and pins for USB A V3.0 on LHS of screen

  //  USB Type A V3.0 to Type B Micro

  // Left USB A Plug

  setTextColor(WHITE);
  setTextSize(0);
  setCursor(20, 15);
  println("USB A");
  setCursor(20, 25);
  println(" v3.0");

  // Pins USB A Pins left

  fillRect(34, 65, 7, 7, CYAN);
  fillRect(34, 87, 7, 7, CYAN);
  fillRect(34, 116, 7, 7, CYAN);
  fillRect(34, 145, 7, 7, CYAN);
  fillRect(34, 167, 7, 7, CYAN);
  fillRect(33, 68, 4, 14, YELLOW);
  fillRect(33, 98, 4, 14, YELLOW);
  fillRect(33, 128, 4, 14, YELLOW);
  fillRect(33, 158, 4, 14, YELLOW);

  // Outer Case USB A Left
  fillRect(21, 56, 13, 129, BLUE);          // Contact Bar
  drawRect(21, 56, 13, 129, BLACK);         // Contact Bar
  drawRoundRect(18, 53, 34, 135, 3, GREEN); // outer
  drawRect(19, 54, 32, 133, GREEN);         // inner

  /*
  setTextColor(WHITE);  tft.setTextSize(0);

  // USB A pin outs

  setCursor(60, 65);    tft.println("5 StdA_SSRX-");
  setCursor(60, 78);    tft.println("4 USB2   GND");
  setCursor(60, 91);    tft.println("6 StdA_SSRX+");
  setCursor(60, 104);   tft.println("3 USB2    D+");
  setCursor(60, 117);   tft.println("7  GND_DRAIN");  
  setCursor(60, 130);   tft.println("2 USB2    D-");
  setCursor(60, 143);   tft.println("8 StdA_SSTX-");  
  setCursor(60, 156);   tft.println("1 USB2   Vcc");
  setCursor(60, 169);   tft.println("9 StdA_SSTX+");
drawRoundRect(0, 0, 320, 240, 10, WHITE);

*/
  /* Wires

  drawLine( 137, 68, 185, 68, WHITE);
  drawLine( 137, 81, 185, 81, WHITE);
  drawLine( 137, 94, 185, 94, WHITE);
  drawLine( 137, 107, 185, 107, WHITE);
  drawLine( 137, 120, 185, 120, WHITE);
  drawLine( 137, 133, 185, 133, WHITE);
  drawLine( 137, 146, 185, 146, WHITE);
  drawLine( 137, 159, 185, 159, WHITE);
  drawLine( 137, 172, 185, 172, WHITE);
*/
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
