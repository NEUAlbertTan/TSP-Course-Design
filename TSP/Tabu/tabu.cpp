//
// Created by 66919 on 2020/7/20.
//

#include "tabu.h"

int *Tabu_Search_double(int City_Num, double Source[500][2]) {
    int temp,flag;
    int rand1,rand2;
    uniform_int_distribution<>r2(0,City_Num-1);
    int max_gen=City_Num*20;/////最大迭代次数
    int best_gen;/////最佳迭代次数
    int gen=0;/////当前迭代次数
    int Ner_search=2*City_Num;/////邻域搜索次数
    int N_gen;/////当前邻居搜索次数
    int TabuLength=int(City_Num/2);/////禁忌长度
    int* OriginList=new int [City_Num+1];/////初始解序列
    int*BestList=new int [City_Num+1];/////最优解序列
    double BestAnswer;/////最优解长度
    int*TempBestList=new int [City_Num+1];/////当前最好解序列
    double TempBestAnswer;/////当前最好解长度
    int* TempList=new int[City_Num+1];/////当前解序列#
    double TempAnswer;/////当前解长度
    int* TempNList=new int [City_Num+1];/////当前邻居序列
    double TempNAnswer;/////当前邻居解长度
    double MaxA;/////初始解长度寄存
    auto * Cities=new double [City_Num+1][2];/////城市集
    auto * TabuList=new int [TabuLength][500];/////禁忌表
    random_device rd;
    mt19937 rn(time(nullptr));
    /////生成城市集/////
    for(int i=0;i<City_Num;i++){
        Cities[i][0]=Source[i][0];
        Cities[i][1]=Source[i][1];
    }
    /////计算距离矩阵/////
    double distances[City_Num][City_Num];
    for(int i=0;i<City_Num;i++){
        for(int j=0;j<City_Num;j++){
            distances[i][j]=Jia::getDistance(Cities[i],Cities[j]);
        }
    }
    /////生成初始解/////
    int* Num_List=new int [City_Num];
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
    BestAnswer=MaxA=TempAnswer=getLength(TempList, City_Num, Source);
    //cout<<BestAnswer<<endl;
    while(gen<max_gen){
        N_gen=0;
        TempBestAnswer=MaxA;
        while(N_gen<Ner_search)
        {
            for(int i=0;i<City_Num;i++){
                TempNList[i]=TempList[i];
            }
            /////交换邻域
            rand1=r2(rn);
            rand2=r2(rn);
            while(rand1==rand2){
                rand2=r2(rn);
            }
            temp=TempNList[rand1];
            TempNList[rand1]=TempNList[rand2];
            TempNList[rand2]=temp;
            TempNList[City_Num]=TempNList[0];
            /////判断是否在禁忌表
            for(int i=0; i < TabuLength; i++){
                flag=0;
                for(int j=0;j<City_Num+1;j++){
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
                TempNAnswer=getLength(TempNList,City_Num,Source);
                if(TempNAnswer<TempBestAnswer){
                    for(int i=0;i<City_Num+1;i++){
                        TempBestList[i]=TempNList[i];
                    }
                    TempBestAnswer=TempNAnswer;
                }
            }
            N_gen++;
        }

        if(TempBestAnswer<BestAnswer){
            for(int i=0;i<City_Num+1;i++){
                BestList[i]=TempBestList[i];
            }
            BestAnswer=TempBestAnswer;
        }
        for(int i=0;i<City_Num+1;i++){
            TempList[i]=TempBestList[i];
        }
        for(int i=0;i<City_Num+1;i++){
            TabuList[gen % TabuLength][i]=TempBestList[i];
        }
        /////更新禁忌表
        /*for(int i=0;i<TabuLenth-1;i++){
            for(int j=0;j<City_Num;j++){
                TabuList[i][j]=TabuList[i+1][j];
            }
        }/////删除第一个禁忌序列，后面的禁忌序列前移
        for(int i=0;i<City_Num;i++){
            TabuList[TabuLenth-1][i]=TempBestList[i];
        }/////插入新的禁忌序列 */
        gen++;
        //cout<<"gen"<<gen<<" length:"<<TempBestAnswer<<endl;
    }
    //cout<<BestAnswer<<endl;
    delete[] OriginList;
    delete[] TempBestList;
    delete[] TempList;
    delete[] TempNList;
    delete[] Cities;
    delete[] TabuList;
    delete[] Num_List;
    return BestList;
}

int *Tabu_Search_int(int City_Num, int Source[500][2]) {
    int temp,flag;
    int rand1,rand2;
    uniform_int_distribution<>r2(0,City_Num-1);
    int max_gen=1000;/////最大迭代次数
    int best_gen;/////最佳迭代次数
    int gen=0;/////当前迭代次数
    int Ner_search=200;/////邻域搜索次数
    int N_gen;/////当前邻居搜索次数
    int TabuLenth=5;/////禁忌长度
    int* OriginList=new int [City_Num+1];/////初始解序列
    int*BestList=new int [City_Num+1];/////最优解序列
    double BestAnswer;/////最优解长度
    int*TempBestList=new int [City_Num+1];/////当前最好解序列
    double TempBestAnswer;/////当前最好解长度
    int* TempList=new int[City_Num+1];/////当前解序列#
    double TempAnswer;/////当前解长度
    int* TempNList=new int [City_Num+1];/////当前邻居序列
    double TempNAnswer;/////当前邻居解长度
    double MaxA;/////初始解长度寄存
    auto * Cities=new int [City_Num+1][2];/////城市集
    auto * TabuList=new int [TabuLenth][500];/////禁忌表
    random_device rd;
    mt19937 rn(time(nullptr));
    /////生成城市集/////
    for(int i=0;i<City_Num;i++){
        Cities[i][0]=Source[i][0];
        Cities[i][1]=Source[i][1];
    }
    /////计算距离矩阵/////
    double distances[City_Num][City_Num];
    for(int i=0;i<City_Num;i++){
        for(int j=0;j<City_Num;j++){
            distances[i][j]=Jia::getDistance(Cities[i],Cities[j]);
        }
    }
    /////生成初始解/////
    int* Num_List=new int [City_Num];
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
    BestAnswer=MaxA=TempAnswer=getLength(TempList, City_Num, Source);
    //cout<<BestAnswer<<endl;
    while(gen<max_gen){
        N_gen=0;
        TempBestAnswer=MaxA;
        while(N_gen<Ner_search)
        {
            for(int i=0;i<City_Num;i++){
                TempNList[i]=TempList[i];
            }
            /////交换邻域
            rand1=r2(rn);
            rand2=r2(rn);
            while(rand1==rand2){
                rand2=r2(rn);
            }
            temp=TempNList[rand1];
            TempNList[rand1]=TempNList[rand2];
            TempNList[rand2]=temp;
            TempNList[City_Num]=TempNList[0];
            /////判断是否在禁忌表
            for(int i=0;i<TabuLenth;i++){
                flag=0;
                for(int j=0;j<City_Num+1;j++){
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
                TempNAnswer=getLength(TempNList,City_Num,Source);
                if(TempNAnswer<TempBestAnswer){
                    for(int i=0;i<City_Num+1;i++){
                        TempBestList[i]=TempNList[i];
                    }
                    TempBestAnswer=TempNAnswer;
                }
            }
            N_gen++;
        }

        if(TempBestAnswer<BestAnswer){
            for(int i=0;i<City_Num+1;i++){
                BestList[i]=TempBestList[i];
            }
            BestAnswer=TempBestAnswer;
        }
        for(int i=0;i<City_Num+1;i++){
            TempList[i]=TempBestList[i];
        }
        for(int i=0;i<City_Num+1;i++){
            TabuList[gen%TabuLenth][i]=TempBestList[i];
        }
        /////更新禁忌表
        /*for(int i=0;i<TabuLenth-1;i++){
            for(int j=0;j<City_Num;j++){
                TabuList[i][j]=TabuList[i+1][j];
            }
        }/////删除第一个禁忌序列，后面的禁忌序列前移
        for(int i=0;i<City_Num;i++){
            TabuList[TabuLenth-1][i]=TempBestList[i];
        }/////插入新的禁忌序列 */
        gen++;
    }
    //cout<<BestAnswer<<endl;
    delete[] OriginList;
    delete[] TempBestList;
    delete[] TempList;
    delete[] TempNList;
    delete[] Cities;
    delete[] TabuList;
    delete[] Num_List;
    return BestList;
}