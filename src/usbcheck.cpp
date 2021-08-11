#include <Arduino.h>

#include "main.h"
#include "usbcheck.h"
#include <stdarg.h>

#define MAXIOS 69

void pr(Print &response, const char *fmt, ... ){
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt);
  vsnprintf(buf, sizeof(buf), (const char *)fmt, args); // for the rest of the world
  va_end(args);
  response.print(buf);
}

void USBCHECK::initpinmode() {    // Initialize all pins in config to digital input
  for (int connector=0; connector<CONNECTIONS_MAX; connector++) {
    connectorinfo i = info[connector];
    for (int p=0; p<i.size; p++) {
      pininfo pin = i.pin[p];

      pinMode(pin.pinnumber, INPUT_PULLUP);
      DEBUG("Inputmode set for");
      DEBUGLN(pin.pinnumber);
    }
  }
}

bool USBCHECK::isconnected(uint8_t sourcepin, uint8_t targetpin) {
  DEBUG("Checking physical pin ");
  DEBUG(sourcepin);
  DEBUG(" -> ");
  DEBUGLN(targetpin);

  pinMode(sourcepin, OUTPUT);
  digitalWrite(sourcepin, LOW);
  delay(10);

  if (digitalRead(targetpin) == LOW) {
    DEBUGLN("Pin activated. Returning true");
    pinMode(sourcepin, INPUT_PULLUP);
    return true;
  } else {
    pinMode(sourcepin, INPUT_PULLUP);
    DEBUGLN("Pin not activated. Returning false");
    return false;
  }
};

bool USBCHECK::isconnected(connectorinfo &source, connectorcheck &targetconnection) {
  connectorinfo *target = &info[targetconnection.target];
  //pr(response, "  Checking for targetconnection [%d] [%s] [%s]\n", targetconnection->target, target->name, target->subname);

  uint8_t tp = targetconnection.check[0].targetpin;
  uint8_t sp = targetconnection.check[0].sourcepin;
  pr(Serial, "    Need to check sourcepin %d (%s) @ [%d] against targetpin %d (%s) @ [%d]\n",
      sp, source.pin[sp].function, source.pin[sp].pinnumber, tp, target->pin[tp].function, target->pin[tp].pinnumber );

  if (isconnected(source.pin[sp].pinnumber, target->pin[tp].pinnumber) ) {
    DEBUGLN("Pin connected");
  } else {
    DEBUGLN("Pin not connected");
    return false;
  }

  tp = targetconnection.check[1].targetpin;
  sp = targetconnection.check[1].sourcepin;
  pr(Serial, "    Also to check sourcepin %d (%s) @ [%d] against targetpin %d (%s) @ [%d]\n",
      sp, source.pin[sp].function, source.pin[sp].pinnumber, tp, target->pin[tp].function, target->pin[tp].pinnumber );  

  if (isconnected(source.pin[sp].pinnumber, target->pin[tp].pinnumber) ) {
    DEBUGLN("Pin connected");
    return true ;
  }
  return false ;
};

void USBCHECK::findactiveconnection(Print &response) {
  pr(response, "Checking for connections\n");

  for(uint8_t leftconnector=0; leftconnector < CONNECTIONS_MAX/2; leftconnector++) {
    connectorinfo *src = &info[leftconnector];
    pr(response, "Checking connector: [%d] [%s] [%s]\n", leftconnector, src->name, src->subname);

    for(uint8_t targetnum=0; targetnum < CONNECTIONS_MAX/2; targetnum++) {
      connectorcheck *targetconnection = &connectinfo[leftconnector][targetnum];

      isconnected(*src, *targetconnection);

      /*
      connectorinfo *target = &info[targetconnection->target];
      pr(response, "  Checking for targetconnection [%d] [%s] [%s]\n", targetconnection->target, target->name, target->subname);

      uint8_t tp = targetconnection->check[0].targetpin;
      uint8_t sp = targetconnection->check[0].sourcepin;
      pr(response, "    Need to check sourcepin %d (%s) @ [%d] against targetpin %d (%s) @ [%d]\n",
          sp, src->pin[sp].function, src->pin[sp].pinnumber, tp, target->pin[tp].function, target->pin[sp].pinnumber );

      tp = targetconnection->check[1].targetpin;
      sp = targetconnection->check[1].sourcepin;
      pr(response, "    Also to check sourcepin %d (%s) @ [%d] against targetpin %d (%s) @ [%d]\n",
          sp, src->pin[sp].function, src->pin[sp].pinnumber, tp, target->pin[tp].function, target->pin[sp].pinnumber );          
      */
    }
  }
}

bool USBCHECK::sanitycheck(Print &response) {
  int8_t pinassignment[MAXIOS+1];
  int8_t connectorassignment[MAXIOS+1];

  for (int i = 0; i <= MAXIOS; i++) {
    pinassignment[i] = -1;
    connectorassignment[i] = -1;
  }


  for (int connector=0; connector<CONNECTIONS_MAX; connector++) {
    response.println("Starting");
    pr(response, "Checking [%d]\n", connector);
    connectorinfo i = info[connector];

    pr(response, "Name: [%d] [%s] [%s] [%d]\n", i.position, i.name, i.subname, i.size);

    for (int p=0; p<i.size; p++) {
      pininfo pin = i.pin[p];
      if (pinassignment[pin.pinnumber] == -1) {
        pr(response, "Assigning:  [%s] @ [%d]\n", pin.function, pin.pinnumber);        
        pinassignment[pin.pinnumber] = p;
        connectorassignment[pin.pinnumber] = connector;
      } else {
        //pr(response, "Dual use:  [%s] @ [%d]\n", pin.function, pin.pinnumber);
        int i = pin.pinnumber;
        connectorinfo cc = info[connectorassignment[i]];
        pininfo cp = cc.pin[pinassignment[i]];
        pr(response, "Dual use: [%s] @ [%d]: Already assigned to:  [%s] of [%s]\n", 
            pin.function, i, cp.function, cc.name);       
      }
    }    
  }

  for (int i=0; i<MAXIOS+1; i++) {
    if (pinassignment[i] != -1) {
      connectorinfo cc = info[connectorassignment[i]];
      pininfo cp = cc.pin[pinassignment[i]];
      pr(response, "Pin [%d] is connected to [%s] of [%s]\n", 
          i, cp.function, cc.name);        

    } else {
      pr(response, "Pin [%d] is unconnected\n", i);
    }
  }

  return true;
}

