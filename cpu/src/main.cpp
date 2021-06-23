//
// Created by dianhsu on 2021/6/20.
//
#include <bits/stdc++.h>

#include "yaml-cpp/yaml.h"

#include "controller.h"


const char *CONFIG_PATH = "data/config-sample.yaml";
const char *PARAMS_PATH = "data/params.txt";
typedef double data_t;

int main() {
    regs[0] = reinterpret_cast<int64_t>(malloc(MAX_MEMORY_SIZE));
    if (!std::filesystem::exists(CONFIG_PATH) or !std::filesystem::is_regular_file(CONFIG_PATH)) {
        std::cerr << std::filesystem::absolute(CONFIG_PATH)
                  << ": file not exist or it is not regular file"
                  << std::endl;
        return -1;
    }
    YAML::Node config = YAML::LoadFile(CONFIG_PATH);
    auto commands = config["commands"];
    std::ifstream pIns(PARAMS_PATH);
    control<data_t>(commands.begin(), commands.end(), pIns);
    free(reinterpret_cast<void *>(regs[0]));
    return 0;
}