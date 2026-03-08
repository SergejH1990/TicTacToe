
#include "tttGameController.h"

using namespace Logic;

TTTGameController::TTTGameController(std::shared_ptr<TTTGameState>& gameState, QObject* parent) :
super(parent),
currentGameState(gameState),
tcpNetworkManager(nullptr)
{
	InitializeResultMatrix();
	tcpNetworkManager = new Network::TTTNetworkManager(this);
}

TTTGameController::~TTTGameController()
{
}

void TTTGameController::InitializeResultMatrix()
{
	for (auto outerResultIterator = currentGameState->ResultMatrix.begin(); outerResultIterator < currentGameState->ResultMatrix.end(); outerResultIterator++)
	{
		for (auto innerResultIterator = outerResultIterator->begin(); innerResultIterator < outerResultIterator->end(); innerResultIterator++)
		{
			*innerResultIterator = gDefaultMatrixEntry;
		}
	}
}

void TTTGameController::UpdateResultMatrix(const int column, const int row, const int matrixEntry)
{
	currentGameState->ResultMatrix[column][row] = matrixEntry;
}

bool TTTGameController::DidPlayerWinner(const int playerWinSum)
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
	auto& matrix = currentGameState->ResultMatrix;
	for (int index = 0; index < General::gEdgeSize; index++)
	{
		sumDiagonal1 += matrix[index][index];
		sumDiagonal2 += matrix[General::gEdgeSize - index - 1][index];
		sumRow1 += matrix[index][0];
		sumRow2 += matrix[index][1];
		sumRow3 += matrix[index][2];
		sumColumn1 += matrix[0][index];
		sumColumn2 += matrix[1][index];
		sumColumn3 += matrix[2][index];
	}

	// Player won if his unique win sum is included in any of the sums.
	return sumDiagonal1 == playerWinSum || sumDiagonal2 == playerWinSum || sumRow1 == playerWinSum || sumRow2 == playerWinSum ||
			sumRow3 == playerWinSum || sumColumn1 == playerWinSum || sumColumn2 == playerWinSum || sumColumn3 == playerWinSum;
}
