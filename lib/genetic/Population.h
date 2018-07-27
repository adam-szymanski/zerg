#ifndef LIB_GENETIC_POPULATION_H
#define LIB_GENETIC_POPULATION_H

#include <experimental/optional>
#include <vector>

#include "lib/assert/Assert.h"

using namespace std;

namespace Zerg {

struct SelectorResult {
    size_t best;
    size_t secondBest;
    size_t worst;
    SelectorResult(size_t best_, size_t secondBest_, size_t worst_)
        : best(best_)
        , secondBest(secondBest_)
        , worst(worst_) {}
};

template<class Entity>
struct ScoredEntity {
    Entity entity;
    experimental::optional<float> score;

    ScoredEntity() {}

    ScoredEntity(Entity entity_, experimental::optional<float> score_)
        : entity(entity_)
        , score(score_) {}
};

template<class Entity, class Environment, class Mutator, class Selector>
class Population {
private:
    Environment& env;
    Selector& selector;
    vector<ScoredEntity<Entity>> entities;

public:
    Population(Environment& env_, Selector& selector_, size_t population_size = 0)
        : env(env_)
        , selector(selector_)
        , entities(population_size) {}

    Environment& getEnv() { return env; }
    size_t getEntitiesNum() { return entities.size(); }
    Entity& getEntity(size_t index) {
        assertIsGreater(entities.size(), index);
        return entities[index];
    }
};

}


#endif // LIB_GENETIC_POPULATION_H