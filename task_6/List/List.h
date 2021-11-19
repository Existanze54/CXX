#pragma once
#include <string>

struct Data {
	int value;
	std::string name;
};

class List {
private:
	struct Element {
		Data data;
		Element* next;
	};
	Element* head;
	int size;

public:
	List(); //Empty constructor
	List(List& obj); //Exception
	List& operator=(List& obj); //Exception

	// Adding element to begin/end/by index
	void add_begin(const Data& new_element);
	void add_end(const Data& new_element);
	void add_index(const Data& new_element, const int index);

	void add(const Data& new_element); // Adding element in ascending order

	// Deleting element
	void del_begin();
	void del_end();
	void del_index(const int index);

	// Serching element by value/name. 
	// Returns -1 if element not found.
	int search_value(const int _value) const;
	int search_name(const std::string _name) const;

	// Removing element by value/name if such element exists
	void remove_value(const int _value);
	void remove_name(const std::string _name);

	int count() const; //Returns number of elements 

	// Returns pointer to the beginning/end of list
	Element* begin();
	Element* end();

	// Shows list on display
	void print() const;

	//Destructor
	~List();
};