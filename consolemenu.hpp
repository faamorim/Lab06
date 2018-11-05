//
// Created by HP User on 11/5/2018.
//

#ifndef LAB06_MENU_HPP
#define LAB06_MENU_HPP
#include "dictionary.hpp"
#include <functional>

class Menu{
private:
    map<int, pair<string, function<void()>>> options;
public:
    Menu(){}

};

#endif //LAB06_MENU_HPP
