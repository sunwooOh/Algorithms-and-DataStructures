#include"applebox.h"
#include<iostream>

using namespace std;

int main() {
	applebox appleBox;
	int app_num, decision = 1;
	cout << "How many apples in the box? :";
	cin >> app_num;
	appleBox.set_num_apple(app_num);
	while (decision == 1) {
		cout << "If you want to put an apple, enter 1. If you want to quit, enter 2 :";
		cin >> decision;
		if (decision == 1)
			appleBox.add_one_apple();
	}
	cout << "apple : " << appleBox.get_num_apple() << endl;

	return 0;
}
