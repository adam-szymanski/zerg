#ifndef LIB_GENETIC_SELECTORS_SELECTOR_H
#define LIB_GENETIC_SELECTORS_SELECTOR_H

#include <vector>

using namespace std;

namespace Zerg {

template<class Entity, class Environment, class Mutator, class Crosser>
class Selector {
public:
    virtual void select(size_t step, vector<ScoredEntity<Entity>>& entities, Environment& env, Mutator& mutator, Crosser& crosser) = 0;
};

}

#endif