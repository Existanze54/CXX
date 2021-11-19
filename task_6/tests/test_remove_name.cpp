#include <cassert>
#include <List.h>

void test_1() {
	List data_list;
	Data data;

	data = { 1, "one" };
	data_list.add(data);

	data = { 2, "two" };
	data_list.add(data);

	data_list.remove_name("one");
	assert(data_list.count() == 1);

	data_list.remove_name("two");
	assert(data_list.count() == 0);
}

void test_2() {
	List data_list;
	Data data;

	data = { 1, "one" };
	data_list.add(data);

	data = { 1, "one" };
	data_list.add(data);

	data_list.remove_name("one");
	assert(data_list.count() == 1);
}

void test_3() {
	List data_list;
	Data data;

	data = { 1, "one" };
	data_list.add(data);

	data_list.remove_name("two");
	assert(data_list.count() == 1);
}

int main(int argc, char* argv[]) {
	test_1();
	test_2();
	test_3();
	return 0;
}