#include <iostream>
#include <random>

float round_n_decimal(float var, int n){
	float value = int(var * pow(10, n) + .5);
	return float(value / pow(10, n));
}

float arr_average(float *arr, int len) {
	float sum = 0;
	for (int i = 0; i < len; i++) {
		sum += arr[i];
	}
	return sum / len;
}

constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 100;

int main() {
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(FLOAT_MIN, FLOAT_MAX);
	for (int n = 0; n < 10; ++n) {
		std::cout << round_n_decimal(dis(gen), 1) << ' ';
	}
	std::cout << '\n';

	std::cout << "Enter the size of the arrays: ";
	int arr_size;
	std::cin >> arr_size;
	float* arr_fst;
	float* arr_sec;
	float* arr_trd;
	arr_fst = new float[arr_size];
	arr_sec = new float[arr_size];
	arr_trd = new float[arr_size];

	for (float *p1 = arr_fst, * p2 = arr_sec, * p3 = arr_trd; p1 < arr_fst + arr_size; ++p1, ++p2, ++p3) {
		*p1 = round_n_decimal(dis(gen), 1);
		*p2 = round_n_decimal(dis(gen), 1);
		*p3 = *p1 + *p2;
	}
	std::cout << "First array: " << std::endl;
	for (int i = 0; i < arr_size; i++)
		std::cout << arr_fst[i] << " ";
	std::cout << std::endl;
	std::cout << "Second array: " << std::endl;
	for (int i = 0; i < arr_size; i++)
		std::cout << arr_sec[i] << " ";
	std::cout << std::endl;
	std::cout << "Third array: " << std::endl;
	for (int i = 0; i < arr_size; i++)
		std::cout << arr_trd[i] << " ";
	std::cout << std::endl;

	float& min_elem = *std::min_element(arr_trd, arr_trd + arr_size);
	float& max_elem = *std::max_element(arr_trd, arr_trd + arr_size);
	std::cout << "Min element in third array: " << min_elem << std::endl;
	std::cout << "Max element in third array: " << max_elem << std::endl;
	std::cout << "Average of third array: " << arr_average(arr_trd, arr_size) << std::endl;

	delete[] arr_fst;
	delete[] arr_sec;
	delete[] arr_trd;

	return 0;
}
