#include "stdafx.h"

typedef std::chrono::high_resolution_clock::time_point TimeVar;
#define duration(a) std::chrono::duration_cast<std::chrono::seconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()
template<typename F, typename... Args>
int funcTime(F func, Args&&... args)
{
	TimeVar t1 = timeNow();
	func(std::forward<Args>(args)...);
	return duration(timeNow() - t1);
}
using namespace std;
using namespace std::chrono;
mutex globalMutex1;
struct NextValue
{
	int input;
	long double output;
	int IndexOfTask;
};
unsigned int CurrentTask = 0;
vector <int> input_numbers;
vector <long double> output_numbers;
long double fibb(int n);
NextValue NextTask();
void MultiTread();
void WriteResult(NextValue task);
void OneProcessFibonacce(unsigned int BeginValue, unsigned int EndValue);
void MultiThreadFibonacce();

int main()
{
	cout << "Multi Thread " << funcTime(MultiThreadFibonacce) << endl; 
	cout<<"One Thread "<< funcTime(OneProcessFibonacce,30, 40)<<endl;
	cin.get();
	return 0;
}

long double fibb(int n)
{
	if (n < 3) return 1;
	return fibb(n - 1) + fibb(n - 2);
}
NextValue NextTask()
{
	lock_guard<std::mutex> lck(globalMutex1); 
	NextValue t;
	if (CurrentTask>=input_numbers.size())
	{
		t.IndexOfTask = -1;
		return t;
	}
	int nextInput = input_numbers[CurrentTask];
	t.input = nextInput;
	t.IndexOfTask = CurrentTask;
	CurrentTask++;
	return t;
}

void WriteResult(NextValue task)
{
	output_numbers[task.IndexOfTask] = task.output;
	cout << task.output << endl;
}

void MultiTread()
{
	while (true)
	{
		NextValue task = NextTask();
		if (task.IndexOfTask == -1)
			break;
		task.output = fibb(task.input);
		WriteResult(task);
	}
}

void OneProcessFibonacce(unsigned int BeginValue, unsigned int EndValue)
{
	for (unsigned int i = BeginValue; i < EndValue; ++i)
	{
		long double x = fibb(i);
		cout << x << endl;
	}
}

void MultiThreadFibonacce()
{
	input_numbers.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		input_numbers.push_back(i + 30);
	}
	output_numbers.resize(10);
	size_t coreCount = thread::hardware_concurrency();
	std::vector<thread*> threads;
	for (size_t i = 0; i < coreCount; ++i)
	{
		threads.push_back(new thread(MultiTread));
	}
	for (size_t i = 0; i < coreCount; ++i)
	{
		threads[i]->join();
	}
	for (vector<long double>::iterator it = output_numbers.begin();
	it != output_numbers.end(); ++it)
	{
		cout << *it << endl;
	}
}