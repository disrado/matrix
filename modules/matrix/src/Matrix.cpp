#include <iostream>
#include <matrix/Matrix.h>
#include <vector>

int main()
{
	std::cout << "Enter size of matrix: ";

	uint32_t size = 0;
	std::cin >> size;

	std::cout << std::endl << "Enter elements of matrix: " << std::endl;

	matrix::Matrix<int64_t> matrix(size);

	for (uint32_t row = 0; row < size; ++row)
	{
		for (uint32_t col = 0; col < size; ++col) {
			std::cin >> matrix(row, col);
		}
	}

	uint32_t offset = 0;
	std::cout << std::endl << "Enter size of ofsset: ";
	std::cin >> offset;

	const auto result = matrix::ShiftMatrix(matrix, offset);

	std::cout << std::endl << "Result:" << std::endl;

	for (uint32_t row = 0; row < size; ++row)
	{
		for (uint32_t col = 0; col < size; ++col) {
			std::cout << result[row][col] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}