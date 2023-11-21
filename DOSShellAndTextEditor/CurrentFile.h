#pragma once
#include<list>
#include<iostream>
#include<fstream>
#include"Lines.h"
#include"utility.h"
using namespace std;

class CurrentFile
{
	list<Lines>text;
	list<Lines>::iterator ri;
	int Curr_row, Curr_col;
	list<char>::iterator ci;
	string Name;
 public:

	 CurrentFile();
	 void Insert();
	 void Set_Max_and_Count(Lines& L);
	 void Print();
	 void SaveFile();
	 void LoadFile();
};

