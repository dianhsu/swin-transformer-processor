#include "model_tree.h"

ModelCompiler::ModelTree::ModelTree() {
    this->root = new ModelNode("Main");
}
void ModelCompiler::ModelTree::build(const torch::jit::script::Module& module) {
    this->root->recursiveBuild(module, this->root);
}
void ModelCompiler::ModelTree::debug() {
    this->root->debug();
}