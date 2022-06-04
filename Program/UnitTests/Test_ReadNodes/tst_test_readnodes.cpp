#include <QtTest>
#include <../App/Declarations.h>

class Test_ReadNodes : public QObject
{
    Q_OBJECT

public:

private slots:
    void NodeIsOperand();
    void NodeIsOperationWithOperandsOnly();
    void NodeIsOperationWithOperandsAndOperations();
    void NodeIsOperationWithOperationsOnly();
};

void Test_ReadNodes::NodeIsOperand()
{
    QFile* input_file = new QFile("../../UnitTests/Test_ReadNodes/test1.xml");

    if (!input_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QXmlStreamReader reader(input_file);
    reader.readNextStartElement();

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* parent_node=new Node;
    parent_node->set_value("sqrt");
    parent_node->set_type(operation);
    std::vector<Node*> parent_node_children = {};
    parent_node->set_children(parent_node_children);

    Node* exp_parent_node=new Node;
    exp_parent_node->set_value("sqrt");
    exp_parent_node->set_type(operation);
    std::vector<Node*> exp_parent_children = {a};
    exp_parent_node->set_children(exp_parent_children);

    int number_of_iteration=-1;
    Read_nodes(reader, *parent_node, number_of_iteration);

    input_file->close();

    bool are_equal = true;
    Comparing(*parent_node, *exp_parent_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_ReadNodes::NodeIsOperationWithOperandsOnly()
{
    QFile* input_file = new QFile("../../UnitTests/Test_ReadNodes/test2.xml");

    if (!input_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QXmlStreamReader reader(input_file);
    reader.readNextStartElement();

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {};
    plus->set_children(plus_children);

    Node* parent_node=new Node;
    parent_node->set_value("sqrt");
    parent_node->set_type(operation);
    std::vector<Node*> parent_node_children = {};
    parent_node->set_children(parent_node_children);


    Node* exp_plus=new Node;
    exp_plus->set_value("+");
    exp_plus->set_type(operation);
    std::vector<Node*> exp_plus_children = {a, b};
    exp_plus->set_children(exp_plus_children);

    Node* exp_parent_node=new Node;
    exp_parent_node->set_value("sqrt");
    exp_parent_node->set_type(operation);
    std::vector<Node*> exp_parent_children = {exp_plus};
    exp_parent_node->set_children(exp_parent_children);

    int number_of_iteration=-1;
    Read_nodes(reader, *parent_node, number_of_iteration);

    input_file->close();

    bool are_equal = true;
    Comparing(*parent_node, *exp_parent_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_ReadNodes::NodeIsOperationWithOperandsAndOperations()
{
    QFile* input_file = new QFile("../../UnitTests/Test_ReadNodes/test3.xml");

    if (!input_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QXmlStreamReader reader(input_file);
    reader.readNextStartElement();

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* four=new Node;
    four->set_value("4");
    four->set_type(operand);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    std::vector<Node*> sqrt_children = {};
    sqrt->set_children(sqrt_children);

    Node* parent_node=new Node;
    parent_node->set_value("sqrt");
    parent_node->set_type(operation);
    std::vector<Node*> parent_node_children = {};
    parent_node->set_children(parent_node_children);


    Node* exp_sqrt=new Node;
    exp_sqrt->set_value("sqrt");
    exp_sqrt->set_type(operation);
    std::vector<Node*> exp_sqrt_children = {four};
    exp_sqrt->set_children(exp_sqrt_children);

    Node* exp_plus=new Node;
    exp_plus->set_value("+");
    exp_plus->set_type(operation);
    std::vector<Node*> exp_plus_children = {a,exp_sqrt};
    exp_plus->set_children(exp_plus_children);

    Node* exp_parent_node=new Node;
    exp_parent_node->set_value("sqrt");
    exp_parent_node->set_type(operation);
    std::vector<Node*> exp_parent_children = {exp_plus};
    exp_parent_node->set_children(exp_parent_children);

    int number_of_iteration=-1;
    Read_nodes(reader, *parent_node, number_of_iteration);

    input_file->close();

    bool are_equal = true;
    Comparing(*parent_node, *exp_parent_node, &are_equal);

    QVERIFY(are_equal==true);
}

void Test_ReadNodes::NodeIsOperationWithOperationsOnly()
{

    QFile* input_file = new QFile("../../UnitTests/Test_ReadNodes/test4.xml");

    if (!input_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QXmlStreamReader reader(input_file);
    reader.readNextStartElement();

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* four=new Node;
    four->set_value("4");
    four->set_type(operand);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    std::vector<Node*> sqrt_children = {};
    sqrt->set_children(sqrt_children);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {};
    plus->set_children(plus_children);

    Node* parent_node=new Node;
    parent_node->set_value("sqrt");
    parent_node->set_type(operation);
    std::vector<Node*> parent_node_children = {};
    parent_node->set_children(parent_node_children);

    Node* exp_mult=new Node;
    exp_mult->set_value("*");
    exp_mult->set_type(operation);
    std::vector<Node*> exp_mult_children = {a,b};
    exp_mult->set_children(exp_mult_children);

    Node* exp_sqrt=new Node;
    exp_sqrt->set_value("sqrt");
    exp_sqrt->set_type(operation);
    std::vector<Node*> exp_sqrt_children = {four};
    exp_sqrt->set_children(exp_sqrt_children);

    Node* exp_plus=new Node;
    exp_plus->set_value("+");
    exp_plus->set_type(operation);
    std::vector<Node*> exp_plus_children = {exp_mult, exp_sqrt};
    exp_plus->set_children(exp_plus_children);

    Node* exp_parent_node=new Node;
    exp_parent_node->set_value("sqrt");
    exp_parent_node->set_type(operation);
    std::vector<Node*> exp_parent_children = {exp_plus};
    exp_parent_node->set_children(exp_parent_children);

    int number_of_iteration=-1;
    Read_nodes(reader, *parent_node, number_of_iteration);

    input_file->close();

    bool are_equal = true;
    Comparing(*parent_node, *exp_parent_node, &are_equal);

    QVERIFY(are_equal==true);
}

QTEST_APPLESS_MAIN(Test_ReadNodes)

#include "tst_test_readnodes.moc"
