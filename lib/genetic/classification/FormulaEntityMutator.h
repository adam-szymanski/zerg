#ifndef LIB_GENETIC_FORMULA_ENTITY_MUTATOR_H
#define LIB_GENETIC_FORMULA_ENTITY_MUTATOR_H

#include "lib/util/Random.h"
#include "lib/genetic/classification/FormulaEntity.h"

namespace Zerg {

class FormulaEntityMutator {
public:
    float mult;

    FormulaEntityMutator(float mult_)
        : mult(mult_) {}

    FormulaEntity mutate(const FormulaEntity& e) {
        return FormulaEntity(e.input_size, e.value * randf(1.0f - mult, 1.0f + mult));
    }
};

}

#endif