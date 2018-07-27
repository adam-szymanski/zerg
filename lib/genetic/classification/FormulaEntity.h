#ifndef LIB_GENETIC_FORMULA_ENTITY_H
#define LIB_GENETIC_FORMULA_ENTITY_H

#include "lib/util/Random.h"

namespace Zerg {

class FormulaEntity {
public:
    float value;
    size_t input_size;

    FormulaEntity(size_t input_size_, float value_)
        : value(value_)
        , input_size(input_size_) {
        }

    FormulaEntity(size_t input_size_)
        : FormulaEntity(input_size_, randf()) {}

    template<typename Iter>
    float evaluate(const Iter& begin, const Iter& end) { return value; }
};

}

#endif