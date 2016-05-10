#pragma once
class Stack {
public:
	Stack(int cap = 50);
	void push(char x);
	char peekHead();
	char pop();
	int size() { return length; }
	bool isEmpty() { return (length == 0); }
	char* returnP() { return p; }

private:
	int capacity;
	char *p;
	int length;
	int head;
};

class dStack {
public:
	dStack(int cap = 50);
	void push(double x);
	double peekHead();
	double pop();
	int size() { return length; }
	bool isEmpty() { return (length == 0); }

private:
	int capacity;
	double *p;
	int length;
	int head;
};