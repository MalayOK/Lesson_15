#include "stdafx.h"

using namespace std;
using namespace std::chrono;
recursive_mutex globalMutex1;
mutex globalMutex2;
struct T
{
	int input;
	long double output;
	int IndexOfTask;
};
unsigned int CurrentTask = 0;
vector <int> input_numbers;
vector <long double> output_numbers;
long double fibb(int n);
T NextTask();
void MultiTread();
void WriteResult(T task);

int main()
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	input_numbers.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		input_numbers.push_back(i+30);
	}
	output_numbers.resize(10);
	size_t coreCount = thread::hardware_concurrency();
	std::vector<thread*> threads;
	for (size_t i = 0; i < coreCount; ++i)
	{
	threads.push_back(new thread(MultiTread));
	}
	//this_thread::sleep_for(std::chrono::seconds(7));
	/*for (vector<long double>::iterator it = output_numbers.begin();
	it != output_numbers.end(); ++it)
	{
		cout << *it << endl;
	}*/
	for (size_t i = 0; i < coreCount; ++i)
	{
		threads[i]->join();
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(t2 - t1).count();
	cout << "duration" << duration << endl;
	//cin.get();
	return 0;
}

long double fibb(int n)
{
	if (n < 3) return 1;
	return fibb(n - 1) + fibb(n - 2);
}
T NextTask()
{
	globalMutex1.lock();
	T t;
	if (CurrentTask>=input_numbers.size())
	{
		t.IndexOfTask = -1;
		return t;
	}
	int nextInput = input_numbers[CurrentTask];
	t.input = nextInput;
	t.IndexOfTask = CurrentTask;
	CurrentTask++;
	globalMutex1.unlock();

	return t;
}

void WriteResult(T task)
{
	globalMutex2.lock();
	output_numbers[task.IndexOfTask] = task.output;
	cout << task.output << endl;
	globalMutex2.unlock();
}

void MultiTread()
{
	while (true)
	{
		T task = NextTask();
		if (task.IndexOfTask == -1)
			break;
		task.output = fibb(task.input);
		WriteResult(task);
	}
}
