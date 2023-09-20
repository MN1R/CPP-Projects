#include <iostream>
#include <vector>
#include <list>

#include "StackAllocator/stack_allocator.h"
#include "List/list.h"


int main() {
	std::vector<int, typename stack_allocator<int>> stl_vector(6, 15);
	std::list<double, typename stack_allocator<double>> stl_list(20, 14);
	list<std::vector<int>, stack_allocator<std::vector<int>>> my_list (3, { 1, 2, 3 });

	for (auto vec : my_list) {

		for (auto el : vec) {
			std::cout << el << ' ';
		}

		std::cout << '\n';
	}

  return 0;
}