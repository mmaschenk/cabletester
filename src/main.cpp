// USB Cable Tracer By TechKiwiGadgets May 2021

/* 
 *  Final Instructable Version 1
 */

#include <Adafruit_GFX.h>    // Core graphics library
// #include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "lcd-display.h"
#include <TouchScreen.h>

#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin

// Revised Touch Callibration numbers
#define TS_MINX 130
#define TS_MINY 88
#define TS_MAXX 915
//#define TS_MAXY 927
#define TS_MAXY 880

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
int BLACK = 0x0000;
int BLUE = 0x001F;
int MAGENTA = 0xF800;
int GREEN = 0x07E0;
int CYAN = 0x07FF;
int RED = 0xF81F;
int YELLOW = 0xFFE0;
int WHITE = 0xFFFF;

int scangraphic = 0; // Pointer to coordinates of graphic being printed within portscan array

boolean screendrawn = false; // Used to minimise screen refreshes

// These variables store a count of connections detected for each configuration of USB port on left and right
int usbcable_ctr = 1;

// These variables point to the first row of text for this port when drawing screen
int usbCleftpointer = 0;   //
int usbAleftpointer = 70;  //
int usbA3leftpointer = 70; //
int usbMinirighttpointer = 160;
int usbMicrorighttpointer = 160;
int usbCrightpointer = 0;

// These flags indicate if one of 9 valid cable configurations has been detected and are used as a future baseline for refresh of the screen

boolean usbAusbMinicable_det = false;
boolean usbAusbMicrocable_det = false;
boolean usbAusbC_det = false;

boolean usbA3usbMinicable_det = false;
boolean usbA3usbMicrocable_det = false;
boolean usbA3usbC_det = false;

boolean usbCusbMinicable_det = false;
boolean usbCusbMicrocable_det = false;
boolean usbCusbC_det = false;

int countusbwires = 0; //  variable to count number of active connections

// Create a Data Structure for each USB type
// Sensor Number , Pin Number, Status, Text description of pin and function

struct usbCleft
{
  int pinnumber;  // 62 to 69, 14 to 29 sensor pin addresses
  int state;      // 1 or 0 showing digital state of pin
  const char *function; // Text description of function and logical pin number
}

usbCleft[16] = {
    {62, 0, "A1   GND"},
    {63, 0, "A2  TX1+"},
    {64, 0, "A3  TX1-"},
    {65, 0, "A4  vBUS"},
    {17, 0, "A5   CC1"},
    {67, 0, "A6    D+"},
    {68, 0, "A7    D-"},
    {14, 0, "A8  SBU1"},
    {15, 0, "A10 RX2-"},
    {16, 0, "A11 RX2+"},
    {19, 0, "B2  TX2+"},
    {20, 0, "B3  TX2-"},
    {29, 0, "B5   CC2"},
    {25, 0, "B8  SBU2"},
    {27, 0, "B10 RX1-"},
    {28, 0, "B11 RX1+"}};

struct usbCright
{
  int pinnumber;  // 30 to 53 sensor pin addresses
  int state;      // 1 or 0 showing digital state of pin
  const char *function; // Text description of function and logical pin number
}

usbCright[16] = {
    {30, 0, "A1   GND"},
    {31, 0, "A2  TX1+"},
    {38, 0, "A3  TX1-"},
    {46, 0, "A4  vBUS"},
    {51, 0, "A5   CC1"},
    {37, 0, "A8  SBU1"},
    {39, 0, "A10 RX2-"},
    {40, 0, "A11 RX2+"},
    {44, 0, "B2  TX2+"},
    {45, 0, "B3  TX2-"},
    {47, 0, "B5   CC2"},
    {48, 0, "B6    D+"},
    {49, 0, "B7    D-"},
    {50, 0, "B8  SBU2"},
    {52, 0, "B10 RX1-"},
    {53, 0, "B11 RX1+"}};

struct usbAleft
{
  int pinnumber;  // 30 to 33 sensor pin addresses
  int state;      // 1 or 0 showing digital state of pin
  const char *function; // Text description of function and logical pin number
}

usbAleft[4] = {
    {66, 0, "1    Vcc"},
    {67, 0, "2     D-"},
    {68, 0, "3     D+"},
    {69, 0, "4    GND"}};

struct usbA3left
{
  int pinnumber;  // 34 to 42 sensor pin addresses
  int state;      // 1 or 0 showing digital state of pin
  const char *function; // Text description of function and logical pin number
}

usbA3left[9] = {
    {18, 0, "1 USB2   Vcc"},
    {19, 0, "2 USB2    D-"},
    {20, 0, "3 USB2    D+"},
    {21, 0, "4 USB2   GND"},
    {22, 0, "5 Std ASSRX-"},
    {23, 0, "6 Std ASSRX+"},
    {24, 0, "7 GND DRAIN"},
    {25, 0, "8 Std ASSTX-"},
    {26, 0, "9 Std ASSTX+"}};

struct usbMiniright
{
  int pinnumber;  // 34 to 42 sensor pin addresses
  int state;      // 1 or 0 showing digital state of pin
  const char *function; // Text description of function and logical pin number
}

usbMiniright[5] = {
    {32, 0, "1   Vcc"},
    {33, 0, "2    D-"},
    {34, 0, "3    D+"},
    {35, 0, "4    ID"},
    {36, 0, "5   GND"}};

struct usbMicroright
{
  int pinnumber;  // 34 to 42 sensor pin addresses
  int state;      // 1 or 0 showing digital state of pin
  const char *function; // Text description of function and logical pin number
}

usbMicroright[5] = {
    {43, 0, "1    Vcc"},
    {41, 0, "2     D-"},
    {40, 0, "3     D+"},
    {42, 0, "4     ID"},
    {39, 0, "5    GND"}};

//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
LCD_DISPLAY tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOX 78 // Block to clear screen
#define BOXSIZE 80
#define BUTTON 20

boolean debounce = false;

// Array with following Structure: {value , X , Y , Solved }

const byte colcoord[9] = {10, 34, 58, 90, 114, 138, 170, 194, 218};
const byte rowcoord[9] = {8, 33, 58, 88, 113, 138, 170, 194, 218};

byte location = 1;

byte puzzlenum = 1; // These identifier for 5 puzzles stored in memory

byte sudoku[82][14];

byte touchlocation = 0; // Used to track the array value that the stylis is closest to in the Sudoku 9x9 framework

int delay1 = 400; // Pause input into screen

byte tempreading = 0;

void splashscreen();
void usbscan();

void setup()
{
  Serial.begin(115200); // Setupserial interface

  tft.reset();

  uint16_t identifier = tft.readID();
  identifier = 0x9341;

  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  // Reset all values in the Array that have been disconnected

  for (int y = 0; y < 16; y++)
  { // Digital Pins usbCleft & usbCright
    usbCleft[y].state = 0;
    usbCright[y].state = 0;
  }

  for (int y = 0; y < 4; y++)
  { // Digital Pins usbAleft
    usbAleft[y].state = 0;
  }

  for (int y = 0; y < 9; y++)
  { // Digital Pins usbA3left
    usbA3left[y].state = 0;
  }

  for (int y = 0; y < 5; y++)
  { // Digital Pins usbMiniright, usbMicroright
    usbMiniright[y].state = 0;
    usbMicroright[y].state = 0;
  }

  pinMode(13, OUTPUT);

  // Set all pins to digital input pins

  for (int v = 14; v < 54; v++)
  { // Digital Pins
    pinMode(v, INPUT_PULLUP);
  }
  for (int v = 62; v < 70; v++)
  { // Analog Pins A18 - A15
    pinMode(v, INPUT_PULLUP);
  }

#define MINPRESSURE 5
#define MAXPRESSURE 1000

  Serial.println("Setting up splash");
  splashscreen();
  Serial.println("Ended splashscreen");
}

