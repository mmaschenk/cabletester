// USB Cable Tracer By TechKiwiGadgets May 2021

/* 
 *  Final Instructable Version 1
 */

#include <Adafruit_GFX.h>    // Core graphics library
// #include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "lcd-display.h"
#include <TouchScreen.h>

#include "usbcheck.h"

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
//    {62, 0, "A1   GND"}, TODO!!!
    {69, 0, "A1   GND"},
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

void usbscan();

USBCHECK usb;

void setup() {
  Serial.begin(115200); // Setupserial interface

  tft.reset();

  usb.sanitycheck(Serial);
  usb.initpinmode();
  
  usb.findactiveconnection(Serial);

  uint16_t identifier = tft.readID();
  identifier = 0x9341;

  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  pinMode(13, OUTPUT);

  

}

void oldsetup()
{
  Serial.begin(115200); // Setupserial interface

  tft.reset();

  usb.sanitycheck(Serial);

  usb.findactiveconnection(Serial);

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
  tft.splashscreen();
  Serial.println("Ended splashscreen");
}

void drawscreen()
{

  //    tft.fillScreen(BLACK);
  // Setup Screen

  GREEN = 0x07E0;
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
        tft.USB2_A_template();
        tft.USB_mini_template();
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
        tft.USB2_A_template();
        tft.USB_micro_template();
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

        tft.USB2_A_template();
        tft.USBC_Right_template();
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
        tft.USB3_A_template();
        tft.USB_mini_template();
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
        tft.USB3_A_template();
        tft.USB_micro_template();
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
        tft.USB3_A_template();
        tft.USBC_Right_template();
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
        tft.USBC_Left_template();
        tft.USBC_Right_template();
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
        tft.USBC_Left_template();
        tft.USB_mini_template();
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
        tft.USBC_Left_template();
        tft.USB_micro_template();
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