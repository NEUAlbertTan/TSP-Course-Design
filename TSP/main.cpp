#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "readFile/readFile.h"
#include "testAlgo/testAlgo.h"

using namespace std;
// functions declarations
void Tic();
void Toc();

// global variant for timing
LARGE_INTEGER g_cpuFreq, g_startTime, g_endTime;
double g_run_time=0.0;      // the total running time
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


    for(int i=0; i<29; i++){
        // 当前文件
        string curFile = files[i];

        // 文件数据
        int src_int[500][2]={};
        double src_double[500][2]={};

        // 数据维度
        int n=0;

        // 数据类型
        string typeName = getType(curFile);

        // 从文件读取目标数据
        if( typeName == "double" ){
            ReadFile(curFile,n,src_double);
        } else if( typeName == "int" ){
            ReadFile( curFile, n, src_int );
        } else {
            cout<< "File type error! "<<endl;
            return 0;
        }

        // 算法结果
        int *ans= nullptr;

        // 算法开始
        Tic();
        if( typeName == "double" ){
            ans = algoName(n,src_double);
            for(int j=1; j<=n; j++){
                cout << src_double[j][0] << ' ' << src_double[j][1] <<endl;
            }

        } else if( typeName == "int" ){
            ans = algoName(n,src_int);
            for(int j=1; j<=n; j++){
                cout << src_int[j][0] << ' ' << src_int[j][1] <<endl;
            }
        }
        // 结束
        Toc();
    }



    return 0;
}
