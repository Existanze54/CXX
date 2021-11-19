#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <cassert>


// Splits string by delimiter.
// Returns vector of separated parts.
std::vector<std::string> split_text(std::string text, std::string delimiter) {
	std::vector<std::string> words{};

	size_t pos = 0;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		words.push_back(text.substr(0, pos));
		text.erase(0, pos + delimiter.length());
	}
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
void find_numbers_in_string(const std::string text) {
	// Pattern for signed/unsigned numbers in decimal/exponential/scientific format
	const std::regex rexp(R"([+-]?(\d+([.]\d*)?([eE][+-]?\d+)?|[.]\d+([eE][+-]?\d+)?))");

	// fixed cases like 255.255.255
	//const std::regex rexp(R"(([^.0-9]|^)[+-]?(\d+([.]\d*)?([eE][+-]?\d+)?|[.]\d+([eE][+-]?\d+)?)([^.0-9]|$))");

	std::smatch match_res;
	bool par = false;

	std::string str = text;
	while (regex_search(str, match_res, rexp)) {
		std::string tmp = split_text(match_res[0].str(), ".")[0];
		if (is_correct_number(tmp))
		    std::cout << match_res[0] << " ";
		str = match_res.suffix().str(); //proceed to the next match
		par = true;
	}

	if (par)
		std::cout << std::endl;
}


// Finds real numbers in a file in decimal/exponential/scientific format
// excluding cases with unwanted zeros at the beginning such as: 001, 010...
void find_numbers_in_file(const std::string path_to_text_file) {
	std::ifstream text_file(path_to_text_file);
	if (text_file.fail())
		std::cout << "File open error" << std::endl;
	assert(text_file.is_open());

	std::string line;

	std::cout << "Real numbers in file: " << std::endl;

	while (std::getline(text_file, line)) {
		if (line.empty())
			continue;

		find_numbers_in_string(line);
	}

	text_file.close();
}


int main(int argc, char* argv[]) {
	if (argc < 2)
		std::cout << "Path to input file not specified" << std::endl;
	else if (argc > 2)
		std::cout << "Too many arguments" << std::endl;
	assert(argc == 2);
	const std::string path_to_text_file = argv[1];

	find_numbers_in_file(path_to_text_file);
	return 0;
}