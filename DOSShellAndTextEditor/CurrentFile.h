#pragma once
#include<list>
#include<iostream>
#include"Lines.h"
#include"utility.h"
using namespace std;

class CurrentFile
{
	list<Lines>text;
	list<Lines>::iterator ri;
	int Curr_row, Curr_col;
	list<char>::iterator ci;

 public:

	 CurrentFile();
	 void Insert();

	



};

