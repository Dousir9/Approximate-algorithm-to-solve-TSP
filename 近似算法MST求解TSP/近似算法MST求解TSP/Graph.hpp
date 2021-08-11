//
//  Graph.hpp
//  近似算法MST求解TSP
//
//  Created by Dousir9 on 2020/5/29.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

struct edge { //表示边的结构体
    int u; //边的端点
    int v; //边的端点
    double w; //边的
    bool operator < (const edge &other) const { //结构体的比较标准
        return w < other.w; //权值小的在前面
    }
};

class Graph { //图类
public:
    void init_graph(); //初始化图
    void kruskal(); //Kruskal算法
    void get_tsp(); //MST算法
    void TSP(); //状态压缩动态规划求解TSP
    void MM(); //MM算法
    int n; //点的个数
private:
    void init_set(); //初始化并查集
    int find(int x); //寻找祖先
    void dfs(int u); //dfs深度优先搜索抄近路
    const string FILE = "/Users/xumingfei/Desktop/项目/近似算法MST求解TSP/SQL/graph.txt"; //文件地址
    vector<edge> e; //边
    vector<vector<double>> g; //用于计算距离的邻接矩阵
    vector<vector<double>> m; //存储最小生成树的邻接矩阵
    vector<int> s; //并查集
    vector<int> path; //TSP路径
    vector<int> vis; //点是否被访问过
};

#endif /* Graph_hpp */
