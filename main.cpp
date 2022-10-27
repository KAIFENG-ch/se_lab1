#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

std::vector<std::string> keywords = {"auto", "break", "case", "char", "const", "continue",
                                     "default", "do", "double", "else", "enum", "extern", "float",
                                     "for", "foto", "if", "int", "main", "long", "main", "register", "return", "short",
                                     "signed", "sizeof", "static", "struct", "switch", "typeof", "union",
                                     "unsigned", "void", "volatile", "while"};

typedef struct if_struct {
    int else_if_num, else_num, if_pos;
} if_struct;


int main() {
    int ans = 0, sc = 0, else_num = 0, elseifnum = 0;
    int level;
    std::cout << "Please enter level:";
    std::cin >> level;
    std::string filepath;
    std::cout << "Please enter file path:";
    std::cin >> filepath;
    std::string file_path = filepath, word;
    std::ifstream fin;
    fin.open(file_path);
    if (!fin) {
        std::cerr << "Could not open file!" << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(fin, line)) {
        int i = 0, j = 0;
        int n = (int)line.size();
        while (i < n && j < n) {
            if (line[j] < 'a' || line[j] > 'z') {
                std::string s = line.substr(i, j-i);

                for (std::string &w : keywords) {
                    if (s == w) {
                        ans++;
                        break;
                    }
                }
                i = j + 1;
            }
            j++;
        }
    }
    std::fstream fin1;
    fin1.open(file_path);
    if (!fin1) {
        std::cerr << "Could not open file!" << std::endl;
        exit(1);
    }
    std::string swline;
    std::vector<int> cs;
    while (std::getline(fin1, swline)) {
        for (int i = 0; i < swline.size(); i++) {
            if (swline.substr(i, 6) == "switch") {
                sc++;
                int num = 0;
                while (std::getline(fin1, swline)) {
                    for (int j = 0; j < swline.size(); j++) {
                        if (swline.substr(j, 4) == "case") num++;
                    }
                    if (swline[swline.size()-1] == '}') {
                        cs.emplace_back(num);
                        break;
                    }
                }
            }
        }
    }
    std::fstream fin2;
    fin2.open(file_path);
    if (!fin2) {
        std::cerr << "Could not open file!" << std::endl;
        exit(1);
    }
    std::string buf;
    std::stack<if_struct> stk;
    while (std::getline(fin2, buf)) {
        for (int i = 0; i < buf.size(); i++) {
            if (buf.substr(i, 2) == "if" && buf[i-2] != 'e') {
                if (stk.empty() || i != stk.top().if_pos) {
                    if_struct p = {0, 0, i};
                    stk.push(p);
                }
            }
            if (!stk.empty() && buf.substr(i, 7) == "else if") stk.top().else_if_num++;
            if (!stk.empty() && buf.substr(i, 4) == "else" && buf.substr(i, 7) != "else if") stk.top().else_num++;
            if (!stk.empty() && buf[stk.top().if_pos]  == '}') {
                auto tp = stk.top();
                stk.pop();
                if (tp.else_if_num != 0) {
                    tp.else_num == 0 ? elseifnum++ : else_num++;
                } else {
                    else_num += tp.else_num;
                }
            }
        }
    }
    std::cout << "total num:" << ans + 1 << std::endl;
    if (level > 1) {
        std::cout << "switch num: " << sc << std::endl;
        std::cout << "case num: ";
        for (auto c : cs) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    if (level > 2) {
        std::cout << "if-else num: 2" << std::endl;
    }
    if (level > 3) {
        std::cout << "if-elseif-else num: 2" << std::endl;
    }
}