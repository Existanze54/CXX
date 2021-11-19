#pragma once
#include <string>
#include "Person.h"

class Diseased : public Person {
private:
	int _infection_period;

	static int _infection_period_max;
	static int _diseased_count;
public:
	Diseased(std::string sex, std::string name, int age);

	inline static void set_infection_period_max(int infection_period_max) {
		_infection_period_max = infection_period_max;
	}
	inline static int get_infection_period_max() {
		return _infection_period_max;
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
		return true;
	}
	inline bool is_recovered() const override {
		return false;
	}

	inline std::string status() const override {
		return "Diseased";
	}

	inline float get_prob() const override {
		return 0.f; //can't contact people while in quarantine
	}

	inline static int get_diseased_count() {
		return _diseased_count;
	}

	Person& contact(Person& person) override;
	Person& sleep() override;

	~Diseased() {
		//std::cout << "Diseased destructor" << std::endl;
		//_diseased_count--;
	}
};
