#include "lib/tensor/Tensor.h"

#include <cstdio>

namespace Zerg {

void Tensor::addRows(size_t rows, bool shrinkToFit) {
  setRows(getRowsNum() + rows, shrinkToFit);
}


void Tensor::saveToFile(const char* filename) const {
  FILE *f = fopen(filename, "wb+");
  assertNotNull(f);
  saveToFile(f);
  fclose(f);
}

void Tensor::saveCSV(FILE* f) const {
  if (size.getDimensionNum() == 1) {
    for (size_t x = 0; x < getElementsNum(); ++x)
      if (x < getRowSize() - 1)
        fprintf(f, "%f,", val(x));
      else
        fprintf(f, "%f\n", val(x));
    return;
  }
  for (size_t y = 0; y < getRowsNum(); ++y) {
    for (size_t x = 0; x < getRowSize(); ++x)
      if (x < getRowSize() - 1)
        fprintf(f, "%f,", val(x, y));
      else
        fprintf(f, "%f\n", val(x, y));
  }
}

void Tensor::saveCSV(const char* filename) const {
  FILE *f = fopen(filename, "wb+");
  assertNotNull(f);
  saveCSV(f);
  fclose(f);
}


void Tensor::saveToFile(FILE* f) const {
  size.saveToFile(f);
  fwrite(getPointer(), sizeof(float) * data.size(), 1, f);
}

Tensor Tensor::loadFromFile(const char* filename) {
  FILE *f = fopen(filename, "rb+");
  assertNotNull(f);
  Tensor t = loadFromFile(f);
  fclose(f);
  return t;
}

Tensor Tensor::loadFromFile(FILE* f) {
  TensorSize s = TensorSize::loadFromFile(f);
  Tensor t(s);
  fread(t.getPointer(), sizeof(float) * t.data.size(), 1, f);
  return t;
}

void Tensor::setRows(size_t rows, bool shrinkToFit) {
  size.setRows(rows);
  data.resize(size.getElementsNum());
  if (shrinkToFit)
    data.shrink_to_fit();
}

void Tensor::reshape(std::vector<size_t> size_) {
  size_t newRowSize = 1;
  for (size_t i : size_)
    newRowSize *= i;
  assertIsEqual(getRowSize(), newRowSize);
  size_.push_back(getRowsNum());
  size = TensorSize(size_);
}

Tensor& Tensor::operator=(const Tensor& t) {
  Tensor::copy(t, *this);
  return *this;
}

Tensor::Tensor(const Tensor& t) {
  Tensor::copy(t, *this);
}

void Tensor::copy(const Tensor& src, Tensor& dest) {
  dest.data = src.data;
  dest.size = src.size;
}

void Tensor::copyData(const Tensor& src) {
  assertIsEqual(getRowSize(), src.getRowSize());
  assertIsEqual(getRowsNum(), src.getRowsNum());
  std::copy(src.data.begin(), src.data.end(), data.begin());
}

Tensor::Tensor() {}

Tensor::Tensor(const TensorSize& size_)
  : size(size_)
  , data(size_.getElementsNum()) {
  data.shrink_to_fit();
}

Tensor::Tensor(const std::vector<size_t>& size_)
  : size(TensorSize(size_))
  , data(size.getElementsNum()) {
  data.shrink_to_fit();
}

Tensor Tensor::createWithShape(const std::vector<size_t>& shape, size_t rows) {
  std::vector<size_t> s(shape);
  s.push_back(rows);
  return Tensor(s);
}

Tensor Tensor::createWithShape(const Tensor& t, size_t rows) {
  TensorSize s(t.getSize());
  s.setRows(rows);
  return Tensor(s);
}

Tensor::Tensor(const Tensor& t, size_t index, size_t rows) {
  size = t.size;
  size.setRows(rows);
  data = vector<float>(size.getElementsNum());
  data.shrink_to_fit();
	std::copy(t.data.begin() + t.size.getElementPos(0, index),
    t.data.begin() + t.size.getElementPos(0, index + rows),
		data.begin());
}

struct SqrtFunctor {
  float operator()(float& x) const { return sqrt(x); }
};


void Tensor::sqrt() {
  std::transform(data.begin(), data.begin() + getElementsNum(),
                    data.begin(), SqrtFunctor());
}

struct WeightedAddFunctor {
  const float a;
  const float b;
  WeightedAddFunctor(float _a, float _b) : a(_a), b(_b) {}
  float operator()(const float& x, const float& y) const {
    return a * x + y * b;
  }
};

void Tensor::addElementWise(const float alpha, const Tensor& t, const float beta) {
	assertIsEqual(t.getElementsNum(), getElementsNum());
	std::transform(data.begin(),
		data.begin() + getElementsNum(),
		t.data.begin(), data.begin(),
		WeightedAddFunctor(alpha, beta));
}

void Tensor::mulElementWise(const Tensor& b, Tensor& out) const {
	assertIsEqual(b.getElementsNum(), getElementsNum());
	assertIsEqual(out.getElementsNum(), getElementsNum());
	std::transform(data.begin(),
		data.begin() + getElementsNum(),
		b.data.begin(), out.data.begin(),
		std::multiplies<float>());
}


void Tensor::divElementWise(const Tensor& b, Tensor& out) const {
	assertIsEqual(b.getElementsNum(), getElementsNum());
	assertIsEqual(out.getElementsNum(), getElementsNum());
	std::transform(data.begin(),
		data.begin() + getElementsNum(),
		b.data.begin(), out.data.begin(),
		std::divides<float>());
}

struct MultiplyByConstantFunctor {
  const float a;
  MultiplyByConstantFunctor(float _a) : a(_a) {}
  float operator()(float& x) const { return x * a; }
};


void Tensor::mul(const float a) {
  std::transform(data.begin(), data.end(), data.begin(),
                    MultiplyByConstantFunctor(a));
}

struct AddConstantFunctor {
  const float a;
  AddConstantFunctor(float _a) : a(_a) {}
  float operator()(float& x) const { return x + a; }
};


void Tensor::add(const float a) {
  std::transform(data.begin(), data.end(), data.begin(),
                    AddConstantFunctor(a));
}


std::ostream& operator<<(std::ostream& os, const Tensor& t) {
  if (t.getSize().getDimensionNum() == 0) return os;
  if (t.getSize().getDimensionNum() == 1) {
    size_t last = t.getElementsNum() - 1;
    for (size_t x = 0; x <= last; ++x) {
      os << t.val(x);
      if (x < last)
        os << ' ';
    }
    os << std::endl;
  } else {
    size_t last = t.getRowSize() - 1;
    for (size_t y = 0; y < t.getRowsNum(); ++y) {
      for (size_t x = 0; x <= last; ++x) {
        os << t.val(x, y);
        if (x < last)
          os << ' ';
      }
      if (y < t.getRowsNum() - 1)
        os << std::endl;
    }
  }
  return os;
}

}; // namespace Zerg