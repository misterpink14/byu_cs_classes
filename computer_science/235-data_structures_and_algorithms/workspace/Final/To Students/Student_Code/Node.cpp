/*
 * Node.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: misterpink14
 */

#include "Node.h"


Node::Node() : data(0), height(0), left(NULL), right(NULL) {}

Node::Node(int d, int h, Node* l, Node* r)
{
	this->data = d;
	this->height = h;
	this->left = l;
	this->right = r;
}


int Node::getData()
{
	return this->data;
}




Node * Node::getLeftChild()
{
	return this->left;
}



Node * Node::getRightChild()
{
	return this->right;
}



int Node::getHeight()
{
	return this->height;
}

