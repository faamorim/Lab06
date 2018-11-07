//
// Created by HP User on 11/5/2018.
//

#include "dictionarymenu.hpp"



DictionaryMenu::DictionaryMenu(Dictionary& dict, istream& in, ostream& out) : ConsoleMenu(in, out), dict(dict){};

bool DictionaryMenu::printDictionary() const{
    dict.printAll(output);
    return true;
}

bool DictionaryMenu::findWordDefinition() const{
    output << "Enter a word to find the definition: " << endl;
    string word;
    if(word.empty()){
        output << "Going back to main menu." << endl;
        return true;
    }
    getline(input, word);
    string def{dict.getDefinition(word)};
    if (def.empty()){
        output << "No definition found for word: " << word << "." << endl;
    }
    else {
        output << def << endl;
    }
    return true;
}

bool DictionaryMenu::addWordDefinition() {
    string word;
    string def;
    do {
        cout << "Enter new word: " << endl;
        getline(input, word);
        word = prepareWordForDictionary(word);
        if(word.empty()) {
            output << "Going back to main menu." << endl;
            return true;
        }
        else {
            def = dict.getDefinition(word);
            if (!def.empty()) {
                output << "Word \"" << word << "\" already have a definition in the dictionary." << endl;
            }
        }
    }while(!def.empty() || word.empty());
    do {
        output << "Enter definition to word \"" << word << "\":" << endl;
        getline(input, def);
        def = trim(def);
        if(def.empty()){
            output << "Invalid definition to be added to the dictionary." << endl;
        }
    }while(def.empty());
    dict.add(word, def);
    output << "Word added to dictionary:" << endl;
    output << dict.getDefinition(word) << endl;
    return true;
}


bool DictionaryMenu::exitMenu() const{
    dict.save();
    return false;
}