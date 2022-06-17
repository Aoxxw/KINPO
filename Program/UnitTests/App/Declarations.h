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


/*!
 * \brief Node_type - enumeration of possible node types
 */
enum Node_type { operation, operand };

/*!
 * \brief Node - expression tree node class
 * \detailed The class stores information about the type, value and children nodes of the node; has methods for setting, getting and editing this information
*/
class Node {

public:

    /*!
     * \brief set_type - setting node type
     * \param[in] type - node type
     */
	void set_type(Node_type type)
	{
		this->type = type;
	}

    /*!
     * \brief set_value - setting node value
     * \param[in] value - node value
     */
	void set_value(QString value)
	{
		this->value = value;
	}

    /*!
     * \brief set_children - setting child nodes
     * \param[in] children - array of child nodes
     */
	void set_children(std::vector<Node*> children)
	{
		this->children = children;
	}

    /*!
     * \brief add_child - adding a node to the end of an array of child nodes
     * \param child - node
     */
	void add_child(Node* child)
	{
		this->children.push_back(child);
	}

    /*!
     * \brief change_child - child node replacement
     * \param child - replacing node
     * \param pos - position of the replaced node in the array of child nodes
     */
    void change_child(Node* child, int pos)
	{
        this->children[pos] = child;
	}

    /*!
     * \brief insert_children - inserting child nodes
     * \param position - insertion position
     * \param children_to_insert - inserted nodes
     */
	void insert_children(int position, std::vector<Node*> children_to_insert)
	{
		auto iter = this->children.cbegin();
		this->children.insert(iter + position, children_to_insert.begin(), children_to_insert.begin()+ children_to_insert.size());
		iter = this->children.cbegin();
	}

    /*!
     * \brief insert_children - inserting a child node
     * \param position - insertion position
     * \param child_to_insert - inserted node
     */
	void insert_children(int position, Node& child_to_insert)
	{
		auto iter = this->children.cbegin();
		this->children.insert(iter + position, &child_to_insert);
		iter = this->children.cbegin();
	}

    /*!
     * \brief erase_child - deleting a child node
     * \param position - deleted node position
     */
	void erase_child(int position)
	{
		auto iter = this->children.cbegin();
		this->children.erase(iter + position);
	}

    /*!
     * \brief get_type - getting node type
     * \return node type
     */
	Node_type get_type()
	{
		return this->type;
	}

    /*!
     * \brief get_value - getting node value
     * \return node value
     */
	QString get_value()
	{
		return this->value;
	}

    /*!
     * \brief get_children - getting child nodes
     * \return array of child nodes
     */
	std::vector<Node*> get_children()
	{
		return this->children;
	}

private:
    /*!
     * \brief type - node type
     */
	Node_type type;

    /*!
     * \brief value - value type
     */
	QString value;

    /*!
     * \brief children - array of child nodes
     */
	std::vector<Node*> children;
};

/*! Checks if two nodes are equal (for testing)
\param[in] node1 - first node
\param[in] node2 - second node
\param[out] are_equal - node equality mark
*/
void Comparing(Node& node1, Node& node2, bool* are_equal);

/*! Reads a tree from a file and returns the appropriate error if found
\param[in] file_path[] - path to input file
\param[in] tree - the tree to read into
\return error number, if found, or 0 on success
*/
int Read_tree_from_file(char file_path[], Node& tree);

/*! Provides a recursive reading of each of the tree nodes
\param[in] reader - xml file reader
\param[in,out] parent_node - the node to which child nodes are written
\param[in,out] number_of_iteration - the current number of recursive calls of this function
\return error number, if found, or 0 on success
*/
int Read_nodes(QXmlStreamReader& reader, Node& parent_node, int& number_of_iteration);

/*! Moves the right side of an (in)equality to the left using the sign change function
\param[in,out] tree - processed tree of (in)equalities
*/
void Transfering_to_left_side(Node& tree);

/*! Changes the sign of the given node
\param[in, out] current_node - current node
\param[in, out] parent_node - parent node of the current node
\param[in] position - the position of the current node among the child nodes of the parent node
*/
void Change_sign(Node& current_node, Node& parent_node, int position);

/*! Combines a series of nodes for summation, negation, or multiplication operations
\param[in, out] current_node - current node
\param[in,out] patent_nade - parent node of the current node
*/
void Uniting_pluses_minuses_multiplications(Node& current_node, Node& parent_node);

/*! Recursively sorts child nodes of the current node alphabetically using the appropriate function
\param[in,out] current_node - current node
*/
void Sorting_in_alphabet_order(Node& current_node);

/*! Sorts the child nodes of the current node alphabetically if its value is "+" or "*"
\param[in, out] current_node - current node
*/
void Sorting_multiplication_and_sum_operands(Node& current_node);

/*! Gets the value of the first (leftmost) encountered operand in the branch below the given node
\param[in] current_node - current node
\param[in,out] operand_value - found operand value
*/
void Search_for_first_operand(Node& current_node, QString* operand_value);

/*! Provides recursive writing of each of the tree nodes
\param[in] out - writing stream
\param[in] current_node - current writed node
*/
void Write_nodes(QTextStream& out, Node& current_node);

#endif // DECLARATIONS_H
