#include <iostream>
#include <random>
#include "Healthy.h"
#include "Infected.h"

int Healthy::_healthy_count = 0;

Healthy::Healthy(std::string sex, std::string name, int age) {
	//std::cout << "Healthy constructor" << std::endl;

	_sex = sex;
	_name = name;
	_age = age;

	_healthy_count++;
}

float Healthy::get_prob() const {// random value to compare with infected
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	int PROB_MIN = 0;
	int PROB_MAX = 1;
	std::uniform_real_distribution<> random_prob(PROB_MIN, PROB_MAX);
	return random_prob(gen);
}

Person& Healthy::contact(Person& person) {
	if (person.is_healthy())
		return *this;
	else if (person.is_infected()) {
		if (this->get_prob() < person.get_prob()) {
			_healthy_count--;
			return *new Infected(_sex, _name, _age);
		}
		else
			return *this;
	}
	else if (person.is_diseased())
		return *this;
	else if (person.is_recovered())
		return *this;
}

Person& Healthy::sleep() {
	return *this;
}