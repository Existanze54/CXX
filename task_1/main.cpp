#include <iostream>
#include <time.h>

int main() {
	std::cout << "Enter your name: ";
	std::string user_name;
	std::cin >> user_name;
	std::cout << "Greetings, " << user_name << std::endl;
	std::cout << "How old are you? " << std::endl;

	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);
	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	int year = aTime->tm_year + 1900; // Year is # years since 1900

	int user_age;
	std::cin >> user_age;
	std::cout << "Your were born in " << year - user_age << std::endl;
	return 0;
}