#ifndef LIB_TENSOR_TENSOR_H
#define LIB_TENSOR_TENSOR_H

#include "lib/assert/Assert.h"
#include "lib/tensor/TensorSize.h"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

namespace Zerg {

class Tensor {
public:
  TensorSize size;
	std::vector<float> data;
public:
/* CONSTRUCTORS */
  // Creates tensor of given size.
  Tensor(const TensorSize& size);
  Tensor(const std::vector<size_t>& size_);

  // Creates tensor which rows are subset of given tensor
  Tensor(const Tensor& t, size_t index, size_t rows);
  
  // Creates tensor with given shape, with 0 rows.
  static Tensor createWithShape(const std::vector<size_t>& shape, size_t rows = 0);
  static Tensor createWithShape(const Tensor& t, size_t rows = 0);

	Tensor(const Tensor& t);
	Tensor& operator=(const Tensor& t);
  Tensor();

/* TENSOR SIZE RELATED FUNCTIONS */
  inline const TensorSize& getSize() const { return size; }
	void setRows(size_t rows, bool shrinkToFit = false);
  void addRows(size_t rows, bool shrinkToFit = false);
  inline size_t getRowsNum() const { return size.getH_2D(); }
  inline size_t getRowSize() const { return size.getDimensionNum() <= 1 ? size.getDimensionNum() : size.getW_2D(); }
  inline size_t getElementsNum() const { return size.getElementsNum(); }
  inline const float* getPointer() const { return &(data[0]); }
	inline float* getPointer() { return &(data[0]); }
  void reshape(std::vector<size_t> size_);

/* VALUE SET/GET*/
  inline float& val(const std::vector<size_t>& index) { return data[size.getElementPos(index)]; }
  inline float& val(size_t x, size_t y, size_t z, size_t w) { return data[size.getElementPos(x, y, z, w)]; }
  inline float& val(size_t x, size_t y, size_t z) { return data[size.getElementPos(x, y, z)]; }
  inline float& val(size_t x, size_t y) { return data[size.getElementPos(x, y)]; }
  inline float& val(size_t x) { return data[size.getElementPos(x)]; }

  inline float val(const std::vector<size_t>& index) const { return data[size.getElementPos(index)]; }
  inline float val(size_t x, size_t y, size_t z, size_t w) const { return data[size.getElementPos(x, y, z, w)]; }
  inline float val(size_t x, size_t y, size_t z) const { return data[size.getElementPos(x, y, z)]; }
  inline float val(size_t x, size_t y) const { return data[size.getElementPos(x, y)]; }
  inline float val(size_t x) const { return data[size.getElementPos(x)]; }
  vector<float>& getData() { return data; }
  const vector<float>& getData() const { return data; }

/* TENSOR MANIPULATION */
  inline void fillWithValue(const float& v) { std::fill(data.begin(), data.end(), v); }
  void copyData(const Tensor& src);

  // Matrix operations
  void addElementWise(const float alpha, const Tensor& t, const float beta);
  void mulElementWise(const Tensor& b, Tensor& out) const;
  void divElementWise(const Tensor& b, Tensor& out) const;

  // Vector operations
  void mulVector(const Tensor& v, Tensor& out) const;
  void addVector(const Tensor& v, Tensor& out) const;

  // Scalar operations
  void add(const float a);
  void mul(const float a);

  // Other but still useful :-)
  void sqrt(); // sqrt on each value

  // Saving / loading.
  void saveToFile(const char* filename) const;
  void saveToFile(FILE* f) const;
  static Tensor loadFromFile(const char* filename);
  static Tensor loadFromFile(FILE* f);
  
  void saveCSV(const char* filename) const;
  void saveCSV(FILE* f) const;
private:
  static void copy(const Tensor& src, Tensor& dest);
};

std::ostream& operator<<(std::ostream& os, const Tensor& t);

}; // namespace Zerg

#endif // LIB_TENSOR_TENSOR_H