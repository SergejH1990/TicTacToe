#include <QTest>

// add necessary includes here

#include "Sources/tttGeneral.h"
#include "Sources/tttGameController.h"

class TestWinConditions : public QObject
{
	Q_OBJECT

public:
	TestWinConditions();
	~TestWinConditions();

private:
	std::shared_ptr<Logic::TTTGameState> gameState;
	Logic::TTTGameController* gameController;

private slots:
	void test_case_initial_condition();
};

TestWinConditions::TestWinConditions():
QObject(),
gameState()
{
	gameState = std::make_shared<Logic::TTTGameState>();
	gameController = new Logic::TTTGameController(gameState, this);
}

TestWinConditions::~TestWinConditions()
{
}

void TestWinConditions::test_case_initial_condition()
{
	gameController->InitializeResultMatrix();
	QVERIFY(gameController->DidPlayerWinner(General::gOPlayerWinSum) == false);
	QVERIFY(gameController->DidPlayerWinner(General::gXPlayerWinSum) == false);
	QVERIFY(gameController->DidPlayerWinner(3 * Logic::gDefaultMatrixEntry) == true);
}

QTEST_MAIN(TestWinConditions)

#include "tst_testwinconditions.moc"
