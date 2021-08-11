//
//  Graph.cpp
//  近似算法MST求解TSP
//
//  Created by Dousir9 on 2020/5/29.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Graph.hpp"

void Graph::init_graph() { //读取文件建图的成员函数
    ifstream out_file; //定义从硬盘到内存的流
    out_file.open(FILE); //打开保存图的文件
    out_file >> n; //首先读入n的大小
    e = vector<edge>(n * (n - 1) / 2); //为存储边的数组分配空间
    g = vector<vector<double>>(n + 1, vector<double>(n + 1)); //为邻接矩阵分配空间
    m = vector<vector<double>>(n + 1, vector<double>(n + 1)); //为存放最小生成树的邻接矩阵分配空间
    for (int i = 0, size = n * (n - 1) / 2; i < size; i++) { //一共有n(n - 1)/2条边
        out_file >> e[i].u >> e[i].v >> e[i].w; //依次读入两个点和两点直接的距离
    }
    out_file.close(); //关闭文件
}

void Graph::init_set() { //建立并查集
    s = vector<int>(n + 1); //为并查集分配空间
    for (int i = 1; i <= n; i++) //共n个点
        s[i] = i; //初始化并查集
}

int Graph::find(int x) { //寻找x在哪个祖先的集中
    if (s[x] == x) //若找到这个集的祖先
        return x; //返回集的祖先
    s[x] = find(s[x]); //更新继续寻找s[x]的祖先
    return s[x]; //返回集的祖先
}

void Graph::kruskal() { //克鲁斯卡尔算法求最小生成树
    sort(e.begin(), e.end()); //对边的大小进行排序
    init_set(); //调用成员函数init_set()初始化并查集
    for (int i = 0, size = n * (n - 1) / 2; i < size; i++) { //共n(n - 1)/2条边
        int a = e[i].u, b = e[i].v; //边的两个点
        g[a][b] = g[b][a] = e[i].w; //将这个边加入到邻接矩阵中
        int x = find(a); //寻找a所在集的祖先x
        int y = find(b); //寻找b所在集的祖先y
        if (x == y) { //a和b的祖先相同
            continue; //进入下次循环
        } else {
            s[y] = x; //将b的所在集的祖先的祖先改为a的祖先
            m[a][b] = m[b][a] = e[i].w; //将这条边加入到最小生成树中
        }
    }
}

void Graph::dfs(int u) { //深度优先搜索
    vis[u] = 1; //标记u已经被访问过
    path.push_back(u); //将u加入到路径中
    for (int v = 1; v <= n; v++) { //遍历u连接的点v
        if (!vis[v] && m[u][v] != 0) { //如果v没被访问过并且u、v之间存在边(u、v之间距离不为0)
            dfs(v); //继续从v点开始深度优先搜索
        }
    }
}

void Graph::get_tsp() { //获取TSP回路
    path.clear();
    vis = vector<int>(n + 1, 0);
    dfs(1);
    double res = 0;
    for (int i = 1; i < n; i++) {
        res += g[path[i - 1]][path[i]];
    }
    res += g[path[n - 1]][path[0]];
    cout << "\nTPS长度为: " << fixed << setprecision(1) << res << '\n';
    cout << "路径为:" << '\n';
    for (int i = 0; i < n; i++) {
        cout << path[i] << "->";
    }
    cout << path[0] << '\n';
}

//状态压缩动态规划求解TSP
void Graph::TSP() {
    if (n > 15)
        return;
    int count = n;
    vector<vector<double>> mm = vector<vector<double>>(count, vector<double>(count));
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            mm[i][j] = g[i + 1][j + 1];
        }
    }
    const int maxn = count;
    vector<vector<double>> dp = vector<vector<double>>(1 << maxn, vector<double>(count));
    vector<vector<int>> front = vector<vector<int>>(1 << maxn, vector<int>(count));
//    double dp[1 << maxn][maxn];
//    int front[1 << maxn][maxn];
    for (int i = 0, size = 1 << maxn; i < size; i++) {
        for (int j = 0; j < maxn; j++) {
            dp[i][j] = 10000.0;
            front[i][j] = -1;
        }
    }
    //memset(dp, 0x3f, sizeof(dp));
    //memset(front, -1, sizeof(front));
    int st = 0;
    dp[(1 << maxn) - 1][st] = 0;
    for (int s = (1 << maxn) - 2; s >= 0; s--) {
        for (int i = 0; i < maxn; i++) {
            if ((s >> i & 1) || s == 0)
                for (int j = 0; j < maxn; j++) {
                    if (!(s >> j & 1)) {
                        if (dp[s][i] > dp[s | 1 << j][j] + mm[i][j]) {
                            dp[s][i] = dp[s | 1 << j][j] + mm[i][j];
                            front[s][i] = j;
                        }
                    }
                }
        }
    }
    vector<int> tsp_path;
    tsp_path.push_back(st);
    for (int i = 0, s = 0, now = st; ; i++) {
        now = front[s][now];
        if (now == -1)
            break;
        tsp_path.push_back(now);
        s = s | 1 << now;
    }
    cout << "\nTPS长度为: " << fixed << setprecision(1) << dp[0][st] << '\n';
    cout << "路径为:" << '\n';
    for (int i = 0; i < tsp_path.size(); i++) {
        cout << tsp_path[i] + 1;
        if (i == tsp_path.size() - 1) {
            cout << '\n';
        } else {
            cout << "->";
        }
    }
}

//最小对集MM算法
void Graph::MM() {
    vector<int> deg(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (m[i][j]) {
                deg[i]++;
                deg[j]++;
            }
        }
    }
    vector<int> p;
    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2 == 1) {
            p.push_back(i);
        }
    }
    int tot = (int) p.size();
    double f[1 << tot];
    f[0] = 0;
    int All = 1 << tot;
    for (int i = 1; i < All; i++)
        f[i] = (double) 2e9;
    vector<pair<int, int>> pre(1 << tot);
    for (int s = 0; s < All; s++) {
        int i = 0;
        while ((1 << i) & s)
            i++;
        for (int j = i + 1; j < tot; j++) {
            if (!((1 << j) & s)) {
                if (f[s | (1 << i) | (1 << j)] > f[s] + g[p[i]][p[j]]) {
                    f[s | (1 << i) | (1 << j)] = f[s] + g[p[i]][p[j]];
                    pre[s | (1 << i) | (1 << j)].first = i;
                    pre[s | (1 << i) | (1 << j)].second = j;
                }
            }
        }
    }
    int s = All - 1;
    while (s > 0) {
        int a = p[pre[s].first], b = p[pre[s].second];
        m[a][b] = m[b][a] = g[a][b];
        int x = 1 << pre[s].first, y = 1 << pre[s].second;
        s -= x;
        s -= y;
    }
}
