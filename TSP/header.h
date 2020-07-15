//
// Created by 66919 on 2020/7/15.
//

#ifndef TSP_HEADER_H
#define TSP_HEADER_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;
// functions declarations
void Tic();
void Toc();

// global variant for timing
LARGE_INTEGER g_cpuFreq, g_startTime, g_endTime;
double g_run_time=0.0;      // the total running time

#endif //TSP_HEADER_H
