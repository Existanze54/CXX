#include <cassert>
#include <List.h>

void test_1() {
	List data_list;
	Data data;

	data = { 1, "one"};
	data_list.add(data);
	assert(data_list.count() == 1);

	data = { 2, "two" };
	data_list.add(data);
	assert(data_list.count() == 2);
}

void test_2() {
	List data_list;
	Data data;

	data = { 1, "one" };
	data_list.add(data);
	assert(data_list.count() == 1);

	data = { 1, "one" };
	data_list.add(data);
	assert(data_list.count() == 2);

	data = { 1, "two" };
	data_list.add(data);
	assert(data_list.count() == 3);
}

int main(int argc, char* argv[]){
	test_1();
	test_2();
	return 0;
}