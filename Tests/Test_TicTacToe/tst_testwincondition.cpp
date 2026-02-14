#include <QTest>

// add necessary includes here

#include "Tests/TTGame_Test.h"

class TestWinCondition : public QObject
{
	Q_OBJECT

public:
	TestWinCondition();
	~TestWinCondition();

private:
	TTGame_Test* gameWindow;

private slots:
	void test_case1();
};

TestWinCondition::TestWinCondition(): QObject(),
gameWindow(nullptr)
{
	gameWindow = new TTGame_Test();
}

TestWinCondition::~TestWinCondition()
{
	gameWindow->deleteLater();
}

void TestWinCondition::test_case1()
{
	gameWindow->InitializeGameRound();
	QVERIFY(gameWindow->DidPlayerWinner(gameWindow->GetFieldButton(0)) == false);
}

QTEST_MAIN(TestWinCondition)

#include "tst_testwincondition.moc"
