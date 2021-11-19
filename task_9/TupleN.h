#pragma once
#include <vector>
#include <string>
#include <cassert>
#include <type_traits>
#include <concepts>


template<typename T, size_t N>
class TupleN {
protected:
	std::vector<T> _components;
	size_t _size;

public:
	TupleN() {
		//std::cout << "Empty constructor parent" << std::endl;
		_size = N;
	}

	TupleN(const T components[N]) {
		//std::cout << "Constructor from array parent" << std::endl;
		for (int i = 0; i < N; ++i) {
			_components.push_back(components[i]);
		}
		_size = N;
	}

	TupleN(const std::vector<T>& vec) {
		if (vec.size() != N) {
			std::cout << "Incorrect vector for constructor from vector parent" << std::endl;
			assert(vec.size() == N);
		}
		else {
			//std::cout << "Constructor from vector parent" << std::endl;
			_components = vec;
			_size = vec.size();
		}
	}

	TupleN(const TupleN<T, N>& to_copy) {
		//std::cout << "Copy constructor parent" << std::endl;
		_components = to_copy._components;
		_size = to_copy._size;
	}

	template <typename ... Args>
	TupleN(T first, Args const& ... components) {
		//std::cout << "Constructor from components parent" << std::endl;
		fill(first, components ...);
		if (_components.size() != N) {
			std::cout << "Incorrect parameters for constructor from ... components parent" << std::endl;
			assert(_components.size() == N);
		}
		else
			_size = N;
	}

	void fill(T const& first) {
		_components.push_back(first);
	}

	template <typename First, typename ... Tail>
	void fill(First const& first, Tail const& ... tail) {
		_components.push_back(first);
		fill(tail...);
	}

	inline size_t size() const {
		return _size;
	}

	void print() const {
		for (T elem : _components) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;
	}

	inline bool operator == (const TupleN<T, N>& to_compare) const {
		return _components == to_compare._components;
	}

	inline bool operator != (const TupleN<T, N>& to_compare) const {
		return _components != to_compare._components;
	}


	~TupleN() {
		//std::cout << "Destructor parent" << std::endl;
		_components.clear();
	}
};


template <typename T, size_t N> 
class Tuple : public TupleN<T, N> {
public:
	Tuple() : TupleN<T, N>() {
		//std::cout << "Empty constructor for generic tuple" << std::endl;
	}

	Tuple(const std::vector<T>& vec) : TupleN<T, N>(vec) {
		//std::cout << "Constructor from vector for generic tuple" << std::endl;
	}

	Tuple(const T components[N]) : TupleN<T, N>(components){
		//std::cout << "Constructor from array for generic tuple" << std::endl;
	}

	Tuple(const Tuple<T, N>& to_copy) : TupleN<T, N>(to_copy){
		//std::cout << "Copy constructor for generic tuple" << std::endl;
	}

	template <typename ... Args>
	Tuple(T first, Args const& ... components) : TupleN<T, N>(first, components ...) {
		//std::cout << "Constructor from components for genetic tuple" << std::endl;
	}
};


template <typename T, size_t N> requires std::is_arithmetic<T>::value
class Tuple<T, N> : public TupleN<T, N> {
public:
	Tuple() : TupleN<T, N>() {
		//std::cout << "Empty constructor for arithmetic tuple" << std::endl;
	}

	Tuple(const T components[N]) : TupleN<T, N>(components) {
		//std::cout << "Constructor from array for arithmetic tuple" << std::endl;
	}

	Tuple(const std::vector<T>& vec) : TupleN<T, N>(vec) {
		//std::cout << "Constructor from vector for arithmetic tuple" << std::endl;
	}

	Tuple(const Tuple<T, N>& to_copy) : TupleN<T, N>(to_copy) {
		//std::cout << "Copy constructor for arithmetic tuple" << std::endl;
	}

	template <typename ... Args>
	Tuple(T first, Args const& ... components) : TupleN<T, N>(first, components ...) {
		//std::cout << "Constructor from components for arithmetic tuple" << std::endl;
	}

	Tuple operator + (const Tuple& tup) const {
		T arr[N];
		//std::cout << "operator + overriden" << std::endl;
		for (size_t i = 0; i < N; ++i)
		{
			arr[i] = this->_components[i] + tup._components[i];
		}
		return Tuple<T, N>(arr);
	}

	Tuple operator - (const Tuple& tup) const {
		T arr[N];
		//std::cout << "operator - overriden" << std::endl;
		for (size_t i = 0; i < N; ++i)
		{
			arr[i] = this->_components[i] - tup._components[i];
		}
		return Tuple<T, N>(arr);
	}

	Tuple operator * (const T& scalar) const {
		T arr[N];
		//std::cout << "scalar multiplication" << std::endl;
		for (size_t i = 0; i < N; ++i)
		{
			arr[i] = this->_components[i] * scalar;
		}
		return Tuple<T, N>(arr);
	}

	auto operator * (const Tuple& tup) const {
		T sum = 0;
		//std::cout << "dot product" << std::endl;
		for (size_t i = 0; i < N; ++i) {
			sum += this->_components[i] * tup._components[i];
		}
		return sum;
	}

};