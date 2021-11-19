#pragma once
#include <string>
#include "Person.h"


class Healthy : public Person {
private:
	static int _healthy_count;
public:
	Healthy(std::string sex, std::string name, int age);

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
		return true;
	}
	inline bool is_infected() const override {
		return false;
	}
	inline bool is_diseased() const override {
		return false;
	}
	inline bool is_recovered() const override {
		return false;
	}

	inline std::string status() const override {
		return "Healthy";
	}

	float get_prob() const override; // random value to compare with infected

	inline static int get_healthy_count() {
		return _healthy_count;
	}

	Person& contact(Person& person) override;
	Person& sleep() override;

	~Healthy() override {
		//std::cout << "Healthy destructor" << std::endl;
		//_healthy_count--;
	}
};
