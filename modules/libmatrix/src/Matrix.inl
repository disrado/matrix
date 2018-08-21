namespace details
{

template<typename T>
using StackOfCircles = std::stack<std::vector<T>>;

template<typename T>
void shiftCircle(std::vector<T>& circle, int offset)
{
	if (circle.size() == offset) {
		return;
	} else if (std::abs(offset) > circle.size()) {
		offset = circle.size() % offset;
	}

	if (offset > 0) {
		std::rotate(circle.begin(), circle.end() - offset, circle.end());
	} else if (offset < 0) {
		std::rotate(circle.begin(), circle.begin() + std::abs(offset), circle.end());
	}
}

template<typename T>
Matrix<T> buildMatrixFromCircles(StackOfCircles<T> circles, const size_t matirxSize)
{
	Matrix<T> resultMatrix(matirxSize);

	while (!circles.empty())
	{
		const size_t circleNum = circles.size() - 1,
					 rowOffset = circleNum,
					 colOffset = circleNum + 1;

		const auto& currentCircle = circles.top();

		const size_t maxIdx = matirxSize - 1;

		size_t counter = 0;

		for (size_t row = 0; row < matirxSize - rowOffset * 2; ++row) {
			resultMatrix(circleNum, rowOffset + row) = currentCircle[counter++];
		}
		
		for (size_t row = 0; row < matirxSize - colOffset * 2; ++row) {
			resultMatrix(colOffset + row, maxIdx - circleNum) = currentCircle[counter++];
		}

		for (size_t row = 0; row < matirxSize - rowOffset * 2; ++row) {
			resultMatrix(maxIdx - circleNum, maxIdx - circleNum - row) = currentCircle[counter++];
		}

		for (size_t row = 0; row < matirxSize - colOffset * 2; ++row) {
			resultMatrix(maxIdx - colOffset - row, circleNum) = currentCircle[counter++];
		}

		circles.pop();
	}

	return resultMatrix;
}

template<typename T>
size_t getSizeOfLongestSameElementsSet(const std::vector<T>& row)
{
	size_t sizeOfSet = 1;
	size_t sizeOfLongestSet = 0;

	for (size_t col = 0; col < row.size() - 1; ++col)
	{
		if (row[col] == row[col + 1]) 
		{
			sizeOfSet++;
		}
		else 
		{
			if (sizeOfSet > sizeOfLongestSet) {
				sizeOfLongestSet = sizeOfSet;
			}
			sizeOfSet = 1;
		}
	}

	if (sizeOfSet > sizeOfLongestSet) {
		sizeOfLongestSet = sizeOfSet;
	}

	return sizeOfLongestSet;
}

} //! namespace details

template<typename T>
Matrix<T>::Matrix(const size_t size)
	: size_(size)
	, matrix_(Matrix<T>::Vector2d<T>(size, std::vector<T>(size)))
{ }

template<typename T>
Matrix<T>::Matrix(const Matrix<T>::Vector2d<T>& matrix)
{
	for (const auto& row : matrix)
	{
		if (matrix.size() != row.size()) {
			throw std::logic_error("Matrix must be square");
		}
	}
	size_ = matrix.size();
	matrix_ = matrix;
}

template<typename T>
size_t Matrix<T>::Size() const
{
	return size_;
}

template<typename T>
const std::vector<T> Matrix<T>::Column(const uint64_t columnIndex) const
{
	std::vector<T> column;

	for (size_t row = 0; row < size_; ++row) {
		column.push_back(matrix_[row][columnIndex]);
	}

	column.shrink_to_fit();

	return column;
}

template<typename T>
void Matrix<T>::ReplaceRow(const size_t rowIndex, const std::vector<T>& newRow)
{
	if (newRow.size() != size_){
		throw std::logic_error("Row must have same size");
	}

	matrix_[rowIndex] = newRow;
}

template<typename T>
void Matrix<T>::ReplaceColumn(const size_t columnIndex, const std::vector<T>& newColumn)
{
	if (newColumn.size() != size_){
		throw std::logic_error("Row must have same size");
	}
	
	for (size_t row = 0; row < size_; ++row) {
		matrix_[row][columnIndex] = newColumn[row];
	}
}

template<typename T>
uint32_t Matrix<T>::GetLocalMinimums() const
{
	uint32_t localMinsCount = 0;

	for (size_t row = 0; row < size_; ++row)
	{
		for (size_t col = 0; col < size_; ++col)
		{
			const bool 
				isLeftCellLess = row > 0 && matrix_[row - 1][col] <= matrix_[row][col],
				isRightCellLess = row < size_ - 1 && matrix_[row + 1][col] <= matrix_[row][col],
				isUpperCellLess = col < size_ - 1 && matrix_[row][col + 1] <= matrix_[row][col],
				isLowerCellLess = col > 0 && matrix_[row][col - 1] <= matrix_[row][col];

			if (isLeftCellLess || isRightCellLess || isUpperCellLess || isLowerCellLess) {
				continue;
			}	
			localMinsCount++;
		}
	}

	return localMinsCount;
}

template<typename T>
int64_t Matrix<T>::GetSumOverMainDiagonal() const
{
	int64_t sum = 0;

	for (size_t row = 0; row < size_; ++row)
	{
		for (size_t col = row + 1; col < size_; ++col) {
			sum += matrix_[row][col];
		}
	}

	return sum;
}

