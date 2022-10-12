#pragma once
#include "Node.h"
#include <iostream>  
#include <iomanip>
using namespace std;


class Deque :
    public Node
{
private:
    Node* head;
    Node* tail;
public:
    //constructor and deconstrcutor
    Deque() : head(nullptr), tail(nullptr) {}
    ~Deque();

    void push_front(string food, int size);
    void push_back(string food, int size);

    bool pop_front();
    bool pop_back();

    bool peek_front(string& food, int& size);
    bool peek_back(string& food, int& size);
    void display(ostream& os);

    friend ostream& operator<<(ostream& os, Deque& right);
};

