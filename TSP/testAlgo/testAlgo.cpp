//
// Created by 66919 on 2020/7/15.
//

#include "testAlgo.h"

/*
* 输入：dimension 是数据的维数，srcFile是数据集，直接拿来用就行
* 输出：返回answer数组
*/
template <typename T>
int* algoName( int &dimension, T srcFile[500][2] ){
    // 结果用一个N+1长的数组
    int* answer = new int[dimension+1];
    for(int i=0; i<dimension+1; i++){
        answer[i] = i;
    }
    return answer;
}