#include <iostream>
#include <random>
#include "Recovered.h"
#include "Infected.h"
#include "Healthy.h"

int Recovered::_recovered_count = 0;

Recovered::Recovered(std::string sex, std::string name, int age) {
	//std::cout << "Recovered constructor" << std::endl;

	_sex = sex;
	_name = name;
	_age = age;

	_immune_period = _immune_period_max;

	_recovered_count++;
}

float Recovered::get_prob() const {// random value + immune addition to compare with infected
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	int PROB_MIN = 0;
	int PROB_MAX = 1;
	std::uniform_real_distribution<> random_prob(PROB_MIN, PROB_MAX);
	return random_prob(gen) + _immune_probability;
}

Person& Recovered::contact(Person& person) {
	if (person.is_healthy())
		return *this;
	else if (person.is_infected()) {
		if (this->get_prob() < person.get_prob()) {
			_recovered_count--;
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

Person& Recovered::sleep() {
	_immune_period--;
	if (_immune_period <= 0) {
		_recovered_count--;
		return *new Healthy(_sex, _name, _age);
	}
	else {
		return *this;
	}
}
