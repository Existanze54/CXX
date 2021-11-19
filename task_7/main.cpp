#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <random>
#include <algorithm>

#include <Person.h>
#include <Healthy.h>
#include <Infected.h>
#include <Diseased.h>
#include <Recovered.h>

std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

int GENDER_MIN = 0;
int GENDER_MAX = 1;
std::uniform_int_distribution<> random_gender(GENDER_MIN, GENDER_MAX);

int AGE_MIN = 10;
int AGE_MAX = 100;
std::uniform_int_distribution<> random_age(AGE_MIN, AGE_MAX);


// Checks if a string contains only numbers.
inline bool has_only_digits(const std::string s) {
    return s.find_first_not_of("0123456789") == std::string::npos;
}

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

// Returns the total number of people in a population.
int population_count() {
	return Healthy::get_healthy_count() + Infected::get_infected_count() +
		Diseased::get_diseased_count() + Recovered::get_recovered_count();
}

// Displays current population information.
void print_population() {
//	std::cout << " TOTAL: " << population_count();// << std::endl;
	std::cout << " Healthy: " << Healthy::get_healthy_count();// << std::endl;
	std::cout << " Infected: " << Infected::get_infected_count() ;//<< std::endl;
	std::cout << " Diseased: " << Diseased::get_diseased_count() ;//<< std::endl;
	std::cout << " Recovered: " << Recovered::get_recovered_count() << std::endl;
	//std::cout << std::endl;
}

// Displays information about each person in population
void print_persons(std::vector<Person*> population) {
	for (int i = 0; i < population.size(); ++i) {
		std::cout << population[i]->get_sex() << " " << population[i]->get_name() << " " << population[i]->get_age() << ": " << population[i]->status() << std::endl;
		/*std::cout << population[i]->is_healthy() << " " << population[i]->is_infected() << 
			" " << population[i]->is_diseased() << " " << population[i]->is_recovered() << std::endl;*/
	}
}

// Displays model parameters
void print_model_parameters() {
	std::cout << "Current model parameters:" << std::endl;
	std::cout << "Infection probability = " << Infected::get_infection_probability() << std::endl;
	std::cout << "Incubation period = " << Infected::get_incubation_period_max() << std::endl;
	std::cout << "Quarantine period = " << Diseased::get_infection_period_max() << std::endl;
	std::cout << "Immune probability = " << Recovered::get_immune_probability() << std::endl;
	std::cout << "Immune period = " << Recovered::get_immune_period_max() << std::endl;
	std::cout << std::endl;
}

// Generates population from numbers in input file.
// Input file should contain string of the following format:
// healthy_count:infected_count:diseased_count:recovered_count
std::vector<Person*> generate_population_from_numbers(std::string path_to_inp_file) {
	std::ifstream inp_file(path_to_inp_file);
	if (!inp_file.is_open()) {
		std::cout << "Couldn't open input file" << std::endl;
		assert(inp_file.is_open());
	}
	
	std::string line;
	std::getline(inp_file, line);
	inp_file.close();

	if (line.empty()) {
		std::cout << "Incorrect format of input file with population numbers" << std::endl;
		assert(!line.empty());
	}

	std::vector<std::string> vector_of_numbers = split_text(line, ":");
	if (vector_of_numbers.size() != 4) {
		std::cout << "Incorrect format of input file with population numbers" << std::endl;
		assert(vector_of_numbers.size() == 4);
	}

	for (int i = 0; i < vector_of_numbers.size(); ++i) {
		if (!has_only_digits(vector_of_numbers[i]) || std::stoi(vector_of_numbers[i]) < 0) {
			std::cout << "Incorrect format of input file with population numbers" << std::endl;
			assert(has_only_digits(vector_of_numbers[i]));
		}
	}
	int healthy_count, infected_count, diseased_count, recovered_count;
	healthy_count = stoi(vector_of_numbers[0]);
	infected_count = stoi(vector_of_numbers[1]);
	diseased_count = stoi(vector_of_numbers[2]);
	recovered_count = stoi(vector_of_numbers[3]);

	std::vector<Person*> population_vector;
	std::string sex, name;
	int age;

	int j = 0;

	for (j; j < healthy_count; j++) {
		if (random_gender(gen) == 0)
			sex = "male";
		else
			sex = "female";
		name = "Person" + std::to_string(j);
		age = random_age(gen);
		population_vector.push_back(new Healthy(sex, name, age));
	}
	for (j; j < healthy_count + infected_count; j++) {
		if (random_gender(gen) == 0)
			sex = "male";
		else
			sex = "female";
		name = "Person" + std::to_string(j);
		age = random_gender(gen);
		population_vector.push_back(new Infected(sex, name, age));
	}
	for (j; j < healthy_count + infected_count + diseased_count; j++) {
		if (random_gender(gen) == 0)
			sex = "male";
		else
			sex = "female";
		name = "Person" + std::to_string(j);
		age = random_age(gen);
		population_vector.push_back(new Diseased(sex, name, age));
	}
	for (j; j < healthy_count + infected_count + diseased_count + recovered_count; j++) {
		if (random_gender(gen) == 0)
			sex = "male";
		else
			sex = "female";
		name = "Person" + std::to_string(j);
		age = random_age(gen);
		population_vector.push_back(new Recovered(sex, name, age));
	}

	std::shuffle(std::begin(population_vector), std::end(population_vector), gen);
	return population_vector;
}

