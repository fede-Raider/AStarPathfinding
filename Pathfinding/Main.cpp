#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <array>
#include "Node.h"

using namespace std;

const int width = 100;
const int height = 20;
array<array <Node, height>, width > map;

vector<Node*> openList;
vector<Node*> path;

Node *currentNode;
Node *target;

bool finish = false;

bool compareFunction(Node* a, Node* b) { return ((a->getCostG() + a->getCostH()) > (b->getCostG() + b->getCostH())); }

void generateWalls() {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			int random = rand() % 7;
			if (random == 0) {
				map[i][j] = Node(i, j, CellType::wall);
			} else {
				map[i][j] = Node(i, j, CellType::none);
			}
		}
	}
	int randomX = rand() % width;
	int randomY = rand() % height;
	map[randomX][randomY] = Node(randomX, randomY, CellType::start);
	currentNode = &map[randomX][randomY];

	int randomX2 = rand() % width;
	int randomY2 = rand() % height;

	while (randomX2 == randomX && randomY2 == randomY) {
		randomX2 = rand() % width;
		randomY2 = rand() % height;
	}
	map[randomX2][randomY2] = Node(randomX2, randomY2, CellType::target);
	target = &map[randomX2][randomY2];
}

void draw() {
	system("cls");

	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}

	cout << endl;

	for (int i = 0; i < height; i++) {
		cout << "#";
		for (int j = 0; j < width; j++) {
			switch (map[j][i].getType()) {
			case CellType::none:
				cout << " ";
				break;
			case CellType::open:
				cout << " ";
				break;
			case CellType::close:
				if (find(path.begin(), path.end(), &map[j][i]) == path.end()) {
					cout << ".";
				} else {
					cout << "X";
				}
				break;
			case CellType::wall:
				cout << "#";
				break;
			case CellType::start:
				cout << "S";
				break;
			case CellType::target:
				cout << "F";
				break;
			}
		}
		cout << "#" << endl;
	}

	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
}

void addOpenNode(int x, int y) {
	if (currentNode->getX() + x >= 0 && currentNode->getX() + x < width && currentNode->getY() + y >= 0 && currentNode->getY() + y < height) {
		Node* node = &map[currentNode->getX() + x][currentNode->getY() + y];
		int newCostH = abs(node->getX() - target->getX()) + abs(node->getY() - target->getY());
		if (node->getType() == CellType::none) {
			node->setCostG(currentNode->getCostG() + 1);
			node->setCostH(newCostH);
			node->setParent(currentNode);
			node->setType(CellType::open);
			openList.push_back(node);
		} else if (node->getType() == CellType::close && currentNode->getCostG() + 1 + newCostH < node->getCostG() + node->getCostH()) {
			node->setCostG(currentNode->getCostG() + 1);
			node->setCostH(newCostH);
			node->setParent(currentNode);
		} else if (node->getType() == CellType::target) {
			finish = true;
			Node* it = currentNode;
			while(it->getParent()) {
				path.push_back(it);
				it = it->getParent();
			}
		}
	}
}

void generatePath() {
	addOpenNode(0, -1);
	addOpenNode(1, 0);
	addOpenNode(0, 1);
	addOpenNode(-1, 0);
	if (!finish) {
		//Ordinare
		stable_sort(openList.begin(), openList.end(), compareFunction);
		//
		currentNode = openList.back();
		openList.pop_back();
		currentNode->setType(CellType::close);
	}
}

int main() {
	srand(time(0));

	generateWalls();

	draw();
	system("PAUSE");

	while (!finish) {
		//draw();
		generatePath();
	}
	draw();
	
	cout << "The Shortest path is "<< path.size() <<" cell long: " << endl;
	reverse(path.begin(), path.end());
	for (Node* node : path) {
		cout << "(" << node->getX() << ", " << node->getY() << ") ";
	}
	cout << endl;

	system("PAUSE");
	
}

