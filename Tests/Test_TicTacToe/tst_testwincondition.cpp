#include <QTest>

// add necessary includes here

class TestWinCondition : public QObject
{
	Q_OBJECT

public:
	TestWinCondition();
	~TestWinCondition();

private slots:
	void test_case1();
};

TestWinCondition::TestWinCondition() {}

TestWinCondition::~TestWinCondition() {}

void TestWinCondition::test_case1()
{
	QString hello = "Hello";
	QVERIFY(hello.toUpper() == "HELLO");
}

QTEST_APPLESS_MAIN(TestWinCondition)

#include "tst_testwincondition.moc"
