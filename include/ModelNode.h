#ifndef __MODEL_NODE_H__
#define __MODEL_NODE_H__
#include <string>
#include <vector>

#include "torch/script.h"

namespace ModelCompiler {
struct ModelNode {
    // left son, right brother
    ModelNode* left;
    ModelNode* right;
    ModelNode* childEnd;
    std::string name;
    std::vector<int> dim;
    std::vector<int> data;
    ModelNode(const std::string&);
    void show(int indent);
    void show();
    void recursiveBuild(const torch::jit::script::Module& module, ModelNode* prev);
};
}

#endif