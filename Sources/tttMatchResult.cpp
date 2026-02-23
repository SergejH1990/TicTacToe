#include "tttMatchResult.h"

using namespace Logic;

TTTMatchResult::TTTMatchResult() :
resultMatrix()
{
	InitializeResultMatrix();
}

void TTTMatchResult::InitializeResultMatrix()
{
	for (auto outerResultIterator = resultMatrix.begin(); outerResultIterator < resultMatrix.end(); outerResultIterator++)
	{
		for (auto innerResultIterator = outerResultIterator->begin(); innerResultIterator < outerResultIterator->end(); innerResultIterator++)
		{
			*innerResultIterator = 100;
		}
	}
}

void TTTMatchResult::UpdateResultMatrix(const int column, const int row, const int matrixEntry)
{
	resultMatrix[column][row] = matrixEntry;
}

bool TTTMatchResult::DidPlayerWinner(const int playerWinSum)
{
	int sumDiagonal1 = 0;
	int sumDiagonal2 = 0;
	int sumRow1 = 0;
	int sumRow2 = 0;
	int sumRow3 = 0;
	int sumColumn1 = 0;
	int sumColumn2 = 0;
	int sumColumn3 = 0;

	// Create sums for all rows, columns and diagonals
	for (int index = 0; index < General::gEdgeSize; index++)
	{
		sumDiagonal1 += resultMatrix[index][index];
		sumDiagonal2 += resultMatrix[General::gEdgeSize - index - 1][index];
		sumRow1 += resultMatrix[index][0];
		sumRow2 += resultMatrix[index][1];
		sumRow3 += resultMatrix[index][2];
		sumColumn1 += resultMatrix[0][index];
		sumColumn2 += resultMatrix[1][index];
		sumColumn3 += resultMatrix[2][index];
	}

	// Player won if his unique win sum is included in any of the sums.
	return sumDiagonal1 == playerWinSum || sumDiagonal2 == playerWinSum || sumRow1 == playerWinSum || sumRow2 == playerWinSum ||
			sumRow3 == playerWinSum || sumColumn1 == playerWinSum || sumColumn2 == playerWinSum || sumColumn3 == playerWinSum;
}
