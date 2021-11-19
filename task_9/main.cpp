#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

#include "TupleN.h"


// Splits string by delimiter. 
// Returns vector of separated parts.
std::vector<std::string> split_text(std::string text, std::string delimiter) {
	std::vector<std::string> words{};

	size_t pos = 0;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		if (text.substr(0, pos) != "")
			words.push_back(text.substr(0, pos));
		text.erase(0, pos + delimiter.length());
	}
	if (text.substr(0, pos) != "")
		words.push_back(text);
	return words;
}

// Checks if a string contains correct form of signed/unsigned integer without unwanted zeros at the beginning
bool is_correct_number(const std::string s) {
	if (s[0] == '+' || s[0] == '-') {
		if (s.length() == 1 || s.length() == 2)
			return true;
		else if (s.length() > 2)
			return s[1] != '0';
	}
	else {
		if (s.length() == 0 || s.length() == 1)
			return true;
		else if (s.length() > 1)
			return s[0] != '0';
	}
}

// Finds real numbers in a string in decimal/exponential/scientific format
// excluding cases with unwanted zeros at the beginning such as: 001, 010...
// Cases a. and .b are allowed
std::vector<std::string> find_float_in_string(const std::string text) {
	// Pattern for signed/unsigned numbers in decimal/exponential/scientific format
	const std::regex rexp(R"([+-]?(\d+([.]\d*)?([eE][+-]?\d+)?|[.]\d+([eE][+-]?\d+)?))");
	std::smatch match_res;
	std::vector<std::string> result;

	std::string str = text;
	while (regex_search(str, match_res, rexp)) {
		std::string tmp = split_text(match_res[0].str(), ".")[0];
		if (is_correct_number(tmp))
			result.push_back(match_res[0]);
		str = match_res.suffix().str(); //proceed to the next match
	}
	return result;
}

// Finds integer numbers in a string 
std::vector<std::string> find_int_in_string(const std::string text) {
	// Pattern for signed/unsigned integer numbers
	const std::regex rexp(R"([+-]?\d+)");
	std::smatch match_res;
	std::vector<std::string> result;

	std::string str = text;
	while (regex_search(str, match_res, rexp)) {
		std::string tmp = split_text(match_res[0].str(), ".")[0];
		if (is_correct_number(tmp))
			result.push_back(match_res[0]);
		str = match_res.suffix().str(); //proceed to the next match
	}
	return result;
}

// Executes operation from file for Tuple<int, n>
void file_with_int(std::string path_to_int_file) {
	const int n = 6;
	std::string line1, command, line2;
	std::vector<std::string> numbers_1, numbers_2;
	std::vector<int> vec_for_tuple_1, vec_for_tuple_2;

	std::ifstream int_file(path_to_int_file);
	if (!int_file.is_open()) {
		std::cout << "Couldn't open int file" << std::endl;
		assert(int_file.is_open());
	}

	std::cout << "Int file:" << std::endl;

	std::getline(int_file, line1);
	std::getline(int_file, command);
	std::getline(int_file, line2);
	int_file.close();

	numbers_1 = find_int_in_string(line1);
	numbers_2 = find_int_in_string(line2);

	if (numbers_1.size() == 1)
		vec_for_tuple_1.push_back(std::stoi(numbers_1[0]));
	else if (numbers_1.size() >= n) {
		for (int i = 0; i < n; ++i) {
			vec_for_tuple_1.push_back(std::stoi(numbers_1[i]));
		}
	}
	else {
		std::cout << "Wrong format of line 1 in int file" << std::endl;
		assert(numbers_1.size() >= n);
	}

	if (numbers_2.size() == 1)
		vec_for_tuple_2.push_back(std::stoi(numbers_2[0]));
	else if (numbers_2.size() >= n) {
		for (int i = 0; i < n; ++i) {
			vec_for_tuple_2.push_back(std::stoi(numbers_2[i]));
		}
	}
	else {
		std::cout << "Wrong format of line 2 in int file" << std::endl;
		assert(numbers_2.size() >= n);
	}

	if (vec_for_tuple_1.size() == n && vec_for_tuple_2.size() == n) {
		Tuple<int, n> tup1(vec_for_tuple_1);
		Tuple<int, n> tup2(vec_for_tuple_2);
		tup1.print();
		std::cout << command << std::endl;
		tup2.print();
		std::cout << "=" << std::endl;
		if (command == "+")
			(tup1 + tup2).print();
		else if (command == "-")
			(tup1 - tup2).print();
		else if (command == "*") {
			auto dot_prod = tup1 * tup2;
			std::cout << dot_prod << std::endl;
		}
		else if (command == "==") {
			if (tup1 == tup2) 
				std::cout << "True" << std::endl;
			else 
				std::cout << "False" << std::endl;
		}
		else if (command == "!=") {
			if (tup1 != tup2)
				std::cout << "True" << std::endl;
			else
				std::cout << "False" << std::endl;
		}
		else
			std::cout << "Undefined" << std::endl;
	}
	else if (vec_for_tuple_1.size() == 1 && vec_for_tuple_2.size() == n) {
		int scalar = vec_for_tuple_1[0];
		Tuple<int, n> tup(vec_for_tuple_2);
		std::cout << scalar << std::endl;
		std::cout << command << std::endl;
		tup.print();
		std::cout << "=" << std::endl;
		if (command == "*")
			(tup * scalar).print();
		else
			std::cout << "Undefined" << std::endl;
	}
	else if (vec_for_tuple_1.size() == n && vec_for_tuple_2.size() == 1) {
		Tuple<int, n> tup(vec_for_tuple_1);
		int scalar = vec_for_tuple_2[0];
		tup.print();
		std::cout << command << std::endl;
		std::cout << scalar << std::endl;
		std::cout << "=" << std::endl;
		if (command == "*")
			(tup * scalar).print();
		else
			std::cout << "Undefined" << std::endl;
	}
	std::cout << std::endl;
}