template<typename T>
std::map<size_t, T> Matrix<T>::GetMultiplicationsOfPositiveRows() const
{
	std::map<size_t, T> multiplications;

	for (size_t row = 0; row < size_; ++row)
	{
		const auto cellIsPositive = [] (const T& cell) -> bool {
				return cell > 0; 
		};

		const bool rowIsPositive = std::all_of(
			matrix_[row].begin(),
			matrix_[row].end(),
			cellIsPositive);

		if (rowIsPositive)
		{
			T multiplicationOfRow = 1;

			for (const auto& cell : matrix_[row]) {
				multiplicationOfRow *= cell;
			}

			multiplications.insert(std::make_pair(row, multiplicationOfRow));
		}
	}

	return multiplications;
}

template<typename T>
size_t Matrix<T>::GetRowNumWithLongestSet() const
{
	size_t sizeOfLongestSet = 0;
	size_t numberOfRow = 0;
 
	for (size_t row = 0; row < size_; ++row)
	{
		const size_t size = details::getSizeOfLongestSameElementsSet(matrix_[row]);

		if (size > sizeOfLongestSet) {
			sizeOfLongestSet = size;
			numberOfRow = row;
		}
	}

	return numberOfRow;
}

template<typename T>
T& Matrix<T>::operator()(const size_t rowIndex, const size_t columnIndex)
{
	return matrix_[rowIndex][columnIndex];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](const size_t rowIndex) const
{
	return matrix_[rowIndex];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& matrix) const
{
	return matrix_ == matrix.matrix_;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T>& matrix) const
{
	return matrix_ != matrix.matrix_;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& matrix)
{
	if (size_ != matrix.size_) {
		throw std::logic_error("Matrix must have same size");
	}

	for (size_t row = 0; row < size_; ++row)
	{
		for (size_t col = 0; col < size_; ++col) {
			matrix_[row][col] += matrix.matrix_[row][col];
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& matrix)
{
	if (size_ != matrix.size_) {
		throw std::logic_error("Matrix must have same size");
	}

	for (size_t row = 0; row < size_; ++row)
	{
		for (size_t col = 0; col < size_; ++col) {
			matrix_[row][col] -= matrix.matrix_[row][col];
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& matrix)
{
	if (size_ != matrix.size_) {
		throw std::logic_error("Matrix must have same size");
	}

	Matrix<T> result(size_);

	for (int row = 0; row < size_; ++row)
	{
		for (int col = 0; col < size_; ++col)
		{
			for (int inner = 0; inner < size_; ++inner) {
				result.matrix_[row][col] += matrix_[row][inner] * matrix.matrix_[inner][col];
			}
		}
	}

	std::swap(*this, std::move(result));

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(T multiplier)
{
	for (size_t row = 0; row < size_; ++row)
	{
		for (size_t col = 0; col < size_; ++col) {
			matrix_[row][col] *= multiplier;
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(T divider)
{
	for (size_t row = 0; row < size_; ++row)
	{
		for (size_t col = 0; col < size_; ++col) {
			matrix_[row][col] /= divider;
		}
	}

	return *this;
}

template<typename T>
const Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	Matrix<T> result(lhs);

	return result += rhs;
}

template<typename T>
const Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	Matrix<T> result(lhs);

	return result -= rhs;
}

template<typename T>
const Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	Matrix<T> result(lhs);

	return result *= rhs;
}

template<typename T>
const Matrix<T> operator*(const Matrix<T>& matrix, T multiplier)
{
	Matrix<T> result(matrix);

	return result *= multiplier;
}

template<typename T>
const Matrix<T> operator/(const Matrix<T>& matrix, T divider)
{
	Matrix<T> result(matrix);

	return result /= divider;
}

template<typename T>
Matrix<T> ShiftMatrix(const Matrix<T>& matrix, const int shiftSize)
{
	if (shiftSize == 0) {
		return Matrix<T>(matrix);
	}

	details::StackOfCircles<T> circles;

	for (size_t i = 0; i < matrix.Size() / 2; ++i)
	{
		const auto& topRow = matrix[i];
		const auto& rightCol = matrix.Column(matrix.Size() - 1 - i);
		const auto& bottomRow = matrix[matrix.Size() - 1 - i];
		const auto& leftCol = matrix.Column(i);

		const size_t rowOffset = i;
		const size_t colOffset = i + 1;

		std::vector<T> circle;
		circle.insert(circle.end(), topRow.cbegin() + rowOffset, topRow.cend() - rowOffset);
		circle.insert(circle.end(), rightCol.cbegin() + colOffset, rightCol.cend() - colOffset);
		circle.insert(circle.end(), bottomRow.crbegin() + rowOffset, bottomRow.crend() - rowOffset);
		circle.insert(circle.end(), leftCol.crbegin() + colOffset, leftCol.crend() - colOffset);

		details::shiftCircle(circle, shiftSize);

		circles.push(circle);
	}

	auto resultMatrix = details::buildMatrixFromCircles(std::move(circles), matrix.Size());

	if (matrix.Size() % 2 > 0) {
		size_t middle = matrix.Size() / 2;
		resultMatrix(middle, middle) = matrix[middle][middle];
	}

	return resultMatrix;
}

template<typename T>
void PrintMatrix(const Matrix<T>& matrix)
{
	for (size_t row = 0; row < matrix.Size(); ++row)
	{
		for (size_t col = 0; col < matrix.Size(); ++col) {
			std::cout << " " << matrix[row][col];
		}
		std::cout << std::endl;
	}
}