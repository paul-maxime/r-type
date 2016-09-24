#include <cstdlib>
#include <iostream>
#include <functional>

#include "RType/Server/ThreadPool.hpp"

void print_number(int number)
{
	// Simulate a very long operation //
	std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 1000));

	std::cout << number << std::endl;
}

// Will execute 100 operations using 8 threads //

int main()
{
	rtype::server::ThreadPool pool(8);

	for (int i = 0; i < 100; ++i)
	{
		pool.add(std::bind(print_number, i));
	}

	pool.join();
}
