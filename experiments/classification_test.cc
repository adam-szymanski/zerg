#include <iostream>
#include <cstdio>
#include <ctime>

#include "lib/genetic/Genetic.h"
#include "lib/tensor/Tensor.h"
#include "lib/tensor/TensorUtil.h"

using namespace std;
using namespace Zerg;

bool fileExists(const char* filename) {
    FILE *f = fopen(filename, "rb");
    if (f)
        fclose(f);
    return f != NULL;
}

int main() {
    srand(time(NULL));
    if (!fileExists("covtype.data.gz")) {
        system("wget https://archive.ics.uci.edu/ml/machine-learning-databases/covtype/covtype.data.gz");
    }

    if (!fileExists("covtype.data")) {
        system("gunzip covtype.data.gz");
    }

    Tensor data = Tensor::loadCSVFromFile("covtype.data");
    Tensor trainData = data.createSlice(1, 0, 11340);
    //Tensor validationData = data.createSlice(1, 11340, 3780);
    //Tensor testData = data.createSlice(1, 11340 + 3780, 565892);

    Tensor trainExamples = trainData.createSlice(0, 0, trainData.getRowSize() - 1);
    Tensor trainLabels = trainData.createSlice(0, trainData.getRowSize() - 1, 1);
    trainLabels = oneHot(trainLabels);

    //Tensor testExamples = testData.createSlice(0, 0, testData.getRowSize() - 1);
    //Tensor testLabels = testData.createSlice(0, testData.getRowSize() - 1, 1);
    cout << trainData.getSize() << endl;
    //cout << validationData.getSize() << endl;
    //cout << testData.getSize() << endl;
    cout << data.createSlice(1, 0, 10) << endl;

    /*ClassificationEnvironment<FormulaEntity> env(trainExamples, trainLabels);
    OnePlusLambdaSelector<FormulaEntity, ClassificationEnvironment<FormulaEntity>, FormulaEntityMutator, FormulaEntityOnePointCross> selectorOnePlus;
    ArenaSelector<FormulaEntity, ClassificationEnvironment<FormulaEntity>, FormulaEntityMutator, FormulaEntityOnePointCross> selectorArena(5);
    FormulaEntityMutator mutator(1.5f);
    FormulaEntityOnePointCross crosser;

    vector<FormulaEntity> entities;
    for (int i = 0; i < 30; ++i)
        entities.push_back(FormulaEntity(trainLabels.getRowSize(), trainExamples.getRowSize(), 35));*/
    ClassificationEnvironment<AveragedFormulasEntity> env(trainExamples, trainLabels);
    OnePlusLambdaSelector<AveragedFormulasEntity, ClassificationEnvironment<AveragedFormulasEntity>, AveragedFormulasEntityMutator, AveragedFormulasEntityOnePointCross> selectorOnePlus;
    //ArenaSelector<AveragedFormulasEntity, ClassificationEnvironment<AveragedFormulasEntity>, AveragedFormulasEntityMutator, AveragedFormulasEntityOnePointCross> selectorArena(5);
    AveragedFormulasEntityMutator mutator(1.0f, FormulaEntityMutator(1.5f));
    AveragedFormulasEntityOnePointCross crosser;

    vector<AveragedFormulasEntity> entities;
    /*for (int i = 0; i < 30; ++i)
        entities.push_back(AveragedFormulasEntity(trainLabels.getRowSize(), trainExamples.getRowSize(), 15, 10));*/
    for (int i = 0; i < 5; ++i)
        entities.push_back(AveragedFormulasEntity(trainLabels.getRowSize(), trainExamples.getRowSize(), 15, 10));

    auto population = makePopulation(env, selectorOnePlus, mutator, crosser, entities);
    for (int i = 0; i < 1000000; ++i) {
        population.step();
    }
}