//
// Created by 66919 on 2020/7/20.
//

#ifndef TSP_INSERTION_H
#define TSP_INSERTION_H
/** @brief
 *  最近插入法和最远插入法的实现
 * */
#include <unordered_set>
#include <unordered_map>
#include <type_traits>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <numeric>
#include <list>

template <typename T> double getDistance(T a[2], T b[2]) {
    return std::sqrt((a[0] - b[0]) * (a[0] - b[0]) +
                     (a[1] - b[1]) * (a[1] - b[1]));
}

inline int getRandomNum(int begin,int end){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(begin,end);
    return dis(gen);
}


template<typename T>
std::vector<int> zycrf(int dimension, T cities[500][2]){
    std::list<int> ans;
    static_assert(std::is_arithmetic<T>::value, "Should give arithmetic array to zycrf.");//限定T是数字类型
    //从随机点开始
    ans.push_back(getRandomNum(0,dimension-1));
    ans.push_back(ans.front());

    //首先初始化的数据结构功能：记下每个不在环上的点对应的1.最近的环上的点2.距离
    //每一次往环上加入一个点之后，更新每个点的这两个值
    auto PointMatch = std::unordered_map<int,std::pair<int,double>>();
    for(int i = 0; i < dimension ; ++i){
        PointMatch[i]={ans.front(),getDistance(cities[i],cities[ans.front()])};
    }

    //每一个不在环上的点到距离最近的环上的点的距离,这个距离最大的点
    //重复,直到将所有点插入环中
    int farthestPoint=ans.front();
    PointMatch.erase(farthestPoint);//刚刚加入环的点从不在环中点的集合里删除
    while(!PointMatch.empty()){//O(N)
        double longestDistance = -1;
        //更新
        for(auto &[x,y]:PointMatch){
            const auto tmpDis=getDistance(cities[x],cities[farthestPoint]);
            if(y.second>tmpDis){//距离更新
                y={farthestPoint,tmpDis};//看最新的
            }
            if(y.second>longestDistance){//顺便寻找最远的点
                longestDistance = y.second;
                farthestPoint = x;
            }
        }


        //插入在环内合适位置
        auto lastiter = ans.cbegin();
        auto iter = ans.cbegin();
        ++iter;
        auto pos = ans.cend();
        double tmpdiff = std::numeric_limits<double>::max();
        while(iter!=ans.cend()){//寻找插入位置O(N)
            const double tmpdis = getDistance(cities[*lastiter],cities[*iter]);
            const double add1 = getDistance(cities[*lastiter],cities[farthestPoint]);
            const double add2 = getDistance(cities[*iter],cities[farthestPoint]);
            if(add1+add2-tmpdis < tmpdiff){
                tmpdiff = add1 + add2 - tmpdis;
                pos = iter;
            }
            ++lastiter;
            ++iter;
        }
        ans.insert(pos,farthestPoint);
        PointMatch.erase(farthestPoint);//刚刚加入环的点从不在环中点的集合里删除
    }
    ans.push_back(ans.front());
    std::vector<int> res;
    res.reserve(dimension+1);
    for(auto &&i:ans){
        res.push_back(i);
    }
    return res;
}

template<typename T>
std::vector<int> zjcrf(int dimension, T cities[500][2]){
    static_assert(std::is_arithmetic<T>::value, "Should give arithmetic array to zycrf.");//限定T是数字类型
    //从随机点开始
    std::vector<int> ans;
    ans.reserve(dimension+1);
    ans.push_back(getRandomNum(0,dimension-1));
    ans.push_back(ans[0]);

    //首先初始化的数据结构功能：记下每个不在环上的点对应的1.最近的环上的点2.距离
    //每一次往环上加入一个点之后，更新每个点的这两个值
    auto PointMatch = std::unordered_map<int,std::pair<int,double>>();
    for(int i = 0; i < dimension ; ++i){
        PointMatch[i]={ans[0],getDistance(cities[i],cities[ans[0]])};
    }

    //每一个不在环上的点到距离最近的环上的点的距离,这个距离最大的点
    //重复,直到将所有点插入环中
    int farthestPoint=ans[0];
    PointMatch.erase(farthestPoint);//刚刚加入环的点从不在环中点的集合里删除
    while(!PointMatch.empty()){
        double shortestDistance = std::numeric_limits<double>::max();
        for(auto &[x,y]:PointMatch){
            const auto tmpDis=getDistance(cities[x],cities[farthestPoint]);
            if(y.second > tmpDis){//距离更新
                y={farthestPoint,tmpDis};//看最新的
            }
            if(y.second < shortestDistance){//寻找最近的点
                shortestDistance = y.second;
                farthestPoint = x;
            }
        }


        //插入在环内合适位置
        auto iter = ans.begin()+1;
        auto pos = ans.end();
        double tmpdiff = std::numeric_limits<double>::max();
        while(iter!=ans.end()){
            const double tmpdis = getDistance(cities[*(iter-1)],cities[*iter]);
            const double add1 = getDistance(cities[*(iter-1)],cities[farthestPoint]);
            const double add2 = getDistance(cities[*iter],cities[farthestPoint]);
            if(add1+add2-tmpdis < tmpdiff){
                tmpdiff = add1 + add2 - tmpdis;
                pos = iter;
            }
            ++iter;
        }
        ans.insert(pos,farthestPoint);
        PointMatch.erase(farthestPoint);//刚刚加入环的点从不在环中点的集合里删除
    }
    return ans;
}

#endif //TSP_INSERTION_H
