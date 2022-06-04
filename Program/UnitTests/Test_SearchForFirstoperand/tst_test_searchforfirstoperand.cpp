#include <QtTest>
#include <../App/Declarations.h>

class Test_SearchForFirstoperand : public QObject
{
    Q_OBJECT

public:

private slots:
    void NodeIsOperand();
    void NodeIsOperationWithOneChild();
    void NodeIsOperationWithSeveralChildren();
    void SeveralLevelsOfNodes();
    void SeveralOperationsAfterNode();
};

void Test_SearchForFirstoperand::NodeIsOperand()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    QString operand_value="";
    Search_for_first_operand(*a, &operand_value);

    QVERIFY(operand_value == "");
}

void Test_SearchForFirstoperand::NodeIsOperationWithOneChild()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    sqrt->add_child(a);

    QString operand_value="";
    Search_for_first_operand(*sqrt, &operand_value);

    QVERIFY(operand_value == "a");
}

void Test_SearchForFirstoperand::NodeIsOperationWithSeveralChildren()
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

    QString operand_value="";
    Search_for_first_operand(*plus, &operand_value);

    QVERIFY(operand_value == "a");
}

void Test_SearchForFirstoperand::SeveralLevelsOfNodes()
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

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {a, b};
    plus->set_children(plus_children);

    Node* mult=new Node;
    mult->set_value("*");
    mult->set_type(operation);
    std::vector<Node*> mult_children = {plus, c};
    mult->set_children(mult_children);

    QString operand_value="";
    Search_for_first_operand(*plus, &operand_value);

    QVERIFY(operand_value == "a");
}

void Test_SearchForFirstoperand::SeveralOperationsAfterNode()
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

    Node* plus1=new Node;
    plus1->set_value("+");
    plus1->set_type(operation);
    std::vector<Node*> plus1_children = {a, b};
    plus1->set_children(plus1_children);

    Node* plus2=new Node;
    plus2->set_value("+");
    plus2->set_type(operation);
    std::vector<Node*> plus2_children = {c, d};
    plus2->set_children(plus2_children);

    Node* mult=new Node;
    mult->set_value("*");
    mult->set_type(operation);
    std::vector<Node*> mult_children = {plus1, plus2};
    mult->set_children(mult_children);

    QString operand_value="";
    Search_for_first_operand(*mult, &operand_value);

    QVERIFY(operand_value == "a");
}

QTEST_APPLESS_MAIN(Test_SearchForFirstoperand)

#include "tst_test_searchforfirstoperand.moc"
