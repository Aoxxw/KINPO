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

	if (Read_tree_from_file(argv[2], *tree) == -1)
	{
		out << "Failed to open file" << endl;
		return -2;
	}

	Transfering_to_left_side(*tree);

	Uniting_pluses_minuses_multiplications(*tree);

	Sorting_in_alphabet_order(*tree->children[0]);

	Write_tree_to_file(argv[3], *tree);

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

	input_file->close();
	return 0;
}

int Read_nodes(QXmlStreamReader& Reader, Node& parent_Node)
{
	Node* current_Node = new Node;

	if (Reader.name() == "operation")
	{
		current_Node->type = operation;
		current_Node->value = Reader.attributes().value("symbol").toString();
		parent_Node.children.push_back(current_Node);

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
			current_Node->type = operand;
			current_Node->value = Reader.readElementText();

			parent_Node.children.push_back(current_Node);

			return 0;
		}
	}
}

void Transfering_to_left_side(Node& tree)
{
	if (tree.children[0]->children[1]->value != "0")
	{
		Node* zero_Node = new Node;
		zero_Node->value = "0";
		zero_Node->type = operand;

		Node* plus_Node = new Node;
		plus_Node->value = "+";
		plus_Node->type = operation;
		plus_Node->children.push_back(tree.children[0]->children[0]);
		plus_Node->children.push_back(tree.children[0]->children[1]);

		Change_sign(*plus_Node->children[1], *plus_Node, 1);

		tree.children[0]->children[0] = plus_Node;
		tree.children[0]->children[1] = zero_Node;
	}
}

void Change_sign(Node& current_Node, Node& parent_Node, int child_pos)
{
	if (current_Node.value == "+" || current_Node.value == "-")
	{
		if (current_Node.children.size() != 0)
		{
			for (int i = 0; i < current_Node.children.size(); i++)
			{
				Change_sign(*current_Node.children[i], current_Node, i);
			}
		}
	}
	if (parent_Node.value == "+")
	{
		if (current_Node.value == "-")
		{
			auto iter = parent_Node.children.cbegin();
			parent_Node.children.insert(iter + child_pos, current_Node.children[0]);
			iter = parent_Node.children.cbegin();
			parent_Node.children.erase(iter + child_pos + 1);
		}
		else
		{
			if (current_Node.value != "+")
			{
				Node* minus_Node = new Node;
				minus_Node->value = "-";
				minus_Node->type = operation;
				minus_Node->children.push_back(&current_Node);

				auto iter = parent_Node.children.cbegin();
				parent_Node.children.insert(iter + child_pos, minus_Node);
				iter = parent_Node.children.cbegin();
				parent_Node.children.erase(iter + child_pos + 1);
			}
		}
	}
	return;
}

void Uniting_pluses_minuses_multiplications(Node& current_Node)
{
	for (int j = 0; j < current_Node.children.size(); j++)
	{
		if (current_Node.children[j]->type == operation)
		{
			Uniting_pluses_minuses_multiplications(*current_Node.children[j]);
		}
	}

	for (int i = 0; i < current_Node.children.size(); i++)
	{
		if (current_Node.value == "+")
		{
			if (current_Node.children[i]->value == "+")
			{
				auto iter = current_Node.children.cbegin();
				int size = current_Node.children[i]->children.size();
				current_Node.children.insert(iter + i, current_Node.children[i]->children.begin(), current_Node.children[i]->children.begin() + current_Node.children[i]->children.size());
				iter = current_Node.children.cbegin();
				current_Node.children.erase(iter + i + size);
			}
		}

		if (current_Node.value == "-" && current_Node.children[i]->value == "+")
		{
			current_Node.value = "+";
			current_Node.children = current_Node.children[i]->children;

			for (int i=0;i<current_Node.children.size(); i++)
			{
				Node* minus_Node = new Node;
				minus_Node->value = "-";
				minus_Node->type = operation;
				minus_Node->children.push_back(current_Node.children[i]);

				auto iter = current_Node.children.cbegin();
				current_Node.children.insert(iter + i, minus_Node);
				iter = current_Node.children.cbegin();
				current_Node.children.erase(iter + i + 1);

			}
		}

		if (current_Node.children[i]->value == "-" && current_Node.children[i]->children[0]->value == "-")
		{
			auto iter = current_Node.children.cbegin();
			current_Node.children.insert(iter + i, current_Node.children[i]->children[0]->children.begin(), current_Node.children[i]->children[0]->children.begin() + 1);
			iter = current_Node.children.cbegin();
			current_Node.children.erase(iter + i + 1);
		}
	}
	


	if (current_Node.value == "*")
	{
		for (int i = 0; i < current_Node.children.size(); i++)
		{
			if (current_Node.children[i]->value == "*")
			{
				auto iter = current_Node.children.cbegin();
				int size = current_Node.children[i]->children.size();
				current_Node.children.insert(iter + i, current_Node.children[i]->children.begin(), current_Node.children[i]->children.begin() + current_Node.children[i]->children.size());
				iter = current_Node.children.cbegin();
				current_Node.children.erase(iter + i + size);
			}
		}
	}
	return;
}

