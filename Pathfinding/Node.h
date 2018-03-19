#include "CellType.h"
#pragma once


class Node {
public:
	Node();
	Node(int x, int y, CellType tipo);
	int getX() const;
	int getY() const;
	void setType(CellType tipo);
	CellType getType() const;
	void setCostH(int cost);
	void setCostG(int cost);
	int getCostG() const;
	int getCostH() const;
	void setParent(Node *father);
	Node*getParent() const;
private:
	CellType tipo = CellType::open;
	int x , y;
	int costH = 0, costG = 0;
	Node* parent = nullptr;
};