#include <iostream>
#include "dictionary.cpp"
#include "consolemenu.cpp"

using namespace std;
void findWordDefinition(const Dictionary& dict);
void addWordDefinition(Dictionary& dict);

int main() {
    Dictionary dict("dictionary.txt");
    map<int, pair<string, function<void()>>> options;
    pair<string, function<void()>> printDict{"PrintDictionary", bind(&Dictionary::printAll, &dict)};
    pair<string, function<void()>> findWord{"Find word definition", bind(&findWordDefinition, dict)};
    pair<string, function<void()>> enterWord("Enter new word and definition", bind(&addWordDefinition, dict));

    cout << dict;
    return 0;
}

void findWordDefinition(const Dictionary& dict){
    string word;
    getline(cin, word);
    string def{dict.getDefinition(word)};
    if (def == ""){
        cout << "No definition found for word: " << word << "." << endl;
    }
    else {
        cout << def;
    }
}

void addWordDefinition(Dictionary& dict){
    string word;
    getline(cin, word);
    string def(dict.getDefinition(word));
    if (def == ""){

    }
}