#include <thread>
#include <memory>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <mutex>

static int Count = 0;

void Work(long long& Value, std::mutex& m) {
	for (int i = 0; i < 10000; ++i) {
		std::lock_guard<std::mutex> lock(m);
		Value += i;
		printf_s("%d ) Hello, I'm Thread %d, Current Value is %d \n", Count++,std::this_thread::get_id(), Value);
	}
}


int main() {
	std::vector<std::thread> Workers;
	
	long long Value = rand() % 500;
	std::mutex m;
	for (int i = 0; i < 4; ++i)	{
		Workers.emplace_back(std::thread(Work, std::ref(Value), std::ref(m)));
	}

	for (int i = 0; i < 4; ++i) {
		Workers[i].join();
	}

	std::cout << Count<< " ) " << "Last Value is " << Value << std::endl;
	system("pause");

	return 0;
}