//
//  InitGraph.cpp
//  近似算法MST求解TSP
//
//  Created by Dousir9 on 2020/5/26.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "InitGraph.hpp"

InitGraph::InitGraph(int size) { //建图类的构造函数
    N = size; //图中点的数量
    MAX = size * 5; //点的边界是点的数量的5倍
    if (N <= 1) { //如果点的数量小于的等于1
        N = 2; //将点的数量修改为2
        MAX = N * 5; //点的边界是点的数量的5倍
    }
    srand((unsigned int) time(0)); //设计随机种子为当前时间
}

void InitGraph::init() { //为类的成员变量分配内存空间和建图的成员函数
    p = vector<pair<int, int>>(N); //对存放点的坐标的数组分配空间
    h = map<pair<int, int>, bool>(); //对为防止点重复的map分配空间
    g = vector<vector<double>> (MAX + 1, vector<double>(MAX + 1)); //为邻接矩阵分配空间
    init_graph(); //调用类的成员函数init_graph()
}

void InitGraph::save_graph() { //保存图信息至文件的成员函数
    ofstream in_file; //定义流对象in_file
    in_file.open(FILE); //流对象打开文件
    in_file << N << '\n'; //将点的数量从内存读入文件
    for (int i = 0; i < N; i++) { //枚举边的第一个点
        for (int j = i + 1; j < N; j++) { //枚举边的第二个点
            in_file << i + 1 << " " << j + 1 << " " << fixed << setprecision(4) <<  g[i][j] << '\n'; //将两个点和两个点的距离写入文件
        }
    }
    in_file.close(); //关闭文件
}

void InitGraph::init_point() { //建立点的成员函数
    for (int i = 0; i < N; i++) { //共有N个点
        int x, y; //点的坐标
        do {
            x = rand() % MAX + 1; //x坐标随机为1~MAX的某个数
            y = rand() % MAX + 1; //y坐标随机为1~MAX的某个数
        } while (h[{x, y}]); //用map查重，查看这个点坐标是否存在
        p[i] = {x, y}; //确定点p的x坐标和y坐标
        h[p[i]] = 1; //标记p的坐标已经存在
    }
}

void InitGraph::init_graph() { //建立图的成员函数
    init_point(); //调动类的成员函数init_point()
    auto distance = [&] (int x1, int y1, int x2, int y2) { //求两点间距离的函数
        int a = x1 - x2; //横坐标差
        int b = y1 - y2; //纵坐标差
        return sqrt(a * a + b * b); //返回两点距离
    };
    for (int i = 0; i < N; i++) { //一共n个点
        int x = p[i].first; //这个点的横坐标
        int y = p[i].second; //这个点的纵坐标
        for (int j = i + 1; j < N; j++) { //枚举另一个店，已经计算过的点不重复计算
            if (i != j) { //如果另一个点不是本身
                int u = p[j].first; //获取另一个点的横坐标
                int v = p[j].second; //获取另一个点的纵坐标
                g[i][j] = g[j][i] = distance(x, y, u, v); //计算两点间的l距离
            }
        }
    }
}

void InitGraph::Puts() {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cout << "(u, v, w):      (" << i + 1 << ", " << j + 1 << ", " << fixed << setprecision(1) << g[i][j] << ")\n";
        }
    }
}

void InitGraph::input() {
    g = vector<vector<double>> (MAX + 1, vector<double>(MAX + 1)); //为邻接矩阵分配空间
    cout << "\n\n                                                 请输入" << N * (N - 1) / 2 << "条边:" << '\n';
    int u, v;
    double w;
    for (int i = 1, size = N * (N - 1) / 2; i <= size; i++) {
        cout << "请输入第" << i << "条边，(u, v, w)，以空格隔开: ";
        cin >> u >> v >> w;
        g[u][v] = g[v][u] = w;
    }
}
