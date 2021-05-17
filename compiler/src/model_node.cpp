#include "model_node.h"
#include <iostream>

ModelCompiler::ModelNodeType getModelType(const std::string& name) {
    std::string tmp = name.substr(name.find_last_of('.') + 1);
    if (tmp == "Linear" or tmp == "Conv2d" or tmp == "Identity") {
        return ModelCompiler::ModelNodeType::MATRIX;
    } else if (tmp == "LayerNorm" or tmp == "Softmax" or tmp == "GELU" or tmp == "Dropout" or tmp == "AdaptiveAvgPool1d" or tmp == "DropPath") {
        return ModelCompiler::ModelNodeType::UNLINEAR;
    } else {
        return ModelCompiler::ModelNodeType::CONTAINER;
    }
}

ModelCompiler::ModelNode::ModelNode(const std::string& nameParam) : type(CONTAINER), name(nameParam) {
    this->left = nullptr;
    this->right = nullptr;
    this->childEnd = nullptr;
}
void ModelCompiler::ModelNode::debug() {
    this->debug(0, std::cout);
}
void ModelCompiler::ModelNode::debug(int indent, std::ostream& out) {
    if (indent > 0) {
        std::string indentStr(indent, ' ');
        out << indentStr;
    }
    out << "< Name: " << this->name << ", Type: " << this->type
        << ", Detail: " << this->typeDetail << " >" << std::endl;
    if (this->left != nullptr) {
        this->left->debug(indent + 4, out);
    }
    auto ptr = this->right;
    while (ptr != nullptr) {
        ptr->debug(indent, out);
        ptr = ptr->right;
    }
}
void ModelCompiler::ModelNode::recursiveBuild(const torch::jit::script::Module& module, ModelCompiler::ModelNode* prev) {
    assert(prev != nullptr);
    prev->typeDetail = module.type()->annotation_str();
    if (module.children().size() == 0) {
        prev->type = getModelType(prev->typeDetail);
        if (prev->type == ModelCompiler::ModelNodeType::CONTAINER) {
            std::cerr << "Unknown Cell: " << prev->typeDetail << std::endl;
        }
    }
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

