#include<iostream>
#include"applebox.h"

using namespace std;

applebox::applebox() {
	num_apple = 0;
}
void applebox::set_box_size(int size) {
	size_of_box = size;
}
void applebox::set_num_apple(int n) {
	num_apple = n;
}
void applebox::add_one_apple(void) {
	num_apple++;
}
void applebox::remove_one_apple(void) {
	num_apple--;
}
int applebox::get_num_apple(void) {
	return num_apple;
}
int applebox::get_box_size(void) {
	return size_of_box;
}
bool applebox::is_empty(void) {
	return num_apple == 0 ? true : false;
}
bool applebox::is_full(void) {
	return num_apple == size_of_box ? true : false;
}
