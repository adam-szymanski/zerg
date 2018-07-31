#ifndef LIB_GENETIC_FORMULA_ENTITY_MUTATOR_H
#define LIB_GENETIC_FORMULA_ENTITY_MUTATOR_H

#include "lib/util/Random.h"
#include "lib/genetic/classification/FormulaEntity.h"

namespace Zerg {

class FormulaEntityMutator {
public:
    float prob;

    FormulaEntityMutator(float prob_)
        : prob(prob_) {
            assertIsGreaterOrEqual(1.0f, prob);
            assertIsGreaterOrEqual(prob, 0.0f);
        }

    FormulaEntity mutate(const FormulaEntity& e) {
        if (randf() > prob)
            return e;
        FormulaEntity e2 = e;
        size_t pos = rand(e2.codons.size());
        e2.codons[pos] = FormulaCodon(pos + e2.inputSize);
        return e2;
    }
};

}

#endif