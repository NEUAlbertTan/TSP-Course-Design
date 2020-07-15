//
// Created by 66919 on 2020/7/15.
//

#include "readFile.h"

/*函数说明：
 * 参数列表：
 *      filePath:文件读取路径
 *      dimension：点的个数，在主函数中定义，在ReadFile中由n赋值
 *      src[500][2]：点的坐标，在主函数中定义，类型由传入值决定
 *      ( 数组下标从一开始，弃用src[0] )
 * 函数功能
 *      从filePath中读取数据，dimension中存放数据维数，src中存放点集，
 *      同时输出文件名、边权类型
 * 函数返回值
 *      无
 */
template <typename T>
void ReadFile( string &filePath,int &dimension, T src[500][2]  ){
    int n=0;
    ifstream inFile(filePath);
    if( !inFile.is_open() ){
        cout<<"failed to open the source file!"<<endl;
        exit(0);
    }

    // display file name
    string str;
    getline(inFile,str);
    cout<<str<<endl;

    // skip some lines
    for(int i=0; i<2; i++){
        getline(inFile,str);
    }

    // get the dimension
    inFile >> str >> n;
    dimension  = n;

    // get the edge_weight_type
//    char edge_weight_type[20] = {};
//    inFile >> str >> edge_weight_type;
//    cout << str <<' '<< edge_weight_type;

    // skip
    getline(inFile,str);
    getline(inFile,str);
    getline(inFile,str);

    // ( index, x, y )
    int index=0;
    T x=0,y=0;
    for( int i=1; i<=n ; i++){
        inFile >> index >> x >> y;
        src[i][0] = x;
        src[i][1] = y;
    }
    inFile.close();
}

/*函数说明：
 * 参数列表：
 *      filePath：文件路径
 * 函数返回值
 *      文件包含的数据类型
 */
string getType(string &filePath){
    ifstream inFile(filePath);
    if( !inFile.is_open() ){
        cout<<"failed to open the source file!"<<endl;
        exit(0);
    }
    string str;
    for(int i=0; i<7; i++){
        getline( inFile,str );
    }
    if( str.find('.') != str.npos ){
        // if find a dot in data
        inFile.close();
        return string("double");
    } else {
        inFile.close();
        return string("int");
    }
}
