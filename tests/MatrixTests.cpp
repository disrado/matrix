#ifdef WIN32
#pragma warning(push)
// warning C4996: 'std::tr1': warning STL4002: The non-Standard st
// d::tr1 namespace and TR1-only machinery are deprecated and will be REMOVED
#pragma warning(disable : 4996)
#endif

#include <gtest/gtest.h>

#ifdef WIN32
#pragma warning(pop)
#endif

#include <matrix/Matrix.h>

#include <iostream>
#include <map>

const std::vector<std::vector<int64_t>> mtrx = {
	{-1, 1, 2, 3, 4, 5, 6, 7, 8,-1 }, //0/ 2 local minimums here
	{ 1, 1,-1, 3, 4, 5, 6, 7, 8, 9 }, //1/ local minimum here
	{ 1, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, //2/ row is positive, multiplication: 362'880
	{ 1, 1, 2, 3, 4,-2, 6, 7, 8, 9 }, //3/ local minimum here
	{ 1, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, //4/ row is positive, multiplication: 362'880
	{ 1, 1, 2, 3, 4, 5, 6, 7, 7, 7 }, //5/ row is positive, multiplication: 246'960
	{ 1, 1, 1, 1, 4, 5, 6, 7, 8,-1 }, //6/ local minimum here
	{ 2, 2, 1, 1, 1, 1, 1, 1,-5, 9 }, //7/ local minimum here
	{ 1, 1, 2, 3, 4, 5, 6, 7, 8, 8 }, //8/ row is positive, multiplication: 322'560
	{-1, 1, 2, 3, 4, 5, 6, 7, 8,-1 }, //9/ 2 local minimums here
};

const uint32_t ValidNumberOfMins = 8;
const int64_t ValidSumOverMainDiagonal = 238;
const std::map<size_t, int64_t> ValidMultiplicationsOfPositiveRows = {
	{2, (int)362'880},
	{4, (int)362'880},
	{5, (int)246'960},
	{8, (int)322'560},
};
const uint32_t VaildNumberOfRowWithLongestSameElementsSet = 7;

TEST(Matrix, Constructor)
{
	const matrix::Matrix<int64_t> mtx(mtrx);

	ASSERT_EQ(mtrx.size(), mtx.Size());

	for (uint32_t row = 0; row < mtrx.size(); ++row)
	{
		for (uint32_t col = 0; col < mtrx.size(); ++col ) {
			ASSERT_EQ(mtrx[row][col], mtx[row][col]);
		}
	}
}

TEST(Matrix, ConstructorWithInvalidMatrix)
{
	const std::vector<std::vector<int32_t>> rectangleMatrix = {
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
	};

	ASSERT_THROW(matrix::Matrix<int32_t> mtx(rectangleMatrix), std::logic_error);
}

TEST(Matrix, Column)
{
	const matrix::Matrix<int64_t> mtx(mtrx);

	const std::vector<int64_t> validColumn = { 8, 8, 8, 8, 8, 7, 8, -5, 8, 8 };
	const std::vector<int64_t> column = mtx.Column(8);

	ASSERT_EQ(column, validColumn);
}

TEST(Matrix, ReplaceRow)
{
	const std::vector<int64_t> newRow = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };

	matrix::Matrix<int64_t> mtx(mtrx);
	
	mtx.ReplaceRow(0, newRow);

	ASSERT_EQ(mtx[0], newRow);

	const std::vector<int64_t> newInvalidRow = { 4, 4, 4, 4 };
	
	ASSERT_THROW(mtx.ReplaceRow(0, newInvalidRow), std::logic_error);
}

TEST(Matrix, ReplaceColumn)
{
	const std::vector<int64_t> newColumn = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };

	matrix::Matrix<int64_t> mtx(mtrx);
	
	mtx.ReplaceColumn(0, newColumn);

	ASSERT_EQ(mtx.Column(0), newColumn);

	const std::vector<int64_t> newInvalidColumn= { 4, 4, 4, 4 };
	
	ASSERT_THROW(mtx.ReplaceColumn(0, newInvalidColumn), std::logic_error);
}

TEST(Matrix, GetLocalMinimums)
{
	const matrix::Matrix<int64_t> mtx(mtrx);

	const uint32_t computedMins = mtx.GetLocalMinimums();

	ASSERT_EQ(computedMins, ValidNumberOfMins);
}

TEST(Matrix, GetSumOverMainDiagonal)
{
	const matrix::Matrix<int64_t> mtx(mtrx);

	const int64_t computedSum = mtx.GetSumOverMainDiagonal();

	ASSERT_EQ(computedSum, ValidSumOverMainDiagonal);
}

TEST(Matrix, GetMultiplicationsOfPositiveRows)
{
	const matrix::Matrix<int64_t> mtx(mtrx);

	const auto computedMultiplications = mtx.GetMultiplicationsOfPositiveRows();

	ASSERT_EQ(computedMultiplications, ValidMultiplicationsOfPositiveRows);
}

TEST(Matrix, GetRowNumWithLongestSet)
{
	const matrix::Matrix<int64_t> mtx(mtrx);

	const auto rowNumber = mtx.GetRowNumWithLongestSet();

	ASSERT_EQ(rowNumber, VaildNumberOfRowWithLongestSameElementsSet);
}

TEST(Matrix, OperatorCircleBraces)
{
	const std::vector<std::vector<int32_t>> mtxTemplate = {
		{ 1, 254 },
		{ 2,   4 }
	};

	matrix::Matrix<int32_t> matrix(mtxTemplate);

	ASSERT_EQ(matrix(0, 1), 254);

	matrix(0, 1) = 128;

	ASSERT_EQ(matrix(0, 1), 128);
}

TEST(Matrix, OperatorSquareBraces)
{
	const std::vector<std::vector<int32_t>> mtxTemplate = {
		{ 1, 254 },
		{ 2,   4 }
	};

	const matrix::Matrix<int32_t> matrix(mtxTemplate);

	ASSERT_EQ(matrix[0][1], 254);
}

TEST(Matrix, OperatorEqual)
{
	const std::vector<std::vector<int32_t>> mtxTemplate_1 = {
		{ 11, 12, 24 },
		{ 81, 16, 32 },
		{ 13, 25, 96 }
	};

	const std::vector<std::vector<int32_t>> mtxTemplate_2 = mtxTemplate_1;

	const matrix::Matrix<int32_t> matrix_1(mtxTemplate_1);
	const matrix::Matrix<int32_t> matrix_2(mtxTemplate_2);

	ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(Matrix, OperatorNotEqual)
{
	const std::vector<std::vector<int32_t>> mtxTemplate_1 = {
		{ 11, 12, 24 },
		{ 81, 16, 32 },
		{ 13, 25, 96 }
	};

	const std::vector<std::vector<int32_t>> mtxTemplate_2 = {
		{ 11, 12, 24 },
		{ 81, 16, 32 },
		{ 13,  0, 96 }
	};

	const matrix::Matrix<int32_t> matrix_1(mtxTemplate_1);
	const matrix::Matrix<int32_t> matrix_2(mtxTemplate_2);

	ASSERT_TRUE(matrix_1 != matrix_2);
}

TEST(Matrix, OperatorAddAndAssign)
{
	const std::vector<std::vector<int32_t>> mtxTemplate_1 = {
		{ 1,-1 },
		{ 1, 1 }
	};

	const std::vector<std::vector<int32_t>> mtxTemplate_2 = {
		{ 1, 1 },
		{ 1,-1 }
	};

	const std::vector<std::vector<int32_t>> validMatrix = {
		{ 2, 0 },
		{ 2, 0 }
	};

	matrix::Matrix<int32_t> matrix_1(mtxTemplate_1);
	const matrix::Matrix<int32_t> matrix_2(mtxTemplate_2);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);

	matrix_1 += matrix_2;

	ASSERT_EQ(matrix_1, validResultMatrix);

	const std::vector<std::vector<int32_t>> invalidMtx = {
		{ 2, 0, 3 },
		{ 2, 0, 3 },
		{ 2, 0, 3 }
	};

	const matrix::Matrix<int32_t> invalidMatrix(invalidMtx);

	ASSERT_THROW(matrix_1 += invalidMatrix, std::logic_error);
}

TEST(Matrix, OperatorSubtractAndAssign)
{
	const std::vector<std::vector<int32_t>> mtxTemplate_1 = {
		{ 1, 2 },
		{ 1, 2 }
	};

	const std::vector<std::vector<int32_t>> mtxTemplate_2 = {
		{ 1, 1 },
		{ 1, 1 }
	};

	const std::vector<std::vector<int32_t>> validMatrix = {
		{ 0, 1 },
		{ 0, 1 }
	};

	matrix::Matrix<int32_t> matrix_1(mtxTemplate_1);
	const matrix::Matrix<int32_t> matrix_2(mtxTemplate_2);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);

	matrix_1 -= matrix_2;

	ASSERT_EQ(matrix_1, validResultMatrix);

	const std::vector<std::vector<int32_t>> invalidMtx = {
		{ 2, 0, 3 },
		{ 2, 0, 3 },
		{ 2, 0, 3 }
	};

	const matrix::Matrix<int32_t> invalidMatrix(invalidMtx);

	ASSERT_THROW(matrix_1 -= invalidMatrix, std::logic_error);
}

TEST(Matrix, OperatorMultiplyAndAssign)
{
	const std::vector<std::vector<int32_t>> mtxTemplate_1 = {
		{ 4, 2 },
		{ 9, 0 }
	};

	const std::vector<std::vector<int32_t>> mtxTemplate_2 = {
		{ 3, 1 },
		{-3, 4 }
	};

	const std::vector<std::vector<int32_t>> validMatrix = {
		{  6, 12 },
		{ 27,  9 }
	};

	matrix::Matrix<int32_t> matrix_1(mtxTemplate_1);
	const matrix::Matrix<int32_t> matrix_2(mtxTemplate_2);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);

	matrix_1 *= matrix_2;

	ASSERT_EQ(matrix_1, validResultMatrix);

	const std::vector<std::vector<int32_t>> invalidMtx = {
		{ 2, 0, 3 },
		{ 2, 0, 3 },
		{ 2, 0, 3 }
	};
	
	const matrix::Matrix<int32_t> invalidMatrix(invalidMtx);

	ASSERT_THROW(matrix_1 *= invalidMatrix, std::logic_error);
}

TEST(Matrix, OperatorMultiplyByNumAndAssign)
{
	const std::vector<std::vector<int32_t>> mtxTemplate = {
		{-1, 2 },
		{ 1,-2 }
	};

	const int32_t multiplier = -5;

	const std::vector<std::vector<int32_t>> validMatrix = {
		{ 5,-10 },
		{-5, 10 }
	};

	matrix::Matrix<int32_t> matrix(mtxTemplate);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);

	matrix *= multiplier;

	ASSERT_EQ(matrix, validResultMatrix);
}

TEST(Matrix, OperatorDivideAndAssign)
{
	const std::vector<std::vector<int32_t>> mtxTemplate = {
		{ 10, -20 },
		{-10,  20 }
	};

	const int32_t divider = -5;

	const std::vector<std::vector<int32_t>> validMatrix = {
		{-2, 4 },
		{ 2,-4 }
	};

	matrix::Matrix<int32_t> matrix(mtxTemplate);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);

	matrix /= divider;

	ASSERT_EQ(matrix, validResultMatrix);
}

