#include <QtTest>
#include <../App/Declarations.h>

class Test_UnitingPlusesMinusesMultiplications : public QObject
{
    Q_OBJECT

public:

private slots:
    void PlusPlus();
    void MinusPlus();
    void MinusMinus();
    void MultMult();
    void TriplePlus();
    void MinusPlusMinus();
};

void Test_UnitingPlusesMinusesMultiplications::PlusPlus()
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

    Node* plus2=new Node;
    plus2->set_value("+");
    plus2->set_type(operation);
    std::vector<Node*> plus2_children = {b, c};
    plus2->set_children(plus2_children);

    Node* plus1=new Node;
    plus1->set_value("+");
    plus1->set_type(operation);
    std::vector<Node*> plus1_children = {a, plus2};
    plus1->set_children(plus1_children);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    std::vector<Node*> sqrt_children = {plus1};
    sqrt->set_children(sqrt_children);


    Node* exp_plus1=new Node;
    exp_plus1->set_value("+");
    exp_plus1->set_type(operation);
    std::vector<Node*> exp_plus1_children = {a, b, c};
    exp_plus1->set_children(exp_plus1_children);

    Node* exp_sqrt=new Node;
    exp_sqrt->set_value("sqrt");
    exp_sqrt->set_type(operation);
    std::vector<Node*> exp_sqrt_children = {exp_plus1};
    exp_sqrt->set_children(exp_sqrt_children);

    Uniting_pluses_minuses_multiplications(*plus1, *sqrt);

    bool are_equal = true;
    Comparing(*sqrt, *exp_sqrt, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_UnitingPlusesMinusesMultiplications::MinusPlus()
{
    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* c=new Node;
    c->set_value("c");
    c->set_type(operand);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {b, c};
    plus->set_children(plus_children);

    Node* minus=new Node;
    minus->set_value("-");
    minus->set_type(operation);
    std::vector<Node*> minus_children = {plus};
    minus->set_children(minus_children);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    std::vector<Node*> sqrt_children = {minus};
    sqrt->set_children(sqrt_children);


    Node* exp_minus1=new Node;
    exp_minus1->set_value("-");
    exp_minus1->set_type(operation);
    std::vector<Node*> exp_minus1_children = {b};
    exp_minus1->set_children(exp_minus1_children);

    Node* exp_minus2=new Node;
    exp_minus2->set_value("-");
    exp_minus2->set_type(operation);
    std::vector<Node*> exp_minus2_children = {c};
    exp_minus2->set_children(exp_minus2_children);

    Node* exp_plus=new Node;
    exp_plus->set_value("+");
    exp_plus->set_type(operation);
    std::vector<Node*> exp_plus_children = {exp_minus1, exp_minus2};
    exp_plus->set_children(exp_plus_children);

    Node* exp_sqrt=new Node;
    exp_sqrt->set_value("sqrt");
    exp_sqrt->set_type(operation);
    std::vector<Node*> exp_sqrt_children = {exp_plus};
    exp_sqrt->set_children(exp_sqrt_children);


    Uniting_pluses_minuses_multiplications(*minus, *sqrt);

    bool are_equal = true;
    Comparing(*sqrt, *exp_sqrt, &are_equal);

    QVERIFY(are_equal==true);

}

void Test_UnitingPlusesMinusesMultiplications::MinusMinus()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* minus2=new Node;
    minus2->set_value("-");
    minus2->set_type(operation);
    std::vector<Node*> minus2_children = {a};
    minus2->set_children(minus2_children);

    Node* minus1=new Node;
    minus1->set_value("-");
    minus1->set_type(operation);
    std::vector<Node*> minus1_children = {minus2};
    minus1->set_children(minus1_children);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    std::vector<Node*> sqrt_children = {minus1};
    sqrt->set_children(sqrt_children);

    Node* exp_sqrt=new Node;
    exp_sqrt->set_value("sqrt");
    exp_sqrt->set_type(operation);
    std::vector<Node*> exp_sqrt_children = {a};
    exp_sqrt->set_children(exp_sqrt_children);

    Uniting_pluses_minuses_multiplications(*minus1, *sqrt);

    bool are_equal = true;
    Comparing(*sqrt, *exp_sqrt, &are_equal);

    QVERIFY(are_equal==true);

}

