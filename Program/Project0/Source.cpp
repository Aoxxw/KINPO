#include <iostream>
#include "../Project0/Declarations.h"

int main(int argc, char* argv[])
{
	QFile output_file(argv[3]);
	output_file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&output_file);

	if (argc != 4) {
		out << "Too many arguments." << endl;
		return -1;
	}

	Node* tree = new Node;

	QString error_text="";
	switch (Read_tree_from_file(argv[2], *tree))
	{
	case -1:
		error_text = "Invalid input file specified. The file may not exist.";
	case -2:
		error_text = "The file extension is incorrect. The file must have the extension .xml";
	case -3:
		error_text = "The file can not be read. The input file may not have the correct syntax.";
	case -4:
		error_text = "The source tree contains unsupported operations.";
	case -5:
		error_text = "The length of one or more operands exceeds the maximum length (100 characters).";
	case -6:
		error_text = "No comparison signs were encountered in the input file.";
	case -7:
		error_text = "Incorrect location of the comparison operation in the input tree.";
	case -8:
		error_text = "One or more operations correspond to an incorrect number of operands.";
	default:

		QFile output_file(argv[3]);
		output_file.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream out(&output_file);

		out << error_text;

		

		break;
	}

	Transfering_to_left_side(*tree);

	Uniting_pluses_minuses_multiplications(*tree);

	Sorting_in_alphabet_order(*tree->get_children()[0]);

	Write_tree_to_file(argv[3], *tree);

	output_file.close();
	return 0;

	/*	int count = 0;
		while (!Reader.atEnd())
		{
			Reader.readNext();
			if (Reader.hasError())
			{
				out << "Errors in xml." << endl;
				return -2;
			}
			if (Reader.isStartElement())
			{
				count++;
			}
		}*/
}

int Read_tree_from_file(char file_path[], Node& tree)
{
	QFile* input_file = new QFile(file_path);

	if (!input_file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return -1;
	}

	QXmlStreamReader Reader(input_file);

	Reader.readNextStartElement();

	Read_nodes(Reader, tree);
	tree = *tree.get_children()[0];

	input_file->close();
	return 0;
}

int Read_nodes(QXmlStreamReader& Reader, Node& parent_Node)
{
	Node* current_Node = new Node;

	if (Reader.name() == "operation")
	{
		current_Node->set_type(operation);
		current_Node->set_value(Reader.attributes().value("symbol").toString());
		parent_Node.add_child(current_Node);

		while (true)
		{
			Reader.readNext();
			while (!Reader.isStartElement() && !Reader.atEnd())
			{
				Reader.readNext();
				if (Reader.isEndElement() && Reader.name() == "operation")
				{
					return 0;
				}
			}
			if (Reader.atEnd())
			{
				return -1;
			}
			Read_nodes(Reader, *current_Node);
		}
	}
	else
	{
		if (Reader.name() == "operand")
		{
			current_Node->set_type(operand);
			current_Node->set_value(Reader.readElementText());

			parent_Node.add_child(current_Node);

			return 0;
		}
	}
}

void Transfering_to_left_side(Node& Main_node)
{
	if (Main_node.get_children()[1]->get_value() != "0")
	{
		Node* zero_Node = new Node;
		zero_Node->set_value("0");
		zero_Node->set_type(operand);

		Node* plus_Node = new Node;
		plus_Node->set_value("+");
		plus_Node->set_type(operation);
		plus_Node->add_child(Main_node.get_children()[0]);
		plus_Node->add_child(Main_node.get_children()[1]);

		Change_sign(*plus_Node->get_children()[1], *plus_Node, 1);

		Main_node.change_child(plus_Node,0);
		Main_node.change_child(zero_Node,1);
	}
	return;
}

