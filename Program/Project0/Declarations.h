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
\param[in] position - позиция текущего узла среди узлов-потомков родительского узла
*/
void Change_sign(Node& current_node, Node& parent_node, int child_pos);

/* Объединяет серии узлов операций суммирования, отрицания или умножения
\param[in, out] current_node - текущий узел
\param[in,out] patent_nade - родительский узел
*/
void Uniting_pluses_minuses_multiplications(Node& current_node);

/* Рекурсивно сортирует в алфавитном порядке узлы-потомки текущего узла с использованием соответствующей функции
\param[in,out] current_node - текущий узел
*/
void Sorting_in_alphabet_order(Node& current_node);

/*! Сортирует в алфавитном порядке узлов-потомков текущего узла, если его значение – "+" или "*", с использованием функции получения набора значений всех операндов, находящихся в ветви ниже данного узла
\param[in, out] current_node - текущий узел
*/
void Sorting_multiplication_and_sum_operands(Node& current_node);

/*! Получает значения всех операндов в ветви ниже данного узла
\param[in] current_node - текущий узел
\param[in,out] all_operands - вектор найденных значений операнда
*/
void Collecting_operands(Node& current_Node, std::vector< QString>& all_operands);

/*! Обеспечивает запись дерева в файл
\param[in] file_path[] - путь к файлу
\param[in] tree - записываемое дерево
*/
int Write_tree_to_file(char file_path[], Node& tree);

/*! Обеспечивает рекурсивную запись каждого из узлов дерева
\param[in] out - поток для записи
\param[in] current_node - записываемый узел
*/
void Write_nodes(QTextStream& out, Node& current_node);




