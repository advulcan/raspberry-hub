#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "controller.h"
#include "display.h"

void initMonitor(int pin);
void refresh(int count);
void refresh(xbox_map_t map);
