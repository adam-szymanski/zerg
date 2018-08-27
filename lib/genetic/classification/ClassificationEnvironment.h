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
        assertIsGreater(labels.getRowSize(), 0);
        assertIsEqual(labels.getRowsNum(), examples.getRowsNum());
    }

    float score(Entity& entity) {
        float error = 0.0f;
        for (size_t i = 0; i < examples.getRowsNum(); ++i) {
            vector<float> output = entity.evaluate(examples.getPointer() + examples.getSize().getElementPos(0, i), examples.getPointer() + examples.getSize().getElementPos(0, i + 1));
            assertIsEqual(output.size(), labels.getRowSize());
            std::transform(output.begin(), output.end(), output.begin(), [](float a) { return 1 / (1 + exp(-a)); });
            for (size_t j = 0; j < output.size(); ++j) {
                float diff = labels.val(j, i) - output[j];
                error += diff * diff;
            }
        }
        return error;
    }
};

}