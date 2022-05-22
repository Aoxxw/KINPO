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

/*! Считывает дерево из файла и возвращает соответствующую ошибку, если она найдена
\param[in] file_path[] путь ко входному файлу
\param[in] tree дерево, в которое будет производиться считывание
*/
int Read_tree_from_file(char file_path[], Node& tree);

/*! Обеспечивает рекурсивное считывание каждого из узлов дерева
\param[in] reader - средство считывания из xml-файла 
\param[in,out] parent_node - узел, в который записываются узлы-потомки
\return - номер ошибки, если она есть, или 0 при успешном завершении
*/
int Read_nodes(QXmlStreamReader& reader, Node& parent_node);

/*! Переносит правую часть (не)равенства в левую с использованием функции смены знаков
\param[in,out] tree - обрабатываемое дерево (не)равенства
*/
void Transfering_to_left_side(Node& tree);

/* Объединяет серии узлов операций суммирования, отрицания или умножения
\param[in, out] current_node - текущий узел
\param[in, out] parent_node - родительский узел текущего узла
\param[in] child_pos - позиция текущего узла среди узлов-потомков родительского узла
*/
void Change_sign(Node& current_node, Node& parent_node, int position);

/* Объединяет серии узлов операций суммирования, отрицания или умножения
\param[in, out] current_node - текущий узел
*/
void Uniting_pluses_minuses_multiplications(Node& current_node, Node& parent_node);

/* Рекурсивно сортирует в алфавитном порядке узлы-потомки текущего узла с использованием соответствующей функции
\param[in,out] current_node - текущий узел
*/
void Sorting_in_alphabet_order(Node& current_node);

/*! Сортирует в алфавитном порядке узлов-потомков текущего узла, если его значение – "+" или "*", с использованием функции получения набора значений всех операндов, находящихся в ветви ниже данного узла
\param[in, out] current_node - текущий узел
*/
void Sorting_multiplication_and_sum_operands(Node& current_node);

/*! Получает значение первого(самого левого) встреченного операнда в ветви ниже данного узла
\param[in] current_node - текущий узел
\param[in,out] operand_value - найденное значение операнда
*/
void Search_for_first_operand(Node& current_node, QString* operand_value);

/*! Обеспечивает рекурсивную запись каждого из узлов дерева
\param[in] out - поток для записи
\param[in] current_node - записываемый узел
*/
void Write_nodes(QTextStream& out, Node& current_node);


#endif // DECLARATIONS_H
