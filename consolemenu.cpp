//
// Created by HP User on 11/5/2018.
//

#include "consolemenu.hpp"
#include <limits>
#include <sstream>

bool ConsoleMenu::addOption(int code, pair<string, function<bool()>> option){
    auto itr = options.find(code);
    if(itr != options.end()){
        cerr << "Trying to add a menu option to code " << code << ", but code is already taken." << endl;
        return false;
    }
    auto menuOption = pair <int, pair<string, function<bool()>>> (code, option);
    options.insert(menuOption);
    return true;
}

void ConsoleMenu::start(){
    int menuOption = 0;
    int count = 0;
    int maxCount = 10;
    bool cont = true;
    do{
        if(count == 0){
            for(pick = options.begin(); pick != options.end(); pick++){
                output << (pick->first) << " - " << (pick->second.first) << endl;
            }
        }
        string s;
        getline(input, s);
        stringstream ss;
        ss << s;
        ss >> menuOption;
        if(ss.fail()) {
            output << "Invalid input." << endl;
            count = (count + 1) % maxCount;
        }
        else {
            pick = options.find(menuOption);
            if(pick != options.end()) {
                count = 0;
                cont = (pick->second.second)();
            }
            else{
                output << "Invalid option." << endl;
                count = (count + 1) % maxCount;
            }
        }
    }while(cont);
}
