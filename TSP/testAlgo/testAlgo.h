//
// Created by 66919 on 2020/7/15.
//

#ifndef TSP_TESTALGO_H
#define TSP_TESTALGO_H

#include <iostream>
#include <fstream>
#include <string>


/*
* 输入：dimension 是数据的维数，srcFile是数据集，直接拿来用就行
* 输出：返回answer数组
*/
//template <typename T>
//int* algoName(int dimension, T srcFile[500][2]){
//    // 结果用一个N+1长的数组
//    int* answer = new int[500];
//    /*
//     *  do something
//     */
//    for(int i=0; i<dimension; i++){
//        answer[i] = i+1;
//    }
//    answer[dimension] = 1;
//    return answer;
//}

int* algoName_int(int dimension, int srcFile[500][2]){
    // 结果用一个N+1长的数组
    int* answer = new int[500];
    /*
     *  do something
     */
    for(int i=0; i<dimension; i++){
        answer[i] = i+1;
    }
    answer[dimension] = 1;
    return answer;
}

int* algoName_double( int dimension, double srcFile[500][2]){
    // 结果用一个500长的数组
    int* answer = new int[500];
    /*
     *  do something
     */
    for(int i=0; i<dimension; i++){
        answer[i] = i+1;
    }
    answer[dimension] = 1;
    return answer;
}

#endif //TSP_TESTALGO_H
