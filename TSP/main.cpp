/*
 * Albert Tan
 */

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <cmath>
#include "readFile.h"
//#include "testAlgo.h"
//#include "ant.h"
#include "tabu.h"
#include "insertion.h"

#define RUN_TIMES 10
#define SAMPLE_AMOUNT 29
#define OUTPUT_PATH "../output.txt"
#define VISUAL_OUTPUT_PATH "../visualOutput.txt"
#define BRIEF_OUTPUT_PATH "../briefOutput.txt"
#define VISUAL_ZJCRF "../visual_zjcrf.txt"
#define VISUAL_ZYCRF "../visual_zycrf.txt"
#define VISUAL_TABU "../visual_Tabu.txt"
#define MAX_DIMENSION 500

using namespace std;

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

// 文件集合
string files[29]={
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
        "pr76.tsp",
        "pr107.tsp",
        "pr124.tsp",
        "pr136.tsp",
        "pr144.tsp",
        "pr152.tsp",
        "rat99.tsp",
        "rat195.tsp",
        "rd100.tsp",
        "st70.tsp",
        "ts225.tsp",
        "tsp225.tsp",
        "u159.tsp"
};
// 最优解
int optimal[SAMPLE_AMOUNT] = {
        7542,118282,6110,6528,15780,629,21282,26524,29368,22141,26130,29437,20749,21294,22068,
        14379,108059,44303,59030,96772,58537,73682,1211,2323,7910,675,126643,3916,42080
};


// 文件流
ofstream outputFile;
ofstream briefOutputFile;
ofstream visual_zjcrf;
ofstream visual_zycrf;
ofstream visual_Tabu;


// global variant for timing
LARGE_INTEGER g_cpuFreq, g_startTime, g_endTime;
double g_run_time=0.0;      // the total running time
double sample_time[SAMPLE_AMOUNT][RUN_TIMES] = {};
double length[SAMPLE_AMOUNT][RUN_TIMES] = {};

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

// 最远插入法 Emon100
void run_zycrf(){
    outputFile << "Algo1: Farthest insertion"<<endl;
    briefOutputFile << "Algo1: Farthest insertion"<<endl;
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
            return ;
        }

        // 算法结果
        vector<int> ans_vec;

        vector<int*> answers_int;
        vector<vector<int>> answers_vector;

        for (int j = 0; j < RUN_TIMES; j++) {
            // 算法开始
            Tic();
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
            sample_time[i][j] = g_run_time;

            //记录长度
            if (typeName == "double") {
                length[i][j] = Albert::getLength( ans_vec,dimension,src_double );
            } else if (typeName == "int") {
                length[i][j] = Albert::getLength( ans_vec,dimension,src_int );
            }

            // 输出到output文件 -- BEGIN
            outputFile << "Trial " <<j+1 << ": Time: " << sample_time[i][j] << "ms Length: " << length[i][j] << endl;
            outputFile<<"Path: ";
            for(int k=0; k<dimension+1; k++){
                outputFile<<ans_vec[k]<<' ';
            }
            outputFile<<endl;
            // 输出到output文件 -- END
        } // for j in RUN_TIMES

        // 计算每一个sample的最优表现 并且记录到output文件
        int bestLen = getBestLength(length,i);
        int bestTime = getBestTime(sample_time, i);
        outputFile<< "The best trial of length: "<< "trial "<< bestLen+1 <<" -- Length: "<<length[i][bestLen]<<endl;
        outputFile << "The best trial of time: " << "trial " << bestTime+1 << " -- Time: " << sample_time[i][bestTime] << "ms" << endl << endl;
        // 简介文件
        briefOutputFile << length[i][bestLen] << ' ' << sample_time[i][bestLen]<<"ms" <<' ';
        // 可视化输出
        visual_zycrf << files[i] << endl;
        visual_zycrf << dimension << endl;
        for(int n=0; n<dimension; n++) {
            if (typeName == "double") {
                visual_zycrf << src_double[n][0] << ' ' << src_double[n][1] << ' ';
            } else if (typeName == "int") {
                visual_zycrf << src_int[n][0] << ' ' << src_int[n][1] << ' ';
            }
        }
        visual_zycrf<<endl;
        for(int n=0; n<dimension+1; n++){
            visual_zycrf << answers_vector[bestLen][n]<<' ';
        }
        visual_zycrf<<endl;
        // 清空解集
        answers_vector.clear();
    }// for i in SAMPLES
    briefOutputFile<<endl;
    visual_zycrf<<endl;
}

