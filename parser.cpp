#include <bits/stdc++.h>

#include <torch/script.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage:" << argv[0] << " <path-to-exported-script-module>" << std::endl;
        return -1;
    }
    torch::jit::script::Module module;
    try {
        module = torch::jit::load(argv[1]);
    } catch (const c10::Error& e) {
        std::cerr << "error loading the model" << std::endl;
        return -1;
    }
    std::cout << "ok" << std::endl;
    return 0;
}