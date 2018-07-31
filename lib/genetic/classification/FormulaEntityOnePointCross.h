#ifndef LIB_GENETIC_FORMULA_ENTITY_ONE_POINT_CROSS_H
#define LIB_GENETIC_FORMULA_ENTITY_ONE_POINT_CROSS_H

#include "lib/util/Random.h"

#include "lib/genetic/classification/FormulaEntity.h"

#include <algorithm>

namespace Zerg {

class FormulaEntityOnePointCross {
public:
    FormulaEntity cross(const FormulaEntity& a, const FormulaEntity& b) {
        bool shouldSwap = rand(2) == 0;
        const FormulaEntity& a_ = shouldSwap ? b : a;
        const FormulaEntity& b_ = shouldSwap ? a : b;
        size_t crossPoint = rand(std::min(a_.codons.size(), b_.codons.size()));
        FormulaEntity child(a_.inputSize, a_.codons.size());
        for (size_t i = 0; i < crossPoint; ++i)
            child.codons[i] = b_.codons[i];
        for (size_t i = crossPoint; i < a_.codons.size(); ++i)
            child.codons[i] = a_.codons[i];
        return child;
    }
};

}

#endif