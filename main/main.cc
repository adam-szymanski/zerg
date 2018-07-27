#include<iostream>

#include "lib/genetic/Genetic.h"
#include "lib/tensor/Tensor.h"

using namespace std;
using namespace Zerg;

int main() {
    Tensor t({1});
    t.val(0) = 0;
    ClassificationEnvironment<FormulaEntity> env(Tensor({1}), t);
    ArenaSelector<FormulaEntity, ClassificationEnvironment<FormulaEntity>> selector(5);
    FormulaEntityMutator mutator(0.1f);

    Population<FormulaEntity,
               ClassificationEnvironment<FormulaEntity>,
               FormulaEntityMutator,
               ArenaSelector<FormulaEntity, ClassificationEnvironment<FormulaEntity>>> population(env, selector, mutator, 10);

    return 0;
}