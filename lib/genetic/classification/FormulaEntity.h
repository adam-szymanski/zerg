#ifndef LIB_GENETIC_FORMULA_ENTITY_H
#define LIB_GENETIC_FORMULA_ENTITY_H

#include "lib/util/Random.h"

namespace Zerg {

class FormulaEntity {
public:
    float value;

    FormulaEntity()
        : value(randf()) {}

    FormulaEntity(float value_)
        : value(value_) {}

    float evaluate() { return value; }
};

}

#endif