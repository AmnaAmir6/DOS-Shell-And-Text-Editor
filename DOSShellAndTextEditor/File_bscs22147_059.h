#pragma once
#include<string>
#include<iostream>
#include<time.h>
#include<ctime>
using namespace std;
class Folder;
class File
{

public:
	string Password;
	string Name;
	string Path;
	Folder* Parent;
	string Owner;
	bool ReadOnly;
	int Priority;
	int TimeToPrint;
	string FileType;
	time_t CreationTime;
	//time_t CreationTime;
	/*int NOChars;
	int AvgChPerLine;
	int NOLines;*/

	File(string pw, string n, string type = ".txt", string path = "", string own = "", Folder* p = {}, bool RO = false, int _priority = 0, int TTP = 0, time_t CT = 0);
	string getName();
	void setName(string n);
	void PrintCreationTime();
	void print();
	~File();
	
};

