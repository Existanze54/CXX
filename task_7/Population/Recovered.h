#pragma once
#include <string>
#include <random>
#include "Person.h"

class Recovered : public Person {
private:
	int _immune_period;

	static float _immune_probability;
	static int _immune_period_max;
	static int _recovered_count;
public:
	Recovered(std::string sex, std::string name, int age);

	inline static void set_immune_period_max(int immune_period_max) {
		_immune_period_max = immune_period_max;
	}
	inline static int get_immune_period_max() {
		return _immune_period_max;
	}

	inline static void set_immune_probability(float immune_probability) {
		_immune_probability = immune_probability;
	}
	inline static float get_immune_probability() {
		return _immune_probability;
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
		return false;
	}
	inline bool is_diseased() const override {
		return false;
	}
	inline bool is_recovered() const override {
		return true;
	}

	inline std::string status() const override {
		return "Recovered";
	}

	float get_prob() const override; // random value + immune addition to compare with infected

	inline static int get_recovered_count() {
		return _recovered_count;
	}

	Person& contact(Person& person) override;
	Person& sleep() override;

	~Recovered() {
		//std::cout << "Recovered destructor" << std::endl;
		//_recovered_count--;
	}
};
