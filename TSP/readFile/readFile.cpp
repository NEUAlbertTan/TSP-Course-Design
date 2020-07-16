//
// Created by 66919 on 2020/7/15.
//

#include "readFile.h"


/*函数说明：
 * 参数列表：
 *      filePath：文件路径
 * 函数返回值
 *      文件包含的数据类型
 */
std::string getType(const std::string &filePath){
    std::ifstream inFile(filePath);
    if( !inFile.is_open() ){
        std::cerr<<"failed to open the source file!"<<std::endl;
        exit(0);
    }
    std::string str;
    for(int i=0; i<7; i++){
        getline( inFile,str );
    }
    if( str.find('.') != str.npos ){
        // if find a dot in data
        inFile.close();
        return std::string("double");
    } else {
        inFile.close();
        return std::string("int");
    }
}
