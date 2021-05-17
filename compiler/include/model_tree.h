#ifndef __MODEL_TREE_H__
#define __MODEL_TREE_H__

#include <torch/script.h>

#include "model_node.h"

namespace ModelCompiler {
struct ModelTree {
    ModelNode* root;
    ModelTree();
    void build(const torch::jit::script::Module& module);
    void debug();
};
}

#endif