#pragma once

#include "lib/util/Random.h"

#include "lib/genetic/classification/FormulaCodon.h"

namespace Zerg {

class FormulaEntity {
public:
    vector<FormulaCodon> codons;
    size_t inputSize;
    vector<float> valueCache;

    FormulaEntity(size_t inputSize_, size_t len)
        : inputSize(inputSize_)
        , valueCache(inputSize + len) {
            codons.reserve(len);
            for (size_t i = 0; i < len; ++i)
                codons.push_back(FormulaCodon(i + inputSize));
        }

    template<typename Iter>
    float evaluate(const Iter& begin, const Iter& end) {
        float val = evaluateInner(begin, end);
        return 1 / (1 + exp(-val));
    }

private:
    template<typename Iter>
    float evaluateInner(const Iter& begin, const Iter& end) {
        assertIsEqual(begin + inputSize, end);
        for (size_t i = 0; i < inputSize; ++ i) {
            valueCache[i] = *(begin + i);
        }
        for (size_t i = 0; i < codons.size(); ++ i) {
            valueCache[i + inputSize] = codons[i].execute(valueCache, i + inputSize);
            //cout << codons[i] << " " << valueCache[i + inputSize] << endl;
            if (codons[i].type == FORMULA_CODON_RETURN)
                return valueCache[i + inputSize];
        }
        return valueCache[valueCache.size() - 1];
    }
};



std::ostream& operator<<(std::ostream& os, const FormulaEntity& fe) {
    for (auto& codon : fe.codons) {
        cout << codon << " ";
    }
    return os;
}

}