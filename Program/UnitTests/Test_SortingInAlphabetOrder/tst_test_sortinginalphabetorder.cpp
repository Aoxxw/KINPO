#include <QtTest>
#include <../App/Declarations.h>

class Test_SortingInAlphabetOrder : public QObject
{
    Q_OBJECT

public:

private slots:
    void NodeIsOperand();
    void NodeIsOperationWithOneChild();
    void SeveralLevelsOfNodes();

};

void Test_SortingInAlphabetOrder::NodeIsOperand()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* exp_node=new Node;
    exp_node->set_value("a");
    exp_node->set_type(operand);

    Sorting_in_alphabet_order(*a);

    bool are_equal = true;
    Comparing(*a, *exp_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_SortingInAlphabetOrder::NodeIsOperationWithOneChild()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    sqrt->add_child(a);

    Node* exp_sqrt_node=new Node;
    exp_sqrt_node->set_value("sqrt");
    exp_sqrt_node->set_type(operation);
    exp_sqrt_node->add_child(a);

    Sorting_in_alphabet_order(*sqrt);

    bool are_equal = true;
    Comparing(*sqrt, *exp_sqrt_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_SortingInAlphabetOrder::SeveralLevelsOfNodes()
{
    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* i=new Node;
    i->set_value("i");
    i->set_type(operand);

    Node* num_5=new Node;
    num_5->set_value("5");
    num_5->set_type(operand);

    Node* degree=new Node;
    degree->set_value("^");
    degree->set_type(operation);
    std::vector<Node*> degree_children = {i, num_5};
    degree->set_children(degree_children);

    Node* mult=new Node;
    mult->set_value("*");
    mult->set_type(operation);
    std::vector<Node*> mult_children = {degree, a};
    mult->set_children(mult_children);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {b, mult};
    plus->set_children(plus_children);


    Node* exp_degree=new Node;
    exp_degree->set_value("^");
    exp_degree->set_type(operation);
    std::vector<Node*> exp_degree_children = {i, num_5};
    exp_degree->set_children(exp_degree_children);

    Node* exp_mult=new Node;
    exp_mult->set_value("*");
    exp_mult->set_type(operation);
    std::vector<Node*> exp_mult_children = {a, exp_degree};
    exp_mult->set_children(exp_mult_children);

    Node* exp_plus=new Node;
    exp_plus->set_value("+");
    exp_plus->set_type(operation);
    std::vector<Node*> exp_plus_children = {exp_mult, b};
    exp_plus->set_children(exp_plus_children);

    Sorting_in_alphabet_order(*plus);

    bool are_equal = true;
    Comparing(*plus, *exp_plus, &are_equal);

    QVERIFY(are_equal==true);
}

QTEST_APPLESS_MAIN(Test_SortingInAlphabetOrder)

#include "tst_test_sortinginalphabetorder.moc"
