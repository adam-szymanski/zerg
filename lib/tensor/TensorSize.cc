#include "lib/tensor/TensorSize.h"

#include <algorithm>
#include <iostream>

#include "lib/assert/Assert.h"

namespace Zerg {

TensorSize TensorSize::loadFromFile(FILE* f) {
  size_t n;
  fread(&n, sizeof(n), 1, f);
  size_t* size = new size_t[n];
  fread(size, sizeof(size_t) * n, 1, f);
  TensorSize s(std::vector<size_t>(size, size + n));
  delete size;
  return s;
}

void TensorSize::saveToFile(FILE* f) const {
  size_t n = size.size();
  fwrite(&n, sizeof(n), 1, f);
  fwrite(&size[0], sizeof(size_t) * n, 1, f);
}
  
bool TensorSize::isShapeCompatible(const std::vector<size_t>& shape, size_t n) const {
  size_t start = 0;
  if (n > getDimensionNum() - 1)
    return false;
  if (shape[start] != size[getDimensionNum() - 1 - n] * getDimSize(n))
    return false;
  size_t end1 = n - 1;
  size_t end2 = size.size() - 2;
  while (end1 > start) {
    if (shape[end1] != size[end2])
      return false;
    --end1;
    --end2;
  }
  return true;
}

bool TensorSize::isShapeCompatible(const TensorSize& size_) const {
  return isShapeCompatible(size_.size, size_.getDimensionNum() - 1);
}

bool TensorSize::isShapeCompatible(const std::vector<size_t>& shape) const {
  return isShapeCompatible(shape, shape.size());
}

bool TensorSize::isShapeEqual(const std::vector<size_t>& shape) const {
  if (getDimensionNum() - 1 != shape.size())
    return false;
  for (size_t i = 0; i < shape.size(); ++i)
    if (shape[i] != size[i])
      return false;
  return true;
}
  
size_t TensorSize::getElementPos(const std::vector<size_t>& index) const {
  size_t pos = 0;
  size_t steps = std::min(index.size() - 1, size.size());
  for (size_t i = 0; i < steps; ++i)
    pos += dimSize[i] * index[index.size() - 1 - i];
  if (index.size() <= size.size())
    pos += index[0];
  return pos;
}

size_t TensorSize::getElementPos(size_t x) const {
  assertIsEqual(getDimensionNum(), 1);
  return x;
}
size_t TensorSize::getElementPos(size_t x, size_t y) const {
  assertIsEqual(getDimensionNum(), 2);
  return x * getDimSize(1) + y * getDimSize(0);
}
size_t TensorSize::getElementPos(size_t x, size_t y, size_t z) const {
  assertIsEqual(getDimensionNum(), 3);
  return x * getDimSize(2) + getDimSize(1) * y + getDimSize(0) * z;
}
size_t TensorSize::getElementPos(size_t x, size_t y, size_t z, size_t w) const {
  assertIsEqual(getDimensionNum(), 4);
  return x * getDimSize(3) + getDimSize(2) * y + getDimSize(1) * z + getDimSize(0) * w;
}
size_t TensorSize::getStride(size_t dim, size_t tensorDim) const {
  assertIsGreaterOrEqual(tensorDim, dim);
  const size_t l = tensorDim - dim;
  if (l > getDimensionNum()) return 0;
  return getDimSize(tensorDim - 1 - dim);
}
size_t TensorSize::getDimSize(size_t dim, size_t tensorDim) const {
  assertIsGreaterOrEqual(tensorDim, dim);
  const size_t l = tensorDim - dim;
  if (l > getDimensionNum()) return 0;
  if (dim == 0)
    return getDimSize(tensorDim - 1) * size[getDimensionNum() - tensorDim];
  else
    return size[getDimensionNum() - l];
}

TensorSize::TensorSize(const std::vector<size_t>& size_)
  : size(size_)
  , dimSize(size_.size()) {
  size_t last = getDimensionNum() - 1;
  dimSize[last] = 1;
  for (size_t i = last; i > 0; --i)
    dimSize[i - 1] = dimSize[i] * size[last - i];
}

std::ostream& operator<<(std::ostream& os, const TensorSize& t) {
  os << "(";
  size_t last = t.getDimensionNum() - 1;
  for (size_t i = 0; i <= last; ++i) {
    os << t.size[i];
    if (i < last)
      os << ",";
  }
  os << ")";
  return os;
}

}; // namespace Zerg