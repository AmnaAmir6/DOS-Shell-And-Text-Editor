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
	int sum_of_words_length;
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
		sum_of_words_length = 0;
	}
	
	int GetWord_Count()
	{
		return word_count;
	}
	void SetSumOfLengths(int s_of_l)
	{
		sum_of_words_length = s_of_l;
	}
	int GetSumOfLengths()
	{
		return sum_of_words_length;
	}
	int GetLongestWordLength()
	{
		return max_length_word;
	}int GetMinWordLength()
	{
		return smallest_word_length;
	}
	void SetWord_Count(int WC)
	{
		word_count = WC;
	}
	void SetLongestWordLength(int max)
	{
		max_length_word=max;
	}
	void SetMinWordLength(int min)
	{
		smallest_word_length=min;
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
		//cout << " count " << word_count<<" ";
		//cout << " max " << max_length_word;

		cout << endl;
	}
	
};

