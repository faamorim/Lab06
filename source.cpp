#include <iostream>
#include "dictionary.cpp"
#include "dictionarymenu.cpp"

using namespace std;

void setupMenu(DictionaryMenu& dict);

int main() {
    Dictionary dict("dictionary.txt");
    DictionaryMenu dictmenu{dict, cin, cout};
    dict.add("b", "b");
    setupMenu(dictmenu);
    dictmenu.start();
    return 0;
}

void setupMenu(DictionaryMenu& dictmenu){
    map<int, pair<string, function<void()>>> options;
    pair<string, function<bool()>> printDict{"PrintDictionary", bind(&DictionaryMenu::printDictionary, cref(dictmenu))};
    pair<string, function<bool()>> findWord{"Find word definition", bind(&DictionaryMenu::findWordDefinition, cref(dictmenu))};
    pair<string, function<bool()>> enterWord("Enter new word and definition", bind(&DictionaryMenu::addWordDefinition, ref(dictmenu)));
    pair<string, function<bool()>> exit("Exit", bind(&DictionaryMenu::exitMenu, cref(dictmenu)));
    dictmenu.addOption(1, printDict);
    dictmenu.addOption(2, findWord);
    dictmenu.addOption(3, enterWord);
    dictmenu.addOption(4, exit);
}