#pragma once
#include<iostream>
#include<list>
#include"utility.h"
using namespace std;
class Lines
{
	int word_count;
	int max_length_word;
	int smallest_word_length;
public:
	//int cuurent_column;
	list<char>Line;
	Lines()
	{
		//cuurent_column = 0;
		word_count = 0;
		max_length_word = 0;
		smallest_word_length=0;
		char a = ' ';
		Line.push_back(a);
	}
	
	int GetWord_Count()
	{
		return word_count;
	}
	int GetLongestWordLength()
	{
		return max_length_word;
	}
	void SetWord_Count(int WC)
	{
		word_count = WC;
	}
	void SetLongestWordLength(int max)
	{
		max_length_word=max;
	}
	void PrintLine(int ri)
	{
		int ci = 0;
		for (auto i = Line.begin(); i != Line.end(); i++,ci++)
		{
			SetClr(240);
			gotoRowCol(ri,ci);
			cout << *i;
		}
		cout << endl;
	}
	
};

