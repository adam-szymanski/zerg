#pragma once

#include "lib/assert/Assert.h"
#include "lib/tensor/Tensor.h"

namespace Zerg {

Tensor oneHot(const Tensor& t) {
    assertIsGreater(t.getElementsNum(), 0);
    assertIsEqual(t.getSize().getDimensionNum(), 2);
    bool onlyIntegers = true;
    float maxValue = t.data[0];
    for (const float& f : t.getData()) {
        assertIsGreaterOrEqual(f, 0);
        if (f != round(f)) {
            onlyIntegers = false;
            break;
        }
        if (maxValue < f)
        maxValue = f;
    }
    assertIsTrue(onlyIntegers);

    size_t rows = (size_t)t.getRowsNum();
    size_t rowSize = (size_t)maxValue;
    Tensor result({rowSize, rows});
    result.fillWithValue(0.0f);
    for (size_t row = 0; row < rows; ++row) {
        result.val(size_t(t.val(0, row)), row) = 1.0f;
    }
    return result;
}

}