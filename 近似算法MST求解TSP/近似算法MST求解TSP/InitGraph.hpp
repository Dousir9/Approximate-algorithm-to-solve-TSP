//
//  InitGraph.hpp
//  近似算法MST求解TSP
//
//  Created by Dousir9 on 2020/5/26.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef InitGraph_hpp
#define InitGraph_hpp

#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

class InitGraph { //建图类
public:
    InitGraph() {cout << "fdsfd";}; //默认构造函数
    InitGraph(int size = 100); //构造函数，size为图的大小，默认为100
    void init(); //初始化，为类的成员变量分配内存空间和建图的成员函数
    void save_graph(); //保存图信息至文件的成员函数
    void input(); //输入数据建图
    void Puts(); //输出图的信息
private:
    void init_point(); //建立点的成员函数
    void init_graph(); //建立图的成员函数
    int N; //点的数量
    int MAX; //坐标上界
    const int INF = 0x3f3f3f3f; //最大值
    const string FILE = "/Users/xumingfei/Desktop/项目/近似算法MST求解TSP/SQL/graph.txt"; //文件地址
    vector<pair<int, int>> p; //点的坐标
    map<pair<int, int>, bool> h; //防止重复点
    vector<vector<double>> g; //通过点的坐标得到的邻接矩阵
};

#endif /* InitGraph_hpp */
