//
//  Menu.cpp
//  近似算法MST求解TSP
//
//  Created by Dousir9 on 2020/6/10.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Menu.hpp"
#define di(s) cout << "                                         " << s << "算法运行时间为";
#define rt(s, e) cout << "\n                                           Running time is: " << static_cast<double>(e - s) / CLOCKS_PER_SEC * 1000 << "ms" << '\n' << '\n';//输出运行时间为毫秒

//清空缓存区
void MY_FLUSH() {
    char ch;
    while(~(ch = getchar()) && ch != '\n');
}
//按任意键返回
void MY_PAUSE() {
    MY_FLUSH();
    cout <<endl<< "                                                 按任意键返回..." << endl;
    getchar();
}

void CLEAR() {
    system("clear");
}

void SLEEP() {
    usleep(40000);
}

void SMALL_SLEEP() {
    usleep(1000000);
}

void BIG_SLEEP() {
    usleep(1500000);
}

//界面优化：
const string HEAD = "\n            ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★  满足三角不等式的TSP问题的近似算法  ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★\n\n";
const string BLANK = "                   ";
const string LEFT_BLANK = "                             ";
const string RIGHT_BLANK = "                                                                        ";
const string SMALL_BLANK = "                         ";
const string NEXT_BLANK = "\n\n                                          ";
const string TOP = "╔════════════════════════════════════════════════════════════════════════╗\n";
const string BOT = "╚════════════════════════════════════════════════════════════════════════╝\n";

//默认构造函数(基类及其派生类)
Menu::Menu() {}

//输出菜单头部
void Menu::ShowMenuHead() {
    CLEAR();
    cout << HEAD;
}

//输出菜单底部
void Menu::ShowMenuBottom() {
    cout << BLANK << BOT << '\n' << '\n';
    cout << "                                                       ";
}
//输出错误信息
void Menu::ShowError() {
    CLEAR();
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                         ");
    printf("     无效的输入，请重新输入\n");
    BIG_SLEEP();
}

//接收指令，只接收第一个字母
char Menu::Input() {
    string ch;
    cin >> ch;
    MY_FLUSH();
    if (ch.size() > 1) {
        return -1;
    }
    return ch[0];
}


//输出菜单信息 (主菜单)
void Menu::ShowMenuInfo() {
    cout << BLANK << TOP; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "①  建立新的图     " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "②  求解旅行商问题 " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << LEFT_BLANK << "③  退出           " << SMALL_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
    cout << BLANK << "║" << RIGHT_BLANK << "║" << '\n'; SLEEP();
}

//主菜单运行
void Menu::MenuRun() {
    ShowMenuHead();
    ShowMenuInfo();
    ShowMenuBottom();
    char ch = Input();
    switch (ch) {
        case '1': //初始化新的满足三角形不等式的图
            InitNewGraph();
            MY_PAUSE();
            MenuRun();
            break;
        case '2': //求解TSP问题
            TSP();
            MY_PAUSE();
            MenuRun();
            break;
        case '3': //退出
            exit(0);
        default: //应对异常输入
            ShowError();
            MenuRun();
    }
}

void Menu::InitNewGraph() {
    ShowMenuHead();
    cout << "\n\n                                   请输入您要创建满足三角形不等式的图规模：";
    int size;
    cin >> size;
    cout << "\n\n                                                 请选择建图方式:" << '\n';
    cout << "\n\n                                                   1.输入数据" << '\n';
    cout << "\n\n                                                   2.自动建图" << '\n';
    string s;
    cin >> s;
    if (s == "1") {
        InitGraph M(size);
        M.input();
        M.save_graph();
    } else if (s == "2") {
        InitGraph M(size);
        M.init();
        M.save_graph();
        M.Puts();
        cout << "\n                                     成功创建规模为" << size << "的图，" << "已保存至文件中" << '\n';
    } else {
        cout << "\n\n                                                   输入有误" << '\n';
    }
}

void Menu::TSP() {
    ShowMenuHead();
    Graph G;
    G.init_graph();
    clock_t s, e;
    s = clock();
    cout << "最小生成树MST算法:";
    G.kruskal();
    G.get_tsp();
    e = clock();
    di("最小生成树MST算法");
    rt(s, e);
    cout << '\n';
    if (G.n <= 15) {
        s = clock();
        cout << "状态压缩动态规划:";
        G.TSP();
        e = clock();
        di("状态压缩动态规划");
        rt(s, e);
        
        s = clock();
        cout << "最小对集MM算法:";
        G.MM();
        G.get_tsp();
        e = clock();
        di("最小对集MM算法");
        rt(s, e);
    }
}