TEST(Matrix, AdditionOfMatrices)
{
	const std::vector<std::vector<int32_t>> mtxTemplate_1 = {
		{ 1,-1 },
		{ 1, 1 }
	};

	const std::vector<std::vector<int32_t>> mtxTemplate_2 = {
		{ 1, 1 },
		{ 1,-1 }
	};

	const std::vector<std::vector<int32_t>> validMatrix = {
		{ 2, 0 },
		{ 2, 0 }
	};

	const matrix::Matrix<int32_t> matrix_1(mtxTemplate_1);
	const matrix::Matrix<int32_t> matrix_2(mtxTemplate_2);

	const matrix::Matrix<int32_t> resultMatrix(matrix_1 + matrix_2);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);

	ASSERT_EQ(resultMatrix, validResultMatrix);
}

TEST(Matrix, SubtractionOfMatrices)
{
	const std::vector<std::vector<int32_t>> mtxTemplate_1 = {
		{ 1, 2 },
		{ 1, 2 }
	};

	const std::vector<std::vector<int32_t>> mtxTemplate_2 = {
		{ 1, 1 },
		{ 1, 1 }
	};

	const std::vector<std::vector<int32_t>> validMatrix = {
		{ 0, 1 },
		{ 0, 1 }
	};

	const matrix::Matrix<int32_t> matrix_1(mtxTemplate_1);
	const matrix::Matrix<int32_t> matrix_2(mtxTemplate_2);

	const matrix::Matrix<int32_t> resultMatrix(matrix_1 - matrix_2);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);

	ASSERT_EQ(resultMatrix, validResultMatrix);
}

