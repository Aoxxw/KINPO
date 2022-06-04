#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <vector>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <qtextstream>
#include <stdio.h>
#include <ctype.h>
#include <QRegularExpression>
#include <QDebug>
#include <QFileInfo>

enum Node_type { operation, operand };

class Node {

public:

	void set_type(Node_type type)
	{
		this->type = type;
	}

	void set_value(QString value)
	{
		this->value = value;
	}

	void set_children(std::vector<Node*> children)
	{
		this->children = children;
	}

	void add_child(Node* child)
	{
		this->children.push_back(child);
	}

	void change_child(Node* child, int i)
	{
		this->children[i] = child;
	}

	void insert_children(int position, std::vector<Node*> children_to_insert)
	{
		auto iter = this->children.cbegin();
		this->children.insert(iter + position, children_to_insert.begin(), children_to_insert.begin()+ children_to_insert.size());
		iter = this->children.cbegin();
	}

	void insert_children(int position, Node& child_to_insert)
	{
		auto iter = this->children.cbegin();
		this->children.insert(iter + position, &child_to_insert);
		iter = this->children.cbegin();
	}

	void erase_child(int position)
	{
		auto iter = this->children.cbegin();
		this->children.erase(iter + position);
	}

	Node_type get_type()
	{
		return this->type;
	}

	QString get_value()
	{
		return this->value;
	}

	std::vector<Node*> get_children()
	{
		return this->children;
	}

private:
	Node_type type;
	QString value;
	std::vector<Node*> children;
};

/*! ������� �������� ��������� ���� �����(��� ������������)
\param[in] node1 - ������ ����
\param[in] node2 - ������ ����
\param[out] are_equal - ���������� ��������� �����
*/
void Comparing(Node& node1, Node& node2, bool* are_equal);

/*! ��������� ������ �� ����� � ���������� ��������������� ������, ���� ��� �������
\param[in] file_path[] ���� �� �������� �����
\param[in] tree ������, � ������� ����� ������������� ����������
*/
int Read_tree_from_file(char file_path[], Node& tree);

/*! ������������ ����������� ���������� ������� �� ����� ������
\param[in] reader - �������� ���������� �� xml-�����
\param[in,out] parent_node - ����, � ������� ������������ ����-�������
\param[in,out] number_of_iteration - ������� ���������� ����������� ������� ������ �������
\return - ����� ������, ���� ��� ����, ��� 0 ��� �������� ����������
*/
int Read_nodes(QXmlStreamReader& reader, Node& parent_node, int& number_of_iteration);

/*! ��������� ������ ����� (��)��������� � ����� � �������������� ������� ����� ������
\param[in,out] tree - �������������� ������ (��)���������
*/
void Transfering_to_left_side(Node& tree);

/*! ���������� ����� ����� �������� ������������, ��������� ��� ���������
\param[in, out] current_node - ������� ����
\param[in, out] parent_node - ������������ ���� �������� ����
\param[in] position - ������� �������� ���� ����� �����-�������� ������������� ����
*/
void Change_sign(Node& current_node, Node& parent_node, int position);

/*! ���������� ����� ����� �������� ������������, ��������� ��� ���������
\param[in, out] current_node - ������� ����
\param[in,out] patent_nade - ������������ ����
*/
void Uniting_pluses_minuses_multiplications(Node& current_node, Node& parent_node);

/*! ���������� ��������� � ���������� ������� ����-������� �������� ���� � �������������� ��������������� �������
\param[in,out] current_node - ������� ����
*/
void Sorting_in_alphabet_order(Node& current_node);

/*! ��������� � ���������� ������� �����-�������� �������� ����, ���� ��� �������� � "+" ��� "*"
\param[in, out] current_node - ������� ����
*/
void Sorting_multiplication_and_sum_operands(Node& current_node);

/*! �������� �������� �������(������ ������) ������������ �������� � ����� ���� ������� ����
\param[in] current_node - ������� ����
\param[in,out] operand_value - ��������� �������� ��������
*/
void Search_for_first_operand(Node& current_node, QString* operand_value);

/*! ������������ ����������� ������ ������� �� ����� ������
\param[in] out - ����� ��� ������
\param[in] current_node - ������������ ����
*/
void Write_nodes(QTextStream& out, Node& current_node);

#endif // DECLARATIONS_H
