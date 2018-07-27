#ifndef LIB_GENETIC_CLASSIFICATION_ENVIRONMENT_H
#define LIB_GENETIC_CLASSIFICATION_ENVIRONMENT_H

using namespace std;

#include "lib/tensor/Tensor.h"

namespace Zerg {

template<class Entity>
class ClassificationEnvironment {
private:
    const Tensor& examples;
    const Tensor& labels;
public:
    ClassificationEnvironment(const Tensor& examples_, const Tensor& labels_)
        : examples(examples_)
        , labels(labels_) {}

    float score(Entity& entity) {
        float diff = labels.val(0) - entity.evaluate();
        return diff * diff;
    }
};

}

#endif