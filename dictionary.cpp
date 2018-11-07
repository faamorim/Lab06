//
// Created by HP User on 11/2/2018.
//

#include <sstream>
#include <iomanip>
#include <limits>
#include "dictionary.hpp"
#include "stringhelper.hpp"
int createCount = 0;
void Dictionary::printFileState(string s1, bool printfile, string s2) const {
    if(!printFileStates)
        return;
    cout << s1;
    if(printfile)
        cout << " (" << fileName << ")";
    if(s2.length() > 0)
        cout << " " << s2;
    cout << endl;
}
Dictionary::Dictionary(string filename, bool print) : fileName(std::move(filename)), printFileStates(print){
    setMargin(4);
    load();
}

bool Dictionary::load(){
    printFileState("Opening file to load.");
    ifstream file = ifstream(fileName, ios_base::in);
    if(!file.is_open()) {
        printFileState("Unable to open file to load.");
        return false;
    }
    else {
        printFileState("Opened file to load.");
        while(add(file));
        printFileState("Closing file after load.");
        file.close();
        if(file.is_open()) {
            printFileState("Unable to close file after load.");
            return false;
        }
        else {
            printFileState("Closed file after load.");
        }
    }
    return true;
}

Dictionary::~Dictionary(){
    //save();
}

bool Dictionary::save() const {
    map<string, string>::const_iterator itr;
    printFileState("Opening file to save.");
    ofstream file = ofstream(fileName, ios_base::out | ios_base::trunc);
    if(!file.is_open()) {
        printFileState("Unable to open file to save.");
        return false;
    }
    else {
        printFileState("Opened file to save.");
        for (itr = dict.begin(); itr != dict.end(); ++itr)
        {
            file  <<  itr->first <<  wordDefFileSeparator << itr->second << '\n';
        }
        printFileState("Closing file after save.");
        file.close();
        if(file.is_open()) {
            printFileState("Unable to close file after save.");
            return false;
        }
        else {
            printFileState("Closed file after save.");
        }
    }
    return true;
}

bool Dictionary::add(istream& stream){
    string curLine;
    string curWord;
    string curDef;
    unsigned long long int sepIndex;
    unsigned long long int defIndex;
    stringstream newlinestr;
    newlinestr<<endl;
    bool newline = wordDefFileSeparator == "\n" || wordDefFileSeparator == newlinestr.str();
    if(getline(stream, curLine)){
        curWord = "";
        curDef = "";
        if(newline){
            curWord = curLine;
            if(!getline(stream, curDef)){
                return false;
            }
        }
        else {
            sepIndex = curLine.find(wordDefFileSeparator);
            defIndex = sepIndex + wordDefFileSeparator.length();
            if (sepIndex > 0) {
                curWord = curLine.substr(0, sepIndex);
                curDef = curLine.substr(defIndex, curLine.length() - (defIndex));
            }
            else{
                return false;
            }
        }
        add(curWord, curDef);
        return true;
    }
    return false;
}
bool Dictionary::add(string wrd, string def) {
    string curWord = prepareWordForDictionary(move(wrd));
    string curDef = trim(move(def));
    if(curWord.length() == 0 || curDef.length() == 0){
        return false;
    }
    dict.insert(pair <string, string> (curWord, curDef));
    int wordLength = (int)min(curWord.length(), (unsigned long long int)(std::numeric_limits<int>::max()));
    largestWordLength = wordLength > largestWordLength ? wordLength : largestWordLength;
    return true;
}

void Dictionary::setMargin(int size){
    leftMargin = getMarginString(size);
}

void Dictionary::printAll(ostream& output) const{
    output << (*this);
}

string Dictionary::getDefinition(string word) const{
    word = prepareWordForDictionary(word);
    auto itr = dict.find(word);
    if(itr == dict.end() || itr->second.empty()){
        return "";
    }
    return getWordDisplay(itr->first, itr->second);
}


ostream& operator<<(ostream& os, const Dictionary& dictionary) {
    map<string, string>::const_iterator itr;
    char curHeader = '\0';
    for (itr = dictionary.dict.begin(); itr != dictionary.dict.end(); ++itr)
    {
        if(dictionary.printHeaders && itr->first.at(0) != curHeader){
            curHeader = itr->first.at(0);
            os << formatHeader(dictionary.headerDisplayFmt, string(1,toupper(curHeader)), dictionary.leftMargin) << endl;
        }
        os <<  dictionary.getWordDisplay(itr->first, itr->second) << endl;
    }
    return os;
}

string Dictionary::getWordDisplay(const string& wrd, const string& def) const {
    return getWordDisplay(wrd, def, fixedWordWidth, leftMargin);
}

string Dictionary::getWordDisplay(const string& wrd, const string& def, bool fixedWordWidth, const string& leftMargin) const {
    int wordWidth = fixedWordWidth ? largestWordLength : 0;
    stringstream str;
    str << formatWordAndDef(wordDefDisplayFmt, wrd, def, wordWidth, leftMargin);
    return str.str();
}


string prepareWordForDictionary(const string& word){
    return toLower(trim(word));
}