// Gets current population from file.
// Information of each person should be in following format:
// sex, name, age, status: "Healthy/Infected/Diseased/Recovered" or "0/1/2/3".
std::vector<Person*> population_from_file(std::string path_to_population_file) {
	std::ifstream population_file(path_to_population_file);
	if (!population_file.is_open()) {
		std::cout << "Couldn't open file" << std::endl;
		assert(population_file.is_open());
	}
	
	std::vector<Person*> population_vector;

	std::string sex, name, status;
	int age;

	std::string line;
	std::vector<std::string> person_vector;
	std::cout << "Creating population with persons from file..." << std::endl;

	while (std::getline(population_file, line)) {
		if (line.empty())
			continue;

		person_vector = split_text(line, " ");

		if (person_vector.size() != 4) {
			std::cout << "Invalid person information format" << std::endl;
		}
		else {
			if (!has_only_digits(person_vector[2])) {
				std::cout << "Invalid person age format" << std::endl;
			}
			else {
				sex = person_vector[0];
				name = person_vector[1];
				age = std::stoi(person_vector[2]);
				status = person_vector[3];
				if (status == "Healthy" || status == "healthy" || status == "0")
					population_vector.push_back(new Healthy(sex, name, age));
				else if (status == "Infected" || status == "infected" || status == "1")
					population_vector.push_back(new Infected(sex, name, age));
				else if (status == "Diseased" || status == "diseased" || status == "2")
					population_vector.push_back(new Diseased(sex, name, age));
				else if (status == "Recovered" || status == "recovered" || status == "3")
					population_vector.push_back(new Recovered(sex, name, age));
				else 
					std::cout << "Invalid person status format" << std::endl;
			}
		}
	}
	std::cout << "Population created successfully" << std::endl;
	population_file.close();
	return population_vector;
}

// Gets social interactions from text file.
// Text file must contain a symmetric matrix with numbers zero/non zero.
std::vector<std::vector<int>> contacts_from_file(std::string path_to_contacts_file) {
	std::ifstream contacts_file(path_to_contacts_file);
	if (!contacts_file.is_open()) {
		std::cout << "Couldn't open file" << std::endl;
		assert(contacts_file.is_open());
	}

	std::vector<std::vector<int>> population_contacts_vector;
	std::vector<int> person_contacts_vector;


	std::string line;
	std::vector<std::string> person_contacts_vector_tmp;
	std::cout << std::endl;
	std::cout << "Getting social interactions from file..." << std::endl;

	while (std::getline(contacts_file, line)) {
		person_contacts_vector.clear();

		if (line.empty())
			continue;

		person_contacts_vector_tmp = split_text(line, " ");

		if (person_contacts_vector_tmp.size() != population_count()) {
			std::cout << "ERROR: The contacts file is inconsistent with the population" << std::endl;
			assert(person_contacts_vector_tmp.size() == population_count());
		}
		else {
			for (int i = 0; i < person_contacts_vector_tmp.size(); ++i) {
				person_contacts_vector.push_back(std::stoi(person_contacts_vector_tmp[i]));
			}
		}

		population_contacts_vector.push_back(person_contacts_vector);
	}

	if (population_contacts_vector.size() != population_count()) {
		std::cout << "ERROR: The contacts file is inconsistent with the population" << std::endl;
		assert(population_contacts_vector.size() == population_count());
	}
	contacts_file.close();
	std::cout << "Retrieving social interactions from file is completed successfully" << std::endl;
	std::cout << std::endl;
	return population_contacts_vector;
}

