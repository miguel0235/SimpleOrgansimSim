#pragma once
#include <string>
using namespace std;

class Node
{
public:
	string foodName;
	int foodSize;

	Node* next;
	Node* prev;

	Node() : foodSize(0), next(nullptr), prev(nullptr) {}
	Node(string foodName, int foodSize) : foodName(foodName), foodSize(foodSize), next(nullptr), prev(nullptr) {}
	Node(string foodName, int foodSize, Node* next, Node* prev) : foodName(foodName), foodSize(foodSize), next(next), prev(prev) {}
};

