#pragma once

#include <algorithm>
#include <map>
#include <stack>
#include <vector>

namespace matrix
{

template<typename T>
class Matrix final
{
	//
	// Alias declaration.
	//
public:
	//! The two dimensional matrix from two std::vectors.
	template<typename T>
	using Vector2d = std::vector<std::vector<T>>;

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	explicit Matrix(const size_t size);
	//! Constructor.
	explicit Matrix(const Vector2d<T>& matrix);

	//
	// Public interface.
	//
public:
	//! Returns the size of matrix.
	size_t Size() const;
	//! Returns the column of matrix.
	const std::vector<T> Column(size_t columnIndex) const;
	//! Replaces the row of matrix.
	void ReplaceRow(const size_t rowIndex, const std::vector<T>& newRow);
	//! Replaces the column of matrix.
	void ReplaceColumn(const size_t columnIndex, const std::vector<T>& newColumn);
	//! Returns the number of local minimums.
	uint32_t GetLocalMinimums() const;
	//! Returns the sum of elements which situated over main diagonal.
	int64_t GetSumOverMainDiagonal() const;
	//! Returns the multiplication of elements in such rows, which don't contain negative elements.
	//! map contains pairs with number of row and multiplication of this string.
	std::map<size_t, T> GetMultiplicationsOfPositiveRows() const;
	//! Returns the number of row, which contains the longest set of identical elements.
	size_t GetRowNumWithLongestSet() const;
	//! Returns the element of matrix.
	T& operator()(const size_t rowIndex, const size_t columnIndex);
	//! Returns the element of matrix.
	const std::vector<T>& operator[](const size_t rowIndex) const;
	//! Operator equal.
	bool operator==(const Matrix<T>& matrix) const;
	//! Operator not equal.
	bool operator!=(const Matrix<T>& matrix) const;
	//! Adds matrix to matrix.
	Matrix<T>& operator+=(const Matrix<T>& matrix);
	//! Subtracts matrix from matrix.
	Matrix<T>& operator-=(const Matrix<T>& matrix);
	//! Multiplies matrix by matrix.
	Matrix<T>& operator*=(const Matrix<T>& matrix);
	//! Multiplies matrix by number.
	Matrix<T>& operator*=(const T multiplier);
	//! Divides matrix by number.
	Matrix<T>& operator/=(const T divider);

	//
	// Private data members.
	//
private:
	//! Size of matrix.
	size_t size_;
	//! Matrix.
	Vector2d<T> matrix_;
};

//! Adds two matrices and return result of operation.
template<typename T>
const Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs);

//! Subtracts two matrices and return result of operation.
template<typename T>
const Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs);

//! Multiplies two matrices and return result of operation.
template<typename T>
const Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs);

//! Multiplies matrix by number and return result of operation.
template<typename T>
const Matrix<T> operator*(const Matrix<T>& matrix, const T multiplier);

//! Divides matrix by number matrices and return result of operation.
template<typename T>
const Matrix<T> operator/(const Matrix<T>& matrix, const T divider);

//! Shifts elements of matrix.
template<typename T>
Matrix<T> ShiftMatrix(const Matrix<T>& matrix, const int shiftSize);

//! Prints object of class Matrix to std::cout.
template<typename T>
void PrintMatrix(const Matrix<T>& matrix);

#include "../../src/Matrix.inl"

} // namespace matrix