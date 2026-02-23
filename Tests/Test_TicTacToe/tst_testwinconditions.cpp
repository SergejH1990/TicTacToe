#include <QTest>

// add necessary includes here

#include "Sources/tttGeneral.h"
#include "Sources/tttMatchResult.h"

class TestWinConditions : public QObject
{
	Q_OBJECT

public:
	TestWinConditions();
	~TestWinConditions();

private:
	TTTMatchResult matchResult;

private slots:
	void test_case_initial_condition();
};

TestWinConditions::TestWinConditions():
QObject(),
matchResult()
{
}

TestWinConditions::~TestWinConditions()
{
}

void TestWinConditions::test_case_initial_condition()
{
	matchResult.InitializeResultMatrix();
	QVERIFY(matchResult.DidPlayerWinner(General::gOPlayerWinSum) == false);
	QVERIFY(matchResult.DidPlayerWinner(General::gXPlayerWinSum) == false);
}

QTEST_MAIN(TestWinConditions)

#include "tst_testwinconditions.moc"
