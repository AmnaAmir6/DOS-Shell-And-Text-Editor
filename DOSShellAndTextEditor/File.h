#pragma once
#include<string>
#include<iostream>
#include<time.h>
#include<ctime>
using namespace std;
class Folder;
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
	time_t CreationTime;
	//time_t CreationTime;
	/*int NOChars;
	int AvgChPerLine;
	int NOLines;*/
public:
	File(string n, string type , string path , string , Folder* p , bool RO , int priority , int TimeToPrint , time_t CT);
	string getName();
	void setName(string n);
	void PrintCreationTime();
};

