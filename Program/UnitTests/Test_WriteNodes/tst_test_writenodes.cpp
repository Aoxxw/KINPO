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
    QFile output_file("../test1.txt");
    output_file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out(&output_file);

    if(output_file.isOpen())
    {
    qDebug() << "File is open";
    }

    Node* a=new Node;
    a->set_value("a");
    a->set_type(operand);

    Write_nodes(out, *a);

    QString text = output_file.readAll();

    QString exp_text = "<operand>a</operand>";

    output_file.close();

    QVERIFY(text == exp_text);
}

void Test_WriteNodes::WritingArithmeticOperation()
{

}
void Test_WriteNodes::WritingMoreOperation()
{

}

void Test_WriteNodes::WritingLessOperation()
{

}

void Test_WriteNodes::WritingMoreOrEqualOperation()
{

}

void Test_WriteNodes::WritingLessOrEqualOperation()
{

}

void Test_WriteNodes::SeveralLevels()
{

}

QTEST_APPLESS_MAIN(Test_WriteNodes)

#include "tst_test_writenodes.moc"
