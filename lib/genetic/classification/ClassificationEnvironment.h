#pragma once

using namespace std;

#include "lib/assert/Assert.h"
#include "lib/tensor/Tensor.h"

namespace Zerg {

template<class Entity>
class ClassificationEnvironment {
public:
    const Tensor& examples;
    const Tensor& labels;
public:
    ClassificationEnvironment(const Tensor& examples_, const Tensor& labels_)
        : examples(examples_)
        , labels(labels_) {
        assertIsEqual(labels.getRowSize(), 1);
        assertIsEqual(labels.getRowsNum(), examples.getRowsNum());
    }

    float score(Entity& entity) {
        float error = 0.0f;
        for (size_t i = 0; i < examples.getRowsNum(); ++i) {
            float out = entity.evaluate(examples.getPointer() + examples.getSize().getElementPos(0, i), examples.getPointer() + examples.getSize().getElementPos(0, i + 1));
            if (out != out) {
                cout << "input: ";
                for (size_t x = 0; x < examples.getRowSize(); ++ x)
                    cout << examples.val(x, i) << " ";
                cout << endl;
                cout << "vals: ";
                for (size_t x = 0; x < entity.valueCache.size(); ++ x)
                    cout << entity.valueCache[x] << " ";
                cout << endl;
                cout << entity << endl;
            }
            float diff = labels.val(0, i) - out;

            error += diff * diff;
        }
        return error;
    }
};

}