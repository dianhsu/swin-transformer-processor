#include "ModelNode.h"
#include <iostream>

ModelCompiler::ModelNode::ModelNode(const std::string& nameParam) : name(nameParam) {
    this->left = nullptr;
    this->right = nullptr;
}
void ModelCompiler::ModelNode::show() {
    this->show(0);
}
void ModelCompiler::ModelNode::show(int indent) {
    if (indent > 0) {
        std::string indentStr(indent, ' ');
        std::cout << indentStr;
    }
    std::cout << this->name << std::endl;
    if (this->left != nullptr) {
        this->left->show(indent + 2);
    }
    auto ptr = this->right;
    while (ptr != nullptr) {
        ptr->show(indent);
        ptr = ptr->right;
    }
}
void ModelCompiler::ModelNode::recursiveBuild(const torch::jit::script::Module& module, ModelCompiler::ModelNode* prev) {
    assert(prev != nullptr);
    for (auto it : module.named_children()) {
        if (prev->childEnd == nullptr) {
            prev->left = new ModelCompiler::ModelNode(it.name);
            prev->childEnd = prev->left;
        } else {
            prev->childEnd->right = new ModelCompiler::ModelNode(it.name);
            prev->childEnd = prev->childEnd->right;
        }
        recursiveBuild(it.value, prev->childEnd);
    }
}