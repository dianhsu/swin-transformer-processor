#include "ModelTree.h"

ModelCompiler::ModelTree::ModelTree() {
    //this->root = new ModelNode("Main");
    // TODO: Complete this module
}
void ModelCompiler::ModelTree::build(const torch::jit::script::Module& module) {
    //this->root->recursiveBuild(module, this->root);
    // TODO: Complete this module
}
void ModelCompiler::ModelTree::show() {
    this->root->show();
}