void Sorting_in_alphabet_order(Node& current_Node)
{
	if (current_Node.type == operand)
	{
		return;
	}
	else
	{
		if (current_Node.type == operation)
		{
			for (int i = 0; i < current_Node.children.size(); i++)
			{
				Sorting_in_alphabet_order(*current_Node.children[i]);
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
	if ( current_Node.value == "*" || current_Node.value == "+")
	{
		for (int i = 0; i < current_Node.children.size(); i++)
		{
			for (int j = 0; j < current_Node.children.size(); j++)
			{
				if (current_Node.children[i]->type == operand && current_Node.children[j]->type == operand
					&& i<j
					&& current_Node.children[i]->value > current_Node.children[j]->value)
				{
					temp_Node = current_Node.children[i];
					current_Node.children[i] = current_Node.children[j];
					current_Node.children[j] = temp_Node;
				}
				else
				{
					if (current_Node.children[i]->type == operation && current_Node.children[j]->type == operation
						&& i < j)
					{
						std::vector<QString> operands0;
						Collecting_operands(*current_Node.children[i], operands0);
						std::vector<QString> operands1;
						Collecting_operands(*current_Node.children[j], operands1);

						if (operands0[0] > operands1[0])
						{
							temp_Node = current_Node.children[i];
							current_Node.children[i] = current_Node.children[j];
							current_Node.children[j] = temp_Node;
						}
					}

					if (current_Node.children[i]->type == operation && current_Node.children[j]->type == operand
						&& i < j)
					{
						std::vector<QString> operands0;
						Collecting_operands(*current_Node.children[i], operands0);

						if (operands0[0] > current_Node.children[j]->value)
						{
							temp_Node = current_Node.children[i];
							current_Node.children[i] = current_Node.children[j];
							current_Node.children[j] = temp_Node;
						}
					}

					if (current_Node.children[i]->type == operand && current_Node.children[j]->type == operation
						&& i < j)
					{
						std::vector<QString> operands1;
						Collecting_operands(*current_Node.children[j], operands1);

						if (current_Node.children[i]->value > operands1[0])
						{
							temp_Node = current_Node.children[i];
							current_Node.children[i] = current_Node.children[j];
							current_Node.children[j] = temp_Node;
						}
					}
				}
			}
		}
	}
	return;
}

void Collecting_operands(Node& current_Node, std::vector< QString>& all_operands)
{
	for (int i = 0; i < current_Node.children.size(); i++)
	{
		if (current_Node.children[i]->type == operation)
		{
			std::vector<QString> current_operands;
			Collecting_operands(*current_Node.children[i], current_operands);
			for (int j = 0; j < current_operands.size(); j++)
			{
				all_operands.push_back(current_operands[j]);
			}
		}
		else
		{
			all_operands.push_back(current_Node.children[i]->value);
		}
	}

	return;
}

int Write_tree_to_file(char file_path[], Node& tree)
{
	QFile output_file(file_path);
	output_file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&output_file);

	Write_nodes(out, *tree.children[0]);

	output_file.close();
	return 0;
}

void Write_nodes(QTextStream& out, Node& current_Node)
{
	if (current_Node.type == operand)
	{
		out << "<operand>" << current_Node.value << "</operand>" << endl;
		return;
	}
	else
	{
		if (current_Node.type == operation)
		{
			QString correct_value = current_Node.value;
			if (current_Node.value == ">")
				correct_value = "&gt;";
			else
			{
				if (current_Node.value == "<")
					correct_value = "&lt;";
				else
				{
					if (current_Node.value == "<=")
						correct_value = "&lt;=";
					else
					{
						if (current_Node.value == ">=")
							correct_value = "&gt;=";
					}
				}
			}

			out << "<operation symbol=\"" << correct_value << "\">" << endl;

			for (int i = 0; i < current_Node.children.size(); i++)
			{
				Write_nodes(out, *current_Node.children[i]);
			}
			out << "</operation>" << endl;
		}
		return;
	}
}
