#include "Node.h"


Node::Node() : x{ -1 }, y{ -1 } {
}

Node::Node(int x, int y, CellType tipo) : x{ x }, y{ y }, tipo{ tipo } {
}

int Node::getCostG() const {
	return costG;
}

int Node::getCostH() const {
	return costH;
}

void Node::setParent(Node * father) {
	parent = father;
}

Node * Node::getParent() const {
	return parent;
}

int Node::getX() const {
	return x;
}

int Node::getY() const {
	return y;
}

void Node::setType(CellType tipo) {
	this->tipo = tipo;
}

CellType Node::getType() const {
	return tipo;
}

void Node::setCostH(int cost) {
	costH = cost;
}

void Node::setCostG(int cost) {
	costG = cost;
}
