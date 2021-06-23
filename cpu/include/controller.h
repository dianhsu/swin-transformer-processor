//
// Created by dianhsu on 2021/6/21.
//

#ifndef STP_CONTROLLER_H
#define STP_CONTROLLER_H

#include <istream>

#include "yaml-cpp/yaml.h"

#include "config.h"
#include "partition_merge.h"

/**
 * 中央控制器
 * @tparam T 操作数据类型
 * @param cIns 指令流
 * @param pIns 参数流
 */
template<typename T>
void control(const YAML::Node::iterator &st, const YAML::Node::iterator &ed, std::istream &pIns) {
    for (auto ptr = st; ptr != ed; ++ptr) {
        const YAML::Node &command = *ptr;
        auto t = command["type"].as<int64_t>();
        if (t == 0) {
            auto pos = command["position"].as<int64_t>();
            regs[pos] = command["value"].as<int64_t>();
        } else if (t == 1) {
            regs[21] = regs[1] * regs[2] * regs[3] + regs[4] * regs[5] * regs[6];
            partition_merge<T>(pIns);
        } else if (t == 2) {
            // TODO: Move Data
            T *basePtr = reinterpret_cast<T *>(regs[0]);
            for (int64_t i = 0; i < regs[4] * regs[5] * regs[6]; ++i) {
                basePtr[i] = basePtr[regs[7] + i];
            }
        } else if (t == 3) {
            // TODO: Swin Block
        } else {
            return;
        }
    }
}

#endif //STP_CONTROLLER_H
