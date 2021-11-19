#include <cassert>
#include <List.h>

void test_1() {
	List data_list;
	Data data;

	data = { 1, "one" };
	data_list.add(data);

	data = { 2, "two" };
	data_list.add(data);

	assert(data_list.search_name("one") == 0);
	assert(data_list.search_name("two") == 1);
}

void test_2() {
	List data_list;
	Data data;

	data = { 1, "one" };
	data_list.add(data);

	data = { 1, "one" };
	data_list.add(data);

	assert(data_list.search_name("one") == 0);
}

void test_3() {
	List data_list;
	Data data;

	data = { 1, "one" };
	data_list.add(data);

	assert(data_list.search_name("two") == -1);
}

int main(int argc, char* argv[]) {
	test_1();
	test_2();
	test_3();
	return 0;
}