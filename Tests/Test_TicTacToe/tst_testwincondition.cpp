#include <QTest>

// add necessary includes here

#include "Sources/tttMatchResult.h"

class TestWinCondition : public QObject
{
	Q_OBJECT

public:
	TestWinCondition();
	~TestWinCondition();

private:
	TTTMatchResult matchResult;

private slots:
	void test_case1();
};

TestWinCondition::TestWinCondition(): QObject(),
matchResult()
{
}

TestWinCondition::~TestWinCondition()
{
}

void TestWinCondition::test_case1()
{
	matchResult.InitializeResultMatrix();
	constexpr int OPlayerWon = 6;
	QVERIFY(matchResult.DidPlayerWinner(OPlayerWon) == true);
}

QTEST_MAIN(TestWinCondition)

#include "tst_testwincondition.moc"
