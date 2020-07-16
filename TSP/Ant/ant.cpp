#include "ant.h"
//#define NULL -1

/*
* 输入：dimension 是数据的维数，srcFile是数据集，直接拿来用就行
* 输出：返回answer数组
*/
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


