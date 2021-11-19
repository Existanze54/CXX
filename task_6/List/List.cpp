#include <iostream>
#include "List.h"

List::List() {
	std::cout << "Default constructor" << std::endl;
	head = nullptr;
	size = 0;
}

List::List(List& obj) {
	try {
		throw 1;
	}
	catch (int i) {
		std::cout << "Error copy" << std::endl;
		abort();
	}
}

List& List::operator=(List& obj) {
	try {
		throw 2;
	}
	catch (int i) {
		std::cout << "Error assign" << std::endl;
		abort();
	}
}

void List::add_begin(const Data& new_element) {
	Element* temp = new Element;
	temp->next = head;
	temp->data = new_element;
	head = temp;
	size++;
	std::cout << "Added element: (" << new_element.value << ", " << new_element.name << ") to the beginning of the list" << std::endl;
}
void List::add_end(const Data& new_element) {
	if (head == nullptr) {
		add_begin(new_element);
	}
	else {
		Element* par = head;
		while (par->next != nullptr) {
			par = par->next;
		}
		Element* temp = new Element;
		temp->next = nullptr;
		temp->data = new_element;
		par->next = temp;
		size++;
		std::cout << "Added element: (" << new_element.value << ", " << new_element.name << ") to the end of the list" << std::endl;
	}
}
void List::add_index(const Data& new_element, const int index) {
	if (index == 0) {
		add_begin(new_element);
	}
	else if (index >= size) {
		add_end(new_element);
	}
	else {
		Element* par = head;
		for (int i = 0; i < index - 1; i++) {
			par = par->next;
		}
		Element* temp = new Element;
		temp->next = par->next;
		temp->data = new_element;
		par->next = temp;
		size++;
		std::cout << "Added element: (" << new_element.value << ", " << new_element.name << ") to the index " << index << std::endl;
	}
}
void List::add(const Data& new_element) {
	if (head == nullptr) {
		add_begin(new_element);
	}
	else {
		Element* par = head;
		int index = 0;
		while (par != nullptr) {
			if (new_element.value > par->data.value) {
				index++;
			}
			par = par->next;
		}
		add_index(new_element, index);
	}
}

void List::del_begin() {
	if (head != nullptr) {
		Element* temp = head->next;
		std::cout << "Removed element: (" << head->data.value << ", " << head->data.name << ") from the beginning of the list" << std::endl;
		delete head;
		head = temp;
		size--;
	}
	else
		std::cout << "List is empty" << std::endl;
}
void List::del_end() {
	if (head != nullptr) {
		Element* temp = head;
		for (int i = 0; i < size - 2; i++) {
			temp = temp->next;
		}
		std::cout << "Removed element: (" << temp->next->data.value << ", " << temp->next->data.name << ") from the end of the list" << std::endl;
		delete(temp->next);
		temp->next = nullptr;
		size--;
		//std::cout << "Removed element from the end of the list" << std::endl;
	}
	else
		std::cout << "List is empty" << std::endl;
}
void List::del_index(const int index) {
	if (index == 0) {
		del_begin();
	}
	else if (index == (size - 1)) {
		del_end();
	}
	else if (index > 0 && index < size - 1) {
		Element* par = head;
		Element* temp = head;
		for (int i = 0; i < index - 1; i++) {
			par = par->next;
			temp = temp->next;
		}
		temp = temp->next;
		par->next = temp->next;
		std::cout << "Removed element: (" << temp->data.value << ", " << temp->data.name << ") with index " << index << std::endl;
		delete(temp);
		size--;
	}
	else
		std::cout << "Nothing deleted" << std::endl;
}

int List::search_value(const int _value) const {
	Element* par = head;
	int index = 0;
	while (par != nullptr) {
		if (par->data.value == _value) {
			std::cout << "Element: (" << par->data.value << ", " << par->data.name << ") with value \"" << _value << "\" found" << std::endl;
			return index;
		}
		par = par->next;
		index++;
	}
	std::cout << "Element with value \"" << _value << "\" not found" << std::endl;
	return -1;
}

int List::search_name(const std::string _name) const {
	Element* par = head;
	int index = 0;
	while (par != nullptr) {
		if (par->data.name == _name) {
			std::cout << "Element: (" << par->data.value << ", " << par->data.name << ") with name \"" << _name << "\" found" << std::endl;
			return index;
		}
		par = par->next;
		index++;
	}
	std::cout << "Element with name \"" << _name << "\" not found" << std::endl;
	return -1;
}

void List::remove_value(const int _value) {
	del_index(search_value(_value));
}

void List::remove_name(const std::string _name) {
	del_index(search_name(_name));
}

int List::count() const {
	std::cout << "List contains " << size << " elements" << std::endl;
	return size;
}
List::Element* List::begin() {
	return head;
}
List::Element* List::end() {
	return nullptr;
}

void List::print() const {
	Element* par = head;
	while (par != nullptr) {
		std::cout << par->data.value << " " << par->data.name << " --> ";
		par = par->next;
	}
	std::cout << "nullptr" << std::endl;
}

List::~List() {
	std::cout << "Destructor" << std::endl;
	while (head != nullptr) {
		Element* temp = head->next;
		delete head;
		head = temp;
	}
}