#pragma once

#include <vector>

#include "lib/assert/Assert.h"
#include "lib/util/Random.h"
#include "lib/genetic/Population.h"
#include "lib/genetic/selectors/Selector.h"

using namespace std;

namespace Zerg {

template<class Entity, class Environment, class Mutator, class Crosser>
class OnePlusLambdaSelector : Selector<Entity, Environment, Mutator, Crosser> {
    typedef ScoredEntity<Entity> SE;
public:
    void select(size_t step, vector<SE>& entities, Environment& env, Mutator& mutator, Crosser& crosser) override {
        assertIsGreater(entities.size(), 0);
        bool first = true;
        const Entity* bestEntity;
        float bestScore;
        for (auto& entity : entities) {
            if (!entity.score) {
                entity.score.emplace(env.score(entity.entity));
            }
            if (first || *entity.score < bestScore) {
                bestScore = *entity.score;
                bestEntity = &entity.entity;
                first = false;
            }
        }
        entities[0] = SE(*bestEntity, bestScore);
        for (size_t i = 1; i < entities.size(); ++i)
            entities[i] = SE(mutator.mutate(entities[0].entity));

        if (step % 100 == 0)
            cout << step << " Best score: " << bestScore << " (" << entities[0].entity << ")" << endl;
    }
};

}