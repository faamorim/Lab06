//
// Created by HP User on 11/5/2018.
//

#ifndef LAB06_MENU_HPP
#define LAB06_MENU_HPP
#include "dictionary.hpp"
#include <functional>

class ConsoleMenu{
private:
    map<int, pair<string, function<bool()>>> options;
    map<int, pair<string, function<bool()>>>::iterator pick;
protected:
    istream& input = cin;
    ostream& output = cout;
public:
    ConsoleMenu(istream& in, ostream& out) : input(in), output(out) {};
    void start();
    bool addOption(int code, pair<string, function<bool()>> option);
};

#endif //LAB06_MENU_HPP
