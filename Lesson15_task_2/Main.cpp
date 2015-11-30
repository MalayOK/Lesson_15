#include "stdafx.h"
using namespace std;

void forEachInTwoWords(string& str, 
	function<void(string&, int )> operation)
{

	for (unsigned int i = 0; i < str.size(); ++i)
	{
		operation(str, i);
	}

}

void replaceLetterNew(vector <string>& s, int index,
	char oldletter, char newletter)
{
	string& str = s[index];
	auto lambda = [oldletter, newletter](string& str, int i)
	{
		
		if (str[i] == oldletter)
			str[i] = newletter;
	};

	forEachInTwoWords(str, lambda);
}

void removeLetterNew(vector <string>& s, int index,char letter)
{
  string& str = s[index];
	auto lambda = [letter](string& str, int i)
	{

		if (str[i] == letter)
			str[i] = ' ';
	};

	forEachInTwoWords(str, lambda);
}

void show_vector(vector<string>& vec)
{
	for (vector<string>::iterator it = vec.begin();
	it != vec.end(); ++it)
	{
		cout << *it << ' ';
	}
}
int main()
{
	vector <string> s1 = {"afha","bsaf","crfwfas","d42a2"};
	vector <string> s2 = { "13a3411","2rweds","3fsafsf","411a3edd" };
	removeLetterNew(s2,3,'1');
	replaceLetterNew(s1, 2, 'a', 'Y');
	show_vector(s2);
	cout << endl;
	show_vector(s1);
	cin.get();
	return 0;
}