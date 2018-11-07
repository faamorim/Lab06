//
// Created by HP User on 11/5/2018.
//

#ifndef LAB06_DICTIONARYMENU_HPP
#define LAB06_DICTIONARYMENU_HPP
#include "consolemenu.cpp"
#include "stringhelper.hpp"


class DictionaryMenu : public ConsoleMenu{
private:
    Dictionary& dict;
public:
    explicit DictionaryMenu(Dictionary& dict, istream& in, ostream& out) ;
    bool printDictionary() const;
    bool findWordDefinition() const;
    bool addWordDefinition();
    bool exitMenu() const;
};


#endif //LAB06_DICTIONARYMENU_HPP
