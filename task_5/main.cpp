#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Vector3D.h"

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

void vector_operation_from_file(std::string path_to_inp_file, std::string path_to_out_file) {
	std::ifstream inp_file(path_to_inp_file);
	std::ofstream out_file(path_to_out_file);
	
	std::string first, operation, sec;

	std::getline(inp_file, first);
	std::getline(inp_file, operation);
	std::getline(inp_file, sec);
	inp_file.close();
    
	std::vector<std::string> a = split_text(first, " ");
	std::vector<std::string> b = split_text(sec, " ");

	std::cout << first << std::endl;
	std::cout << operation << std::endl;
	std::cout << sec << std::endl;
	std::cout << "=" << std::endl;

	if (a.size() == 1) {
		int scal = std::stoi(a[0]);
		Vector3D vec = Vector3D(std::stoi(b[0]), std::stoi(b[1]), std::stoi(b[2]));
		out_file << (vec * scal).get_coord() << std::endl;
		(vec * scal).disp();
	}
	else if (b.size() == 1) {
	    int scal = std::stoi(b[0]);
		Vector3D vec = Vector3D(std::stoi(a[0]), std::stoi(a[1]), std::stoi(a[2]));
		out_file << (vec * scal).get_coord() << std::endl;
		(vec * scal).disp();
	}
	else {
		Vector3D vec1 = Vector3D(std::stoi(a[0]), std::stoi(a[1]), std::stoi(a[2]));
		Vector3D vec2 = Vector3D(std::stoi(b[0]), std::stoi(b[1]), std::stoi(b[2]));
		if (operation == "+") {
			out_file << (vec1 + vec2).get_coord() << std::endl;
			(vec1 + vec2).disp();
		}
		else if (operation == "-") {
			out_file << (vec1 - vec2).get_coord() << std::endl;
			(vec1 - vec2).disp();
		}
		else if (operation == "*") {
			out_file << (vec1 * vec2).get_coord() << std::endl;
			(vec1 * vec2).disp();
		}
	}
	out_file.close();
}

int main(int argc, char* argv[]) {
	std::string path_to_inp_file = argv[1];
	std::string path_to_out_file = argv[2];
	vector_operation_from_file(path_to_inp_file, path_to_out_file);

	return 0;
}