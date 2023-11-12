#pragma once
#include<string>
#include<iostream>
using namespace std;
#include"Folder.h"
class File
{
	string Name;
	string Path;
	Folder* Parent;
	string Owner;
	bool ReadOnly;
	int Priority;
	int TimeToPrint;
	string FileType;
	double CreationTime;
	/*int NOChars;
	int AvgChPerLine;
	int NOLines;*/
public:
	File(string n, string type = ".txt", string path = "", string own = "", Folder* p = {}, bool RO = false, int priority = 0, int TimeToPrint = 0, double CT = 0);
	string getName();
	void setName(string n);
};

