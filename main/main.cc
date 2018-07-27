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

    Population<FormulaEntity,
               ClassificationEnvironment<FormulaEntity>,
               int,
               ArenaSelector<FormulaEntity, ClassificationEnvironment<FormulaEntity>>> population(env, selector, 10);

    return 0;
}