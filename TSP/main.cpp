#include "header.h"
#include "readFile/readFile.h"
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
    for(int j=0; j<10; j++){
        Tic();
        for(int i=0; i<10000000;i++){

        }
        Toc();
    }
    return 0;
}
