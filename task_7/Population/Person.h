#pragma once

class Person {
protected:
	std::string _sex;
	std::string _name;
	int _age;
public:
	virtual bool is_healthy() const = 0;
	virtual bool is_infected() const = 0;
	virtual bool is_diseased() const = 0;
	virtual bool is_recovered() const = 0;

	virtual std::string get_sex() const = 0;
	virtual std::string get_name() const = 0;
	virtual int get_age() const = 0;

	virtual std::string status() const = 0;

	virtual float get_prob() const = 0;

	virtual Person& contact(Person& person) = 0;
	virtual Person& sleep() = 0;

	virtual ~Person() {}
};