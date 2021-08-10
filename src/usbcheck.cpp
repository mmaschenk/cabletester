#include <Arduino.h>

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
        pr(response, "Cannot assign:  [%s] @ [%d]\n", pin.function, pin.pinnumber);
        int i = pin.pinnumber;
        connectorinfo cc = info[connectorassignment[i]];
        pininfo cp = cc.pin[pinassignment[i]];
        pr(response, "  [%d]: Already assigned to:  [%s] of [%s]\n", 
            i, cp.function, cc.name);        
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