// Executes operation from file for Tuple<float, n>
void file_with_float(std::string path_to_float_file) {
	const int n = 6;
	std::string line1, command, line2;
	std::vector<std::string> numbers_1, numbers_2;
	std::vector<float> vec_for_tuple_1, vec_for_tuple_2;

	std::ifstream float_file(path_to_float_file);
	if (!float_file.is_open()) {
		std::cout << "Couldn't open float file" << std::endl;
		assert(float_file.is_open());
	}

	std::cout << "Float file:" << std::endl;

	std::getline(float_file, line1);
	std::getline(float_file, command);
	std::getline(float_file, line2);
	float_file.close();

	numbers_1 = find_float_in_string(line1);
	numbers_2 = find_float_in_string(line2);

	if (numbers_1.size() == 1)
		vec_for_tuple_1.push_back(std::stof(numbers_1[0]));
	else if (numbers_1.size() >= n) {
		for (int i = 0; i < n; ++i) {
			vec_for_tuple_1.push_back(std::stof(numbers_1[i]));
		}
	}
	else {
		std::cout << "Wrong format of line 1 in float file" << std::endl;
		assert(numbers_1.size() >= n);
	}

	if (numbers_2.size() == 1)
		vec_for_tuple_2.push_back(std::stof(numbers_2[0]));
	else if (numbers_2.size() >= n) {
		for (int i = 0; i < n; ++i) {
			vec_for_tuple_2.push_back(std::stof(numbers_2[i]));
		}
	}
	else {
		std::cout << "Wrong format of line 2 in float file" << std::endl;
		assert(numbers_2.size() >= n);
	}

	if (vec_for_tuple_1.size() == n && vec_for_tuple_2.size() == n) {
		Tuple<float, n> tup1(vec_for_tuple_1);
		Tuple<float, n> tup2(vec_for_tuple_2);
		tup1.print();
		std::cout << command << std::endl;
		tup2.print();
		std::cout << "=" << std::endl;
		if (command == "+")
			(tup1 + tup2).print();
		else if (command == "-")
			(tup1 - tup2).print();
		else if (command == "*") {
			auto dot_prod = tup1 * tup2;
			std::cout << dot_prod << std::endl;
		}
		else if (command == "==") {
			if (tup1 == tup2)
				std::cout << "True" << std::endl;
			else
				std::cout << "False" << std::endl;
		}
		else if (command == "!=") {
			if (tup1 != tup2)
				std::cout << "True" << std::endl;
			else
				std::cout << "False" << std::endl;
		}
		else
			std::cout << "Undefined" << std::endl;
	}
	else if (vec_for_tuple_1.size() == 1 && vec_for_tuple_2.size() == n) {
		float scalar = vec_for_tuple_1[0];
		Tuple<float, n> tup(vec_for_tuple_2);
		std::cout << scalar << std::endl;
		std::cout << command << std::endl;
		tup.print();
		std::cout << "=" << std::endl;
		if (command == "*")
			(tup * scalar).print();
		else
			std::cout << "Undefined" << std::endl;
	}
	else if (vec_for_tuple_1.size() == n && vec_for_tuple_2.size() == 1) {
		Tuple<float, n> tup(vec_for_tuple_1);
		float scalar = vec_for_tuple_2[0];
		tup.print();
		std::cout << command << std::endl;
		std::cout << scalar << std::endl;
		std::cout << "=" << std::endl;
		if (command == "*")
			(tup * scalar).print();
		else
			std::cout << "Undefined" << std::endl;
	}
	std::cout << std::endl;
}