TEST(Matrix, MultiplicationOfMatrices)
{
	const std::vector<std::vector<int32_t>> mtxTemplate_1 = {
		{ 4, 2 },
		{ 9, 0 }
	};

	const std::vector<std::vector<int32_t>> mtxTemplate_2 = {
		{ 3, 1 },
		{-3, 4 }
	};

	const std::vector<std::vector<int32_t>> validMatrix = {
		{ 6, 12 },
		{ 27, 9 }
	};

	const matrix::Matrix<int32_t> matrix_1(mtxTemplate_1);
	const matrix::Matrix<int32_t> matrix_2(mtxTemplate_2);

	const matrix::Matrix<int32_t> resultMatrix(matrix_1 * matrix_2);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);
	
	ASSERT_EQ(resultMatrix, validResultMatrix);
}

TEST(Matrix, MultiplicationMatrixByNum)
{
	const std::vector<std::vector<int32_t>> mtxTemplate = {
		{-1, 2 },
		{ 1,-2 }
	};

	const int32_t multiplier = -5;

	const std::vector<std::vector<int32_t>> validMatrix = {
		{ 5,-10 },
		{-5, 10 }
	};

	const matrix::Matrix<int32_t> sourceMatrix(mtxTemplate);

	const matrix::Matrix<int32_t> resultMatrix(sourceMatrix * multiplier);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);

	ASSERT_EQ(resultMatrix, validResultMatrix);
}

