#include <QtTest>
#include <../App/Declarations.h>

class Test_TransferingToLeftSide : public QObject
{
    Q_OBJECT

public:

private slots:
    void ZeroInRightSide();
    void OperandInrightSide();
    void OperationInRightSide();
};

void Test_TransferingToLeftSide::ZeroInRightSide()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* zero=new Node;
    zero->set_value("0");
    zero->set_type(operand);

    Node* mult=new Node;
    mult->set_value("*");
    mult->set_type(operation);
    std::vector<Node*> mult_children = {a, b};
    mult->set_children(mult_children);

    Node* equal=new Node;
    equal->set_value("=");
    equal->set_type(operation);
    std::vector<Node*> equal_children = {mult, zero};
    equal->set_children(equal_children);

    Node* exp_mult=new Node;
    exp_mult->set_value("*");
    exp_mult->set_type(operation);
    std::vector<Node*> exp_mult_children = {a, b};
    exp_mult->set_children(exp_mult_children);

    Node* exp_equal=new Node;
    exp_equal->set_value("=");
    exp_equal->set_type(operation);
    std::vector<Node*> exp_equal_children = {exp_mult, zero};
    exp_equal->set_children(exp_equal_children);

    bool are_equal = true;
    Comparing(*equal, *exp_equal, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_TransferingToLeftSide::OperandInrightSide()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* c=new Node;
    c->set_value("c");
    c->set_type(operand);

    Node* zero=new Node;
    zero->set_value("0");
    zero->set_type(operand);

    Node* mult=new Node;
    mult->set_value("*");
    mult->set_type(operation);
    std::vector<Node*> mult_children = {a, b};
    mult->set_children(mult_children);

    Node* equal=new Node;
    equal->set_value("=");
    equal->set_type(operation);
    std::vector<Node*> equal_children = {mult, c};
    equal->set_children(equal_children);

    Node* exp_mult=new Node;
    exp_mult->set_value("*");
    exp_mult->set_type(operation);
    std::vector<Node*> exp_mult_children = {a, b};
    exp_mult->set_children(exp_mult_children);

    Node* minus=new Node;
    minus->set_value("-");
    minus->set_type(operation);
    std::vector<Node*> minus_children = {c};
    minus->set_children(minus_children);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {exp_mult,minus};
    plus->set_children(plus_children);

    Node* exp_equal=new Node;
    exp_equal->set_value("=");
    exp_equal->set_type(operation);
    std::vector<Node*> exp_equal_children = {plus, zero};
    exp_equal->set_children(exp_equal_children);

    Transfering_to_left_side(*equal);

    bool are_equal = true;
    Comparing(*equal, *exp_equal, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_TransferingToLeftSide::OperationInRightSide()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* c=new Node;
    c->set_value("c");
    c->set_type(operand);

    Node* zero=new Node;
    zero->set_value("0");
    zero->set_type(operand);

    Node* mult=new Node;
    mult->set_value("*");
    mult->set_type(operation);
    std::vector<Node*> mult_children = {b, c};
    mult->set_children(mult_children);

    Node* equal=new Node;
    equal->set_value("=");
    equal->set_type(operation);
    std::vector<Node*> equal_children = {a, mult};
    equal->set_children(equal_children);


    Node* exp_mult=new Node;
    exp_mult->set_value("*");
    exp_mult->set_type(operation);
    std::vector<Node*> exp_mult_children = {b, c};
    exp_mult->set_children(exp_mult_children);

    Node* minus=new Node;
    minus->set_value("-");
    minus->set_type(operation);
    std::vector<Node*> minus_children = {exp_mult};
    minus->set_children(minus_children);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {a,minus};
    plus->set_children(plus_children);

    Node* exp_equal=new Node;
    exp_equal->set_value("=");
    exp_equal->set_type(operation);
    std::vector<Node*> exp_equal_children = {plus, zero};
    exp_equal->set_children(exp_equal_children);

    Transfering_to_left_side(*equal);

    bool are_equal = true;
    Comparing(*equal, *exp_equal, &are_equal);

    QVERIFY(are_equal==true);
}

QTEST_APPLESS_MAIN(Test_TransferingToLeftSide)

#include "tst_test_transferingtoleftside.moc"
