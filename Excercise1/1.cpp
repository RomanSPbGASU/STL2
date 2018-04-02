#include <Windows.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <conio.h>
using namespace std;

struct names
{
	int number;
	char name_b[80];
	friend istream& operator >> (istream& is, names& n)
	{
		char ch;
		is >> n.number >> ch;
		is.getline(n.name_b, 80);
		return is;
	}
};
struct plans
{
	char plan;
	float num_sc;
	string name;
	friend istream& operator >> (istream& is, plans& p)
	{
		char ch[240];
		char ch1;
		is >> p.plan >> ch1 >> p.num_sc >> ch1;
		is.get(ch, 240);
		p.name = ch;
		return is;
	}
};
struct money
{
	int regn;
	char plan;
	int num_sc;
	char a_p;
	float vr, vv, vitg, ora, ova, oitga, orp, ovr, oitgp, ir, iv, iitg;
	string dt;
	float priz;
	friend istream& operator >> (istream& is, money& m)
	{
		char ch1, ch[18];
		string date;
		is >> m.regn >> ch1
			>> m.plan >> ch1
			>> m.num_sc >> ch1
			>> m.a_p >> ch1
			>> m.vr >> ch1
			>> m.vv >> ch1
			>> m.vitg >> ch1
			>> m.ora >> ch1
			>> m.ova >> ch1
			>> m.oitga >> ch1
			>> m.orp >> ch1
			>> m.ovr >> ch1
			>> m.oitgp >> ch1
			>> m.ir >> ch1
			>> m.iv >> ch1
			>> m.iitg >> ch1;
		for (int i = 0; i < 18; i++)
			ch[i] = is.get();
		date = ch;
		m.dt = date.substr(0, 10);
		is >> ch1 >> m.priz;
		return is;
	}
};
struct res
{
	int regn, num_sc;
	string dt;
	float iitg;
	friend ostream& operator << (ostream& os, const res& r)
	{
		os << r.regn << "  " << r.num_sc << "  " << r.dt << "  " << setw(7) << fixed << setprecision(0) << r.iitg;
		return os;
	}
};

void read_names(const char*, vector<names>&);
void read_money(const char*, vector<money>&);
void read_plans(const char*, vector<plans>&);
string read_name(int, vector<names>);
string read_plan(int, vector<plans>);
void search_money(float, int, vector<money>, vector<res>&);
void show_res(vector<res>);
void write_res(const char*, vector<res>);

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	vector<names> vname;
	vector <money> vmoney;
	vector <plans> vplans;
	vector <res> vres;
	const char*f1 = "101F.txt",
		*f2 = "NAMES.txt",
		*f3 = "PLAN.txt",
		*fr = "result.txt";
	read_names(f2, vname);
	read_plans(f3, vplans);
	read_money(f1, vmoney);

	int reg_b, num_b;
	cout << "Введите номер банка: "; cin >> reg_b;
	cout << "Введите номер счета: "; cin >> num_b;
	cout << endl;
	cout << "Денежные остатки на счете №" << num_b << " " << read_plan(num_b, vplans) << " " << endl;
	cout << "	Для банка №" << reg_b << " " << read_name(reg_b, vname) << endl;

	search_money(reg_b, num_b, vmoney, vres);
	show_res(vres);
	write_res(fr, vres);

	_getch();
}

void read_names(const char* fl, vector<names>& vc)
{
	ifstream myfile;
	myfile.open(fl, ios::in, ios::_Nocreate);

	istream_iterator<names> name_it(myfile);
	istream_iterator<names> end_of_stream;
	copy(name_it, end_of_stream, back_inserter(vc));

	//string fle = fl;
	//string name = fle.substr(fle.size() - 8, fle.size());
	cout << "Считано " << vc.size() << " записей из файла " << fl << ";" << endl;
	myfile.close();
}
void read_plans(const char* fl, vector<plans>&vc)
{
	ifstream myfile;
	myfile.open(fl, ios::in, ios::_Nocreate);

	istream_iterator<plans> plans_it(myfile);
	istream_iterator<plans> end_of_stream;
	copy(plans_it, end_of_stream, back_inserter(vc));

	cout << "Считано " << vc.size() << " записей из файла " << fl << ";" << endl;
	myfile.close();
}
void read_money(const char* fl, vector<money>& vc)
{
	ifstream myfile;
	myfile.open(fl, ios::in, ios::_Nocreate);

	istream_iterator<money> money_it(myfile);
	istream_iterator<money> end_of_stream;
	copy(money_it, end_of_stream, back_inserter(vc));

	cout << "Считано " << vc.size() << " записей из файла " << fl << ";" << endl;
	myfile.close();
}
// получение наименования банка по его номеру
string read_name(int id, vector<names> vc)
{
	for (int i = 0; i < vc.size(); i++)
	{
		if (vc[i].number == id)
			return vc[i].name_b;
	}
	return "Банк c заданным id не обнаружен!";
}
//получение наименования счёта по его номеру
string read_plan(int id, vector<plans> vc)
{
	for (int i = 0; i < vc.size(); i++)
	{
		if (vc[i].num_sc == id)
			return vc[i].name;
	}
	return "Счет c заданным id не обнаружен!";
}
// поиск записей, удовлетворяющих заданным условиям
void search_money(float id_b, int id_sc, vector<money> vc, vector<res>& rs)
{
	res temp;
	for (int i = 0; i < vc.size(); i++)
	{
		if (vc[i].num_sc == id_sc && vc[i].regn == id_b)
		{
			temp.regn = id_b;
			temp.num_sc = id_sc;
			temp.iitg = vc[i].iitg;
			temp.dt = vc[i].dt;
			rs.push_back(temp);
		}
	}
	cout << "Найдено " << rs.size() << " записей" << endl;
}
// вывод результатов на экран
void show_res(vector<res> rs)
{
	if (rs.size() != 0)
	{
		cout << setiosflags(ios::left) << setw(20) << "Дата" << setw(10) << "Сумма" << endl;
		for (int i = 0; i < rs.size(); i++)
			cout << setiosflags(ios::left) << setw(20) << rs[i].dt << setw(10) << setiosflags(ios::fixed) << setprecision(0) << rs[i].iitg << endl;
	}
	else
		cout << "Нет данных для вывода!" << endl;
}
// запись рузультатов в файл RESULT.txt
void write_res(const char* fl, vector<res> rs)
{
	ofstream myfile;
	myfile.open(fl, ios::out);
	myfile << setiosflags(ios::left) << setw(7) << "REGN" << setw(7) << "NUM_SC" << setw(15) << "DT" << setw(10) << "IITG" << endl;
	for (int i = 0; i < rs.size(); i++)
		myfile << setiosflags(ios::left) << setw(7) << rs[i].regn << setw(7) << rs[i].num_sc << setw(15) << rs[i].dt << setw(10) << setiosflags(ios::fixed) << setprecision(0) << rs[i].iitg << endl;

	cout << "Сохранено " << rs.size() << " записей в файл " << fl << ";" << endl;
	myfile.close();
}