TEST(Matrix, DivisionOfMatrix)
{
	const std::vector<std::vector<int32_t>> mtxTemplate = {
		{ 10, -20 },
		{-10,  20 }
	};

	const int32_t divider = -5;

	const std::vector<std::vector<int32_t>> validMatrix = {
		{-2, 4 },
		{ 2,-4 }
	};

	const matrix::Matrix<int32_t> sourceMatrix(mtxTemplate);

	const matrix::Matrix<int32_t> resultMatrix(sourceMatrix / divider);
	const matrix::Matrix<int32_t> validResultMatrix(validMatrix);

	ASSERT_EQ(resultMatrix, validResultMatrix);
}

TEST(MatrixNonClassFunction, ShiftMatrix)
{
	std::vector<std::vector<uint32_t>> mtxTemplate_1 = {
		{ 24, 65, 46, 21, 11 },
		{ 12, 96, 25, 14, 12 },
		{ 11, 32, 16, 96, 13 },
		{ 81, 13, 18, 25, 14 },
		{ 84, 13, 12, 21, 15 }
	};

	std::vector<std::vector<uint32_t>> positiveShiftedMatrix = {
		{ 11, 12, 24, 65, 46 },
		{ 81, 13, 32, 96, 21 },
		{ 84, 18, 16, 25, 11 },
		{ 13, 25, 96, 14, 12 },
		{ 12, 21, 15, 14, 13 }
	};

	const std::vector<std::vector<uint32_t>> negativeShiftedMatrix = {
		{ 46, 21, 11, 12, 13 },
		{ 65, 14, 96, 25, 14 },
		{ 24, 25, 16, 18, 15 },
		{ 12, 96, 32, 13, 21 },
		{ 11, 81, 84, 13, 12 }
	};

	matrix::Matrix<uint32_t> matrix(mtxTemplate_1);
	int8_t positiveOffset = 2;
	const int8_t negativeOffset = -2;

	matrix::Matrix<uint32_t> resulMatrix = matrix::ShiftMatrix(matrix, positiveOffset);
	matrix::Matrix<uint32_t> validMatrixWithPositiveShift(positiveShiftedMatrix);

	ASSERT_EQ(resulMatrix, validMatrixWithPositiveShift);

	resulMatrix = matrix::ShiftMatrix(matrix, negativeOffset);
	const matrix::Matrix<uint32_t> validMatrixWithNegativeShift(negativeShiftedMatrix);

	ASSERT_EQ(resulMatrix, validMatrixWithNegativeShift);

	// Checking with zero shift size
	positiveOffset = 0;
	resulMatrix = matrix::ShiftMatrix(matrix, positiveOffset);
	ASSERT_EQ(resulMatrix, matrix);

	// Checking with shift size which equal to circle size
	positiveOffset = 16;
	resulMatrix = matrix::ShiftMatrix(matrix, positiveOffset);
	ASSERT_EQ(resulMatrix, matrix);

	// Checking with shift size which greater then circle size
	positiveOffset = 18;
	resulMatrix = matrix::ShiftMatrix(matrix, positiveOffset);
	ASSERT_EQ(resulMatrix, validMatrixWithPositiveShift);
}

TEST(MatrixNonClassFunction, PrintMatrix)
{
	const std::vector<std::vector<int32_t>> mtx = {
		{ 0, 1 },
		{ 2, 4 }
	};

	const matrix::Matrix<int32_t> matrix(mtx);

	matrix::PrintMatrix(matrix);
}