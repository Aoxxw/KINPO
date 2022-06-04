#include <QtTest>
#include <../App/Declarations.h>

class Test_WriteNodes : public QObject
{
    Q_OBJECT

public:
private slots:
    void WritingOperand();
    void WritingArithmeticOperation();
    void WritingMoreOperation();
    void WritingLessOperation();
    void WritingMoreOrEqualOperation();
    void WritingLessOrEqualOperation();
    void SeveralLevels();
};

void Test_WriteNodes::WritingOperand()
{
    QFile output_file("../../UnitTests/Test_WriteNodes/test1.txt");
    output_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&output_file);

    if(output_file.isOpen())
    {
    qDebug() << "File is open";
    }

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Write_nodes(out, *a);
    output_file.close();


    output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&output_file);

    QString text;
    text = in.readAll();

    QString exp_text = "<operand>a</operand>\n";

    QVERIFY(text==exp_text);
}

void Test_WriteNodes::WritingArithmeticOperation()
{
    QFile output_file("../../UnitTests/Test_WriteNodes/test2.txt");
    output_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&output_file);

    if(output_file.isOpen())
    {
    qDebug() << "File is open";
    }

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* plus=new Node;
    plus->set_value("+");
    plus->set_type(operation);
    std::vector<Node*> plus_children = {a,b};
    plus->set_children(plus_children);


    Write_nodes(out, *plus);
    output_file.close();


    output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&output_file);

    QString text;
    text = in.readAll();

    QString exp_text = "<operation symbol=\"+\">\n<operand>a<\/operand>\n<operand>b<\/operand>\n<\/operation>\n";

    QVERIFY(text==exp_text);
}
void Test_WriteNodes::WritingMoreOperation()
{
    QFile output_file("../../UnitTests/Test_WriteNodes/test3.txt");
    output_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&output_file);

    if(output_file.isOpen())
    {
    qDebug() << "File is open";
    }

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* more=new Node;
    more->set_value(">");
    more->set_type(operation);
    std::vector<Node*> more_children = {a,b};
    more->set_children(more_children);


    Write_nodes(out, *more);
    output_file.close();


    output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&output_file);

    QString text;
    text = in.readAll();

    QString exp_text = "<operation symbol=\"&gt;\">\n<operand>a<\/operand>\n<operand>b<\/operand>\n<\/operation>\n";

    QVERIFY(text==exp_text);
}

void Test_WriteNodes::WritingLessOperation()
{
    QFile output_file("../../UnitTests/Test_WriteNodes/test4.txt");
    output_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&output_file);

    if(output_file.isOpen())
    {
    qDebug() << "File is open";
    }

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* less=new Node;
    less->set_value("<");
    less->set_type(operation);
    std::vector<Node*> less_children = {a,b};
    less->set_children(less_children);


    Write_nodes(out, *less);
    output_file.close();


    output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&output_file);

    QString text;
    text = in.readAll();

    QString exp_text = "<operation symbol=\"&lt;\">\n<operand>a<\/operand>\n<operand>b<\/operand>\n<\/operation>\n";

    QVERIFY(text==exp_text);
}

void Test_WriteNodes::WritingMoreOrEqualOperation()
{
    QFile output_file("../../UnitTests/Test_WriteNodes/test5.txt");
    output_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&output_file);

    if(output_file.isOpen())
    {
    qDebug() << "File is open";
    }

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* more_equal=new Node;
    more_equal->set_value(">=");
    more_equal->set_type(operation);
    std::vector<Node*> more_equal_children = {a,b};
    more_equal->set_children(more_equal_children);


    Write_nodes(out, *more_equal);
    output_file.close();


    output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&output_file);

    QString text;
    text = in.readAll();

    QString exp_text = "<operation symbol=\"&gt;=\">\n<operand>a<\/operand>\n<operand>b<\/operand>\n<\/operation>\n";

    QVERIFY(text==exp_text);
}

void Test_WriteNodes::WritingLessOrEqualOperation()
{
    QFile output_file("../../UnitTests/Test_WriteNodes/test6.txt");
    output_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&output_file);

    if(output_file.isOpen())
    {
    qDebug() << "File is open";
    }

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* b=new Node;
    b->set_value("b");
    b->set_type(operand);

    Node* less_equal=new Node;
    less_equal->set_value("<=");
    less_equal->set_type(operation);
    std::vector<Node*> less_equal_children = {a,b};
    less_equal->set_children(less_equal_children);


    Write_nodes(out, *less_equal);
    output_file.close();


    output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&output_file);

    QString text;
    text = in.readAll();

    QString exp_text = "<operation symbol=\"&lt;=\">\n<operand>a<\/operand>\n<operand>b<\/operand>\n<\/operation>\n";

    QVERIFY(text==exp_text);
}

void Test_WriteNodes::SeveralLevels()
{
    QFile output_file("../../UnitTests/Test_WriteNodes/test7.txt");
    output_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&output_file);

    if(output_file.isOpen())
    {
    qDebug() << "File is open";
    }

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Node* minus=new Node;
    minus->set_value("-");
    minus->set_type(operation);
    std::vector<Node*> minus_children = {a};
    minus->set_children(minus_children);

    Node* sqrt=new Node;
    sqrt->set_value("sqrt");
    sqrt->set_type(operation);
    std::vector<Node*> sqrt_children = {minus};
    sqrt->set_children(sqrt_children);


    Write_nodes(out, *sqrt);
    output_file.close();


    output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&output_file);

    QString text;
    text = in.readAll();

    QString exp_text = "<operation symbol=\"sqrt\">\n<operation symbol=\"-\">\n<operand>a<\/operand>\n<\/operation>\n<\/operation>\n";

    QVERIFY(text==exp_text);
}

QTEST_APPLESS_MAIN(Test_WriteNodes)

#include "tst_test_writenodes.moc"
