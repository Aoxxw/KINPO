#include <QtTest>
#include <../App/Declarations.h>

class Test_ChangeSign : public QObject
{
    Q_OBJECT

public:

private slots:
    void ChangingOperandSign();
    void ChangingNegationOperationSign();
    void ChangingNotNegationOperationSign();
    void ChangingSignOfBranchWithSeveralOperations();
};

void Test_ChangeSign::ChangingOperandSign()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {a, b};
    plus->set_children(plus_children);

    Node* minus=new Node;
    minus->set_value("-");
    minus->set_type(operation);
    std::vector<Node*> minus_children = {b};
    minus->set_children(minus_children);

    Node* exp_plus=new Node;
    exp_plus->set_value("+");
    exp_plus->set_type(operation);
    std::vector<Node*> exp_plus_children = {a, minus};
    exp_plus->set_children(exp_plus_children);

    Change_sign(*b, *plus, 1);

    bool are_equal = true;
    Comparing(*plus, *exp_plus, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_ChangeSign::ChangingNegationOperationSign()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* minus=new Node;
    minus->set_value("-");
    minus->set_type(operation);
    std::vector<Node*> minus_children = {b};
    minus->set_children(minus_children);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {a, minus};
    plus->set_children(plus_children);

    Node* exp_plus=new Node;
    exp_plus->set_value("+");
    exp_plus->set_type(operation);
    std::vector<Node*> exp_plus_children = {a, b};
    exp_plus->set_children(exp_plus_children);

    Change_sign(*minus, *plus, 1);

    bool are_equal = true;
    Comparing(*plus, *exp_plus, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_ChangeSign::ChangingNotNegationOperationSign()
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

    Node* degree=new Node;
    degree->set_value("^");
    degree->set_type(operation);
    std::vector<Node*> degree_children = {b, c};
    degree->set_children(degree_children);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {a, degree};
    plus->set_children(plus_children);


    Node* exp_degree=new Node;
    exp_degree->set_value("^");
    exp_degree->set_type(operation);
    std::vector<Node*> exp_degree_children = {b, c};
    exp_degree->set_children(exp_degree_children);

    Node* minus=new Node;
    minus->set_value("-");
    minus->set_type(operation);
    std::vector<Node*> minus_children = {exp_degree};
    minus->set_children(minus_children);

    Node* exp_plus=new Node;
    exp_plus->set_value("+");
    exp_plus->set_type(operation);
    std::vector<Node*> exp_plus_children = {a, minus};
    exp_plus->set_children(exp_plus_children);

    Change_sign(*degree, *plus, 1);

    bool are_equal = true;
    Comparing(*plus, *exp_plus, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_ChangeSign::ChangingSignOfBranchWithSeveralOperations()
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

    Node* d=new Node;
    d->set_value("d");
    d->set_type(operand);

    Node* plus2=new Node;
    plus2->set_value("+");
    plus2->set_type(operation);
    std::vector<Node*> plus2_children = {b, c};
    plus2->set_children(plus2_children);

    Node* mult=new Node;
    mult->set_value("+");
    mult->set_type(operation);
    std::vector<Node*> mult_children = {plus2, d};
    mult->set_children(mult_children);

    Node* plus1=new Node;
    plus1->set_value("+");
    plus1->set_type(operation);
    std::vector<Node*> plus1_children = {a, mult};
    plus1->set_children(plus1_children);


    Node* exp_plus2=new Node;
    exp_plus2->set_value("+");
    exp_plus2->set_type(operation);
    std::vector<Node*> exp_plus2_children = {b, c};
    exp_plus2->set_children(exp_plus2_children);

    Node* exp_mult=new Node;
    exp_mult->set_value("+");
    exp_mult->set_type(operation);
    std::vector<Node*> exp_mult_children = {exp_plus2, d};
    exp_mult->set_children(exp_mult_children);

    Node* minus=new Node;
    minus->set_value("-");
    minus->set_type(operation);
    std::vector<Node*> minus_children = {exp_mult};
    minus->set_children(minus_children);

    Node* exp_plus1=new Node;
    exp_plus1->set_value("+");
    exp_plus1->set_type(operation);
    std::vector<Node*> exp_plus1_children = {a, minus};
    exp_plus1->set_children(exp_plus1_children);

    Change_sign(*mult, *plus1, 1);

    bool are_equal = true;
    Comparing(*plus1, *exp_plus1, &are_equal);

    QVERIFY(are_equal==true);
}

QTEST_APPLESS_MAIN(Test_ChangeSign)

#include "tst_test_changesign.moc"