void drawscreen()
{

  //    tft.fillScreen(BLACK);
  // Setup Screen

  GREEN = 0x07E0;
}

void USBC_Right_template()
{

  //  USB Type C v3.0

  // Right USB C Plug

  tft.setTextColor(WHITE);
  tft.setTextSize(0);

  tft.setCursor(270, 15);
  tft.println("USB C");
  tft.setCursor(270, 25);
  tft.println(" v3.0");

  // Pins USB 3 Pins right
  tft.fillRect(295, 63, 4, 6, YELLOW);
  tft.fillRect(295, 73, 4, 6, YELLOW);
  tft.fillRect(295, 83, 4, 6, YELLOW);
  tft.fillRect(295, 93, 4, 6, YELLOW);
  tft.fillRect(295, 103, 4, 6, YELLOW);
  tft.fillRect(295, 113, 4, 6, YELLOW);
  tft.fillRect(295, 123, 4, 6, YELLOW);
  tft.fillRect(295, 133, 4, 6, YELLOW);
  tft.fillRect(295, 143, 4, 6, YELLOW);
  tft.fillRect(295, 153, 4, 6, YELLOW);
  tft.fillRect(295, 163, 4, 6, YELLOW);
  tft.fillRect(295, 173, 4, 6, YELLOW);

  // Pins USB 3 Pins left
  tft.fillRect(277, 63, 4, 6, YELLOW);
  tft.fillRect(277, 73, 4, 6, YELLOW);
  tft.fillRect(277, 83, 4, 6, YELLOW);
  tft.fillRect(277, 93, 4, 6, YELLOW);
  tft.fillRect(277, 103, 4, 6, YELLOW);
  tft.fillRect(277, 113, 4, 6, YELLOW);
  tft.fillRect(277, 123, 4, 6, YELLOW);
  tft.fillRect(277, 133, 4, 6, YELLOW);
  tft.fillRect(277, 143, 4, 6, YELLOW);
  tft.fillRect(277, 153, 4, 6, YELLOW);
  tft.fillRect(277, 163, 4, 6, YELLOW);
  tft.fillRect(277, 173, 4, 6, YELLOW);

  // Outer Case USB C Right
  tft.drawRoundRect(275, 52, 26, 137, 10, GREEN); // outer
  tft.drawRoundRect(277, 54, 22, 133, 10, GREEN); // inner

  //  tft.drawRoundRect(273, 50, 30, 141, 12, MAGENTA);   // outer
  //  tft.drawRoundRect(277, 54, 22, 133, 10, MAGENTA);  // inner

  /*
 tft.setTextColor(WHITE);  tft.setTextSize(0);


  // USB C pin outs
  tft.setCursor(195, 2);     tft.println("GND     A1");
  tft.setCursor(195, 11);    tft.println("GND    B12");
  tft.setCursor(195, 20);    tft.println("TX1+    A2");
  tft.setCursor(195, 30);    tft.println("RX1+   B11");
  tft.setCursor(195, 40);    tft.println("TX1-    A3");
  tft.setCursor(195, 50);    tft.println("RX1-   B10");
  tft.setCursor(195, 60);    tft.println("vBUS    A4");
  tft.setCursor(195, 70);    tft.println("vBUS    B9");
  tft.setCursor(195, 80);    tft.println("CC1     A5");
  tft.setCursor(195, 90);    tft.println("SBUS2   B8");
  tft.setCursor(195, 100);   tft.println("D+      A6");
  tft.setCursor(195, 110);   tft.println("D-      B7");
  tft.setCursor(195, 120);   tft.println("D-      A7");
  tft.setCursor(195, 130);   tft.println("D+      B6");
  tft.setCursor(195, 140);   tft.println("SBU1    A8");
  tft.setCursor(195, 150);   tft.println("CC2     B5");
  tft.setCursor(195, 160);   tft.println("vBUS    A9");
  tft.setCursor(195, 170);   tft.println("vBUS    B4");
  tft.setCursor(195, 180);   tft.println("RX2-   A10");
  tft.setCursor(195, 190);   tft.println("TX2-    B3");
  tft.setCursor(195, 200);   tft.println("RX2+   A11");
  tft.setCursor(195, 210);   tft.println("RX2-    B2");
  tft.setCursor(195, 220);   tft.println("GND    A12");
  tft.setCursor(195, 230);   tft.println("GND     B1");
  

  tft.drawRoundRect(0, 0, 320, 240, 10, WHITE);
*/
}

