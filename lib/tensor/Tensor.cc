#include "lib/tensor/Tensor.h"

#include <cstdlib>
#include <cstring>

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

Tensor Tensor::createSlice(size_t dim, size_t offset, size_t num) {
  const TensorSize& size = getSize();
  assertIsGreater(size.getDimensionNum(), dim);
  assertIsGreaterOrEqual(size.getDimension(dim), offset);
  assertIsGreaterOrEqual(size.getDimension(dim), offset + num);

  vector<size_t> newSizeV(size.getSize().begin(), size.getSize().end());
  newSizeV[dim] = num;

  Tensor out(newSizeV);
  const TensorSize& newSize = out.getSize();
  size_t lineSize = size.getStride(dim + 1, size.getDimensionNum());
  size_t newLineSize = newSize.getStride(dim + 1, newSize.getDimensionNum());
  size_t lines = getElementsNum() / lineSize;
  size_t end = size.getElementsNum();
  size_t posSrc = size.getStride(dim, size.getDimensionNum()) * offset;
  for (size_t posDst = 0; posSrc < end; posSrc += lineSize, posDst += newLineSize) {
    memcpy(&out.data[posDst], &data[posSrc], sizeof(float) * newLineSize);
  }
  return out;
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

Tensor Tensor::loadCSVFromFile(FILE* f, char delimeter) {
	if (!f) {
		return Tensor();
	}
	char buffer[4096]; // line buffer
	Tensor out({1, 0});
	float a;
	bool firstLine = true;
	unsigned int line = 0;
	while (fscanf(f, "%[^\n]\n", buffer) > 0) {
		unsigned int pos = 0;
		size_t length = strlen(buffer);
		unsigned int n = 0;
		if (!firstLine) {
			out.addRows(1);
      std::fill(out.data.begin() + out.getSize().getElementPos(0, line), out.data.begin() + out.getSize().getElementPos(0, line + 1), 0);
		}
		for (unsigned int i = 0; i < length; ++i) {
			if (buffer[i] == delimeter || i == length - 1) {
				sscanf(buffer + pos, "%f", &a);
				pos = i + 1;
				if (firstLine) {
					out.addRows(1);
					out.val(0, out.getRowsNum() - 1) = a;
				} else {
					out.val(n, line) = a;
				}
				++n;
			}
		}
		if (firstLine) {
      out.size = TensorSize({n, 1});
		}
		++line;
		firstLine = false;
	}
	return out;
}

Tensor Tensor::loadCSVFromFile(const char* filename, char delimeter){
	FILE* f = fopen(filename, "rb");
  assertNotNull(f);
  if (!f) return Tensor();
	Tensor m = loadCSVFromFile(f, delimeter);
	if (f)
		fclose(f);
	return m;
}

}; // namespace Zerg