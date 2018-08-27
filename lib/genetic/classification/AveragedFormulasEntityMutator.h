#pragma once

#include "lib/util/Random.h"
#include "lib/genetic/classification/AveragedFormulasEntity.h"
#include "lib/genetic/classification/FormulaEntityMutator.h"

namespace Zerg {

class AveragedFormulasEntityMutator {
public:
    float prob;
    const FormulaEntityMutator& mutator;

    AveragedFormulasEntityMutator(float prob_, const FormulaEntityMutator& mutator_)
        : prob(prob_)
        , mutator(mutator_) {
            assertIsGreaterOrEqual(prob, 0.0f);
        }

    AveragedFormulasEntity mutate(const AveragedFormulasEntity& e) const {
        float acc = prob;
        AveragedFormulasEntity e2 = e;
        while (acc > 0) {
            if (randf() > prob)
                break;
            size_t pos = rand(e2.genes.size());
            e2.genes[pos] = mutator.mutate(e2.genes[pos]);
            acc -= 1.0f;
        }
        return e2;
    }
};

}