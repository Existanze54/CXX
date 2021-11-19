#include <iostream>
#include "Infected.h"
#include "Diseased.h"

int Infected::_infected_count = 0;

Infected::Infected(std::string sex, std::string name, int age) {
	//std::cout << "Infected constructor" << std::endl;

	_sex = sex;
	_name = name;
	_age = age;

	_incubation_period = _incubation_period_max;

	_infected_count++;
}

Person& Infected::contact(Person& person) { //Infected status does not change upon contact because already infected
	if (person.is_healthy())
		return *this;
	else if (person.is_infected())
		return *this;
	else if (person.is_diseased())
		return *this;
	else if (person.is_recovered())
		return *this;
}

Person& Infected::sleep() {
	_incubation_period--;
	if (_incubation_period <= 0) {
		_infected_count--;
		return *new Diseased(_sex, _name, _age);
	}
	else
		return *this;
}