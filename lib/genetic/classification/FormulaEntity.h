#pragma once

#include "lib/genetic/classification/FormulaCodon.h"
#include "lib/util/Random.h"

#include <iostream>

namespace Zerg {

class FormulaEntity {
public:
    vector<FormulaCodon> codons;
    size_t outputSize;
    size_t inputSize;
    vector<float> valueCache;

    FormulaEntity(size_t outputSize_, size_t inputSize_, size_t len)
        : outputSize(outputSize_)
        , inputSize(inputSize_)
        , valueCache(inputSize + len) {
            codons.reserve(len);
            for (size_t i = 0; i < len; ++i)
                codons.push_back(FormulaCodon(i + inputSize));
        }

    template<typename Iter>
    vector<float> evaluate(const Iter& begin, const Iter& end) {
        assertIsEqual(begin + inputSize, end);
        for (size_t i = 0; i < inputSize; ++ i) {
            valueCache[i] = *(begin + i);
        }
        for (size_t i = 0; i < codons.size(); ++ i) {
            valueCache[i + inputSize] = codons[i].execute(valueCache, i + inputSize);
        }
        return vector<float>(valueCache.end() - outputSize, valueCache.end());
    }
};



std::ostream& operator<<(std::ostream& os, const FormulaEntity& fe) {
    for (auto& codon : fe.codons) {
        cout << codon << " ";
    }
    return os;
}

}