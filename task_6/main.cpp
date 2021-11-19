#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <List.h>


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

// Checks if a string contains only signed/unsigned integer numbers
bool has_only_digits(const std::string s) {
	if (s[0] == '+' || s[0] == '-')
		return s.substr(1).find_first_not_of("0123456789") == std::string::npos;
	else
		return s.find_first_not_of("0123456789") == std::string::npos;
}


// Fills List object data_list with pairs: (value, name) which read from input file.
void list_from_file(std::string path_to_input_file, List& data_list) {
	std::ifstream input_file(path_to_input_file);

	std::string line, name;
	int value;
	std::vector<std::string> data_vector;
	Data data;

	std::cout << "Filling list with pairs from file..." << std::endl;

	while (std::getline(input_file, line)) {
		if (line.empty())
			continue;

		data_vector = split_text(line, " ");

		if (data_vector.size() != 2) {
			std::cout << "Invalid format of pair" << std::endl;
		}
		else {
			if (!has_only_digits(data_vector[0])) {
				std::cout << "Invalid format of pair" << std::endl;
			}
			else {
				value = std::stoi(data_vector[0]);
				name = data_vector[1];
				data = { value, name };
				data_list.add(data);
			}
		}
	}
	input_file.close();
}

// Executes commands for the List object data_list from command file.
void commands_to_list_from_file(std::string path_to_command_file, List& data_list) {
	std::ifstream command_file(path_to_command_file);

	std::string line, command, name;
	int value;
	std::vector<std::string> command_vector;
	Data data;

	std::cout << "Executing commands for the list from command file..." << std::endl;

	while (std::getline(command_file, line)) {
		if (line.empty())
			continue;

		command_vector = split_text(line, " ");


		if (command_vector.size() == 1) {
			command = command_vector[0];
			if (command == "count") {
				data_list.count();
			}
			else if (command == "print") {
				data_list.print();
			}

			else {
				std::cout << "Invalid command" << std::endl;
			}
		}

		else if (command_vector.size() == 2) {
			command = command_vector[0];
			if (command == "remove_value") {
				if (!has_only_digits(command_vector[1])) {
					std::cout << "Invalid command" << std::endl;
				}
				else {
					value = std::stoi(command_vector[1]);
					data_list.remove_value(value);
				}
			}
			else if (command == "remove_name") {
				name = command_vector[1];
				data_list.remove_name(name);
			}
			else if (command == "search_value") {
				if (!has_only_digits(command_vector[1])) {
					std::cout << "Invalid command" << std::endl;
				}
				else {
					value = std::stoi(command_vector[1]);
					data_list.search_value(value);
				}
			}
			else if (command == "search_name") {
				name = command_vector[1];
				data_list.search_name(name);
			}

			else {
				std::cout << "Invalid command" << std::endl;
			}
		}

		else if (command_vector.size() == 3) {
			command = command_vector[0];
			if (command == "add") {
				if (!has_only_digits(command_vector[1])) {
					std::cout << "Invalid command" << std::endl;
				}
				else {
					value = std::stoi(command_vector[1]);
					name = command_vector[2];
					data = { value, name };
					data_list.add(data);
				}
			}

			else {
				std::cout << "Invalid command" << std::endl;
			}
		}

		else {
			std::cout << "Invalid command" << std::endl;
		}
	}
	command_file.close();
}

int main(int argc, char* argv[]) {
	std::string path_to_input_file = argv[1];
	std::string path_to_command_file = argv[2];

	List data_list;
	list_from_file(path_to_input_file, data_list);

	std::cout << std::endl;
	std::cout << "List from file: ";
	data_list.print();
	std::cout << std::endl;

	commands_to_list_from_file(path_to_command_file, data_list);

	return 0;
}