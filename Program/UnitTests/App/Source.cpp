#include <iostream>
#include "Declarations.h"

int Read_tree_from_file(char file_path[], Node& tree)
{
	QFile* input_file = new QFile(file_path);
    QFileInfo file_info(file_path);

	if (!input_file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return -1;
	}

    if(file_info.suffix()!="xml")
    {
        return -2;
    }

	QXmlStreamReader reader(input_file);

	reader.readNextStartElement();

    int read_error = 0;
    int number_of_iteration=-1;

    read_error = Read_nodes(reader, tree, number_of_iteration);
    if(read_error<0)
    {
        switch (read_error)
        {
        case -1://ошибки синтаксиса
            return -3;
            break;
        case -2: // неизвестна€ операци€
            return -4;
            break;
        case -3:// длина операнда более 100
            return -5;
            break;
        case -4: // операци€ сравнени€ некорректна
            return -6;
            break;
        case -5: // некорректное количество операндов
           return -7;
            break;
        }
    }

	tree = *tree.get_children()[0];

	input_file->close();
	return 0;
}

int Read_nodes(QXmlStreamReader& reader, Node& parent_node, int& number_of_iteration)
{
	Node* current_node = new Node;
    int error=0;
    number_of_iteration++;

	if (reader.name() == "operation")
	{
		current_node->set_type(operation);
		current_node->set_value(reader.attributes().value("symbol").toString());
		parent_node.add_child(current_node);

        if(reader.hasError())
        {
            return -1;
        }

        //проверка значени€ текущей операции
        if(current_node->get_value()!="^" && current_node->get_value()!="/" && current_node->get_value()!="+" &&
           current_node->get_value()!="*" && current_node->get_value()!="-" && current_node->get_value()!="sqrt" &&
           current_node->get_value()!="=" && current_node->get_value()!=">" && current_node->get_value()!="<" &&
           current_node->get_value()!=">=" && current_node->get_value()!="<=" )
        {
           return -2;
        }

        //местоположение операции
        if((current_node->get_value()=="=" || current_node->get_value()==">" || current_node->get_value()=="<" || current_node->get_value()==">=" || current_node->get_value()=="<=" ) && number_of_iteration!=0)
        {
          return -4;
        }


		while (true)
		{
			reader.readNext();
			while (!reader.isStartElement() && !reader.atEnd())
			{
				reader.readNext();

                if (reader.atEnd())
                {
                    return -1;
                }

                if(reader.hasError())
                {
                    return -1;
                }

				if (reader.isEndElement() && reader.name() == "operation")
                {
                    if (    ((current_node->get_value()=="^" || current_node->get_value()=="/") && current_node->get_children().size() !=2) ||
                            ((current_node->get_value()=="+" || current_node->get_value()=="*") && current_node->get_children().size()<2) ||
                            ((current_node->get_value()=="-" || current_node->get_value()=="sqrt") && current_node->get_children().size()!=1) ||
                            ((current_node->get_value()=="=" || current_node->get_value()==">" || current_node->get_value()=="<" || current_node->get_value()==">=" || current_node->get_value()=="<=" ) && current_node->get_children().size()!=2) )
                    {
                        return -5;
                    }
                   return error;
				}
			}

            if(error==0)
            {
               error=Read_nodes(reader, *current_node, number_of_iteration);
            }
            else
            {
                return error;
            }
        }

        //число потомков операции

	}
	else
	{
		if (reader.name() == "operand")
        {
            current_node->set_value(reader.readElementText());
            current_node->set_type(operand);
            parent_node.add_child(current_node);

            if(current_node->get_value().length()>100)
            {
                return -3;
            }

            if(reader.hasError())
            {
                return -1;
            }

            return 0;
		}
	}
    //return error;
}

void Transfering_to_left_side(Node& main_node)
{
	if (main_node.get_children()[1]->get_value() != "0")
	{
		Node* zero_node = new Node;
		zero_node->set_value("0");
		zero_node->set_type(operand);

		Node* plus_node = new Node;
		plus_node->set_value("+");
		plus_node->set_type(operation);
		plus_node->add_child(main_node.get_children()[0]);
		plus_node->add_child(main_node.get_children()[1]);

		Change_sign(*plus_node->get_children()[1], *plus_node, 1);

		main_node.change_child(plus_node, 0);
		main_node.change_child(zero_node, 1);
	}
	return;
}

void Change_sign(Node& current_node, Node& parent_node, int position)
{
	if (current_node.get_value() == "-")
	{
		parent_node.insert_children(position, current_node.get_children());
		parent_node.erase_child(position + 1);
	}
	else
	{
		Node* minus_node = new Node;
		minus_node->set_value("-");
		minus_node->set_type(operation);
		minus_node->add_child(&current_node);

		parent_node.insert_children(position, *minus_node);
		parent_node.erase_child(position + 1);
	}
	return;
}