void Change_sign(Node& current_Node, Node& parent_Node, int child_pos)
{
	if (current_Node.get_value() == "+" || current_Node.get_value() == "-")
	{
		if (current_Node.get_children().size() != 0)
		{
			for (int i = 0; i < current_Node.get_children().size(); i++)
			{
				Change_sign(*current_Node.get_children()[i], current_Node, i);
			}
		}
	}
	if (parent_Node.get_value() == "+")
	{
		if (current_Node.get_value() == "-")
		{
			auto iter = parent_Node.get_children().cbegin();
			parent_Node.get_children().insert(iter + child_pos, current_Node.get_children()[0]);
			iter = parent_Node.get_children().cbegin();
			parent_Node.get_children().erase(iter + child_pos + 1);
		}
		else
		{
			if (current_Node.get_value() != "+")
			{
				Node* minus_Node = new Node;
				minus_Node->set_value("-");
				minus_Node->set_type(operation);
				minus_Node->add_child(&current_Node);

				auto iter = parent_Node.get_children().cbegin();
				parent_Node.get_children().insert(iter + child_pos, minus_Node);
				iter = parent_Node.get_children().cbegin();
				parent_Node.get_children().erase(iter + child_pos + 1);
			}
		}
	}
	return;
}

void Uniting_pluses_minuses_multiplications(Node& current_Node)
{
	for (int j = 0; j < current_Node.get_children().size(); j++)
	{
		if (current_Node.get_children()[j]->get_type() == operation)
		{
			Uniting_pluses_minuses_multiplications(*current_Node.get_children()[j]);
		}
	}

	for (int i = 0; i < current_Node.get_children().size(); i++)
	{
		if (current_Node.get_value() == "+")
		{
			if (current_Node.get_children()[i]->get_value() == "+")
			{
				auto iter = current_Node.get_children().cbegin();
				int size = current_Node.get_children()[i]->get_children().size();
				current_Node.get_children().insert(iter + i, current_Node.get_children()[i]->get_children().begin(), current_Node.get_children()[i]->get_children().begin() + current_Node.get_children()[i]->get_children().size());
				iter = current_Node.get_children().cbegin();
				current_Node.get_children().erase(iter + i + size);
			}
		}

		if (current_Node.get_value() == "-" && current_Node.get_children()[i]->get_value() == "+")
		{
			current_Node.set_value("+");
			current_Node.set_children(current_Node.get_children()[i]->get_children());

			for (int i=0;i<current_Node.get_children().size(); i++)
			{
				Node* minus_Node = new Node;
				minus_Node->set_value("-");
				minus_Node->set_type(operation);
				minus_Node->add_child(current_Node.get_children()[i]);

				auto iter = current_Node.get_children().cbegin();
				current_Node.get_children().insert(iter + i, minus_Node);
				iter = current_Node.get_children().cbegin();
				current_Node.get_children().erase(iter + i + 1);

			}
		}

		if (current_Node.get_children()[i]->get_value() == "-" && current_Node.get_children()[i]->get_children()[0]->get_value() == "-")
		{
			auto iter = current_Node.get_children().cbegin();
			current_Node.get_children().insert(iter + i, current_Node.get_children()[i]->get_children()[0]->get_children().begin(), current_Node.get_children()[i]->get_children()[0]->get_children().begin() + 1);
			iter = current_Node.get_children().cbegin();
			current_Node.get_children().erase(iter + i + 1);
		}
	}
	
	if (current_Node.get_value() == "*")
	{
		for (int i = 0; i < current_Node.get_children().size(); i++)
		{
			if (current_Node.get_children()[i]->get_value() == "*")
			{
				auto iter = current_Node.get_children().cbegin();
				int size = current_Node.get_children()[i]->get_children().size();
				current_Node.get_children().insert(iter + i, current_Node.get_children()[i]->get_children().begin(), current_Node.get_children()[i]->get_children().begin() + current_Node.get_children()[i]->get_children().size());
				iter = current_Node.get_children().cbegin();
				current_Node.get_children().erase(iter + i + size);
			}
		}
	}
	return;
}

