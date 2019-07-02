#include "ros/ros.h"
#include "goinghome_host_eventhandler/request.h"
#include <iostream>
#include <cstdio>
#include <string>

typedef struct location
{
    int px, py, pz;
    int ox, oy, oz, ow;
} Loc;

#define    BASE 0
#define SECTOR1 1
#define SECTOR2 2
#define SECTOR3 3
#define SECTOR4 4
#define SECTOR5 5
#define SECTOR6 6
#define SECTOR7 7
#define SECTOR8 8

// HARD CODING FIRST, IMPLEMENT IT TO FILE SYSTEM LATER!

void destination_menu();
void gobase();
void set_destination(std::string &dest, std::string &name, std::string &mode);
void initialize_control();
void goSurveilancemode();
