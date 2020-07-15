//
// Created by 66919 on 2020/7/15.
//

#ifndef TSP_READFILE_H
#define TSP_READFILE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename T>
void ReadFile( string &filePath,int &dimension, T src[500][2]  );
string getType(string &filePath);

#endif //TSP_READFILE_H
