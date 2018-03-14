#include"SkipList.h"
#include<iostream>
using namespace std;
#include<vector>
class comp {
public:
	bool operator()(const int &T1, const int &T2)
	{
		return T1 > T2;
	}
};
int main()
{
	SkipList<int, int,comp> sl(1000, 0.5);
	for (int i = 1; i < 200; i++)
	{
		sl.insert(rand(),rand());
		//cout << i << ":" << endl;
		//sl.print();
	}
	sl.print();
	int result = 0;
	bool flag = false;
	flag = sl.find(12, result);
	result = 0;
	sl.remove(12, result);
	sl.insert(12, rand());
	cout << "******************" << endl;
	sl.print();
	cout << flag << endl << result << endl;
	cout << sl.empty() << sl.size() << endl;
	return 0;
	}