// 最近插入法 Emon100
void run_zjcrf(){
    outputFile << "Algo2: Nearest insertion"<<endl;
    briefOutputFile << "Algo2: Nearest insertion"<<endl;
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
            return ;
        }

        // 算法结果
        vector<int> ans_vec;

        vector<int*> answers_int;
        vector<vector<int>> answers_vector;

        for (int j = 0; j < RUN_TIMES; j++) {
            // 算法开始
            Tic();
            if (typeName == "double") {
                ans_vec = zjcrf( dimension,src_double );
            } else if (typeName == "int") {
                ans_vec = zjcrf(dimension, src_int);
            }
            // 结束
            Toc();

            // 记录answer
            answers_vector.push_back(ans_vec);

            // 记录时间
            sample_time[i][j] = g_run_time;

            //记录长度
            if (typeName == "double") {
                length[i][j] = Albert::getLength( ans_vec,dimension,src_double );
            } else if (typeName == "int") {
                length[i][j] = Albert::getLength( ans_vec,dimension,src_int );
            }

            // 输出到output文件 -- BEGIN
            outputFile << "Trial " <<j+1 << ": Time: " << sample_time[i][j] << "ms Length: " << length[i][j] << endl;
            outputFile<<"Path: ";
            for(int k=0; k<dimension+1; k++){
                outputFile<<ans_vec[k]<<' ';
            }
            outputFile<<endl;
            // 输出到output文件 -- END
        } // for j in RUN_TIMES

        // 计算每一个sample的最优表现 并且记录到output文件
        int bestLen = getBestLength(length,i);
        int bestTime = getBestTime(sample_time, i);
        outputFile<< "The best trial of length: "<< "trial "<< bestLen+1 <<" -- Length: "<<length[i][bestLen]<<endl;
        outputFile << "The best trial of time: " << "trial " << bestTime+1 << " -- Time: " << sample_time[i][bestTime] << "ms" << endl << endl;
        // 简介文件
        briefOutputFile << length[i][bestLen] << ' ' << sample_time[i][bestLen]<<"ms" << ' ';
        // 可视化输出
        visual_zjcrf << files[i] << endl;
        visual_zjcrf << dimension << endl;
        for(int n=0; n<dimension; n++) {
            if (typeName == "double") {
                visual_zjcrf << src_double[n][0] << ' ' << src_double[n][1] << ' ';
            } else if (typeName == "int") {
                visual_zjcrf << src_int[n][0] << ' ' << src_int[n][1] << ' ';
            }
        }
        visual_zjcrf<<endl;
        for(int n=0; n<dimension+1; n++){
            visual_zjcrf << answers_vector[bestLen][n]<<' ';
        }
        visual_zjcrf<<endl;
        // 清空解集
        answers_vector.clear();
    }// for i in SAMPLES
    briefOutputFile<<endl;
}

// 禁忌搜索 Jia
void run_Tabu(){
    outputFile << "Algo3: Tabu Search "<<endl;
    briefOutputFile<< "Algo3: Tabu Search "<<endl;
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
            return ;
        }

        // 算法结果
        int *ans = nullptr;

        vector<int*> answers_int;

        for (int j = 0; j < RUN_TIMES; j++) {
            // 算法开始
            Tic();
            if (typeName == "double") {
                ans = Tabu_Search_double(dimension,src_double);
            } else if (typeName == "int") {
                ans = Tabu_Search_int(dimension,src_int);
            }
            // 结束
            Toc();

            // 记录answer
            answers_int.push_back(ans);

            // 记录时间
            sample_time[i][j] = g_run_time;
            //记录长度
            if (typeName == "double") {
                length[i][j] = Albert::getLength( ans,dimension,src_double );
            } else if (typeName == "int") {
                length[i][j] = Albert::getLength( ans,dimension,src_int );
            }

            // 输出到output文件 -- BEGIN
            outputFile << "Trial " <<j+1 << ": Time: " << sample_time[i][j] << "ms Length: " << length[i][j] << endl;
            outputFile<<"Path: ";
            for(int k=0; k<dimension+1; k++){
                outputFile<<ans[k]<<' ';
            }
            outputFile<<endl;
            // 输出到output文件 -- END

        } // for j in RUN_TIMES

        // 计算每一个sample的最优表现 并且记录到output文件
        int bestLen = getBestLength(length,i);
        int bestTime = getBestTime(sample_time, i);
        outputFile<< "The best trial of length: "<< "trial "<< bestLen+1 <<" -- Length: "<<length[i][bestLen]<<endl;
        outputFile << "The best trial of time: " << "trial " << bestTime+1 << " -- Time: " << sample_time[i][bestTime] << "ms" << endl << endl;
        briefOutputFile << length[i][bestLen] << ' ' << sample_time[i][bestLen]<<"ms" << ' ';
        // 可视化输出
        visual_Tabu << files[i] << endl;
        visual_Tabu << dimension << endl;
        for(int n=0; n<dimension; n++) {
            if (typeName == "double") {
                visual_Tabu << src_double[n][0] << ' ' << src_double[n][1] << ' ';
            } else if (typeName == "int") {
                visual_Tabu << src_int[n][0] << ' ' << src_int[n][1] << ' ';
            }
        }
        visual_Tabu<<endl;
        for(int n=0; n<dimension+1; n++){
            visual_Tabu << answers_int[bestLen][n]<<' ';
        }
        visual_Tabu<<endl;
        // 清空解集
        answers_int.clear();
    }// for i in SAMPLES
    briefOutputFile<<endl;
}

int main() {
    outputFile.open(OUTPUT_PATH);
    briefOutputFile.open(BRIEF_OUTPUT_PATH);
    visual_Tabu.open(VISUAL_TABU);
    visual_zjcrf.open(VISUAL_ZJCRF);
    visual_zycrf.open(VISUAL_ZYCRF);
    for(auto & file : files){
        briefOutputFile<< file << ' '<<" X ";
    }
    briefOutputFile<<endl;
    if( !outputFile.is_open() || !briefOutputFile.is_open() || !visual_zycrf.is_open() || !visual_zjcrf.is_open() || !visual_Tabu.is_open() ){
        cout<<"outputFile error!"<<endl;
        return 0;
    }

    //Emon100: Farthest insertion
    run_zycrf();

    //Emon100: Nearest insertion
    run_zjcrf();

    //Jia: Tabu Search
    //run_Tabu();

    briefOutputFile<<"optimal"<<endl;
    for(int i : optimal){
        briefOutputFile<< i << ' '<<" X ";
    }
    briefOutputFile<<endl;

    visual_zjcrf.close();
    visual_zycrf.close();
    visual_Tabu.close();
    outputFile.close();
    briefOutputFile.close();
    return 0;
}
