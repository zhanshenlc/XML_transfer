#include <iostream>
#include <cstdio>
#include <string>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <vector>

using namespace std;
using namespace boost;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Wrong number of inputs" << endl;
    }
    string inpref = argv[1];
    string outpref = argv[2];

    string filename = inpref + ".xml"; // *.xml file as default
    fstream fin;
    fin.open(filename.c_str(), ios::in);

    fstream out;
    out.open(outpref + ".txt", ios::out);

    vector<string> v;
    string tmp;
    bool inPara = false;

    while (getline(fin, tmp)) {
        if (tmp.find("sent id=") != std::string::npos) {
            inPara = true;
        } else if (tmp.find("</sent>") != std::string::npos) {
            inPara = false;
            out << "\r\n";
        } else if (inPara) {
            char_separator<char> sep(" ");
            tokenizer<char_separator<char>> tok(tmp, sep);
            for (tokenizer<char_separator<char>>::iterator beg = tok.begin(); beg != tok.end(); beg ++) {
                string s = *beg;
                if (s.find("cont") != std::string::npos) {
                    for (int i = 0; i < 6; i ++) {
                        s.erase(s.begin());
                    }
                    s.erase(s.end() - 1);
                    s.push_back('/');
                    out << s.c_str();
                }
                if (s.find("pos") != std::string::npos) {
                    for (int i = 0; i < 5; i ++) {
                        s.erase(s.begin());
                    }
                    s.erase(s.end() - 1);
                    s.push_back('#');
                    out << s.c_str();
                }
                if (s.find("ne") != std::string::npos) {
                    for (int i = 0; i < 4; i ++) {
                        s.erase(s.begin());
                    }
                    s.erase(s.end() - 1);
                    s.push_back(' ');
                    out << s.c_str();
                }
            }
        }
    }
    out.close();
    return 0;
}