// Simulates population evolution.
// Vector connections - represents NxN symmetric matrix of social connections,
// max_days - evolution period.
void population_evolve(std::vector<Person*> current_population, std::vector<std::vector<int>> connections, int max_day) {
	std::vector<Person*> next_population;

	//std::cout << "-------------------------" << std::endl;
	std::cout << "Day: 0";// << std::endl;
	//std::cout << std::endl;
	next_population = current_population;
	//print_persons(next_population);
	//std::cout << std::endl;
	print_population();

	int day = 1;

	while (day <= max_day) {
		//std::cout << "-------------------------" << std::endl;
		std::cout << "Day: " << day;// << std::endl;
		//std::cout << std::endl;

		for (int i = 0; i < current_population.size(); ++i) {
			for (int j = 0; j < current_population.size(); ++j) {
				if (i != j && connections[i][j] != 0) {
					Person* tmp = &(next_population[i]->contact(*current_population[j]));
					if (next_population[i]->status() != tmp->status()) {
						next_population[i] = tmp;
						break;
					}
				}
			}
		}

		for (int i = 0; i < next_population.size(); ++i) {
			if (current_population[i]->status() == next_population[i]->status()) {
				next_population[i] = &(next_population[i]->sleep());
			}
		}

		for (int i = 0; i < current_population.size(); ++i) {
			if (current_population[i]->status() != next_population[i]->status()) {
				delete current_population[i];
			}
		}

		//print_persons(next_population);
		//std::cout << std::endl;
		print_population();

		current_population.clear();
		current_population = next_population;
		day++;
	}

	for (int i = 0; i < current_population.size(); ++i)
		delete current_population[i];
}


// Default values if no given
float Infected::_infection_probability = 0.5f;
int Infected::_incubation_period_max = 7;
int Diseased::_infection_period_max = 3;
float Recovered::_immune_probability = 0.1f;
int Recovered::_immune_period_max = 7;
int max_day = 20;


int main(int argc, char* argv[]) {
	float infection_probability = 0.5f;
	int incubation_period_max = 7;
	int infection_period_max = 3;
	float immune_probability = 0.1f;
	int immune_period_max = 7;

	std::string path_to_population_numbers_file;
	std::string path_to_contacts_file;

	if (argc < 3) {
		std::cout << "Input files are not specified" << std::endl;
		assert(argc >= 3);
	}
	else {
		path_to_population_numbers_file = argv[1];
		path_to_contacts_file = argv[2];

		if (argc == 8) {
			infection_probability = std::stof(argv[3]);
			incubation_period_max = std::stoi(argv[4]);
			infection_period_max = std::stoi(argv[5]);
			immune_probability = std::stof(argv[6]);
			immune_period_max = std::stoi(argv[7]);
		}
		else if (argc == 9) {
			infection_probability = std::stof(argv[3]);
			incubation_period_max = std::stoi(argv[4]);
			infection_period_max = std::stoi(argv[5]);
			immune_probability = std::stof(argv[6]);
			immune_period_max = std::stoi(argv[7]);
			max_day = std::stoi(argv[8]);
		}
		else {
			std::cout << "Incorrect number of input arguments" << std::endl;
			std::cout << "Model parameters are set by default" << std::endl;
			std::cout << std::endl;
		}
	}

	/*std::string path_to_population_file = "../../../initial_population.txt";
	std::string path_to_contacts_file = "../../../contacts_matrix.txt";*/

	Infected::set_infection_probability(infection_probability);
	Infected::set_incubation_period_max(incubation_period_max);

	Diseased::set_infection_period_max(infection_period_max);

	Recovered::set_immune_probability(immune_probability);
	Recovered::set_immune_period_max(immune_period_max);

	print_model_parameters();

	//std::vector <Person*> current_population = population_from_file(path_to_population_file);
	std::vector <Person*> current_population = generate_population_from_numbers(path_to_population_numbers_file);
	print_population();
	std::vector<std::vector<int>> connections = contacts_from_file(path_to_contacts_file);

	population_evolve(current_population, connections, max_day);

	return 0;
}
