#pragma once
#include <string>
#include "Person.h"

class Infected : public Person {
private:
	int _incubation_period;

	static float _infection_probability;
	static int _incubation_period_max;
	static int _infected_count;
public:
	Infected(std::string sex, std::string name, int age);

	inline static void set_incubation_period_max(int incubation_period_max) {
		_incubation_period_max = incubation_period_max;
	}
	inline static int get_incubation_period_max() {
		return _incubation_period_max;
	}

	inline static void set_infection_probability(float infection_probability) {
		_infection_probability = infection_probability;
	}
	inline static float get_infection_probability() {
		return _infection_probability;
	}

	inline std::string get_sex() const override {
		return this->_sex;
	}
	inline std::string get_name() const override {
		return this->_name;
	}
	inline int get_age() const override {
		return this->_age;
	}

	inline bool is_healthy() const override {
		return false;
	}
	inline bool is_infected() const override {
		return true;
	}
	inline bool is_diseased() const override {
		return false;
	}
	inline bool is_recovered() const override {
		return false;
	}

	inline std::string status() const override {
		return "Infected";
	}

	inline float get_prob() const override {
		return _infection_probability;
	}

	inline static int get_infected_count() {
		return _infected_count;
	}

	Person& contact(Person& person) override;
	Person& sleep() override;

	~Infected() {
		//std::cout << "Infected destructor" << std::endl;
		//_infected_count--;
	}
};