void Sorting_in_alphabet_order(Node& current_Node)
{
	if (current_Node.get_type() == operand)
	{
		return;
	}
	else
	{
		if (current_Node.get_type() == operation)
		{
			for (int i = 0; i < current_Node.get_children().size(); i++)
			{
				Sorting_in_alphabet_order(*current_Node.get_children()[i]);
			}
			Sorting_multiplication_and_sum_operands(current_Node);
		}
		return;
	}
	return;
}

void Sorting_multiplication_and_sum_operands(Node& current_Node)
{
	Node* temp_Node;
	if ( current_Node.get_value() == "*" || current_Node.get_value() == "+")
	{
		for (int i = 0; i < current_Node.get_children().size(); i++)
		{
			for (int j = 0; j < current_Node.get_children().size(); j++)
			{
				if (current_Node.get_children()[i]->get_type() == operand && current_Node.get_children()[j]->get_type() == operand
					&& i<j
					&& current_Node.get_children()[i]->get_value() > current_Node.get_children()[j]->get_value())
				{
					temp_Node = current_Node.get_children()[i];
					current_Node.change_child(current_Node.get_children()[j],i);
					current_Node.change_child(temp_Node,j);
				}
				else
				{
					if (current_Node.get_children()[i]->get_type() == operation && current_Node.get_children()[j]->get_type() == operation
						&& i < j)
					{
						QString operand_value1 = "";
						QString operand_value2 = "";
						Search_for_first_operand(*current_Node.get_children()[i], &operand_value1);
						Search_for_first_operand(*current_Node.get_children()[j], &operand_value2);

						if (operand_value1 > operand_value2)
						{
							temp_Node = current_Node.get_children()[i];
							current_Node.change_child(current_Node.get_children()[j], i);
							current_Node.change_child(temp_Node, j);
						}
					}

					if (current_Node.get_children()[i]->get_type() == operation && current_Node.get_children()[j]->get_type() == operand
						&& i < j)
					{
						QString operand_value = "";
						Search_for_first_operand(*current_Node.get_children()[i], &operand_value);
						if (operand_value > current_Node.get_children()[j]->get_value())
						{
							temp_Node = current_Node.get_children()[i];
							current_Node.change_child(current_Node.get_children()[j], i);
							current_Node.change_child(temp_Node, j);
						}
					}

					if (current_Node.get_children()[i]->get_type() == operand && current_Node.get_children()[j]->get_type() == operation
						&& i < j)
					{
						QString operand_value = "";
						Search_for_first_operand(*current_Node.get_children()[j], &operand_value);
						if (current_Node.get_children()[i]->get_value() > operand_value)
						{
							temp_Node = current_Node.get_children()[i];
							current_Node.change_child(current_Node.get_children()[j], i);
							current_Node.change_child(temp_Node, j);
						}
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

int Write_tree_to_file(char file_path[], Node& tree)
{
	QFile output_file(file_path);
	output_file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&output_file);

	Write_nodes(out, *tree.get_children()[0]);

	output_file.close();
	return 0;
}

void Write_nodes(QTextStream& out, Node& current_Node)
{
	if (current_Node.get_type() == operand)
	{
		out << "<operand>" << current_Node.get_value() << "</operand>" << endl;
		return;
	}
	else
	{
		if (current_Node.get_type() == operation)
		{
			QString correct_value = current_Node.get_value();
			if (current_Node.get_value() == ">")
				correct_value = "&gt;";
			else
			{
				if (current_Node.get_value() == "<")
					correct_value = "&lt;";
				else
				{
					if (current_Node.get_value() == "<=")
						correct_value = "&lt;=";
					else
					{
						if (current_Node.get_value() == ">=")
							correct_value = "&gt;=";
					}
				}
			}

			out << "<operation symbol=\"" << correct_value << "\">" << endl;

			for (int i = 0; i < current_Node.get_children().size(); i++)
			{
				Write_nodes(out, *current_Node.get_children()[i]);
			}
			out << "</operation>" << endl;
		}
		return;
	}
}
