#ifndef __MODEL_NODE_H__
#define __MODEL_NODE_H__
#include <string>
#include <vector>

#include "torch/script.h"

namespace ModelCompiler {
enum ModelNodeType {
    CONTAINER,
    MATRIX,
    VECTOR,
    UNLINEAR
};
struct ModelNode {
    // left son, right brother
    ModelNode* left;
    ModelNode* right;
    ModelNode* childEnd;

    ModelNodeType type;
    std::string typeDetail;
    std::string name;

    ModelNode(const std::string&);
    void debug(int indent, std::ostream&);
    void debug();
    void recursiveBuild(const torch::jit::script::Module& module, ModelNode* prev);
};
}

#endif