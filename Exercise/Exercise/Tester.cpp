#include "Pool_Thread.h"
#include "CBingoTest.h"
#include <iostream>
#include <stdio.h>

int AddFunction(int i, int id) {

	printf_s("%d start \n", id);
	std::this_thread::sleep_for(std::chrono::seconds(i));
	printf_s("%d end after %d\n", id, i);

	return i + id;
}


int main() {

	/*CPool_Thread pool(3);

	std::vector<std::future<int>> futures;
	for (int i = 0; i < 10; ++i) {
		futures.emplace_back(pool.Enqueue(AddFunction, i % 3 + 1, i));
	}

	for (auto& iter : futures) {
		printf_s("result : %d \n", iter.get());
	}

	system("pause");*/
	std::vector<std::vector<int>> Data;
	int a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 1});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 2});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 3});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 4});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 6});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 9});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 11});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 15});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 27});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{1, 5});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{2, 3});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{2, 10});
	a = sizeof(Data);
	Data.push_back(std::vector<int>{2, 12});
	a = sizeof(Data);

	Data.size();

	CBingoTest Tester;
	int result = Tester.Insert(Data);

	return 0;
}