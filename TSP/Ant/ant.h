//
// Created by 66919 on 2020/7/16.
//

#ifndef TSP_ANT_H
#define TSP_ANT_H

#include <bits/stdc++.h>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<iostream>

#define MAX_DIMENSION 500


int random (int l,int h);
double random(double l,double h);
double Random (double ans);
double power(double x, int y);


template <typename T>
int* algoAnt( int &dimension, T srcFile[500][2] ){
    // 结果用一个N+1长的数组
    typedef long long ll;
    double INF = 10e9;
    const int num_ant=30;//蚂蚁的数量
    const int MAX_GEN=1000;//最大迭代次数
    int ALPHA = 1;//信息素的权重
    int BETA = 4;//启发式因子重要程度权重
    int remain = 100;//信息素残留参数
    //double beat_path;//最优路径长度
    double dis[dimension+50][dimension+50];//各个城市的距离

    //各个城市的位置
    int vis[dimension][dimension];//禁忌表
    double info[dimension][dimension];//信息素矩阵
    //double active[dimension][dimension];//启发因子矩阵
    const int Q = 100;//信息素残留系数
    double ROU = 0.5;//信息素残留度
    unsigned seed=(unsigned)time(0);

    struct Ant
    {
        int Path[MAX_DIMENSION];
        double length;//当前已走的长度；
        int vis[MAX_DIMENSION];//已走的城市
        int cur_city;//现在所在的城市
        int num_move;//已经走的城市数
        void Init()
        {
            memset(vis,0,sizeof(vis));
            length=0.0;
            cur_city=random(0,dimension);
            Path[0]=cur_city;
            vis[cur_city]=1;
            num_move=1;
        }
        int choose()
        {
            int select_city=-1;//选择的城市
            double sum=0.0;
            double possible_city[dimension];//各个城市被选中的概率
            for(int i=0;i<dimension;i++)
            {
                if(!vis[i])
                {
                    possible_city[i]=power(info[cur_city][i],ALPHA)*power(1.0/dis[cur_city][i],BETA);
                    sum+=possible_city[i];//计算概率
                }
                else
                {
                    possible_city[i]=0;
                }
            }
            //轮盘赌选择
            double possible_du=0.0;
            //double sum_tmp=0.0;
            if(sum>0.0)
            {
                possible_du=random(0.0,sum);
                for(int i=0;i<dimension;i++)
                {
                    if(!vis[i])
                    {
                        possible_du-=possible_city[i];
                        if(possible_du<0.0)
                        {
                            select_city=i;
                            break;
                        }
                    }
                }
            }
            if(select_city==-1)
            {
                for(int i=0;i<dimension;i++)
                {
                    if(!vis[i])
                    {
                        select_city=i;
                        break;
                    }
                }
            }
            return select_city;
        }
        void move_ant()
        {
            //if(num_move>=30)printf("KKKKKKK");
            int next_city=choose();//选择的城市
            Path[num_move]=next_city;
            vis[next_city]=1;
            cur_city=next_city;//更新当前位置
            length+=dis[Path[num_move-1]][Path[num_move]];
            num_move++;
            //if(num_move>=30)printf("KKKKKKK");
        }
        void find_()
        {
            Init();
            while(num_move<dimension)
            {
                move_ant();
                //printf("%d ",num_move);
                //printf("?????");
            }
            //printf("???");
            length+=dis[Path[dimension-1]][Path[0]];//更新长度
            //printf("??");
        }
    };
    struct TSP
    {
        Ant ants[num_ant];
        Ant ant_best;
        void Init()
        {
            ant_best.length=double(INF);//初始化最优的蚂蚁，设为最大
            printf("Begin to count\n");
            for(int i=0;i<dimension;i++)
            {
                for(int j=0;j<dimension;j++)
                {
                    double tmp1=srcFile[j][0]-srcFile[i][0];
                    double tmp2=srcFile[j][1]-srcFile[i][1];
                    dis[i][j]=sqrt(tmp1*tmp1+tmp2*tmp2);//计算每个城市间的距离
                    //printf("%d %d %lf\n",i,j,dis[i][j]);
                }
            }
            printf("Init Information\n");
            for(int i=0;i<dimension;i++)
            {
                for(int j=0;j<dimension;j++)
                {
                    info[i][j]=1.0;//初始化信息素
                }
            }
        }
        void Update()
        {
            double tmpinfo[dimension][dimension];//临时矩阵储存新增的信息素
            memset(tmpinfo,0,sizeof(tmpinfo));
            int n=0;
            int m=0;
            //蚁量算法更新信息素
            for(int i=0;i<num_ant;i++)
            {
                for(int j=1;j<dimension;j++)
                {
                    n=ants[i].Path[j-1];
                    m=ants[i].Path[j];
                    tmpinfo[n][m]+=Q/ants[i].length;
                    tmpinfo[m][n]=tmpinfo[n][m];
                }
                n=ants[i].Path[0];
                tmpinfo[n][m]+=Q/ants[i].length;
                tmpinfo[m][n]=tmpinfo[n][m];
            }
            //更新环境的信息素
            for(int i=0;i<dimension;i++)
            {
                for(int j=0;j<dimension;j++)
                {
                    //新环境的信息素=残留的+新留下的
                    info[i][j]=info[i][j]*ROU+tmpinfo[i][j];//感觉ROU有待商榷
                }
            }
        }

        void find_()
        {
            for(int i=0;i<MAX_GEN;i++)
            {
                printf("current generation is %d\n",i);
                for(int j=0;j<num_ant;j++)
                {
                    ants[j].find_();
                    //printf("****");
                }
                for(int j=0;j<num_ant;j++)
                {
                    if(ant_best.length>ants[j].length)
                    {
                        ant_best=ants[j];//更新每一代的最优解
                    }
                }
                Update();
                printf("current best length is %lf\n",ant_best.length);
            }
        }
    };
    srand(seed);//随机函数初始化
    TSP tsp;
//    printf("Please enter 30 cities position\n");
//    for(int i=0;i<30;i++)
//    {
//        scanf("%d%d",&srcFile[i][0],&srcFile[i][1]);//可以自己手动输入城市位置
//    }
    tsp.Init();
    tsp.find_();
    tsp.ant_best.Path[dimension]=tsp.ant_best.Path[0];
    printf("The minimum path is \n");
    for(int i=0;i<dimension+1;i++)
    {
        printf("%d ",tsp.ant_best.Path[i]);//打印出路径
    }
    return tsp.ant_best.Path;

}



#endif //TSP_ANT_H
