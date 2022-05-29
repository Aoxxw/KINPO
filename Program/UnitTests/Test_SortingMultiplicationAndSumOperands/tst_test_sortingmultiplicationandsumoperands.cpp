#include <QtTest>
#include <../App/Declarations.h>

class Test_SortingMultiplicationAndSumOperands : public QObject
{
    Q_OBJECT

public:

private slots:
    void NotMultOrPlus();
    void OnlyOperands();
    void BothOperandsAndOperations1();
    void BothOperandsAndOperations2();
    void BothOperandsAndOperations3();
    void OperationAfterOperation();
};

void Test_SortingMultiplicationAndSumOperands::NotMultOrPlus()
{
    Node* devision=new Node;
    devision->set_value("/");
    devision->set_type(operation);

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    std::vector<Node*> devision_children = {a, b};
    devision->set_children(devision_children);

    Node* exp_node = new Node;
    exp_node->set_type(operation);
    exp_node->set_value("/");
    exp_node->set_children(devision_children);

    Sorting_multiplication_and_sum_operands(*devision);

    bool are_equal = true;
    Comparing(*devision, *exp_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_SortingMultiplicationAndSumOperands::OnlyOperands()
{
    Node* plus = new Node;
    plus->set_value("+");
    plus->set_type(operation);

    Node* a= new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b= new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* c= new Node;
    c->set_value("c");
    c->set_type(operand);

    std::vector<Node*> plus_children = {b,c,a};
    plus->set_children(plus_children);

    Node* exp_plus_node= new Node;
    exp_plus_node->set_type(operation);
    exp_plus_node->set_value("+");
    std::vector<Node*> exp_plus_children = {a,b,c};
    exp_plus_node->set_children(exp_plus_children);

    Sorting_multiplication_and_sum_operands(*plus);

    bool are_equal = true;
    Comparing(*plus, *exp_plus_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_SortingMultiplicationAndSumOperands::BothOperandsAndOperations1()
{     
    Node* a= new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b= new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* g= new Node;
    g->set_value("g");
    g->set_type(operand);

    Node* z= new Node;
    z->set_value("z");
    z->set_type(operand);

    Node* plus = new Node;
    plus->set_value("+");
    plus->set_type(operation);

    Node* mult = new Node;
    mult->set_type(operation);
    mult->set_value("*");

    std::vector<Node*> mult_children = {z,g};
    std::vector<Node*> plus_children = {b,mult,a};
    mult->set_children(mult_children);
    plus->set_children(plus_children);   

    Node* exp_mult_node = new Node;
    exp_mult_node->set_type(operation);
    exp_mult_node->set_value("*");
    std::vector<Node*> exp_mult_children = {z,g};
    exp_mult_node->set_children(exp_mult_children);

    Node* exp_plus_node = new Node;
    exp_plus_node->set_type(operation);
    exp_plus_node->set_value("+");
    std::vector<Node*> exp_plus_children = {a,b,exp_mult_node};
    exp_plus_node->set_children(exp_plus_children);

    Sorting_multiplication_and_sum_operands(*plus);

    bool are_equal = true;
    Comparing(*plus, *exp_plus_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_SortingMultiplicationAndSumOperands::BothOperandsAndOperations2()
{
    Node* a= new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b= new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* j= new Node;
    j->set_value("j");
    j->set_type(operand);

    Node* p= new Node;
    p->set_value("p");
    p->set_type(operand);

    Node* plus = new Node;
    plus->set_value("+");
    plus->set_type(operation);

    Node* mult = new Node;
    mult->set_type(operation);
    mult->set_value("*");

    std::vector<Node*> mult_children = {b,a};
    std::vector<Node*> plus_children = {j,mult,p};
    mult->set_children(mult_children);
    plus->set_children(plus_children);

    Node* exp_mult_node = new Node;
    exp_mult_node->set_type(operation);
    exp_mult_node->set_value("*");
    std::vector<Node*> exp_mult_children = {b,a};
    exp_mult_node->set_children(exp_mult_children);

    Node* exp_plus_node = new Node;
    exp_plus_node->set_type(operation);
    exp_plus_node->set_value("+");
    std::vector<Node*> exp_plus_children = {exp_mult_node,j,p};
    exp_plus_node->set_children(exp_plus_children);

    Sorting_multiplication_and_sum_operands(*plus);

    bool are_equal = true;
    Comparing(*plus, *exp_plus_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_SortingMultiplicationAndSumOperands::BothOperandsAndOperations3()
{
    Node* a= new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b= new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* j= new Node;
    j->set_value("j");
    j->set_type(operand);

    Node* z= new Node;
    z->set_value("z");
    z->set_type(operand);

    Node* plus = new Node;
    plus->set_value("+");
    plus->set_type(operation);

    Node* mult = new Node;
    mult->set_type(operation);
    mult->set_value("*");

    std::vector<Node*> mult_children = {b,z};
    std::vector<Node*> plus_children = {j,mult,a};
    mult->set_children(mult_children);
    plus->set_children(plus_children);

    Node* exp_mult_node = new Node;
    exp_mult_node->set_type(operation);
    exp_mult_node->set_value("*");
    std::vector<Node*> exp_mult_children = {b,z};
    exp_mult_node->set_children(exp_mult_children);

    Node* exp_plus_node = new Node;
    exp_plus_node->set_type(operation);
    exp_plus_node->set_value("+");
    std::vector<Node*> exp_plus_children = {a,exp_mult_node,j};
    exp_plus_node->set_children(exp_plus_children);

    Sorting_multiplication_and_sum_operands(*plus);

    bool are_equal = true;
    Comparing(*plus, *exp_plus_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_SortingMultiplicationAndSumOperands::OperationAfterOperation()
{
    Node* a1= new Node;
    a1->set_value("a");
    a1->set_type(operand);

    Node* a2= new Node;
    a2->set_value("a");
    a2->set_type(operand);

    Node* j= new Node;
    j->set_value("j");
    j->set_type(operand);

    Node* z= new Node;
    z->set_value("j");
    z->set_type(operand);

    Node* e= new Node;
    e->set_value("j");
    e->set_type(operand);

    Node* plus1 = new Node;
    plus1->set_value("+");
    plus1->set_type(operation);

    Node* mult = new Node;
    mult->set_type(operation);
    mult->set_value("*");

    Node* plus2 = new Node;
    plus2->set_value("+");
    plus2->set_type(operation);

    std::vector<Node*> mult_children = {plus2,z};
    std::vector<Node*> plus1_children = {j,a1,mult};
    std::vector<Node*> plus2_children = {a2,e};
    mult->set_children(mult_children);
    plus1->set_children(plus1_children);
    plus2->set_children(plus2_children);


    Node* exp_plus2_node = new Node;
    exp_plus2_node->set_type(operation);
    exp_plus2_node->set_value("+");
    std::vector<Node*> exp_plus2_children = {a2,e};
    exp_plus2_node->set_children(exp_plus2_children);

    Node* exp_mult_node = new Node;
    exp_mult_node->set_type(operation);
    exp_mult_node->set_value("*");
    std::vector<Node*> exp_mult_children = {exp_plus2_node,z};
    exp_mult_node->set_children(exp_mult_children);

    Node* exp_plus1_node = new Node;
    exp_plus1_node->set_type(operation);
    exp_plus1_node->set_value("+");
    std::vector<Node*> exp_plus1_children = {a1,exp_mult_node,j};
    exp_plus1_node->set_children(exp_plus1_children);


    Sorting_multiplication_and_sum_operands(*plus1);

    bool are_equal = true;
    Comparing(*plus1, *exp_plus1_node, &are_equal);

    QVERIFY(are_equal==true);
}

QTEST_APPLESS_MAIN(Test_SortingMultiplicationAndSumOperands)

#include "tst_test_sortingmultiplicationandsumoperands.moc"
