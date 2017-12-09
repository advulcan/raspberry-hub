#ifndef DISPALY_H
#define DISPALY_H
#include <stdio.h>
#include "controller.h"

void initDisplay();
void display(xbox_map_t map);
void display(int count);
void display(int count, double v);
#endif