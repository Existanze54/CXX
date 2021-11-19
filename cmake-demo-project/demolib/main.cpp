#include <iostream>
#include <Eigen/Dense>


int demofun(int x)
{
	std::cout << "[demolib] demofun(" << x << ")" << std::endl;
	return x > 0 ? x + demofun(x-1) : 0;
}
