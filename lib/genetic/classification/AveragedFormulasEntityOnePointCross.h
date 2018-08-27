#pragma once

#include "lib/util/Random.h"

#include "lib/genetic/classification/AveragedFormulasEntity.h"

#include <algorithm>

namespace Zerg {

class AveragedFormulasEntityOnePointCross {
public:
    AveragedFormulasEntity cross(const AveragedFormulasEntity& a, const AveragedFormulasEntity& b) {
        bool shouldSwap = rand(2) == 0;
        const AveragedFormulasEntity& a_ = shouldSwap ? b : a;
        const AveragedFormulasEntity& b_ = shouldSwap ? a : b;
        size_t crossPoint = rand(std::min(a_.genes.size(), b_.genes.size()));
        AveragedFormulasEntity child(a_.outputSize, a_.inputSize, 0, a_.genes.size());
        for (size_t i = 0; i < crossPoint; ++i)
            child.genes[i] = b_.genes[i];
        for (size_t i = crossPoint; i < a_.genes.size(); ++i)
            child.genes[i] = a_.genes[i];
        return child;
    }
};

}