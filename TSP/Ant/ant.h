//
// Created by 66919 on 2020/7/16.
//

#ifndef TSP_ANT_H
#define TSP_ANT_H
#include <bits/stdc++.h>
#include <cmath>
#include <windows.h>
using namespace std;
namespace sama{
    double INF = 10e9;
    constexpr int num_ant=52;//蚂蚁的数量
    constexpr int dimension=250;//max城市数量
    constexpr int MAX_GEN=100;//最大迭代次数
    constexpr int ALPHA = 1;//信息素的权重
    constexpr int BETA = 4;//启发式因子重要程度权重
    constexpr int remain = 100;//信息素残留参数
}

//double srcFile[dimension][2] = {{565,575},{25,185},{345,750},{945,685},{845,655},{880,660},{25,230},{525,1000},{580,1175},{650,1130},{1605,620},{1220,580},{1465,200},{1530,5},{845,680},{725,370},{145,665},{415,635},{510,875},{560,365},{300,465},{520,585},{480,415},{835,625},{975,580},{1215,245},{1320,315},{1250,400},{660,180},{410,250},{420,555},{575,665},{1150,1160},{700,580},{685,595},{685,610},{770,610},{795,645},{720,635},{760,650},{475,960},{95,260},{875,920},{700,500},{555,815},{830,485},{1170,65},{830,610},{605,625},{595,360},{1340,725},{1740,245}};

//各个城市的位置
//double active[dimension][dimension];//启发因子矩阵
const int Q = 100;//信息素残留系数
double ROU = 0.5;//信息素残留度

unsigned seed=(unsigned)time(0);
int random (int l,int h)
{
    return l+(h-l)*rand()/(RAND_MAX+1);
}
double random(double l,double h)
{
    return l+(h-l)*rand()/(RAND_MAX+1.0);
}
double Random (double ans)
{
    return (double)((int)(ans+0.5));
}
double power(double x, int y)//快速幂
{
    double ans = 1;
    while(y)
    {
        if(y&1)ans*=x;
        x*=x;
        y>>=1;
    }
    return ans;
}
struct Ant
{
    static double (*dis)[sama::dimension+50];//各个城市的距离
    static double (*info)[sama::dimension];//信息素矩阵
    int Path[sama::dimension+1];
    double length;//当前已走的长度；
    int vis[sama::dimension];//已走的城市
    int cur_city;//现在所在的城市
    int num_move;//已经走的城市数
    void Init()
    {
        memset(vis,0,sizeof(vis));
        length=0.0;
        cur_city=random(0,sama::dimension);
        Path[0]=cur_city;
        vis[cur_city]=1;
        num_move=1;
    }
    int choose()
    {
        int select_city=-1;//选择的城市
        double sum=0.0;
        double possible_city[sama::dimension];//各个城市被选中的概率
        for(int i=0;i<sama::dimension;i++)
        {
            if(!vis[i])
            {
                possible_city[i]=power(info[cur_city][i],sama::ALPHA)*power(1.0/dis[cur_city][i],sama::BETA);
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
            for(int i=0;i<sama::dimension;i++)
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
            for(int i=0;i<sama::dimension;i++)
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
        //if(num_move>=30)//printf("KKKKKKK");
        int next_city=choose();//选择的城市
        Path[num_move]=next_city;
        vis[next_city]=1;
        cur_city=next_city;//更新当前位置
        length+=dis[Path[num_move-1]][Path[num_move]];
        num_move++;
        //if(num_move>=30)//printf("KKKKKKK");
    }
    void find_()
    {
        Init();
        while(num_move<sama::dimension)
        {
            move_ant();
            ////printf("%d ",num_move);
            ////printf("?????");
        }
        ////printf("???");
        length+=dis[Path[sama::dimension-1]][Path[0]];//更新长度
        ////printf("??");
    }
};
double (*Ant::dis)[sama::dimension+50]= nullptr;
double (*Ant::info)[sama::dimension]= nullptr;
struct TSP
{
    Ant ants[sama::num_ant];
    Ant ant_best;
    void Update()
    {
        double tmpinfo[sama::dimension][sama::dimension];//临时矩阵储存新增的信息素
        memset(tmpinfo,0,sizeof(tmpinfo));
        int n=0;
        int m=0;
        //蚁量算法更新信息素
        for(int i=0;i<sama::num_ant;i++)
        {
            for(int j=1;j<sama::dimension;j++)
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
        for(int i=0;i<sama::dimension;i++)
        {
            for(int j=0;j<sama::dimension;j++)
            {
                //新环境的信息素=残留的+新留下的
                Ant::info[i][j]=Ant::info[i][j]*ROU+tmpinfo[i][j];//感觉ROU有待商榷
            }
        }
    }

    void find_()
    {
        for(int i=0;i<sama::MAX_GEN;i++)
        {
            //printf("current generation is %d\n",i);
            for(int j=0;j<sama::num_ant;j++)
            {
                ants[j].find_();
                ////printf("****");
            }
            for(int j=0;j<sama::num_ant;j++)
            {
                if(ant_best.length>ants[j].length)
                {
                    ant_best=ants[j];//更新每一代的最优解
                }
            }
            Update();
            //printf("current best length is %lf\n",ant_best.length);
        }
    }
    explicit TSP(double srcFile[sama::dimension][2]){
        Ant::dis = new double[sama::dimension+50][sama::dimension+50];
        Ant::info= new double[sama::dimension][sama::dimension];
        ant_best.length=double(sama::INF);//初始化最优的蚂蚁，设为最大
        //printf("Begin to count\n");
        for(int i=0;i<sama::dimension;i++)
        {
            for(int j=0;j<sama::dimension;j++)
            {
                double tmp1=srcFile[j][0]-srcFile[i][0];
                double tmp2=srcFile[j][1]-srcFile[i][1];
                Ant::dis[i][j]=sqrt(tmp1*tmp1+tmp2*tmp2);//计算每个城市间的距离
                ////printf("%d %d %lf\n",i,j,dis[i][j]);
            }
        }
        ////printf("Init Information\n");
        for(int i=0;i<sama::dimension;i++)
        {
            for(int j=0;j<sama::dimension;j++)
            {
                Ant::info[i][j]=1.0;//初始化信息素
            }
        }
    }
};

int *ant(int dimension, double cities[][2]){
    TSP tsp(cities);
    tsp.find_();
    tsp.ant_best.Path[dimension]=tsp.ant_best.Path[0];

    int *res = new int[dimension+1];
    for(int i=0;i<dimension+1;i++)
    {
        //printf("%d ",tsp.ant_best.Path[i]);//打印出路径
        res[i]=tsp.ant_best.Path[i];
    }
    return res;
}

#endif //TSP_ANT_H
