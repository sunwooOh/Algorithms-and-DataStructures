#include<iostream>
#include"applebox.h"

using namespace std;

void applebox::set_num_apple(int n) {
	num_apple = n;
}
void applebox::add_one_apple(void) {
	num_apple++;
}
int applebox::get_num_apple(void) {
	return num_apple;
}
