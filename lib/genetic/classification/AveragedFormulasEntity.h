#pragma once

#include "lib/genetic/classification/FormulaEntity.h"
#include "lib/util/Random.h"

#include <iostream>

namespace Zerg {

class AveragedFormulasEntity {
public:
    vector<FormulaEntity> genes;
    size_t outputSize;
    size_t inputSize;

    AveragedFormulasEntity(size_t outputSize_, size_t inputSize_, size_t len, size_t genesNum)
        : outputSize(outputSize_)
        , inputSize(inputSize_) {
            genes.reserve(len);
            for (size_t i = 0; i < genesNum; ++i)
                genes.push_back(FormulaEntity(outputSize_, inputSize_, len));
        }

    template<typename Iter>
    vector<float> evaluate(const Iter& begin, const Iter& end) {
        assertIsEqual(begin + inputSize, end);
        vector<float> output(outputSize);
        std::fill(output.begin(), output.end(), 0.0f);
        for (size_t i = 0; i < genes.size(); ++ i) {
            const auto& result = genes[i].evaluate(begin, end);
            for (size_t j = 0; j < result.size(); ++j)
                output[j] += result[j];
        }
        return output;
    }
};



std::ostream& operator<<(std::ostream& os, const AveragedFormulasEntity& fe) {
    for (auto& gene : fe.genes) {
        cout << "[ " << gene << "] ";
    }
    return os;
}

}