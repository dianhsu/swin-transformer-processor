#ifndef __MODEL_CELL_VECTOR_H__
#define __MODEL_CELL_VECTOR_H__

#include "cell.h"

namespace ModelCompiler {
template<typename T>
class CellVector :public Cell {
public:
    void forward(vector<T> input1, vector<T> input2, vector<T>& output) {
        assert(input1.size() == input2.size() and input1.size() == output.size());
        for (int i = 0; i < input1.size(); ++i) {
            output[i] = input1[i] + input2[i];
        }

    }
};
}

#endif