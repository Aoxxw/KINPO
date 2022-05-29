#include <QtTest>
#include "../functions.h"

class Test_CollectingOperands : public QObject
{
    Q_OBJECT

public:
private slots:

void TwoOperands();
void OneOperand();
void NoOperands();
void SeveralLevelsWithOperands();
};

void Test_CollectingOperands::NoOperands()
{
    Node a;
    a.set_value("a");
    a.set_type(operand);

    std::vector<QString> all_operands;
    std::vector<QString> true_all_operands= {};
    Collecting_operands(a, all_operands);

   QVERIFY(all_operands == true_all_operands);
}

void Test_CollectingOperands::OneOperand()
{
    Node sqrt;
    sqrt.set_value("sqrt");
    sqrt.set_type(operation);

    Node a;
    a.set_value("a");
    a.set_type(operand);

    sqrt.add_child(&a);

    std::vector<QString> all_operands;
    std::vector<QString> true_all_operands= {"a"};
    Collecting_operands(sqrt, all_operands);

    QVERIFY(all_operands == true_all_operands);
}

void Test_CollectingOperands::TwoOperands()
{
    Node plus;
    plus.set_value("+");
    plus.set_type(operation);

    Node a;
    a.set_value("a");
    a.set_type(operand);

    Node b;
    b.set_value("b");
    b.set_type(operand);

    plus.add_child(&a);
    plus.add_child(&b);

    std::vector<QString> all_operands;
    std::vector<QString> true_all_operands= {"a","b"};
    Collecting_operands(plus, all_operands);

   QVERIFY(all_operands == true_all_operands);
}

void Test_CollectingOperands::SeveralLevelsWithOperands()
{
    Node plus;
    plus.set_value("+");
    plus.set_type(operation);

    Node a;
    a.set_value("a");
    a.set_type(operand);

    Node b;
    b.set_value("b");
    b.set_type(operand);

    Node mult;
    plus.set_value("*");
    plus.set_type(operation);

    Node c;
    c.set_value("c");
    c.set_type(operand);

    std::vector<Node*> plus_children = {&a,&b};
    std::vector<Node*> mult_children = {&plus, &c};
    plus.set_children(plus_children);
    mult.set_children(mult_children);

    std::vector<QString> all_operands;
    std::vector<QString> true_all_operands= {"a","b","c"};
    Collecting_operands(mult, all_operands);

    QVERIFY(all_operands == true_all_operands);
}

QTEST_APPLESS_MAIN(Test_CollectingOperands)

#include "tst_test_collectingoperands.moc"
