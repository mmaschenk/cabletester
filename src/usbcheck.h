#ifndef _USBCHECK__H_
#define _USBCHECK__H_

#include <Arduino.h>

#define MAXIOS 69
#define FIRSTPIN 14

class USBDrawable {
  public:
    virtual void drawMeAtDefaultPosition() = 0;
    virtual void drawMeAt(int x, int y, bool highlight = false) = 0;
};

enum connectorposition {
  LEFT, RIGHT
};

typedef struct
{
  int pinnumber;        // 62 to 69, 14 to 29 sensor pin addresses
  int state;            // 1 or 0 showing digital state of pin
  const char *function; // Text description of function and logical pin number
} pininfo;

typedef struct
{
  int size; // Number of pins in connector  
  connectorposition position;
  const char *name;
  const char *subname;
  pininfo pin[16];
  USBDrawable *draw;
} connectorinfo;

enum connections
{
  cleft,
  a2left,
  a3left,
  cright,
  miniright,
  microright,
  CONNECTIONS_MAX
};

#define CONNECTIONSPERSIDE (CONNECTIONS_MAX/2)
#define LEFTSIDECONNECTIONS (CONNECTIONS_MAX/2)
#define RIGHTSIDECONNECTIONS LEFTSIDECONNECTIONS

typedef struct 
{
  uint8_t sourcepin;
  uint8_t targetpin;
} pinconnection;

typedef struct 
{
  uint8_t target;
  pinconnection check[2];
} connectorcheck;



class USBCHECK
{
public:
  connectorinfo info[CONNECTIONS_MAX];
  connectorcheck connectinfo[CONNECTIONS_MAX/2][CONNECTIONS_MAX/2];
  void CtoC();
  USBCHECK()
  {
    info[cleft] = { 16, LEFT, "USB C", "v3.0", 
    {
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
      {28, 0, "B11 RX1+"}}
    };

    info[a2left] = { 4, LEFT, "USB A", "v2.0",
    {
      {66, 0, "1    Vcc"},
      {67, 0, "2     D-"},
      {68, 0, "3     D+"},
      {69, 0, "4    GND"}}
    };

    info[a3left] = { 9, LEFT, "USB A", "v3.0",
    {
      {18, 0, "1 USB2   Vcc"},
      {19, 0, "2 USB2    D-"},
      {20, 0, "3 USB2    D+"},
      {21, 0, "4 USB2   GND"},
      {22, 0, "5 Std ASSRX-"},
      {23, 0, "6 Std ASSRX+"},
      {24, 0, "7 GND DRAIN"},
      {25, 0, "8 Std ASSTX-"},
      {26, 0, "9 Std ASSTX+"}}
    };

    info[cright] = { 16, RIGHT, "USB C", "v3.0", 
    {
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
      {53, 0, "B11 RX1+"}}
    };

    info[miniright] = { 5, RIGHT, "USB Mini", "v2.0",
    {
      {32, 0, "1   Vcc"},
      {33, 0, "2    D-"},
      {34, 0, "3    D+"},
      {35, 0, "4    ID"},
      {36, 0, "5   GND"}}
    };

    info[microright] = { 5, RIGHT, "USB Micro", "v2.0",
    {
      {43, 0, "1    Vcc"},
      {41, 0, "2     D-"},
      {40, 0, "3     D+"},
      {42, 0, "4     ID"},
      {39, 0, "5    GND"}}
    };

    connectinfo[a2left][0] =  {
      miniright, {
        {0, 0}, // Vcc -> Vcc
        {3,4}   // GND -> GND
      }
    };
    connectinfo[a2left][1] =  {
      microright, {
        {0, 0}, // Vcc -> Vcc
        {3,0}   // GND -> GND
      }
    };
    connectinfo[a2left][2] =  {
      cright, {
        {0, 3}, // Vcc -> Vcc
        {3, 0}   // GND -> GND
      }
    };

    connectinfo[a3left][0] = {
      miniright, {
        {0, 0}, // Vcc -> Vcc
        {3, 4}, // GND -> GND
      }
    };
    connectinfo[a3left][1] = {
      microright, {
        {0, 0}, // Vcc -> Vcc
        {3, 4}, // GND -> GND
      }
    };
    connectinfo[a3left][2] = {
      cright, {
        {0, 3}, // Vcc -> Vcc
        {3, 0}, // GND -> GND
      }
    };

    connectinfo[cleft][0] = {
      miniright, {
        {3, 0}, // Vcc -> Vcc
        {0, 4}  // GND -> GND
      }
    };
    connectinfo[cleft][1] = {
      microright, {
        {3, 0}, // Vcc -> Vcc
        {0, 4}  // GND -> GND
      }
    };
    connectinfo[cleft][2] = {
      cright, {
        {3, 3}, // Vcc -> Vcc
        {0, 0}  // GND -> GND
      }
    };


  };

  bool sanitycheck(Print &response);
  void findactiveconnection(Print &response);
  void initpinmode();
  bool isconnected(connectorinfo &source, connectorcheck &targetconnection);
  bool isconnected(uint8_t sourcepin, uint8_t targetpin);

};

#endif