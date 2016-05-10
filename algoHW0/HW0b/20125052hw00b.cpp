#include<iostream>
#include"applebox.h"

using namespace std;

int main() {

	int app_num, box_size, decision = 1, box_num;
	applebox* appleBox = new applebox[3];
	for (int i = 0; i < 3; i++) {
		cout << "Size of the " << i + 1 << "th box : ";
		cin >> box_size;
		appleBox[i].set_box_size(box_size);
	}
	while (decision != 3) {
		cout << "If you want to put an apple, enter 1. take out, enter 2, quit the program, enter 3 : ";
		cin >> decision;
		if (decision == 1) {
			cout << "Which box? (1, 2, 3): ";
			cin >> box_num;
			if (!appleBox[box_num - 1].is_full())
				appleBox[box_num - 1].add_one_apple();
			else
				cout << "The box is full!" << endl;
		}
		else if (decision == 2) {
			cout << "Which box? (1, 2, 3): ";
			cin >> box_num;
			if (!appleBox[box_num - 1].is_empty())
				appleBox[box_num - 1].remove_one_apple();
			else
				cout << "The box is empty!" << endl;
		}
	}
	for (int i = 0; i < 3; i++)
		cout << "box " << i + 1 << ": size : " << appleBox[i].get_box_size() << " apple : " << appleBox[i].get_num_apple() << endl;

}
