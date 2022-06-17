#include <Declarations.h>

int main(int argc, char* argv[])
{
    //��������� ������������ �������� �������
    if (argc != 4)
    {
        qDebug() << "Incorrect amount of arguments." << endl;
    }

    QFile output_file(argv[3]);

    //���� ������� ������� �������� ����
    if (output_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&output_file);

        Node* tree = new Node;
        tree->set_type(operation);

        //������� ������ �� �����
        int Error_number = 0;
        Error_number = Read_tree_from_file(argv[2], *tree);

        //���� ��� ���������� ���� ���������� ������
        QString error_text = "";
        if(Error_number<0)
        {
            switch (Error_number)
            {
            case -1:    //��� ���������� �� ������� ������� ������� ����
                error_text = "Invalid input file specified. The file may not exist.";
                break;
            case -2:    //���������� �������� ����� �����������
                error_text = "The file extension is incorrect. The file must have the extension .xml";
                break;
            case -3:    //���������� ������� ������� ����, ������������ ���������
                error_text = "The file can not be read. The input file may not have the correct syntax.";
                break;
            case -4:    //� �������� ������ ��������� ����������� ��������
                error_text = "The source tree contains unsupported operations.";
                break;
            case -5:    //� �������� ������ ��������� �������� � ������ �������� ����� �����������
                error_text = "The length of one or more operands exceeds the maximum length (100 characters).";
                break;
            case -6:    //� �������� ������ �������� ��������� �����������
                error_text = "Incorrect location or amount of the comparison operations in the input tree.";
                break;
            case -7:    //� �������� ������ ������������ ������������ ���������� ���������, ��������������� ������������ ���������
                error_text = "One or more operations correspond to an incorrect number of operands.";
                break;
            }
            out << error_text;
            return 0;
        }

        //��������� ������ ����� (��)��������� ����� �� ������ �����
        Transfering_to_left_side(*tree);

        //���������� ����� ����� �������� ������������, ��������� ��� ���������
        Node* ghost_parent = new Node;
        ghost_parent->set_type(operation);
        ghost_parent->set_value("");
        std::vector<Node*> ghost_parent_child = { tree };
        ghost_parent->set_children(ghost_parent_child);
        Uniting_pluses_minuses_multiplications(*tree, *ghost_parent);

        //������������� ��������� � ��������� � ���������� �������
        Sorting_in_alphabet_order(*tree->get_children()[0]);

        //�������� ������ � �������� ����
        Write_nodes(out, *tree);

        output_file.close();
    }
    else    //����� ������� ��������� � ���, ��� �������� ���� ���������� �������
    {
        qDebug() << "Invalid output file specified. The specified location may not exist.";
    }

return 0;
}


