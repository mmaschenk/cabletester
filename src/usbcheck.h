#ifndef _USBCHECK__H_
#define _USBCHECK__H_

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
} connectorinfo;

enum connections
{
  cleft,
  cright,
  aleft,
  CONNECTIONS_MAX
};

class USBCHECK
{
private:
  connectorinfo info[CONNECTIONS_MAX];
  /*
  pininfo cleftinfo[16] = {
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
  connectorinfo info[2] = {
    { 2, LEFT, "USB C", "v3.0", { 
      {16, 0, "A11 RX2+"},
      {16, 0, "A11 RX2+"}
      } 
    },
    { 2, LEFT, "USB C", { 
      {16, 0, "A11 RX2+"},
      {16, 0, "A11 RX2+"}
      } 
    }

  };
  */ 
public:
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

    info[aleft] = { 4, LEFT, "USB A", "v2.0",
    {
      {66, 0, "1    Vcc"},
      {67, 0, "2     D-"},
      {68, 0, "3     D+"},
      {69, 0, "4    GND"}}
    };

  };

  bool sanitycheck(Print &response);
};

#endif