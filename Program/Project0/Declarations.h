#pragma once
#include <vector>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <qtextstream>
#include <stdio.h>
#include <ctype.h>
#include <QRegularExpression>

enum Node_type { operation, operand };

class Node {

public:
	Node_type type;
	QString value;
	std::vector<Node*> children;
private:
	
};

/*! ��������� ������ �� ����� � ���������� ��������������� ������, ���� ��� �������
\param[in] file_path[] ���� �� �������� �����
\param[in] tree ������, � ������� ����� ������������� ����������
*/
int Read_tree_from_file(char file_path[], Node& tree);

/*! ������������ ����������� ���������� ������� �� ����� ������
\param[in] reader - �������� ���������� �� xml-����� 
\param[in,out] parent_node - ����, � ������� ������������ ����-�������
\return - ����� ������, ���� ��� ����, ��� 0 ��� �������� ����������
*/
int Read_nodes(QXmlStreamReader& reader, Node& parent_node);

/*! ��������� ������ ����� (��)��������� � ����� � �������������� ������� ����� ������
\param[in,out] tree - �������������� ������ (��)���������
*/
void Transfering_to_left_side(Node& tree);

/* ���������� ����� ����� �������� ������������, ��������� ��� ���������
\param[in, out] current_node - ������� ����
\param[in, out] parent_node - ������������ ���� �������� ����
\param[in] position - ������� �������� ���� ����� �����-�������� ������������� ����
*/
void Change_sign(Node& current_node, Node& parent_node, int child_pos);

/* ���������� ����� ����� �������� ������������, ��������� ��� ���������
\param[in, out] current_node - ������� ����
\param[in,out] patent_nade - ������������ ����
*/
void Uniting_pluses_minuses_multiplications(Node& current_node);

/* ���������� ��������� � ���������� ������� ����-������� �������� ���� � �������������� ��������������� �������
\param[in,out] current_node - ������� ����
*/
void Sorting_in_alphabet_order(Node& current_node);

/*! ��������� � ���������� ������� �����-�������� �������� ����, ���� ��� �������� � "+" ��� "*", � �������������� ������� ��������� ������ �������� ���� ���������, ����������� � ����� ���� ������� ����
\param[in, out] current_node - ������� ����
*/
void Sorting_multiplication_and_sum_operands(Node& current_node);

/*! �������� �������� ���� ��������� � ����� ���� ������� ����
\param[in] current_node - ������� ����
\param[in,out] all_operands - ������ ��������� �������� ��������
*/
void Collecting_operands(Node& current_Node, std::vector< QString>& all_operands);

/*! ������������ ������ ������ � ����
\param[in] file_path[] - ���� � �����
\param[in] tree - ������������ ������
*/
int Write_tree_to_file(char file_path[], Node& tree);

/*! ������������ ����������� ������ ������� �� ����� ������
\param[in] out - ����� ��� ������
\param[in] current_node - ������������ ����
*/
void Write_nodes(QTextStream& out, Node& current_node);




