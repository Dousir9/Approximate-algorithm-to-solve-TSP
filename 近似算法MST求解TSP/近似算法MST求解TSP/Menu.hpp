//
//  Menu.hpp
//  近似算法MST求解TSP
//
//  Created by Dousir9 on 2020/6/10.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include "Graph.hpp"
#include "InitGraph.hpp"
#include <unistd.h>

class Menu {
public:
    Menu();
    void ShowMenuHead();
    void ShowMenuInfo();
    void ShowMenuBottom();
    void ShowError();
    char Input();
    void MenuRun();
    void InitNewGraph();
    void TSP();
};

#endif /* Menu_hpp */
