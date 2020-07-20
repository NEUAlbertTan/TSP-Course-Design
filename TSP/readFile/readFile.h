//
// Created by 66919 on 2020/7/15.
//


#ifndef TSP_READFILE_H
#define TSP_READFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
template <typename T>
void ReadFile(const std::string &filePath, int &dimension, T src[500][2]){
    int n=0;
    std::ifstream inFile(filePath);
    if( !inFile.is_open() ){
        std::cerr<<"failed to open the source file!"<<std::endl;
        exit(0);
    }

    // display file name
    std::string str;
    getline(inFile,str);
    std::cout<<str<<std::endl;

    // skip some lines
    for(int i=0; i<2; i++){
        getline(inFile,str);
    }

    // get the dimension
    getline(inFile,str);
    // 提取str末尾数字
    for(int i = str.size()-1 ; i >= 0; --i){
        if( str[i] == ' ' || str[i] == ':' ){
            n = atoi ( ( str.substr( i+1,str.size() ) ).c_str());
            break;
        }
    }
    // 将dimension赋值
    dimension = n;
    if( dimension > 500 ){
        std::cerr<<"File dimension overflow!"<<std::endl;
        exit(0);
    }
    // get the edge_weight_type
    //    char edge_weight_type[20] = {};
    //    inFile >> str >> edge_weight_type;
    //    cout << str <<' '<< edge_weight_type;

    // skip
    getline(inFile,str);
    getline(inFile,str);

    // ( index, x, y )
    int index=0;
    T x=0,y=0;
    for( int i=0; i<n ; i++){
        inFile >> index >> x >> y;
        src[i][0] = x;
        src[i][1] = y;
    }
    inFile.close();
}
std::string getType(const std::string &filePath);
#endif //TSP_READFILE_H
