#include<iostream>
#include<string.h>
#include<assert.h>
#include"Stack.h"

using namespace std;

Stack::Stack(int cap) {
	capacity = cap;
	p = new char[capacity];
	length = 0;
	head = 0;
}
void Stack::push(char x) {
	if (length == 0) { p[head] = x; length++; }
	else if (length < capacity) {
		head++; length++;
		p[head] = x;
	}
	else {
		char *q = new char[2 * capacity];
		for (int i = 0; i < capacity; i++) q[i] = p[i];
		head = capacity;
		q[head] = x;
		length++;
		capacity = 2 * capacity;
		delete[] p;
		p = q;
	}
}
char Stack::pop() {
	assert(length > 0);
	char x = p[head];
	head > 0 ? head-- : head = 0;
	length--;
	return x;
}
char Stack::peekHead() {
	assert(length > 0);
	char x = p[head];
	return x;
}

dStack::dStack(int cap) {
	capacity = cap;
	p = new double[capacity];
	length = 0;
	head = 0;
}
void dStack::push(double x) {
	if (length == 0) { p[head] = x; length++; }
	else if (length < capacity) {
		head++; length++;
		p[head] = x;
	}
	else {
		double *q = new double[2 * capacity];
		for (int i = 0; i < capacity; i++) q[i] = p[i];
		head = capacity;
		q[head] = x;
		length++;
		capacity = 2 * capacity;
		delete[] p;
		p = q;
	}
}
double dStack::pop() {
	assert(length > 0);
	double x = p[head];
	head > 0 ? head-- : head = 0;
	length--;
	return x;
}
double dStack::peekHead() {
	assert(length > 0);
	double x = p[head];
	return x;
}

enum precedence{
	lparen,
	rparen,
	pluss,
	minuss,
	times,
	divide,
	eos,
	operand
};

precedence get_token(char symbol) {
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return pluss;
	case '-': return minuss;
	case '/': return divide;
	case '*': return times;
	case ' ': return eos;
	default: return operand;
	}
}

char* toPostfix(char* expr) {
	char symbol;
	precedence token;
	int n = 0;
	int len = strlen(expr);

	static int isp[] = { 0, 19, 12, 12, 13, 13, 0 };
	static int icp[] = { 20, 19, 12, 12, 13, 13, 0 };
	
	Stack result;
	Stack S;
	S.push(' ');

	for (token = get_token(*expr); token != eos; token = get_token(*expr)) {
		symbol = *expr; expr++; n++;
		if (token == operand && symbol != '\0')
			result.push(symbol);
		else if (token == rparen) {
			while (S.peekHead() != '(')
				result.push(S.pop());
			S.pop();
		}
		else {
			while (isp[get_token(S.peekHead())] >= icp[token] && S.size() > 1)
				result.push(S.pop());
			S.push(symbol);
		}
		if (len < n)
			break;
	}
	result.push('\0');
	return result.returnP();
}

double eval(char* expr) {
	precedence token;
	dStack S;
	char symbol = 'a';
	double op1, op2;
	int n = 0;

	symbol = *expr;
	token = get_token(*expr);
	expr++;

	while (symbol != '\0') {
		if (symbol >= 65 && symbol < 91)
			S.push(symbol - 64);
		else if (symbol >= 97 && symbol < 123)
			S.push(symbol - 96);
		else if (token == operand)
			S.push(symbol - '0');
		else {
			op2 = S.pop();
			op1 = S.pop();
			switch (token) {
			case pluss: S.push(op1 + op2); break;
			case minuss: S.push(op1 - op2); break;
			case times: S.push(op1*op2); break;
			case divide: S.push(op1 / op2); break;
			}
		}
		symbol = *expr;
		token = get_token(*expr);
		expr++;
	}
	return S.pop();
}

int main() {
	char *str = new char[50];
	char *res;
	double val;

	cout << "Input infix expression: ";
	cin >> str;

	res = toPostfix(str);

	cout << "Postfix expression is: ";
	for (int i = 0; i < strlen(res); i++)
		cout << res[i];

	val = eval(res);

	cout << endl << "Evalutation is: " << val;
	
	return 0;
 }

