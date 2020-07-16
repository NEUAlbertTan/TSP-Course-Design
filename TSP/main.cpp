/*
 * Albert Tan
 */

#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>
#include "readFile.h"
#include "testAlgo.h"
#include "ant.h"

#define RUN_TIMES 10
#define SAMPLE_AMOUNT 29

using namespace std;
// functions declarations
void Tic();
void Toc();

/*
 * 计算两点欧氏距离
 */
template <typename T>
double getDistance( T a[2], T b[2] ){
    return sqrt( (a[0] - b[0])*(a[0] - b[0]) + (a[1] - b[1])*(a[1] - b[1]) );
}
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
        length += getDistance( src[ans[i]],src[ans[i+1]] );
    }
    return length;
}


// global variant for timing
LARGE_INTEGER g_cpuFreq, g_startTime, g_endTime;
double g_run_time=0.0;      // the total running time


// 文件集合
string files[30]={
        "berlin52.tsp",
        "bier127.tsp",
        "ch130.tsp",
        "ch150.tsp",
        "d198.tsp",
        "eil101.tsp",
        "kroA100.tsp",
        "kroA150.tsp",
        "kroA200.tsp",
        "kroB100.tsp",
        "kroB150.tsp",
        "kroB200.tsp",
        "kroC100.tsp",
        "kroD100.tsp",
        "kroE100.tsp",
        "lin105.tsp",
        "pr107.tsp",
        "pr124.tsp",
        "pr136.tsp",
        "pr144.tsp",
        "pr152.tsp",
        "pr76.tsp",
        "rat195.tsp",
        "rat99.tsp",
        "rd100.tsp",
        "st70.tsp",
        "ts225.tsp",
        "tsp225.tsp",
        "u159.tsp"
};


// timer begin
void Tic(){
    QueryPerformanceFrequency(&g_cpuFreq);
    QueryPerformanceCounter(&g_startTime);
}

// timer end
void Toc(){
    QueryPerformanceCounter(&g_endTime);
    g_run_time = (((g_endTime.QuadPart - g_startTime.QuadPart) * 1000.0f) / g_cpuFreq.QuadPart);
    cout << g_run_time << " ms" << endl;
}


int main() {
    double time[SAMPLE_AMOUNT][RUN_TIMES] = {};
    double length[SAMPLE_AMOUNT][RUN_TIMES] = {};
    for(int i=0; i<SAMPLE_AMOUNT; i++) {
        // 当前文件
        string curFile = "../source-files/";
        curFile += files[i];

        // 文件数据
        int src_int[500][2] = {};
        double src_double[500][2] = {};

        // 数据维度
        int dimension = 0;

        // 数据类型
        string typeName = getType(curFile);

        // 从文件读取目标数据
        if (typeName == "double") {
            ReadFile(curFile, dimension, src_double);
        } else if (typeName == "int") {
            ReadFile(curFile, dimension, src_int);
        } else {
            cout << "File type error! " << endl;
            return 0;
        }

        // 算法结果
        int *ans = nullptr;

        for (int j = 0; j < RUN_TIMES; j++) {
            // 算法开始
            Tic();
            if (typeName == "double") {
                ans = algoName(dimension, src_double);
            } else if (typeName == "int") {
                ans = algoName(dimension, src_int);
            }
            // 结束
            Toc();
            time[i][j] = g_run_time;
            if (typeName == "double") {
               length[i][j] = getLength( ans,dimension,src_double );
            } else if (typeName == "int") {
                length[i][j] = getLength( ans,dimension,src_int );
            }
        }
    }

    return 0;
}
