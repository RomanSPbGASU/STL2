#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <conio.h>
using namespace std;

struct names
{
	int number;
	string name_b;
public:
	friend ostream& operator << (ostream& os, const names& n)
	{
		os << n.number << ";" << n.name_b;
		return os;
	}
	friend istream& operator >> (istream& is, names& n)
	{
		try
		{
			string numstr;
			getline(is, numstr, ';');
			n.number = stoi(numstr);
			getline(is, n.name_b);
		}
		catch (invalid_argument)
		{}
		return is;
	}
};

bool comp_num_greater(const names n1, const names n2)
{
	if (n1.number > n2.number)
		return true;
	else
		return false;
}

void read_names(const char* fl, vector<names>& vc)
{
	ifstream myfile(fl);
	istream_iterator<names> name_it(myfile);
	istream_iterator<names> end_of_stream;
	copy(name_it, end_of_stream, back_inserter(vc));
}

void write_names(const char * fl, vector<names>& vc)
{
	ofstream myfile(fl);
	ostream_iterator<names> name_it(myfile, "\n");
	copy(vc.begin(), vc.end(), name_it);
}

int main()
{
	SetConsoleOutputCP(1251);

	vector<names> vnames;
	read_names("NAMES.txt", vnames);
	cout << "Загружено " << vnames.size() << " записей из файла NAMES.txt" << endl;

	cout << "Сортировка...";
	sort(vnames.begin(), vnames.end(), comp_num_greater);

	write_names("NAMES_new.txt", vnames);

	cout << endl << "Записано " << vnames.size() << " записей в файл NAMES_new.txt" << endl << endl;

	_getch();
}