void Test_UnitingPlusesMinusesMultiplications::MultMult()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* mult2=new Node;
    mult2->set_value("*");
    mult2->set_type(operation);
    std::vector<Node*> mult2_children = {a};
    mult2->set_children(mult2_children);

    Node* mult1=new Node;
    mult1->set_value("*");
    mult1->set_type(operation);
    std::vector<Node*> mult1_children = {mult2};
    mult1->set_children(mult1_children);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    std::vector<Node*> sqrt_children = {mult1};
    sqrt->set_children(sqrt_children);


    Node* exp_mult1=new Node;
    exp_mult1->set_value("*");
    exp_mult1->set_type(operation);
    std::vector<Node*> exp_mult1_children = {a};
    exp_mult1->set_children(exp_mult1_children);

    Node* exp_sqrt=new Node;
    exp_sqrt->set_value("sqrt");
    exp_sqrt->set_type(operation);
    std::vector<Node*> exp_sqrt_children = {mult1};
    exp_sqrt->set_children(exp_sqrt_children);

    Uniting_pluses_minuses_multiplications(*mult1, *sqrt);

    bool are_equal = true;
    Comparing(*sqrt, *exp_sqrt, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_UnitingPlusesMinusesMultiplications::TriplePlus()
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

    Node* plus3=new Node;
    plus3->set_value("+");
    plus3->set_type(operation);
    std::vector<Node*> plus3_children = {c, d};
    plus3->set_children(plus3_children);

    Node* plus2=new Node;
    plus2->set_value("+");
    plus2->set_type(operation);
    std::vector<Node*> plus2_children = {plus3, b};
    plus2->set_children(plus2_children);

    Node* plus1=new Node;
    plus1->set_value("+");
    plus1->set_type(operation);
    std::vector<Node*> plus1_children = {plus2, a};
    plus1->set_children(plus1_children);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    std::vector<Node*> sqrt_children = {plus1};
    sqrt->set_children(sqrt_children);


    Node* exp_plus1=new Node;
    exp_plus1->set_value("+");
    exp_plus1->set_type(operation);
    std::vector<Node*> exp_plus1_children = {c, d, b, a};
    exp_plus1->set_children(exp_plus1_children);

    Node* exp_sqrt=new Node;
    exp_sqrt->set_value("sqrt");
    exp_sqrt->set_type(operation);
    std::vector<Node*> exp_sqrt_children = {exp_plus1};
    exp_sqrt->set_children(exp_sqrt_children);

    Uniting_pluses_minuses_multiplications(*plus1, *sqrt);

    bool are_equal = true;
    Comparing(*sqrt, *exp_sqrt, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_UnitingPlusesMinusesMultiplications::MinusPlusMinus()
{
    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* c=new Node;
    c->set_value("c");
    c->set_type(operand);

    Node* minus2=new Node;
    minus2->set_value("-");
    minus2->set_type(operation);
    std::vector<Node*> minus2_children = {c};
    minus2->set_children(minus2_children);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {minus2, b};
    plus->set_children(plus_children);

    Node* minus1=new Node;
    minus1->set_value("-");
    minus1->set_type(operation);
    std::vector<Node*> minus1_children = {plus};
    minus1->set_children(minus1_children);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    std::vector<Node*> sqrt_children = {minus1};
    sqrt->set_children(sqrt_children);


    Node* exp_minus=new Node;
    exp_minus->set_value("-");
    exp_minus->set_type(operation);
    std::vector<Node*> exp_minus_children = {b};
    exp_minus->set_children(exp_minus_children);

    Node* exp_plus=new Node;
    exp_plus->set_value("+");
    exp_plus->set_type(operation);
    std::vector<Node*> exp_plus_children = {c, exp_minus};
    exp_plus->set_children(exp_plus_children);

    Node* exp_sqrt=new Node;
    exp_sqrt->set_value("sqrt");
    exp_sqrt->set_type(operation);
    std::vector<Node*> exp_sqrt_children = {exp_plus};
    exp_sqrt->set_children(exp_sqrt_children);

    Uniting_pluses_minuses_multiplications(*minus1, *sqrt);

    bool are_equal = true;
    Comparing(*sqrt, *exp_sqrt, &are_equal);

    QVERIFY(are_equal==true);
}

QTEST_APPLESS_MAIN(Test_UnitingPlusesMinusesMultiplications)

#include "tst_test_unitingplusesminusesmultiplications.moc"
