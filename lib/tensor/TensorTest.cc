#include "gtest/gtest.h"
#include "lib/tensor/Tensor.h"

#include <iostream>
#include <vector>

using namespace Zerg;
using namespace std;

TEST(TensorTest, MatrixSize) {
    Tensor m({4, 3, 2});
    EXPECT_EQ(m.getRowSize(), 12);
    EXPECT_EQ(m.getRowsNum(), 2);
}

TEST(TensorTest, Stride) {
    Tensor m({4, 3, 2});
    EXPECT_EQ(m.getSize().getStride(0, 3), 1);
    EXPECT_EQ(m.getSize().getStride(1, 3), 4);
    EXPECT_EQ(m.getSize().getStride(2, 3), 12);
    EXPECT_EQ(m.getSize().getStride(3, 3), 24);

    EXPECT_EQ(m.getSize().getStride(0, 2), 1);
    EXPECT_EQ(m.getSize().getStride(1, 2), 12);
    EXPECT_EQ(m.getSize().getStride(2, 2), 24);

    EXPECT_EQ(m.getSize().getStride(0, 1), 1);
    EXPECT_EQ(m.getSize().getStride(1, 1), 24);
}

TEST(TensorTest, DimSize) {
    Tensor m({4, 3, 2});
    EXPECT_EQ(m.getSize().getDimSize(0, 3), 4);
    EXPECT_EQ(m.getSize().getDimSize(1, 3), 3);
    EXPECT_EQ(m.getSize().getDimSize(2, 3), 2);

    EXPECT_EQ(m.getSize().getDimSize(0, 2), 12);
    EXPECT_EQ(m.getSize().getDimSize(1, 2), 2);

    EXPECT_EQ(m.getSize().getDimSize(0, 1), 24);
}

TEST(TensorTest, ElementPos_dim1) {
    Tensor m({2});
    EXPECT_EQ(m.getSize().getElementPos(0), 0);
    EXPECT_EQ(m.getSize().getElementPos(1), 1);
}

TEST(TensorTest, ElementPos_dim2) {
    Tensor m({3, 2});
    EXPECT_EQ(m.getSize().getElementPos(0, 0), 0);
    EXPECT_EQ(m.getSize().getElementPos(1, 0), 1);
    EXPECT_EQ(m.getSize().getElementPos(2, 0), 2);
    EXPECT_EQ(m.getSize().getElementPos(0, 1), 3);
    EXPECT_EQ(m.getSize().getElementPos(1, 1), 4);
    EXPECT_EQ(m.getSize().getElementPos(2, 1), 5);
}

TEST(TensorTest, ElementPos_dim3) {
    Tensor m({2, 3, 2});
    EXPECT_EQ(m.getSize().getElementPos(0, 0, 0), 0);
    EXPECT_EQ(m.getSize().getElementPos(1, 0, 0), 1);
    EXPECT_EQ(m.getSize().getElementPos(0, 1, 0), 2);
    EXPECT_EQ(m.getSize().getElementPos(1, 1, 0), 3);
    EXPECT_EQ(m.getSize().getElementPos(0, 2, 0), 4);
    EXPECT_EQ(m.getSize().getElementPos(1, 2, 0), 5);
    EXPECT_EQ(m.getSize().getElementPos(0, 0, 1), 6);
    EXPECT_EQ(m.getSize().getElementPos(1, 0, 1), 7);
    EXPECT_EQ(m.getSize().getElementPos(0, 1, 1), 8);
    EXPECT_EQ(m.getSize().getElementPos(1, 1, 1), 9);
    EXPECT_EQ(m.getSize().getElementPos(0, 2, 1), 10);
    EXPECT_EQ(m.getSize().getElementPos(1, 2, 1), 11);
}

TEST(TensorTest, Slice) {
    Tensor m({3, 4});
    for (size_t i = 0; i < m.getElementsNum(); ++i)
        m.data[i] = i;

    {
        Tensor sliced = m.createSlice(1, 1, 2);
        EXPECT_EQ(sliced.getData(), vector<float>({3, 4, 5, 6, 7, 8}));
    }
    {
        Tensor sliced = m.createSlice(0, 1, 1);
        EXPECT_EQ(sliced.getData(), vector<float>({1, 4, 7, 10}));
    }
}

TEST(TensorTest, LoadCSV) {
    Tensor m = Tensor::loadCSVFromFile("lib/tensor/test.csv");
    EXPECT_EQ(m.getRowSize(), 3);
    EXPECT_EQ(m.getRowsNum(), 2);
    EXPECT_EQ(m.getData(), vector<float>({1, 2, 3, 4, 5, 6}));
}