void Uniting_pluses_minuses_multiplications(Node& current_node, Node& parent_node)
{
	for (int j = 0; j < current_node.get_children().size(); j++)
	{
		if (current_node.get_children()[j]->get_type() == operation)
		{
			Uniting_pluses_minuses_multiplications(*current_node.get_children()[j], current_node);
		}
	}

	for (int i = 0; i < current_node.get_children().size(); i++)
	{
		if (current_node.get_value() == "+" && current_node.get_children()[i]->get_value() == "+")
		{
			int size = current_node.get_children()[i]->get_children().size();
			current_node.insert_children(i, current_node.get_children()[i]->get_children());
			current_node.erase_child(i + size);
		}

		if (current_node.get_value() == "-" && current_node.get_children()[i]->get_value() == "+")
		{
			current_node.set_value("+");
			current_node.set_children(current_node.get_children()[i]->get_children());

			for (int i = 0; i < current_node.get_children().size(); i++)
			{
				Node* minus_node = new Node;
				minus_node->set_value("-");
				minus_node->set_type(operation);
				minus_node->add_child(current_node.get_children()[i]);

				current_node.insert_children(i, *minus_node);
				current_node.erase_child(i + 1);

				Uniting_pluses_minuses_multiplications(*current_node.get_children()[i], current_node);
			}
		}

		if (current_node.get_value() == "-" && current_node.get_children()[0]->get_value() == "-")
		{
            parent_node.insert_children(i, current_node.get_children()[0]->get_children());
			parent_node.erase_child(i + 1);
		}

		if (current_node.get_value() == "*" && current_node.get_children()[i]->get_value() == "*")
		{
			int size = current_node.get_children()[i]->get_children().size();
			current_node.insert_children(i, current_node.get_children()[i]->get_children());
			current_node.erase_child(i + size);
		}
	}

	return;
}

void Sorting_in_alphabet_order(Node& current_node)
{
	if (current_node.get_type() == operand)
	{
		return;
	}
	else
	{
		if (current_node.get_type() == operation)
		{
			for (int i = 0; i < current_node.get_children().size(); i++)
			{
				Sorting_in_alphabet_order(*current_node.get_children()[i]);
			}
			Sorting_multiplication_and_sum_operands(current_node);
		}
		return;
	}
	return;
}

void Sorting_multiplication_and_sum_operands(Node& current_node)
{
	Node* temp_node;
	if (current_node.get_value() == "*" || current_node.get_value() == "+")
	{
		for (int i = 0; i < current_node.get_children().size(); i++)
		{
			for (int j = 0; j < current_node.get_children().size(); j++)
			{

				if (current_node.get_children()[i]->get_type() == operand && current_node.get_children()[j]->get_type() == operand
					&& i<j
					&& current_node.get_children()[i]->get_value() > current_node.get_children()[j]->get_value())
				{
					temp_node = current_node.get_children()[i];
					current_node.change_child(current_node.get_children()[j], i);
					current_node.change_child(temp_node, j);
				}

				if (current_node.get_children()[i]->get_type() == operation && current_node.get_children()[j]->get_type() == operation
					&& i < j)
				{
					QString operand_value1 = "";
					QString operand_value2 = "";
					Search_for_first_operand(*current_node.get_children()[i], &operand_value1);
					Search_for_first_operand(*current_node.get_children()[j], &operand_value2);

					if (operand_value1 > operand_value2)
					{
						temp_node = current_node.get_children()[i];
						current_node.change_child(current_node.get_children()[j], i);
						current_node.change_child(temp_node, j);
					}
				}

				if (current_node.get_children()[i]->get_type() == operation && current_node.get_children()[j]->get_type() == operand
					&& i < j)
				{
					QString operand_value = "";
					Search_for_first_operand(*current_node.get_children()[i], &operand_value);
					if (operand_value > current_node.get_children()[j]->get_value())
					{
						temp_node = current_node.get_children()[i];
						current_node.change_child(current_node.get_children()[j], i);
						current_node.change_child(temp_node, j);
					}
				}

				if (current_node.get_children()[i]->get_type() == operand && current_node.get_children()[j]->get_type() == operation
					&& i < j)
				{
					QString operand_value = "";
					Search_for_first_operand(*current_node.get_children()[j], &operand_value);
					if (current_node.get_children()[i]->get_value() > operand_value)
					{
						temp_node = current_node.get_children()[i];
						current_node.change_child(current_node.get_children()[j], i);
						current_node.change_child(temp_node, j);
					}
				}
			}
		}
	}
	return;
}

void Search_for_first_operand(Node& current_node, QString* operand_value)
{
	for (int i = 0; i < current_node.get_children().size(); i++)
	{
		if (current_node.get_children()[i]->get_type() == operation)
		{
			Search_for_first_operand(*current_node.get_children()[i], operand_value);
		}
		else
		{
			if (*operand_value == "")
				*operand_value = current_node.get_children()[i]->get_value();
		}
	}
	return;
}

void Write_nodes(QTextStream& out, Node& current_node)
{
	if (current_node.get_type() == operand)
	{
		out << "<operand>" << current_node.get_value() << "</operand>" << endl;
		return;
	}
	else
	{
		if (current_node.get_type() == operation)
		{
			QString correct_value = current_node.get_value();
			if (current_node.get_value() == ">")
				correct_value = "&gt;";
			else
			{
				if (current_node.get_value() == "<")
					correct_value = "&lt;";
				else
				{
					if (current_node.get_value() == "<=")
						correct_value = "&lt;=";
					else
					{
						if (current_node.get_value() == ">=")
							correct_value = "&gt;=";
					}
				}
			}

			out << "<operation symbol=\"" << correct_value << "\">" << endl;

			for (int i = 0; i < current_node.get_children().size(); i++)
			{
				Write_nodes(out, *current_node.get_children()[i]);
			}
			out << "</operation>" << endl;
		}
		return;
	}
}


void Comparing(Node& node1, Node& node2, bool* are_equal)
{
    if(node1.get_children().size()==node2.get_children().size())
    {
        for(int i=0;i<node1.get_children().size();i++)
        {
            Comparing(*node1.get_children()[i], *node2.get_children()[i], are_equal);
        }
    }
    else
        *are_equal=false;

    if (node1.get_type()!=node2.get_type() || node1.get_value()!=node2.get_value())
        *are_equal=false;
}
