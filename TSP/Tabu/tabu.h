//
// Created by 66919 on 2020/7/20.
//

#ifndef TSP_TABU_H
#define TSP_TABU_H
#include <iostream>
#include <math.h>
#include <random>
using namespace std;
#define MAX_DIMENSION 500

int *Tabu_Search_Double(int City_Num, double Source[500][2]);
random_device rd2;
mt19937 rn(rd2());
namespace Jia{
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
    double getLength(const int *ans, int dimension, T src[500][2]){
        double length = 0;
        for(int i=0; i<dimension; i++){
            length += getDistance( src[ans[i]],src[ans[i+1]] );
        }
        return length;
    }
}
int *Tabu_Search_Double(int City_Num, double Source[500][2]) {
    int temp,flag;
    int rand1,rand2;
    //uniform_int_distribution<>r2(0,City_Num-1);
    uniform_int_distribution<>r2(0,MAX_DIMENSION);
    int max_gen=1000;/////最大迭代次数
    int best_gen;/////最佳迭代次数
    int gen=0;/////当前迭代次数
    int Ner_search=200;/////邻域搜索次数
    int N_gen;/////当前邻居搜索次数
    const int TabuLenth=20;/////禁忌长度
    //int OriginList[City_Num+1];/////初始解序列
    int* OriginList = new int[MAX_DIMENSION];/////初始解序列
    int* BestList = new int[City_Num + 1];/////最优解序列
    double BestAnswer;/////最优解长度
    //int TempBestList[City_Num+1];/////当前最好解序列
    int* TempBestList = new int[MAX_DIMENSION];/////当前最好解序列
    double TempBestAnswer;/////当前最好解长度
    //int TempList[City_Num+1];/////当前解序列
    int* TempList = new int[MAX_DIMENSION];/////当前解序列
    double TempAnswer;/////当前解长度
    //int TempNList[City_Num+1];/////当前邻居序列
    int* TempNList = new int[MAX_DIMENSION];/////当前邻居序列
    double TempNAnswer;/////当前邻居解长度
    double MaxA;/////初始解长度寄存
    //int Cities[City_Num+1][2];/////城市集
    double Cities[MAX_DIMENSION][2];/////城市集
    //int TabuList[TabuLenth][City_Num];/////禁忌表
    int TabuList[20][MAX_DIMENSION];/////禁忌表
    random_device rd;
    mt19937 rn(rd());
    /////生成城市集/////
    for(int i=0;i<City_Num;i++){
        Cities[i][0]=Source[i][0];
        Cities[i][1]=Source[i][1];
    }
    /////计算距离矩阵/////
    //double distances[City_Num][City_Num];
    double distances[MAX_DIMENSION][MAX_DIMENSION];
    for(int i=0;i<City_Num;i++){
        for(int j=0;j<City_Num;j++){
            distances[i][j]=Jia::getDistance(Cities[i],Cities[j]);
        }
    }
    /////生成初始解/////
    //int Num_List[City_Num];
    int Num_List[MAX_DIMENSION];
    int tempNum;
    int numexchange;
    int RSumNum=City_Num-1;
    uniform_int_distribution<> dis(0,RSumNum);
    for(int i=0;i<City_Num;i++){
        Num_List[i]=i;
    }
    /////洗牌算法生成初始序列
    for(int i=0;i<City_Num;i++){
        tempNum=dis(rn);
        numexchange=Num_List[RSumNum];
        Num_List[RSumNum]=Num_List[tempNum];
        Num_List[tempNum]=numexchange;
        RSumNum--;
    }
    for(int i=0;i<City_Num;i++){
        OriginList[i]=Num_List[i];
        TempList[i]=Num_List[i];
    }
    TempList[City_Num]=TempList[0];
    BestAnswer=MaxA=TempAnswer=Jia::getLength(TempList, City_Num, Source);
    while(gen<max_gen){
        N_gen=0;
        TempBestAnswer=MaxA;
        while(N_gen<Ner_search){
            /////交换邻域
            for(int i=0;i<City_Num;i++){
                TempNList[i]=TempList[i];
            }
            TempNList[City_Num]=TempNList[0];
            rand1=r2(rd2);
            rand2=r2(rd2);
            while(rand1==rand2){
                rand2=r2(rd2);
            }
            temp=TempNList[rand1];
            TempNList[rand1]=TempNList[rand2];
            TempNList[rand2]=TempNList[rand1];
            TempNList[City_Num]=TempNList[0];
            /////判断是否在禁忌表
            for(int i=0;i<TabuLenth;i++){
                flag=0;
                for(int j=0;j<City_Num;j++){
                    if(TempNList[j]!=TabuList[i][j]){
                        flag=1;
                        break;
                    }
                }
                if(flag==0){
                    break;
                }
            }
            /////不在禁忌表内
            if(flag==1){
                TempNAnswer=Jia::getLength(TempNList,City_Num,Source);
                if(TempNAnswer<TempBestAnswer){
                    for(int i=0;i<City_Num+1;i++){
                        TempBestList[i]=TempNList[i];
                        TempBestAnswer=TempNAnswer;
                    }
                }
                N_gen++;
            }
        }
        if(TempBestAnswer<BestAnswer){
            best_gen=gen;
            for(int i=0;i<City_Num+1;i++){
                BestList[i]=TempBestList[i];
            }
            BestAnswer=TempBestAnswer;
        }
        for(int i=0;i<City_Num+1;i++){
            OriginList[i]=TempBestList[i];
        }
        /////更新禁忌表
        for(int i=0;i<TabuLenth-1;i++){
            for(int j=0;j<City_Num;j++){
                TabuList[i][j]=TabuList[i+1][j];
            }
        }/////删除第一个禁忌序列，后面的禁忌序列前移
        for(int i=0;i<City_Num;i++){
            TabuList[TabuLenth-1][i]=TempBestList[i];
        }/////插入新的禁忌序列
        gen++;
    }
    return BestList;
}


#endif //TSP_TABU_H
