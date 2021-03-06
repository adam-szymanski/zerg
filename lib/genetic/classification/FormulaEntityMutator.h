#pragma once

#include "lib/util/Random.h"
#include "lib/genetic/classification/FormulaEntity.h"

namespace Zerg {

class FormulaEntityMutator {
public:
    float prob;

    FormulaEntityMutator(float prob_)
        : prob(prob_) {
            assertIsGreaterOrEqual(prob, 0.0f);
        }

    FormulaEntity mutate(const FormulaEntity& e) {
        float acc = prob;
        FormulaEntity e2 = e;
        while (acc > 0) {
            if (randf() > prob)
                break;
            size_t pos = rand(e2.codons.size());
            e2.codons[pos] = FormulaCodon(pos + e2.inputSize);
            acc -= 1.0f;
        }
        return e2;
    }
};

}