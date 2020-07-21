/*
 * Albert Tan
 */

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <cmath>
#include "readFile.h"
#include "testAlgo.h"
#include "ant.h"
#include "tabu.h"
#include "insertion.h"

#define RUN_TIMES 3
#define SAMPLE_AMOUNT 29
#define OUTPUT_PATH "../output.txt"
#define VISUAL_OUTPUT_PATH "../visualOutput.txt"

using namespace std;
// functions declarations
void Tic();
void Toc();

namespace Albert{
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
    template <typename T, typename D>
    double getLength(D ans, int dimension, T src[MAX_DIMENSION][2]){
        double length = 0;
        for(int i=0; i<dimension; i++){
            length += getDistance( src[ans[i]],src[ans[i+1]] );
        }
        return length;
    }
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
}

int getBestLength( const double length[SAMPLE_AMOUNT][RUN_TIMES], const int currentSample ){
    int index = 0;
    double minLength = length[0][0];
    for(int i=1; i<RUN_TIMES; i++ ){
        if( length[currentSample][i] < minLength ){
            index = i;
            minLength = length[currentSample][i];
        }
    }
    return index;
}

int getBestTime( const double time[SAMPLE_AMOUNT][RUN_TIMES], const int currentSample ){
    int index = 0;
    double minLength = time[0][0];
    for(int i=1; i<RUN_TIMES; i++ ){
        if( time[currentSample][i] < minLength ){
            index = i;
            minLength = time[currentSample][i];
        }
    }
    return index;
}


int main() {
    ofstream outputFile(OUTPUT_PATH);
    ofstream visualOutputFile(VISUAL_OUTPUT_PATH);
    if( !outputFile.is_open() || !visualOutputFile.is_open() ){
        cout<<"outputFile error!"<<endl;
        return 0;
    }

    outputFile << "Algo1: "<<endl;
    double time[SAMPLE_AMOUNT][RUN_TIMES] = {};
    double length[SAMPLE_AMOUNT][RUN_TIMES] = {};
    for(int i=0; i<SAMPLE_AMOUNT; i++) {
        // 当前文件
        string curFile = "../source-files/";
        curFile += files[i];
        outputFile << "File Name: "<< files[i] << endl;

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
        vector<int> ans_vec;

        vector<int*> answers_int;
        vector<vector<int>> answers_vector;

        for (int j = 0; j < RUN_TIMES; j++) {
            // 算法开始
            Tic();
//            if (typeName == "double") {
//                ans = algoName_double( dimension,src_double );
//            } else if (typeName == "int") {
//                ans = algoName_int(dimension, src_int);
//            }
            if (typeName == "double") {
                ans_vec = zycrf( dimension,src_double );
            } else if (typeName == "int") {
                ans_vec = zycrf(dimension, src_int);
            }
            // 结束
            Toc();

            // 记录answer
            answers_vector.push_back(ans_vec);

            // 记录时间
            time[i][j] = g_run_time;

            //记录长度
            if (typeName == "double") {
               length[i][j] = Albert::getLength( ans_vec,dimension,src_double );
            } else if (typeName == "int") {
                length[i][j] = Albert::getLength( ans_vec,dimension,src_int );
            }

            // 输出到output文件 -- BEGIN
            outputFile<< "Trial "<<j+1<<": Time: "<<time[i][j]<<"ms Length: "<<length[i][j]<<endl;
            outputFile<<"Path: ";
//            for(int k=0; k<dimension+1; k++){
//                outputFile<<ans[k]<<' ';
//            }
            for(int k=0; k<dimension+1; k++){
                outputFile<<ans_vec[k]<<' ';
            }
            outputFile<<endl;
            // 输出到output文件 -- END

        } // for j in RUN_TIMES

        // 计算每一个sample的最优表现 并且记录到output文件
        int bestLen = getBestLength(length,i);
        int bestTime = getBestTime(time,i);
        outputFile<< "The best trial of length: "<< "trial "<< bestLen+1 <<" -- Length: "<<length[i][bestLen]<<endl;
        outputFile<< "The best trial of time: "<< "trial "<< bestTime+1 <<" -- Time: "<<time[i][bestTime]<<"ms"<<endl<<endl;

        // 可视化输出
        visualOutputFile << dimension << endl;
        for(int n=0; n<dimension; n++) {
            if (typeName == "double") {
                visualOutputFile << src_double[n][0] << ' ' << src_double[n][1] << ' ';
            } else if (typeName == "int") {
                visualOutputFile << src_int[n][0] << ' ' << src_int[n][1] << ' ';
            }
        }
        visualOutputFile<<endl;
        for(int n=0; n<dimension+1; n++){
            visualOutputFile << answers_vector[bestLen][n]<<' ';
        }
        visualOutputFile<<endl;
        // 清空解集
        answers_vector.clear();
    }// for i in SAMPLES


    
    visualOutputFile.close();
    outputFile.close();
    return 0;
}