void USBC_Left_template()
{

  //  USB Type C Cable v3.0

  tft.setTextColor(WHITE);
  tft.setTextSize(0);

  tft.setCursor(20, 15);
  tft.println("USB C");
  tft.setCursor(20, 25);
  tft.println(" v3.0");

  // Pins USB 3 Pins right
  tft.fillRect(42, 63, 4, 6, YELLOW);
  tft.fillRect(42, 73, 4, 6, YELLOW);
  tft.fillRect(42, 83, 4, 6, YELLOW);
  tft.fillRect(42, 93, 4, 6, YELLOW);
  tft.fillRect(42, 103, 4, 6, YELLOW);
  tft.fillRect(42, 113, 4, 6, YELLOW);
  tft.fillRect(42, 123, 4, 6, YELLOW);
  tft.fillRect(42, 133, 4, 6, YELLOW);
  tft.fillRect(42, 143, 4, 6, YELLOW);
  tft.fillRect(42, 153, 4, 6, YELLOW);
  tft.fillRect(42, 163, 4, 6, YELLOW);
  tft.fillRect(42, 173, 4, 6, YELLOW);

  // Pins USB 3 Pins left
  tft.fillRect(24, 63, 4, 6, YELLOW);
  tft.fillRect(24, 73, 4, 6, YELLOW);
  tft.fillRect(24, 83, 4, 6, YELLOW);
  tft.fillRect(24, 93, 4, 6, YELLOW);
  tft.fillRect(24, 103, 4, 6, YELLOW);
  tft.fillRect(24, 113, 4, 6, YELLOW);
  tft.fillRect(24, 123, 4, 6, YELLOW);
  tft.fillRect(24, 133, 4, 6, YELLOW);
  tft.fillRect(24, 143, 4, 6, YELLOW);
  tft.fillRect(24, 153, 4, 6, YELLOW);
  tft.fillRect(24, 163, 4, 6, YELLOW);
  tft.fillRect(24, 173, 4, 6, YELLOW);

  // Outer Case USB C Left
  tft.drawRoundRect(22, 52, 26, 137, 10, GREEN); // outer
  tft.drawRoundRect(24, 54, 22, 133, 10, GREEN); // inner

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

void USB2_A_template()
{

  // Draws the connector and pins for USB A V2.0 on LHS of screen

  // Left USB A Plug

  tft.setTextColor(WHITE);
  tft.setTextSize(0);

  tft.setCursor(20, 15);
  tft.println("USB A");
  tft.setCursor(20, 25);
  tft.println(" v2.0");

  // Pins USB A Pins left

  tft.fillRect(33, 68, 4, 14, YELLOW);
  tft.fillRect(33, 98, 4, 14, YELLOW);
  tft.fillRect(33, 128, 4, 14, YELLOW);
  tft.fillRect(33, 158, 4, 14, YELLOW);

  // Outer Case USB A Left
  tft.fillRect(21, 56, 13, 129, WHITE);         // Contact Bar
  tft.drawRect(21, 56, 13, 129, BLUE);          // Contact Bar
  tft.drawRoundRect(18, 53, 34, 135, 3, GREEN); // outer
  tft.drawRect(19, 54, 32, 133, GREEN);         // inner
}

void USB3_A_template()
{

  // Draws the connector and pins for USB A V3.0 on LHS of screen

  //  USB Type A V3.0 to Type B Micro

  // Left USB A Plug

  tft.setTextColor(WHITE);
  tft.setTextSize(0);

  tft.setCursor(20, 15);
  tft.println("USB A");
  tft.setCursor(20, 25);
  tft.println(" v3.0");

  // Pins USB A Pins left

  tft.fillRect(34, 65, 7, 7, CYAN);
  tft.fillRect(34, 87, 7, 7, CYAN);
  tft.fillRect(34, 116, 7, 7, CYAN);
  tft.fillRect(34, 145, 7, 7, CYAN);
  tft.fillRect(34, 167, 7, 7, CYAN);

  tft.fillRect(33, 68, 4, 14, YELLOW);
  tft.fillRect(33, 98, 4, 14, YELLOW);
  tft.fillRect(33, 128, 4, 14, YELLOW);
  tft.fillRect(33, 158, 4, 14, YELLOW);

  // Outer Case USB A Left
  tft.fillRect(21, 56, 13, 129, BLUE);          // Contact Bar
  tft.drawRect(21, 56, 13, 129, BLACK);         // Contact Bar
  tft.drawRoundRect(18, 53, 34, 135, 3, GREEN); // outer
  tft.drawRect(19, 54, 32, 133, GREEN);         // inner

  /*
 tft.setTextColor(WHITE);  tft.setTextSize(0);

  // USB A pin outs

  tft.setCursor(60, 65);    tft.println("5 StdA_SSRX-");
  tft.setCursor(60, 78);    tft.println("4 USB2   GND");
  tft.setCursor(60, 91);    tft.println("6 StdA_SSRX+");
  tft.setCursor(60, 104);   tft.println("3 USB2    D+");
  tft.setCursor(60, 117);   tft.println("7  GND_DRAIN");  
  tft.setCursor(60, 130);   tft.println("2 USB2    D-");
  tft.setCursor(60, 143);   tft.println("8 StdA_SSTX-");  
  tft.setCursor(60, 156);   tft.println("1 USB2   Vcc");
  tft.setCursor(60, 169);   tft.println("9 StdA_SSTX+");


  tft.drawRoundRect(0, 0, 320, 240, 10, WHITE);

*/
  /* Wires

 tft.drawLine( 137, 68, 185, 68, WHITE);
 tft.drawLine( 137, 81, 185, 81, WHITE);
 tft.drawLine( 137, 94, 185, 94, WHITE);
 tft.drawLine( 137, 107, 185, 107, WHITE);
 tft.drawLine( 137, 120, 185, 120, WHITE);
 tft.drawLine( 137, 133, 185, 133, WHITE);
 tft.drawLine( 137, 146, 185, 146, WHITE);
 tft.drawLine( 137, 159, 185, 159, WHITE);
 tft.drawLine( 137, 172, 185, 172, WHITE);
*/
}

void USB_mini_template()
{

  // Draws the connector and pins for USB Mini on RHS of screen

  tft.setTextColor(WHITE);
  tft.setTextSize(0);

  tft.setCursor(255, 15);
  tft.println("USB Mini");
  tft.setCursor(260, 25);
  tft.println(" v2.0");

  // Outer Case USB Mini Right

  tft.fillRoundRect(286, 71, 12, 109, 4, BLUE); // Connector Bar

  tft.drawRoundRect(273, 70, 27, 111, 10, GREEN); // right outer
  tft.drawRoundRect(274, 71, 25, 109, 8, GREEN);  // right inner

  tft.drawRoundRect(254, 85, 27, 81, 8, GREEN); // left outer
  tft.drawRoundRect(255, 86, 25, 79, 6, GREEN); // left inner

  tft.fillRect(265, 87, 20, 77, BLACK); // Delete overlap
  tft.fillRect(273, 79, 10, 93, BLACK); // Delete overlap
  tft.fillRect(266, 85, 20, 81, BLACK); // Delete overlap

  // Draw angled case

  tft.drawLine(264, 85, 274, 75, GREEN); // Upper angle
  tft.drawLine(265, 85, 275, 75, GREEN); // Upper angle

  tft.drawLine(264, 87, 279, 72, BLACK); // Upper Tidy Up 1
  tft.drawLine(264, 88, 279, 73, BLACK); // Upper Tidy Up 2

  tft.drawLine(264, 165, 274, 175, GREEN); // Lower angle
  tft.drawLine(265, 165, 275, 175, GREEN); // Lower angle

  tft.drawLine(264, 163, 279, 178, BLACK); // Lower Tidy Up 1
  tft.drawLine(264, 162, 279, 177, BLACK); // Lower Tidy Up 2

  // Draw contacts

  tft.fillRect(285, 82, 4, 8, YELLOW);
  tft.fillRect(285, 102, 4, 8, YELLOW);
  tft.fillRect(285, 122, 4, 8, YELLOW);
  tft.fillRect(285, 142, 4, 8, YELLOW);
  tft.fillRect(285, 162, 4, 8, YELLOW);

  /*
  tft.setCursor(195, 160);    tft.println("Vcc    1");
  tft.setCursor(195, 140);    tft.println("Data-  2");
  tft.setCursor(195, 120);    tft.println("Data+  3");
  tft.setCursor(195, 100);    tft.println("ID     4");
  tft.setCursor(195, 80);     tft.println("GND    5");

  tft.drawRoundRect(0, 0, 320, 240, 10, WHITE);
*/

  /* Wires

 tft.drawLine( 135, 80, 185, 80, WHITE);

 tft.drawLine( 135, 100, 185, 100, WHITE);

 tft.drawLine( 135, 120, 185, 120, WHITE);

 tft.drawLine( 135, 140, 185, 140, WHITE);

 tft.drawLine( 135, 160, 185, 160, WHITE);
*/
}

void USB_micro_template()
{

  // Draws the connector and pins for USB Micro-b on RHS of screen

  tft.setTextColor(WHITE);
  tft.setTextSize(0);

  tft.setCursor(255, 15);
  tft.println("USB Micro");
  tft.setCursor(260, 25);
  tft.println(" v2.0");

  // Outer Case USB Mini Right

  tft.fillRoundRect(286, 71, 12, 109, 4, BLUE); // Connector Bar

  tft.drawRoundRect(273, 70, 27, 111, 10, GREEN); // right outer
  tft.drawRoundRect(274, 71, 25, 109, 8, GREEN);  // right inner

  //  tft.drawRoundRect(254, 85, 27, 81, 8, WHITE);   // left outer
  //  tft.drawRoundRect(255, 86, 25, 79, 6, WHITE);  // left inner

  tft.fillRect(265, 87, 20, 77, BLACK); // Delete overlap
  tft.fillRect(273, 79, 10, 93, BLACK); // Delete overlap
  tft.fillRect(266, 85, 20, 81, BLACK); // Delete overlap

  // Draw angled case

  tft.drawLine(264, 85, 274, 75, GREEN); // Upper angle
  tft.drawLine(265, 85, 275, 75, GREEN); // Upper angle

  tft.drawLine(264, 87, 279, 72, BLACK); // Upper Tidy Up 1
  tft.drawLine(264, 88, 279, 73, BLACK); // Upper Tidy Up 2

  tft.drawLine(264, 165, 274, 175, GREEN); // Lower angle
  tft.drawLine(265, 165, 275, 175, GREEN); // Lower angle

  tft.drawLine(264, 163, 279, 178, BLACK); // Lower Tidy Up 1
  tft.drawLine(264, 162, 279, 177, BLACK); // Lower Tidy Up 2

  tft.drawLine(264, 164, 264, 86, GREEN); // COnnector line
  tft.drawLine(265, 164, 265, 86, GREEN); // COnnector line

  // Draw contacts

  tft.fillRect(285, 82, 4, 8, YELLOW);
  tft.fillRect(285, 102, 4, 8, YELLOW);
  tft.fillRect(285, 122, 4, 8, YELLOW);
  tft.fillRect(285, 142, 4, 8, YELLOW);
  tft.fillRect(285, 162, 4, 8, YELLOW);

  /*
  tft.setCursor(195, 160);    tft.println("Vcc    1");
  tft.setCursor(195, 140);    tft.println("Data-  2");
  tft.setCursor(195, 120);    tft.println("Data+  3");
  tft.setCursor(195, 100);    tft.println("ID     4");
  tft.setCursor(195, 80);     tft.println("GND    5");

  tft.drawRoundRect(0, 0, 320, 240, 10, WHITE);
*/
  /* Wires

 tft.drawLine( 135, 80, 185, 80, WHITE);

 tft.drawLine( 135, 100, 185, 100, WHITE);

 tft.drawLine( 135, 120, 185, 120, WHITE);

 tft.drawLine( 135, 140, 185, 140, WHITE);

 tft.drawLine( 135, 160, 185, 160, WHITE);
*/
}

void usbAusbMinicable()
{

  //determine if USB A to USB mini is being used. Test is that both GND and Vcc pins are directly connected.

  pinMode(usbAleft[0].pinnumber, OUTPUT);
  digitalWrite(usbAleft[0].pinnumber, LOW); // TURN USB A Vcc pin LOW
  delay(10);

  if (digitalRead(usbMiniright[0].pinnumber) == LOW)
  {                                               // If Vcc on Mini LOW then test next pin
    pinMode(usbAleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);

    pinMode(usbAleft[3].pinnumber, OUTPUT);
    digitalWrite(usbAleft[3].pinnumber, LOW); // TURN USBA GND pin LOW
    delay(10);

    if (digitalRead(usbMiniright[4].pinnumber) == LOW)
    {                                               // If USB Mini GND pin LOW then test next pin
      pinMode(usbAleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
      delay(10);
      // Execute Drawing the USB A and USB Mini screen

      if (screendrawn == false)
      {

        // Now run a scan to count wires to position screen
        usbscan();
        // Position text based on number of detected connections to keep text in centre of the screen

        if ((countusbwires > 21))
        {
          usbAleftpointer = 0;
        }

        if ((countusbwires > 19) && (countusbwires < 22))
        {
          usbAleftpointer = 20;
        }

        if ((countusbwires > 14) && (countusbwires < 20))
        {
          usbAleftpointer = 40;
        }

        if ((countusbwires > 9) && (countusbwires < 15))
        {
          usbAleftpointer = 70;
        }

        if ((countusbwires > 4) && (countusbwires < 10))
        {
          usbAleftpointer = 90;
        }
        if (countusbwires < 5)
        {
          usbAleftpointer = 110;
        }

        tft.fillScreen(BLACK); // Firstly Clear the Screen of any items
        USB2_A_template();
        USB_mini_template();
        screendrawn = true; // Flag set to indicate screen drawn for this configuration

        usbcable_ctr = 0;

        // Run through all pins in real time and confirm connectivity by drawing on the screen

        for (int y = 0; y < 4; y++)
        { // Digital Pins usbCleft

          pinMode(usbAleft[y].pinnumber, OUTPUT);
          digitalWrite(usbAleft[y].pinnumber, LOW); // TURN USB A Vcc pin LOW
          delay(10);

          for (int x = 0; x < 5; x++)
          {
            if (digitalRead(usbMiniright[x].pinnumber) == LOW)
            { // If Vcc on Mini LOW then test next pin
              tft.setCursor(70, usbAleftpointer);
              tft.print(usbAleft[y].function);
              tft.println(" -----------");
              tft.setCursor(195, usbAleftpointer);
              tft.println(usbMiniright[x].function);
              usbcable_ctr++;
              usbAleftpointer = usbAleftpointer + 10;
            }
          }
          pinMode(usbAleft[y].pinnumber, INPUT_PULLUP); // Reset previous pin
          delay(10);
        }

        screendrawn = true; // Flag set to indicate screen drawn for this configuration
      }
    }
    pinMode(usbAleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);
  }
  pinMode(usbAleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
  delay(10);
}

/*
 * boolean usbAusbMinicable_det = false;
boolean usbAusbMicrocable_det = false;
boolean usbAusbC_det = false;

boolean usbA3usbMinicable_det = false;
boolean usbA3usbMicrocable_det = false;
boolean usbA3usbC_det = false;

boolean usbCusbMinicable_det = false;
boolean usbCusbMicrocable_det = false;
boolean usbCusbC_det = false;
 */

void usbAusbMicrocable()
{

  //determine if USB A to USB Micro is being used. Test is that both GND and Vcc pins are directly connected.

  pinMode(usbAleft[0].pinnumber, OUTPUT);
  digitalWrite(usbAleft[0].pinnumber, LOW); // TURN USB A Vcc pin LOW
  delay(10);

  if (digitalRead(usbMicroright[0].pinnumber) == LOW)
  {                                               // If Vcc on Micro LOW then test next pin
    pinMode(usbAleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(1);
    pinMode(usbAleft[3].pinnumber, OUTPUT);
    digitalWrite(usbAleft[3].pinnumber, LOW); // TURN USBA GND pin LOW
    delay(10);

    if (digitalRead(usbMicroright[4].pinnumber) == LOW)
    {                                               // If USB Micro GND pin LOW then test next pin
      pinMode(usbAleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
      delay(10);
      // Execute Drawing the USB A and USB Micro screen

      if (screendrawn == false)
      {

        // Now run a scan to count wires to position screen
        usbscan();
        // Position text based on number of detected connections to keep text in centre of the screen

        if ((countusbwires > 21))
        {
          usbAleftpointer = 0;
        }

        if ((countusbwires > 19) && (countusbwires < 22))
        {
          usbAleftpointer = 20;
        }

        if ((countusbwires > 14) && (countusbwires < 20))
        {
          usbAleftpointer = 40;
        }

        if ((countusbwires > 9) && (countusbwires < 15))
        {
          usbAleftpointer = 70;
        }

        if ((countusbwires > 4) && (countusbwires < 10))
        {
          usbAleftpointer = 90;
        }
        if (countusbwires < 5)
        {
          usbAleftpointer = 110;
        }

        tft.fillScreen(BLACK); // Firstly Clear the Screen of any items
        USB2_A_template();
        USB_micro_template();
        screendrawn = true; // Flag set to indicate screen drawn for this configuration

        usbcable_ctr = 0;

        // Run through all pins in real time and confirm connectivity by drawing on the screen

        for (int y = 0; y < 4; y++)
        { // Digital Pins usbCleft

          pinMode(usbAleft[y].pinnumber, OUTPUT);
          digitalWrite(usbAleft[y].pinnumber, LOW); // TURN USB A Vcc pin LOW
          delay(10);

          for (int x = 0; x < 5; x++)
          {
            if (digitalRead(usbMicroright[x].pinnumber) == LOW)
            { // If Vcc on Mini LOW then test next pin
              tft.setCursor(70, usbAleftpointer);
              tft.print(usbAleft[y].function);
              tft.println(" -----------");
              tft.setCursor(195, usbAleftpointer);
              tft.println(usbMicroright[x].function);
              usbcable_ctr++;
              usbAleftpointer = usbAleftpointer + 10;
            }
          }
          pinMode(usbAleft[y].pinnumber, INPUT_PULLUP); // Reset previous pin
          delay(10);
        }

        screendrawn = true; // Flag set to indicate screen drawn for this configuration
      }
    }
    pinMode(usbAleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);
  }
  pinMode(usbAleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
  delay(10);
}

void usbAusbCcable()
{ // Need to apply logic to slect USB C cable

  //determine if USB A to USB Micro is being used. Test is that both GND and Vcc pins are directly connected.

  pinMode(usbAleft[0].pinnumber, OUTPUT);
  digitalWrite(usbAleft[0].pinnumber, LOW); // TURN USB A Vcc pin LOW
                                            //  delay(10); Any delay here causes the pulse to be missed. Suspect this is cable capacitance

  if (digitalRead(usbCright[0].pinnumber) == LOW)
  {                                               // If USB A GND pin LOW then test next pin
    pinMode(usbAleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);

    pinMode(usbAleft[3].pinnumber, OUTPUT);
    digitalWrite(usbAleft[3].pinnumber, LOW); // TURN USBA GND pin LOW
    delay(10);

    if (digitalRead(usbCright[0].pinnumber) == LOW)
    {                                               // If Vcc on USB C LOW then test next pin
      pinMode(usbAleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
      delay(10);

      // Execute Drawing the USB A and USB Micro screen

      if (screendrawn == false)
      {

        // Now run a scan to count wires to position screen
        usbscan();
        // Position text based on number of detected connections to keep text in centre of the screen

        if ((countusbwires > 21))
        {
          usbAleftpointer = 0;
        }

        if ((countusbwires > 19) && (countusbwires < 22))
        {
          usbAleftpointer = 20;
        }

        if ((countusbwires > 14) && (countusbwires < 20))
        {
          usbAleftpointer = 40;
        }

        if ((countusbwires > 9) && (countusbwires < 15))
        {
          usbAleftpointer = 70;
        }

        if ((countusbwires > 4) && (countusbwires < 10))
        {
          usbAleftpointer = 90;
        }
        if (countusbwires < 5)
        {
          usbAleftpointer = 110;
        }

        tft.fillScreen(BLACK); // Firstly Clear the Screen of any items

        USB2_A_template();
        USBC_Right_template();
        screendrawn = true; // Flag set to indicate screen drawn for this configuration

        usbcable_ctr = 0;

        // Run through all pins in real time and confirm connectivity by drawing on the screen

        for (int y = 0; y < 4; y++)
        { // Digital Pins usbCleft

          pinMode(usbAleft[y].pinnumber, OUTPUT);
          digitalWrite(usbAleft[y].pinnumber, LOW); // TURN USB A Vcc pin LOW
          delay(10);

          for (int x = 0; x < 16; x++)
          {
            if (digitalRead(usbCright[x].pinnumber) == LOW)
            { // If Vcc on USB C LOW then test next pin
              tft.setCursor(70, usbAleftpointer);
              tft.print(usbAleft[y].function);
              tft.println(" -----------");
              // Comment out previous line and use this to printout pins tft.setCursor(70, usbAleftpointer);   tft.print(usbAleft[y].function); tft.print(" -"); tft.print(usbAleft[y].pinnumber); tft.print("-");tft.print(y);tft.print("-");tft.print(x);tft.print("-");tft.println(usbCright[x].pinnumber);
              tft.setCursor(195, usbAleftpointer);
              tft.println(usbCright[x].function);
              usbcable_ctr++;
              usbAleftpointer = usbAleftpointer + 10;
            }
          }
          pinMode(usbAleft[y].pinnumber, INPUT_PULLUP); // Reset previous pin
          delay(10);
        }
        screendrawn = true; // Flag set to indicate screen drawn for this configuration
      }
    }
    pinMode(usbAleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);
  }
  pinMode(usbAleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
  delay(10);
}

void usbA3usbMinicable()
{

  //determine if USB A3 to USB mini is being used. Test is that both GND and Vcc pins are directly connected.

  pinMode(usbA3left[0].pinnumber, OUTPUT);
  digitalWrite(usbA3left[0].pinnumber, LOW); // TURN USB A3 Vcc pin LOW
  delay(10);

  if (digitalRead(usbMiniright[0].pinnumber) == LOW)
  {                                                // If Vcc on Mini LOW then test next pin
    pinMode(usbA3left[0].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);

    pinMode(usbA3left[3].pinnumber, OUTPUT);
    digitalWrite(usbA3left[3].pinnumber, LOW); // TURN USBA3 GND pin LOW
    delay(10);

    if (digitalRead(usbMiniright[4].pinnumber) == LOW)
    {                                                // If USB Mini GND pin LOW then test next pin
      pinMode(usbA3left[3].pinnumber, INPUT_PULLUP); // Reset previous pin
      delay(10);

      // Execute Drawing the USB A and USB Mini screen

      if (screendrawn == false)
      {

        // Now run a scan to count wires to position screen
        usbscan();
        // Position text based on number of detected connections to keep text in centre of the screen

        if ((countusbwires > 21))
        {
          usbA3leftpointer = 0;
        }

        if ((countusbwires > 19) && (countusbwires < 22))
        {
          usbA3leftpointer = 20;
        }

        if ((countusbwires > 14) && (countusbwires < 20))
        {
          usbA3leftpointer = 40;
        }

        if ((countusbwires > 9) && (countusbwires < 15))
        {
          usbA3leftpointer = 70;
        }

        if ((countusbwires > 4) && (countusbwires < 10))
        {
          usbA3leftpointer = 90;
        }
        if (countusbwires < 5)
        {
          usbA3leftpointer = 110;
        }

        tft.fillScreen(BLACK); // Firstly Clear the Screen of any items
        USB3_A_template();
        USB_mini_template();
        screendrawn = true; // Flag set to indicate screen drawn for this configuration

        usbcable_ctr = 0;

        // Run through all pins in real time and confirm connectivity by drawing on the screen

        for (int y = 0; y < 9; y++)
        { // Digital Pins usbCleft

          pinMode(usbA3left[y].pinnumber, OUTPUT);
          digitalWrite(usbA3left[y].pinnumber, LOW); // TURN USB A Vcc pin LOW
          delay(10);

          for (int x = 0; x < 5; x++)
          {
            if (digitalRead(usbMiniright[x].pinnumber) == LOW)
            { // If Vcc on Mini LOW then test next pin
              tft.setCursor(70, usbA3leftpointer);
              tft.print(usbA3left[y].function);
              tft.println(" -------");
              tft.setCursor(195, usbA3leftpointer);
              tft.println(usbMiniright[x].function);
              usbcable_ctr++;
              usbA3leftpointer = usbA3leftpointer + 10;
            }
          }
          pinMode(usbA3left[y].pinnumber, INPUT_PULLUP); // Reset previous pin
          delay(10);
        }

        screendrawn = true; // Flag set to indicate screen drawn for this configuration
      }
    }
    pinMode(usbA3left[3].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);
  }
  pinMode(usbA3left[0].pinnumber, INPUT_PULLUP); // Reset previous pin
  delay(10);
}

void usbA3usbMicrocable()
{

  //determine if USB A3 to USB mini is being used. Test is that both GND and Vcc pins are directly connected.

  pinMode(usbA3left[0].pinnumber, OUTPUT);
  digitalWrite(usbA3left[0].pinnumber, LOW); // TURN USB A3 Vcc pin LOW
  delay(10);

  if (digitalRead(usbMicroright[0].pinnumber) == LOW)
  {                                                // If Vcc on Micro LOW then test next pin
    pinMode(usbA3left[0].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);

    pinMode(usbA3left[3].pinnumber, OUTPUT);
    digitalWrite(usbA3left[3].pinnumber, LOW); // TURN USBA3 GND pin LOW
    delay(10);

    if (digitalRead(usbMicroright[4].pinnumber) == LOW)
    {                                                // If USB Micro GND pin LOW then test next pin
      pinMode(usbA3left[3].pinnumber, INPUT_PULLUP); // Reset previous pin
      delay(10);

      // Execute Drawing the USB A and USB Mini screen

      if (screendrawn == false)
      {

        // Now run a scan to count wires to position screen
        usbscan();
        // Position text based on number of detected connections to keep text in centre of the screen

        if ((countusbwires > 21))
        {
          usbA3leftpointer = 0;
        }

        if ((countusbwires > 19) && (countusbwires < 22))
        {
          usbA3leftpointer = 20;
        }

        if ((countusbwires > 14) && (countusbwires < 20))
        {
          usbA3leftpointer = 40;
        }

        if ((countusbwires > 9) && (countusbwires < 15))
        {
          usbA3leftpointer = 70;
        }

        if ((countusbwires > 4) && (countusbwires < 10))
        {
          usbA3leftpointer = 90;
        }
        if (countusbwires < 5)
        {
          usbA3leftpointer = 110;
        }

        tft.fillScreen(BLACK); // Firstly Clear the Screen of any items
        USB3_A_template();
        USB_micro_template();
        screendrawn = true; // Flag set to indicate screen drawn for this configuration

        usbcable_ctr = 0;

        // Run through all pins in real time and confirm connectivity by drawing on the screen

        for (int y = 0; y < 9; y++)
        { // Digital Pins usbCleft

          pinMode(usbA3left[y].pinnumber, OUTPUT);
          digitalWrite(usbA3left[y].pinnumber, LOW); // TURN USB A Vcc pin LOW
          delay(10);

          for (int x = 0; x < 5; x++)
          {
            if (digitalRead(usbMicroright[x].pinnumber) == LOW)
            { // If Vcc on Mini LOW then test next pin
              tft.setCursor(70, usbA3leftpointer);
              tft.print(usbA3left[y].function);
              tft.println(" -------");
              tft.setCursor(195, usbA3leftpointer);
              tft.println(usbMicroright[x].function);
              usbcable_ctr++;
              usbA3leftpointer = usbA3leftpointer + 10;
            }
          }
          pinMode(usbA3left[y].pinnumber, INPUT_PULLUP); // Reset previous pin
          delay(10);
        }

        screendrawn = true; // Flag set to indicate screen drawn for this configuration
      }
    }
    pinMode(usbA3left[3].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);
  }
  pinMode(usbA3left[0].pinnumber, INPUT_PULLUP); // Reset previous pin
  delay(10);
}

void usbA3usbCcable()
{

  //determine if USB A3 to USB mini is being used. Test is that both GND and Vcc pins are directly connected.

  pinMode(usbA3left[0].pinnumber, OUTPUT);
  digitalWrite(usbA3left[0].pinnumber, LOW); // TURN USB A3 Vcc pin LOW
  delay(10);

  if (digitalRead(usbCright[3].pinnumber) == LOW)
  {                                                // If USB Micro GND pin LOW then test next pin
    pinMode(usbA3left[0].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);

    pinMode(usbA3left[3].pinnumber, OUTPUT);
    digitalWrite(usbA3left[3].pinnumber, LOW); // TURN USBA3 GND pin LOW
    delay(10);

    if (digitalRead(usbCright[0].pinnumber) == LOW)
    {                                                // If Vcc on USB C LOW then test next pin
      pinMode(usbA3left[3].pinnumber, INPUT_PULLUP); // Reset previous pin
      delay(10);

      // Execute Drawing the USB A3 and USB C screen

      if (screendrawn == false)
      {

        // Now run a scan to count wires to position screen
        usbscan();
        // Position text based on number of detected connections to keep text in centre of the screen

        if ((countusbwires > 21))
        {
          usbA3leftpointer = 0;
        }

        if ((countusbwires > 19) && (countusbwires < 22))
        {
          usbA3leftpointer = 20;
        }

        if ((countusbwires > 14) && (countusbwires < 20))
        {
          usbA3leftpointer = 40;
        }

        if ((countusbwires > 9) && (countusbwires < 15))
        {
          usbA3leftpointer = 70;
        }

        if ((countusbwires > 4) && (countusbwires < 10))
        {
          usbA3leftpointer = 90;
        }
        if (countusbwires < 5)
        {
          usbA3leftpointer = 110;
        }

        tft.fillScreen(BLACK); // Firstly Clear the Screen of any items
        USB3_A_template();
        USBC_Right_template();
        screendrawn = true; // Flag set to indicate screen drawn for this configuration

        usbcable_ctr = 0;

        // Run through all pins in real time and confirm connectivity by drawing on the screen

        for (int y = 0; y < 9; y++)
        { // Digital Pins usbCleft

          pinMode(usbA3left[y].pinnumber, OUTPUT);
          digitalWrite(usbA3left[y].pinnumber, LOW); // TURN USB A Vcc pin LOW
          delay(10);

          for (int x = 0; x < 16; x++)
          {
            if (digitalRead(usbCright[x].pinnumber) == LOW)
            { // If Vcc on Mini LOW then test next pin
              tft.setCursor(70, usbA3leftpointer);
              tft.print(usbA3left[y].function);
              tft.println(" -------");
              tft.setCursor(195, usbA3leftpointer);
              tft.println(usbCright[x].function);
              usbcable_ctr++;
              usbA3leftpointer = usbA3leftpointer + 10;
            }
          }
          pinMode(usbA3left[y].pinnumber, INPUT_PULLUP); // Reset previous pin
          delay(10);
        }

        screendrawn = true; // Flag set to indicate screen drawn for this configuration
      }
    }
    pinMode(usbA3left[3].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);
  }
  pinMode(usbA3left[0].pinnumber, INPUT_PULLUP); // Reset previous pin
  delay(10);
}

void usbCusbCcable()
{

  //determine if USB C to USB C is being used. Test is that both GND and Vcc pins are directly connected.

  pinMode(usbCleft[3].pinnumber, OUTPUT);
  digitalWrite(usbCleft[3].pinnumber, LOW); // TURN USB C Vcc pin LOW
  delay(10);

  if (digitalRead(usbCright[3].pinnumber) == LOW)
  {                                               // If USB Micro GND pin LOW then test next pin
    pinMode(usbCleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);

    pinMode(usbCleft[0].pinnumber, OUTPUT);
    digitalWrite(usbCleft[0].pinnumber, LOW); // TURN USB C GND pin LOW
    delay(10);

    if (digitalRead(usbCright[0].pinnumber) == LOW)
    {                                               // If Vcc on USB C LOW then test next pin
      pinMode(usbCleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
      delay(10);

      // Execute Drawing the USB C and USB C screen

      if (screendrawn == false)
      {

        // Now run a scan to count wires to position screen
        usbscan();
        // Position text based on number of detected connections to keep text in centre of the screen

        if ((countusbwires > 21))
        {
          usbCleftpointer = 0;
        }

        if ((countusbwires > 19) && (countusbwires < 22))
        {
          usbCleftpointer = 20;
        }

        if ((countusbwires > 14) && (countusbwires < 20))
        {
          usbCleftpointer = 40;
        }

        if ((countusbwires > 9) && (countusbwires < 15))
        {
          usbCleftpointer = 70;
        }

        if ((countusbwires > 4) && (countusbwires < 10))
        {
          usbCleftpointer = 90;
        }
        if (countusbwires < 5)
        {
          usbCleftpointer = 110;
        }

        tft.fillScreen(BLACK); // Firstly Clear the Screen of any items
        USBC_Left_template();
        USBC_Right_template();
        screendrawn = true; // Flag set to indicate screen drawn for this configuration

        usbcable_ctr = 0;

        // Run through all pins in real time and confirm connectivity by drawing on the screen

        for (int y = 0; y < 16; y++)
        { // Digital Pins usbCleft

          pinMode(usbCleft[y].pinnumber, OUTPUT);
          digitalWrite(usbCleft[y].pinnumber, LOW); // TURN USB A Vcc pin LOW
          delay(10);

          for (int x = 0; x < 16; x++)
          {
            if (digitalRead(usbCright[x].pinnumber) == LOW)
            { // If Vcc on Mini LOW then test next pin
              tft.setCursor(70, usbCleftpointer);
              tft.print(usbCleft[y].function);
              tft.println("   ---------");
              // Comment out previous line and use this to printout pins                                     tft.setCursor(70, usbCleftpointer);   tft.print(usbCleft[y].function); tft.print("-"); tft.print(usbCleft[y].pinnumber); tft.print("-");tft.print(y);tft.print("-");tft.print(x); tft.print("-");tft.println(usbCright[x].pinnumber);
              tft.setCursor(210, usbCleftpointer);
              tft.println(usbCright[x].function);
              usbcable_ctr++;
              usbCleftpointer = usbCleftpointer + 10;
            }
          }
          pinMode(usbCleft[y].pinnumber, INPUT_PULLUP); // Reset previous pin
          delay(10);
        }

        screendrawn = true; // Flag set to indicate screen drawn for this configuration
      }
    }
    pinMode(usbCleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);
  }
  pinMode(usbCleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
  delay(10);
}

void usbCusbMinicable()
{

  //determine if USB C to USB Mini is being used. Test is that both GND and Vcc pins are directly connected.

  pinMode(usbCleft[3].pinnumber, OUTPUT);
  digitalWrite(usbCleft[3].pinnumber, LOW); // TURN USB C Vcc pin LOW
  delay(10);

  if (digitalRead(usbMiniright[0].pinnumber) == LOW)
  {                                               // If USB Mini GND pin LOW then test next pin
    pinMode(usbCleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin

    pinMode(usbCleft[0].pinnumber, OUTPUT);
    digitalWrite(usbCleft[0].pinnumber, LOW); // TURN USB C GND pin LOW
    delay(10);

    if (digitalRead(usbMiniright[4].pinnumber) == LOW)
    {                                               // If Vcc on USB C LOW then test next pin
      pinMode(usbCleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
      delay(10);
      // Execute Drawing the USB C and USB C screen

      if (screendrawn == false)
      {

        usbscan();
        // Position text based on number of detected connections to keep text in centre of the screen

        if ((countusbwires > 21))
        {
          usbCleftpointer = 0;
        }

        if ((countusbwires > 19) && (countusbwires < 22))
        {
          usbCleftpointer = 20;
        }

        if ((countusbwires > 14) && (countusbwires < 20))
        {
          usbCleftpointer = 40;
        }

        if ((countusbwires > 9) && (countusbwires < 15))
        {
          usbCleftpointer = 70;
        }

        if ((countusbwires > 4) && (countusbwires < 10))
        {
          usbCleftpointer = 90;
        }
        if (countusbwires < 5)
        {
          usbCleftpointer = 110;
        }

        tft.fillScreen(BLACK); // Firstly Clear the Screen of any items
        USBC_Left_template();
        USB_mini_template();
        screendrawn = true; // Flag set to indicate screen drawn for this configuration

        usbcable_ctr = 0;

        // Run through all pins in real time and confirm connectivity by drawing on the screen

        for (int y = 0; y < 16; y++)
        { // Digital Pins usbCleft

          pinMode(usbCleft[y].pinnumber, OUTPUT);
          digitalWrite(usbCleft[y].pinnumber, LOW); // TURN USB A Vcc pin LOW
          delay(10);

          for (int x = 0; x < 5; x++)
          {
            if (digitalRead(usbMiniright[x].pinnumber) == LOW)
            { // If Vcc on Mini LOW then test next pin
              tft.setCursor(70, usbCleftpointer);
              tft.print(usbCleft[y].function);
              tft.println("  ---------");
              tft.setCursor(195, usbCleftpointer);
              tft.println(usbMiniright[x].function);
              usbcable_ctr++;
              usbCleftpointer = usbCleftpointer + 10;
            }
          }
          pinMode(usbCleft[y].pinnumber, INPUT_PULLUP); // Reset previous pin
          delay(10);
        }

        screendrawn = true; // Flag set to indicate screen drawn for this configuration
      }
    }
    pinMode(usbCleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);
  }
  pinMode(usbCleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
  delay(10);
}

void usbCusbMicrocable()
{

  //determine if USB C to USB Micro is being used. Test is that both GND and Vcc pins are directly connected.

  pinMode(usbCleft[3].pinnumber, OUTPUT);
  digitalWrite(usbCleft[3].pinnumber, LOW); // TURN USB C Vbus pin LOW
  delay(10);

  if (digitalRead(usbMicroright[0].pinnumber) == LOW)
  {                                               // If USB Micro GND pin LOW then test next pin
    pinMode(usbCleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin

    pinMode(usbCleft[0].pinnumber, OUTPUT);
    digitalWrite(usbCleft[0].pinnumber, LOW); // TURN USB C GND pin LOW
    delay(10);

    if (digitalRead(usbMicroright[4].pinnumber) == LOW)
    {                                               // If GND on USBMicro LOW then test next pin
      pinMode(usbCleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
      delay(10);
      // Execute Drawing the USB C and USB C screen

      if (screendrawn == false)
      {

        usbscan();
        // Position text based on number of detected connections to keep text in centre of the screen

        if ((countusbwires > 21))
        {
          usbCleftpointer = 0;
        }

        if ((countusbwires > 19) && (countusbwires < 22))
        {
          usbCleftpointer = 20;
        }

        if ((countusbwires > 14) && (countusbwires < 20))
        {
          usbCleftpointer = 40;
        }

        if ((countusbwires > 9) && (countusbwires < 15))
        {
          usbCleftpointer = 70;
        }

        if ((countusbwires > 4) && (countusbwires < 10))
        {
          usbCleftpointer = 90;
        }
        if (countusbwires < 5)
        {
          usbCleftpointer = 110;
        }

        tft.fillScreen(BLACK); // Firstly Clear the Screen of any items
        USBC_Left_template();
        USB_micro_template();
        screendrawn = true; // Flag set to indicate screen drawn for this configuration

        usbcable_ctr = 0;

        // Run through all pins in real time and confirm connectivity by drawing on the screen

        for (int y = 0; y < 16; y++)
        { // Digital Pins usbCleft

          pinMode(usbCleft[y].pinnumber, OUTPUT);
          digitalWrite(usbCleft[y].pinnumber, LOW); // TURN USB A Vcc pin LOW
          delay(10);

          for (int x = 0; x < 5; x++)
          {
            if (digitalRead(usbMicroright[x].pinnumber) == LOW)
            { // If Vcc on Mini LOW then test next pin
              tft.setCursor(70, usbCleftpointer);
              tft.print(usbCleft[y].function);
              tft.println("  ---------");
              tft.setCursor(195, usbCleftpointer);
              tft.println(usbMicroright[x].function);
              usbcable_ctr++;
              usbCleftpointer = usbCleftpointer + 10;
            }
          }
          pinMode(usbCleft[y].pinnumber, INPUT_PULLUP); // Reset previous pin
          delay(10);
        }

        screendrawn = true; // Flag set to indicate screen drawn for this configuration
      }
    }
    pinMode(usbCleft[0].pinnumber, INPUT_PULLUP); // Reset previous pin
    delay(10);
  }
  pinMode(usbCleft[3].pinnumber, INPUT_PULLUP); // Reset previous pin
  delay(10);
}

void usbscan()
{ // Scan the Digital Input Pins and update the status of all Arrays

  // ##### Scan usbCleft to usbCright covering all ports #####

  countusbwires = 0; //  reset counter

  // Step through the Analog Pins first on LHS

  for (int y = 62; y < 70; y++)
  { // Digital Pins usbAleft

    pinMode(y, OUTPUT);
    digitalWrite(y, LOW);
    delay(10);

    for (int x = 30; x < 54; x++)
    { // If HIGH record both the left and right state as 1

      if (digitalRead(x) == LOW)
      {
        countusbwires++;
      }
    }
    // Reset the pin to an input
    pinMode(y, INPUT_PULLUP);
    delay(10);
  }

  // Step through the Digital Pins first on LHS

  for (int y = 14; y < 30; y++)
  { // Digital Pins usbAleft

    pinMode(y, OUTPUT);
    digitalWrite(y, LOW);
    delay(10);

    for (int x = 30; x < 54; x++)
    { // If HIGH record both the left and right state as 1

      if (digitalRead(x) == LOW)
      {
        countusbwires++;
      }
    }
    // Reset the pin to an input
    pinMode(y, INPUT_PULLUP);
    delay(10);
  }

  if (countusbwires != usbcable_ctr)
  {

    tft.setTextColor(WHITE);
    tft.setTextSize(3);

    screendrawn = false;   // Flag set to indicate configuration changed
    tft.fillScreen(BLACK); // Firstly Clear the Screen of any items
    tft.setCursor(40, 100);
    tft.print("Scanning Ports");

    tft.setTextColor(MAGENTA);
    tft.setCursor((40 + (scangraphic * 15)), 135);
    tft.print("->");
    tft.setTextColor(BLUE);
    tft.setCursor((240 - (scangraphic * 15)), 70);
    tft.print("<-");
    tft.setTextColor(WHITE);
    scangraphic++;
    if (scangraphic > 15)
    {
      scangraphic = 0;
    }

    tft.setTextColor(WHITE);
    tft.setTextSize(0);
  }
  else
  {

    // test print
    tft.setCursor(20, 200);
    tft.print("Ctr ");
    tft.println(usbcable_ctr);
    tft.setCursor(20, 220);
    tft.print("CW  ");
    tft.println(countusbwires);
  }
}

void splashscreen()
{

  // **** Splash Screen

  //  tft.drawRoundRect(0, 0, 320, 240, 10, WHITE);

  byte g = 70;

  // First row of text

  tft.drawCircle(28, g - 40, 20, GREEN);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.setCursor(21, g - 50);
  tft.println("U");

  tft.drawCircle(81, g - 40, 20, GREEN);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.setCursor(74, g - 50);
  tft.println("S");

  tft.drawCircle(134, g - 40, 20, GREEN);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.setCursor(127, g - 50);
  tft.println("B");

  // Second row of text

  tft.drawCircle(28, g + 12, 20, RED);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(21, g + 2);
  tft.println("C");

  tft.drawCircle(81, g + 12, 20, RED);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(74, g + 2);
  tft.println("A");

  tft.drawCircle(134, g + 12, 20, RED);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(127, g + 2);
  tft.println("B");

  tft.drawCircle(187, g + 12, 20, RED);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(180, g + 2);
  tft.println("L");

  tft.drawCircle(239, g + 12, 20, RED);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(232, g + 2);
  tft.println("E");

  // 3rd row of text

  tft.drawCircle(28, g + 64, 20, YELLOW);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.setCursor(21, g + 54);
  tft.println("T");

  tft.drawCircle(81, g + 64, 20, YELLOW);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.setCursor(74, g + 54);
  tft.println("R");

  tft.drawCircle(134, g + 64, 20, YELLOW);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.setCursor(127, g + 54);
  tft.println("A");

  tft.drawCircle(187, g + 64, 20, YELLOW);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.setCursor(180, g + 54);
  tft.println("C");

  tft.drawCircle(239, g + 64, 20, YELLOW);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.setCursor(232, g + 54);
  tft.println("E");

  tft.drawCircle(292, g + 64, 20, YELLOW);
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
  tft.setCursor(285, g + 54);
  tft.println("R");

  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 170);
  tft.println("Test, Diagnose, Repair");

  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 200);
  tft.println("By TechKiwiGadgets 2021");

  // Arduino logo

  tft.drawCircle(20, 225, 9, WHITE);
  tft.drawCircle(37, 225, 9, WHITE);
  tft.drawCircle(20, 225, 8, WHITE);
  tft.drawCircle(37, 225, 8, WHITE);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(16, 218);
  tft.println("-");
  tft.setCursor(33, 218);
  tft.println("+");

  //       tft.setTextColor(WHITE);  tft.setTextSize(1);
  //       tft.setCursor(10, 220);   tft.println("Arduino");

  delay(2000);

  tft.setTextColor(WHITE);
  tft.setTextSize(0);
  tft.fillScreen(BLACK);
}

void splashscreen2()
{
  // **** Splash Screen

  //  tft.drawRoundRect(0, 0, 320, 240, 10, WHITE);

  byte g = 70;

  // First row of text

  tft.drawCircle(28, g - 40, 20, GREEN);
  tft.fillCircle(28, g - 40, 17, GREEN);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(21, g - 50);
  tft.println("U");

  tft.drawCircle(81, g - 40, 20, GREEN);
  tft.fillCircle(81, g - 40, 17, GREEN);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(74, g - 50);
  tft.println("S");

  tft.drawCircle(134, g - 40, 20, GREEN);
  tft.fillCircle(134, g - 40, 17, GREEN);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(127, g - 50);
  tft.println("B");

  // Second row of text

  tft.drawCircle(28, g + 12, 20, RED);
  tft.fillCircle(28, g + 12, 17, RED);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(21, g + 2);
  tft.println("C");

  tft.drawCircle(81, g + 12, 20, RED);
  tft.fillCircle(81, g + 12, 17, RED);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(74, g + 2);
  tft.println("A");

  tft.drawCircle(134, g + 12, 20, RED);
  tft.fillCircle(134, g + 12, 17, RED);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(127, g + 2);
  tft.println("B");

  tft.drawCircle(187, g + 12, 20, RED);
  tft.fillCircle(187, g + 12, 17, RED);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(180, g + 2);
  tft.println("L");

  tft.drawCircle(239, g + 12, 20, RED);
  tft.fillCircle(239, g + 12, 17, RED);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(232, g + 2);
  tft.println("E");

  // 3rd row of text

  tft.drawCircle(28, g + 64, 20, YELLOW);
  tft.fillCircle(28, g + 64, 17, YELLOW);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(21, g + 54);
  tft.println("T");

  tft.drawCircle(81, g + 64, 20, YELLOW);
  tft.fillCircle(81, g + 64, 17, YELLOW);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(74, g + 54);
  tft.println("R");

  tft.drawCircle(134, g + 64, 20, YELLOW);
  tft.fillCircle(134, g + 64, 17, YELLOW);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(127, g + 54);
  tft.println("A");

  tft.drawCircle(187, g + 64, 20, YELLOW);
  tft.fillCircle(187, g + 64, 17, YELLOW);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(180, g + 54);
  tft.println("C");

  tft.drawCircle(239, g + 64, 20, YELLOW);
  tft.fillCircle(239, g + 64, 17, YELLOW);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(232, g + 54);
  tft.println("E");

  tft.drawCircle(292, g + 64, 20, YELLOW);
  tft.fillCircle(292, g + 64, 17, YELLOW);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(285, g + 54);
  tft.println("R");

  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 170);
  tft.println("Test, Diagnose, Repair");

  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 200);
  tft.println("By TechKiwiGadgets 2021");

  // Arduino logo

  tft.drawCircle(20, 225, 9, WHITE);
  tft.drawCircle(37, 225, 9, WHITE);
  tft.drawCircle(20, 225, 8, WHITE);
  tft.drawCircle(37, 225, 8, WHITE);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(16, 218);
  tft.println("-");
  tft.setCursor(33, 218);
  tft.println("+");

  //       tft.setTextColor(WHITE);  tft.setTextSize(1);
  //       tft.setCursor(10, 220);   tft.println("Arduino");

  delay(1000);

  tft.setTextColor(WHITE);
  tft.setTextSize(0);
  tft.fillScreen(BLACK);
}

void loop()
{

  // screendrawn = false;

  usbAusbMinicable();

  usbAusbMicrocable();
  usbAusbCcable();

  usbA3usbMinicable();
  usbA3usbMicrocable();
  usbA3usbCcable();

  usbCusbMinicable();

  usbCusbMicrocable();

  usbCusbCcable();

  usbscan();
}