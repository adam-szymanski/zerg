#include<iostream>

#include "lib/genetic/Genetic.h"
#include "lib/tensor/Tensor.h"

using namespace std;
using namespace Zerg;

int main() {
    Tensor labels({1});
    labels.val(0) = 10.5f;
    Tensor examples({1});
    ClassificationEnvironment<FormulaEntity> env(examples, labels);
    ArenaSelector<FormulaEntity, ClassificationEnvironment<FormulaEntity>, FormulaEntityMutator> selector(5);
    FormulaEntityMutator mutator(0.1f);

    vector<FormulaEntity> entities;
    for (int i = 0; i < 10; ++i)
        entities.push_back(FormulaEntity(examples.getRowSize(), 4));

    Population<FormulaEntity,
               ClassificationEnvironment<FormulaEntity>,
               FormulaEntityMutator,
               ArenaSelector<FormulaEntity, ClassificationEnvironment<FormulaEntity>, FormulaEntityMutator>> population(env, selector, mutator, entities);

    for (int i = 0; i < 100000; ++i) {
        selector.select(population.entities, env, mutator);
    }
    return 0;
}