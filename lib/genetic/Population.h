#ifndef LIB_GENETIC_POPULATION_H
#define LIB_GENETIC_POPULATION_H

#include <experimental/optional>
#include <vector>

#include "lib/assert/Assert.h"

using namespace std;

namespace Zerg {

template<class Entity>
struct ScoredEntity {
    Entity entity;
    experimental::optional<float> score;

    ScoredEntity() {}
    ScoredEntity(Entity entity_)
        : entity(entity_) {}

    ScoredEntity(Entity entity_, experimental::optional<float> score_)
        : entity(entity_)
        , score(score_) {}
};

template<class Entity, class Environment, class Mutator, class Selector>
class Population {
public:
    Environment& env;
    Selector& selector;
    Mutator& mutator;
    vector<ScoredEntity<Entity>> entities;

public:
    Population(Environment& env_, Selector& selector_, Mutator& mutator_, vector<Entity>& entities_)
        : env(env_)
        , selector(selector_)
        , mutator(mutator_) {
        entities.reserve(entities_.size());
        for (auto& e : entities_)
            entities.push_back(ScoredEntity<Entity>(e));
    }

    Environment& getEnv() { return env; }
    size_t getEntitiesNum() { return entities.size(); }
    Entity& getEntity(size_t index) {
        assertIsGreater(entities.size(), index);
        return entities[index];
    }
};

}


#endif // LIB_GENETIC_POPULATION_H