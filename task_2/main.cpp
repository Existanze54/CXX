#include <iostream>
#include <string>

int fibonacci(int n) {
	int a = 0, b = 1, c;
	if (n < 0) {
		if (n % 2 == 0)
			return -fibonacci(-n);
		else
			return fibonacci(-n);
	}
	else if (n == 0)
		return a;
	else if (n == 1)
		return b;
	else
	    for (int i = 2; i <= n; i++) {
		    c = a + b;
		    a = b;
		    b = c;
	    }
	return c;
}

int main(int argc, char* argv[]) {
	int n = std::stoi(argv[1]);
	std::cout << "Fibonacci number: " << fibonacci(n);
	return 0;
}