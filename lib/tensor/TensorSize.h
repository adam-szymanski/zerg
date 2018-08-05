#pragma once

#include <cstdio>
#include <iostream>
#include <vector>

#include "lib/assert/Assert.h"

namespace Zerg {


struct TensorSize {
private:
  std::vector<size_t> size;
  std::vector<size_t> dimSize;
public:
  TensorSize() {}
  TensorSize(const std::vector<size_t>& size);

  // Getters
  inline size_t getDimensionNum() const { return size.size(); }
  inline size_t getDimension(size_t dim) const { return dim < getDimensionNum() ? size[dim] : 0; }
  size_t getDimSize(size_t dim, size_t tensorDim) const;
  size_t getStride(size_t dim, size_t tensorDim) const;
  size_t getElementsNum() const { return getDimensionNum() > 0 ? dimSize[0] * size[getDimensionNum() - 1] : 0; }
  size_t getElementPos(const std::vector<size_t>& index) const;
  size_t getElementPos(size_t x) const;
  size_t getElementPos(size_t x, size_t y) const;
  size_t getElementPos(size_t x, size_t y, size_t z) const;
  size_t getElementPos(size_t x, size_t y, size_t z, size_t w) const;
  inline std::vector<size_t> getShape() const { return getDimensionNum() > 0 ? std::vector<size_t>(size.begin(), --size.end()) : std::vector<size_t>(); }
  
  size_t getW_1D() const { return getDimSize(0, 1); }
  size_t getW_2D() const { return getDimSize(0, 2); }
  size_t getH_2D() const { return getDimSize(1, 2); }
  // Setters
  void setRows(size_t rows) { assertIsGreater(getDimensionNum(), 0); size[getDimensionNum() - 1] = rows; }

  // Other
  bool isShapeEqual(const std::vector<size_t>& shape) const;
  bool isShapeCompatible(const std::vector<size_t>& shape) const;
  bool isShapeCompatible(const TensorSize& size) const;

  friend std::ostream& operator<<(std::ostream& os, const TensorSize& t);

  void saveToFile(FILE* f) const;
	static TensorSize loadFromFile(FILE* f);
private:
  inline size_t getDimSize(size_t dim) const { return dim < getDimensionNum() ? dimSize[dim] : 0; }
  bool isShapeCompatible(const std::vector<size_t>& shape, size_t n) const;
};

std::ostream& operator<<(std::ostream& os, const TensorSize& t);

}; // namespace Zerg