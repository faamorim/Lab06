//
// Created by HP User on 11/3/2018.
//

#ifndef LAB06_TRIMSTR_HPP
#define LAB06_TRIMSTR_HPP
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;

string trimLeft(string str){
    while(isspace(str.at(0))){
        str = str.substr(1);
    }
    return str;
}

string trimRight(string str){
    while(isspace(str.at(str.length()-1))){
        str = str.substr(0, str.length()-1);
    }
    return str;
}

string trim(string str){
    str = trimLeft(str);
    str = trimRight(str);
    return str;
}


string formatString(string fmt, const map<char, string>& codes, const string& leftMargin = ""){
    bool carryIndent = true;
    stringstream str;
    unsigned long long int pos;
    while((pos = fmt.find('%')) != -1 && fmt.length() > 1){
        char curChar = fmt.at(pos+1);
        if(carryIndent && curChar != 't') {
            str << leftMargin;
            carryIndent = false;
        }
        str << fmt.substr(0,pos);
        switch (curChar){
            case 'n':
                str << endl;
                carryIndent = true;
                break;
            case 't':
                str << '\t';
                break;
            default:
                auto code = codes.find(curChar);
                if(code == codes.end())
                    str << curChar;
                else
                    str << code->second;
                break;
        }
        fmt = fmt.substr(pos+2, fmt.length() - (pos+2));
    }
    if(carryIndent)
        str << leftMargin;
    str << fmt;
    return str.str();
}

string formatHeader(const string& fmt, const string& header, const string& leftMargin = ""){
    map<char, string> fmtHdrCodes;
    fmtHdrCodes.insert(pair<char, string>('h', header));
    return formatString(fmt, fmtHdrCodes, leftMargin);
}

string formatWordAndDef(string fmt, const string& word, const string& def, int wordWidth = 0, const string& leftMargin = ""){
    map<char, string> fmtWrdAndDefCodes;
    stringstream wrdstream;
    wrdstream << setw(wordWidth) << std::left << word;
    fmtWrdAndDefCodes.insert(pair<char, string>('w', wrdstream.str()));
    fmtWrdAndDefCodes.insert(pair<char, string>('d', def));
    return formatString(fmt, fmtWrdAndDefCodes, leftMargin);
}



string getMarginString(int marginSize){
    stringstream str;
    int i{marginSize};
    while(i-- > 0){
        str << " ";
    }
    return str.str();
}

#endif //LAB06_TRIMSTR_HPP
