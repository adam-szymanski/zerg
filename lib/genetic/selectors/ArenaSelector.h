#ifndef LIB_GENETIC_ARENA_SELECTOR_H
#define LIB_GENETIC_ARENA_SELECTOR_H

#include <tuple>

#include "lib/util/Random.h"
#include "lib/genetic/Population.h"

using namespace std;

namespace Zerg {

template<class Entity, class Environment>
class ArenaSelector {
    size_t arenaSize;
public:
    ArenaSelector(size_t arenaSize_)
        : arenaSize(arenaSize_) {}

    SelectorResult select(vector<ScoredEntity<Entity>>& entities, Environment& env) {
        //TODO actual selection.
        return SelectorResult(0, 1, 2);
    }
};

}

#endif