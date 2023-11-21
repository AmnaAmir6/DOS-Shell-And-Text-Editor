#pragma once
#include<iostream>
#include<list>
using namespace std;
class Lines
{
	int word_count;
	int max_length_word;
	int smallest_word_length;
public:
	//int cuurent_column;

	list<char>Line;
	list<char>::iterator ci;
	Lines()
	{
		//cuurent_column = 0;
		word_count = 0;
		max_length_word = 0;
		smallest_word_length=0;
		char a = ' ';
		Line.push_back(a);
		ci = Line.begin();
	}
	list<char>::iterator GetBegin()
	{
		return Line.begin();
	}
	
	int GetWord_Count()
	{
		return word_count;
	}
	int GetLongestWordLength()
	{
		return max_length_word;
	}
	
};

