#include <iostream>
#include <ctime>

#include "lib/genetic/Genetic.h"
#include "lib/tensor/Tensor.h"

using namespace std;
using namespace Zerg;

int main() {
    srand(time(NULL));
    Tensor labels({1, 4});
    labels.val(0, 0) = 0;
    labels.val(0, 1) = 1;
    labels.val(0, 2) = 1;
    labels.val(0, 3) = 0;

    Tensor examples({2, 4});
    examples.val(0, 0) = 0;
    examples.val(1, 0) = 0;

    examples.val(0, 1) = 0;
    examples.val(1, 1) = 1;

    examples.val(0, 2) = 1;
    examples.val(1, 2) = 0;

    examples.val(0, 3) = 1;
    examples.val(1, 3) = 1;

    ClassificationEnvironment<FormulaEntity> env(examples, labels);
    ArenaSelector<FormulaEntity, ClassificationEnvironment<FormulaEntity>, FormulaEntityMutator> selector(5);
    FormulaEntityMutator mutator(0.1f);

    vector<FormulaEntity> entities;
    for (int i = 0; i < 30; ++i)
        entities.push_back(FormulaEntity(examples.getRowSize(), 15));

    Population<FormulaEntity,
               ClassificationEnvironment<FormulaEntity>,
               FormulaEntityMutator,
               ArenaSelector<FormulaEntity, ClassificationEnvironment<FormulaEntity>, FormulaEntityMutator>> population(env, selector, mutator, entities);

    for (int i = 0; i < 1000000; ++i) {
        selector.select(population.entities, env, mutator);
    }
    return 0;
}