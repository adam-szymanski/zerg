#pragma once

#include <vector>

using namespace std;

namespace Zerg {

template<class Entity, class Environment, class Mutator, class Crosser>
class Selector {
public:
    virtual void select(size_t step, vector<ScoredEntity<Entity>>& entities, Environment& env, Mutator& mutator, Crosser& crosser) = 0;
};

}