#ifndef LIB_GENETIC_ARENA_SELECTOR_H
#define LIB_GENETIC_ARENA_SELECTOR_H

#include <set>
#include <tuple>

#include "lib/assert/Assert.h"
#include "lib/util/Random.h"
#include "lib/genetic/Population.h"

using namespace std;

namespace Zerg {

template<class Entity, class Environment, class Mutator, class Crosser>
class ArenaSelector {
    size_t arenaSize;

    typedef ScoredEntity<Entity> SE;
public:
    ArenaSelector(size_t arenaSize_)
        : arenaSize(arenaSize_) {
        assertIsGreater(arenaSize, 2);
    }

    void select(vector<SE>& entities, Environment& env, Mutator& mutator, Crosser& crosser) {
        assertIsGreaterOrEqual(entities.size(), arenaSize);
        set<size_t> selectedIds;
        int newId;
        for (size_t i = 0; i < arenaSize; ++i) {
            while (selectedIds.count(newId = rand(entities.size())) > 0);
            selectedIds.insert(newId);
        }
        vector<int> rank;
        rank.reserve(selectedIds.size());
        for (auto& entityId : selectedIds) {
            auto& e = entities[entityId];
            rank.push_back(entityId);
            if (!e.score) {
                e.score.emplace(env.score(e.entity));
            }
        }
        sort(rank.begin(), rank.end(), [entities](const int& a, const int& b) -> bool { return *entities[a].score < *entities[b].score; });

        // Mutate the best one and place in place of worst one.
        cout << "Best score: " << *entities[rank[0]].score << " (" << entities[rank[0]].entity << ")" << endl;
        entities[rank[rank.size() - 1]] = SE(mutator.mutate(crosser.cross(entities[rank[0]].entity, entities[rank[1]].entity)));
    }
};

}

#endif