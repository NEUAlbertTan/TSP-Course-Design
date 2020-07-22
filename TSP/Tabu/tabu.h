//
// Created by 66919 on 2020/7/20.
//

#ifndef TSP_TABU_H
#define TSP_TABU_H

#include <iostream>
#include <math.h>
#include <random>
#include <ctime>
using namespace std;
namespace Jia{
    template <typename T>
    double getDistance( T a[2], T b[2] ){
        return sqrt( (a[0] - b[0])*(a[0] - b[0]) + (a[1] - b[1])*(a[1] - b[1]) );
    }
}
int *Tabu_Search_int(int City_Num, int Source[500][2]);
int *Tabu_Search_double(int City_Num, double Source[500][2]);
/*
 * 计算路径长度
 * dimension：维度；
 * ans：dimension+1维的数组，全排列
 * src：原数据
 */
template <typename T>
double getLength( const int *ans, int dimension, T src[500][2] ){
    double length = 0;
    for(int i=0; i<dimension; i++){
        length += Jia::getDistance( src[ans[i]],src[ans[i+1]] );
    }
    return length;
}



#endif //TSP_TABU_H
