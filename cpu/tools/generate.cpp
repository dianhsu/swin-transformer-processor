//
// Created by dianhsu on 2021/6/23.
//

#include <bits/stdc++.h>

const char *PARAM_PATH = "data/params.txt";

using namespace std;

int main() {
    std::ofstream ofs(PARAM_PATH);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1, 1);
    for (int i = 0; i < 300000000; ++i) {
        string tmp = to_string(dist(gen)) + "\n";
        ofs.write(tmp.c_str(), (long) tmp.length());
        if ((i + 1) % 30000 == 0) {
            printf("\rGenerated: [%.2f%%]", 100.0 * (i + 1) / (double) 300000000);
            fflush(stdout);
        }
    }
    ofs.close();
}