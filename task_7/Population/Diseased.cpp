#include <iostream>
#include "Diseased.h"
#include "Recovered.h"

int Diseased::_diseased_count = 0;

Diseased::Diseased(std::string sex, std::string name, int age) {
	//std::cout << "Diseased constructor" << std::endl;

	_sex = sex;
	_name = name;
	_age = age;
	_infection_period = _infection_period_max;

	_diseased_count++;
}

Person& Diseased::contact(Person& person) { //Diseased status does not change upon contact because in quarantine
	if (person.is_healthy())
		return *this;
	else if (person.is_infected())
		return *this;
	else if (person.is_diseased())
		return *this;
	else if (person.is_recovered())
		return *this;
}

Person& Diseased::sleep() {
	_infection_period--;
	if (_infection_period <= 0) {
		_diseased_count--;
		return *new Recovered(_sex, _name, _age);
	}
	else
		return *this;
}