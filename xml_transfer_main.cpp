#include <iostream>
#include <cstdio>
#include <string>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <vector>

using namespace std;
using namespace boost;

int main() {
    string filename = "text.xml"; //enter your input file
    fstream fin;
    fin.open(filename.c_str(), ios::in);

    vector<string> v;
    string tmp;

    while (getline(fin, tmp)) {
        v.push_back(tmp);
    }

    vector<string> strs;

    for (vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
        string s = *i;
        if (s.find("word") != std::string::npos) {
            strs.push_back(s);
        }
    }

    fstream out;
    out.open("text.txt", ios::out); //enter your output file

    for (vector<string>::const_iterator i = strs.begin(); i != strs.end(); ++i) {
        string s = *i;
        char_separator<char> sep(" ");
        tokenizer<char_separator<char>> tok(s, sep);
        for (tokenizer<char_separator<char>>::iterator j = tok.begin(); j != tok.end(); ++j) {
            string s = *j;
            if (s.find("cont") != std::string::npos) {
                for (int i = 0; i < 6; i++) {
                    s.erase(s.begin());
                }
                s.erase(s.end() - 1);
                s.push_back('/');
                out << s.c_str();
            }
            if (s.find("pos") != std::string::npos) {
                for (int i = 0; i < 5; i++) {
                    s.erase(s.begin());
                }
                s.erase(s.end() - 1);
                s.push_back('#');
                out << s.c_str();
            }
            if (s.find("ne") != std::string::npos) {
                for (int i = 0; i < 4; i++) {
                    s.erase(s.begin());
                }
                s.erase(s.end() - 1);
                s.push_back(' ');
                out << s.c_str();
            }
        }
    }
    out.close();
    return 0;
}