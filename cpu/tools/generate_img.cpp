//
// Created by dianhsu on 2021/6/24.
//


#include <bits/stdc++.h>

const char *IMG_PATH = "data/img.txt";
constexpr int IMG_SIZE = 96 * 56 * 56;
using namespace std;

int main() {
    std::ofstream ofs(IMG_PATH);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1, 1);
    for (int i = 0; i < IMG_SIZE; ++i) {
        string tmp = to_string(dist(gen)) + "\n";
        ofs.write(tmp.c_str(), (long) tmp.length());
    }
    ofs.close();
}