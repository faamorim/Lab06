//
// Created by HP User on 11/2/2018.
//

#ifndef LAB06_DICTIONARY_HPP
#define LAB06_DICTIONARY_HPP
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

class Dictionary {
private:
    bool printFileStates;
    string const wordDefFileSeparator = "-><-";
    string wordDefDisplayFmt = "%w - %d";
    string headerDisplayFmt = "----- %h -----";
    string fileName;
    map<string, string> dict;
    int largestWordLength = 0;
    bool printHeaders = true;
    string leftMargin;
    bool fixedWordWidth = false;
    string getWordDisplay(const string& wrd, const string& def) const;
    string getWordDisplay(const string& wrd, const string& def, bool fixedWordWidth, const string& leftMargin) const;
public:
    void setMargin(int size);
    explicit Dictionary(string filename, bool print = false);
    bool load();
    bool save() const;
    ~Dictionary();
    bool add(istream& stream);
    bool add(string wrd, string def);
    void printFileState(string s1, bool printfile = false, string s2 = "") const;
    friend ostream& operator<<(ostream& os, const Dictionary& mat);
    void printAll(ostream& output = cout) const;
    string getDefinition(string word) const;
};

string prepareWordForDictionary(const string& word);

#endif //LAB06_DICTIONARY_HPP