// Executes operation from file for Tuple<std::string, n>
void file_with_string(std::string path_to_string_file) {
	const int n = 6;
	std::string line1, command, line2;
	std::vector<std::string> strings_1, strings_2;
	std::vector<std::string> vec_for_tuple_1, vec_for_tuple_2;

	std::ifstream string_file(path_to_string_file);
	if (!string_file.is_open()) {
		std::cout << "Couldn't open string file" << std::endl;
		assert(string_file.is_open());
	}

	std::cout << "String file:" << std::endl;

	std::getline(string_file, line1);
	std::getline(string_file, command);
	std::getline(string_file, line2);
	string_file.close();

	strings_1 = split_text(line1, " ");
	strings_2 = split_text(line2, " ");

	if (strings_1.size() < n) {
		std::cout << "Wrong format of line 1 in string file" << std::endl;
		assert(strings_1.size() >= n);
	}
	else if (strings_2.size() < n) {
		std::cout << "Wrong format of line 2 in string file" << std::endl;
		assert(strings_2.size() >= n);
	}
	else {
		for (int i = 0; i < n; ++i) {
			vec_for_tuple_1.push_back(strings_1[i]);
			vec_for_tuple_2.push_back(strings_2[i]);
		}
		Tuple<std::string, n> tup1(vec_for_tuple_1);
		Tuple<std::string, n> tup2(vec_for_tuple_2);
		tup1.print();
		std::cout << command << std::endl;
		tup2.print();
		std::cout << "=" << std::endl;
	    if (command == "==") {
		    if (tup1 == tup2)
			    std::cout << "True" << std::endl;
		    else
			    std::cout << "False" << std::endl;
	    }
	    else if (command == "!=") {
		    if (tup1 != tup2)
			    std::cout << "True" << std::endl;
		    else
			    std::cout << "False" << std::endl;
	    }
		else
			std::cout << "Undefined" << std::endl;
	}
	std::cout << std::endl;
}



int main(int argc, char* argv[]) {
	/*const int n = 6;
	Tuple<double, n> tup1(5., 1.3, 2.87, 9.17, 22.1, 0.);
	tup1.print();
	Tuple<double, n> tup2(25., 11.4, 3.2, 11.01, 2.31, 0.1);
	tup2.print();

	Tuple<double, n> tup_sum = tup1 + tup2;
	tup_sum.print();
	Tuple<double, n> tup_sub = tup1 - tup2;
	tup_sub.print();
	auto dot_prod = tup1 * tup2;
	std::cout << dot_prod << std::endl;

	Tuple<double, n> tup_scal = tup1 * 5;
	tup_scal.print();

	Tuple<double, n> tup111(tup_sum);
	tup111.print();*/

	if (argc != 4) {
		std::cout << "Invalid number of input parameters" << std::endl;
		assert(argc == 4);
	}

	/*std::string path_to_float_file = "../../../float_file.txt";
	std::string path_to_int_file = "../../../int_file.txt";
	std::string path_to_string_file = "../../../string_file.txt";*/

	std::string path_to_float_file = argv[1];
	std::string path_to_int_file = argv[2];
	std::string path_to_string_file = argv[3];

	file_with_float(path_to_float_file);
	file_with_int(path_to_int_file);
	file_with_string(path_to_string_file);

	return 0;
}