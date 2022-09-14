#include "Pool_Thread.h"
#include <iostream>
#include <stdio.h>

int AddFunction(int i, int id) {

	printf_s("%d start \n", id);
	std::this_thread::sleep_for(std::chrono::seconds(i));
	printf_s("%d end after %d\n", id, i);

	return i + id;
}


int main() {

	CPool_Thread pool(3);

	std::vector<std::future<int>> futures;
	for (int i = 0; i < 10; ++i) {
		futures.emplace_back(pool.Enqueue(AddFunction, i % 3 + 1, i));
	}

	for (auto& iter : futures) {
		printf_s("result : %d \n", iter.get());
	}

	system("pause");
	return 0;
}