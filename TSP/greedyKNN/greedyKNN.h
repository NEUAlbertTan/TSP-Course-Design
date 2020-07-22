#ifndef GREEDY_KNN_H
#define GREEDY_KNN_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;
namespace DST{
    template <typename T>
    double getDistance( T a[2], T b[2] ){
        return sqrt( (a[0] - b[0])*(a[0] - b[0]) + (a[1] - b[1])*(a[1] - b[1]) );
    }
}
/*
* ���룺dimension �����ݵ�ά����srcFile�����ݼ���ֱ�������þ���
* ���������answer����
*/
int* greedy_knn_int(int dimension, int srcFile[500][2]){
    int* answer = new int[500];
    int pastnum,citynum,lastcitynum,listnum;
    int flag;
    int Dtemp;
    //int S[n];
    int sum = 0;
    auto * Cities=new double [dimension+1][2];/////���м�
    /////���ɳ��м�/////
    for(int i=0;i<dimension;i++){
        Cities[i][0]=srcFile[i][0];
        Cities[i][1]=srcFile[i][1];
    }
    /////����������/////
    double distances[dimension][dimension];
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            distances[i][j]=DST::getDistance(Cities[i],Cities[j]);
        }
    }
    srand((int)time(0));
    int firstnum = rand()%dimension;//��ʼ�����ڳ���
    answer[0] = firstnum;
    pastnum = 1;//�ѷ��ʵĳ�������
    do{
        citynum = 0;Dtemp = numeric_limits<int>::max();//Dtemp��ʼ��������
        do{
            listnum = 0;flag = 0;
            do{
                if(answer[listnum] == citynum){//�жϸó����Ƿ��ѱ����ʹ����������ʹ���
                    flag = 1;//��flagΪ1
                    break;//����ѭ�������������ıȽ�
                }else
                    listnum++;
            }while(listnum < pastnum);
            if(flag == 0&&distances[citynum][answer[pastnum - 1]] < Dtemp){
                //��ʾ��ǰδ�����ʵĳ�������һ���ѷ��ʹ��ĳ���֮��ľ���*/
                lastcitynum = citynum;
                //j���ڴ洢�ѷ��ʹ��ĳ���k
                Dtemp = distances[citynum][answer[pastnum - 1]];
                //Dtemp������ʱ�洢��ǰ��С·����ֵ
            }
            citynum++;
        }while(citynum < dimension);
        answer[pastnum] = lastcitynum;//���ѷ��ʹ��ĳ���j���뵽S[i]��
        pastnum++;
        sum += Dtemp;
        //���������֮�����̾��룬ע�⣺�ڽ���ѭ��ʱ������������δ�ص�ԭ�����ĳ���
    }while(pastnum < dimension);
    sum += distances[0][lastcitynum];
    //D[0][j]Ϊ���������ڵ����һ��������ԭ�����ĳ���֮��ľ���
    //cout<<sum<<endl;//������·����ֵ
    answer[dimension] = firstnum;
    return answer;
}

int* greedy_knn_double( int dimension, double srcFile[500][2]){
    int* answer = new int[500];
    int pastnum,citynum,lastcitynum,listnum;
    int flag;
    int Dtemp;
    //int S[n];
    int sum = 0;
    auto * Cities=new double [dimension+1][2];/////���м�
    /////���ɳ��м�/////
    for(int i=0;i<dimension;i++){
        Cities[i][0]=srcFile[i][0];
        Cities[i][1]=srcFile[i][1];
    }
    /////����������/////
    double distances[dimension][dimension];
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            distances[i][j]=DST::getDistance(Cities[i],Cities[j]);
        }
    }
    srand((int)time(0));
    int firstnum = rand()%dimension;//��ʼ�����ڳ���
    answer[0] = firstnum;
    pastnum = 1;//�ѷ��ʵĳ�������
    do{
        citynum = 0;Dtemp = 10000;//Dtemp��ʼ��������
        do{
            listnum = 0;flag = 0;
            do{
                if(answer[listnum] == citynum){//�жϸó����Ƿ��ѱ����ʹ����������ʹ���
                    flag = 1;//��flagΪ1
                    break;//����ѭ�������������ıȽ�
                }else
                    listnum++;
            }while(listnum < pastnum);
            if(flag == 0&&distances[citynum][answer[pastnum - 1]] < Dtemp){
                //��ʾ��ǰδ�����ʵĳ�������һ���ѷ��ʹ��ĳ���֮��ľ���*/
                lastcitynum = citynum;
                //j���ڴ洢�ѷ��ʹ��ĳ���k
                Dtemp = distances[citynum][answer[pastnum - 1]];
                //Dtemp������ʱ�洢��ǰ��С·����ֵ
            }
            citynum++;
        }while(citynum < dimension);
        answer[pastnum] = lastcitynum;//���ѷ��ʹ��ĳ���j���뵽S[i]��
        pastnum++;
        sum += Dtemp;
        //���������֮�����̾��룬ע�⣺�ڽ���ѭ��ʱ������������δ�ص�ԭ�����ĳ���
    }while(pastnum < dimension);
    sum += distances[0][lastcitynum];
    //D[0][j]Ϊ���������ڵ����һ��������ԭ�����ĳ���֮��ľ���
    //cout<<sum<<endl;//������·����ֵ
    answer[dimension] = firstnum;
    return answer;
}

#endif //GREEDY_KNN_H
