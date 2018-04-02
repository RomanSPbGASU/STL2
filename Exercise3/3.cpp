#include <Windows.h>
#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

class person
{
private:
	string lastName, firstName;
public:
	person() : lastName(" "), firstName(" ")	// конструктор по умолчанию
	{}
	person(string lName, string fName) : lastName(lName), firstName(fName) // конструктор с двумя параметрами
	{}
	friend bool operator < (const person& p1, const person& p2)
	{
		if (p1.lastName == p2.lastName)
			return (p1.firstName < p2.firstName) ? true : false;
		return (p1.lastName < p2.lastName) ? true : false;
	}
	friend ostream& operator << (ostream& os, const person& p)
	{
		os << setw(15) << left << p.lastName << " " << setw(15) << left << p.firstName;
		return os;
	}
	friend istream& operator >> (istream& is, person& p)
	{
		is >> p.lastName >> p.firstName;
		return is;
	}
};
// считывает данные в двустороннюю очередь
deque<person> input(const char* filename)
{
	ifstream myfile(filename);
	istream_iterator<person> person_iter(myfile);
	istream_iterator<person> end_of_stream;

	deque<person> group;
	copy(person_iter, end_of_stream, back_inserter(group));
	return group;
}
// возвращает случайное число в диапазоне от 1 до uppervalue
int rnd(unsigned int uppervalue)
{
	return 1 + (rand() % uppervalue);
}
// возвращяет отображение "студент -> номер варианта"
map<person, int> random(deque<person> group)
{
	unsigned int var_count;
	cout << "Введите количество вариантов: "; cin >> var_count; cout << endl;
	map<person, int> randomized_group;
	for (int i = 0; i < group.size(); i++)
	{
		randomized_group[group[i]] = rnd(var_count);
	}
	return randomized_group;
}

// выводит отображение на экран и записывает в файл
void output(map<person, int> random_group, const char* fl)
{
	ofstream os(fl);
	for (auto iter = random_group.begin(); iter != random_group.end(); iter++)
	{
		os	 << iter->first << "№ " << iter->second << endl;
		cout << iter->first << "№ " << iter->second << endl;
	}
}

int main()
{
	SetConsoleOutputCP(1251); // русская однобайтовая кодировка
	srand(time(NULL));	// позволяет при каждом запуске программы выводить новую последовательность случайных чисел

	output(random(input("group.txt")), "group_pair_out.txt");

	system("pause");
}