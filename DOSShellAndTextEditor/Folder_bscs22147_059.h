#pragma once
#include<string>
#include<time.h>
#include<ctime>
#include<iostream>
#include<list>
#include"utility_bscs22147_059.h"
#include"File_bscs22147_059.h"
using namespace std;
class Folder
{
public:
	string Name;
	list<Folder*> Folders;
	list<File*> Files;
	Folder* Parent;
	time_t CreationTime;
	string Path;
	string Owner;
	bool Hidden;
public:
	
	Folder(string n = {}, string path = {}, string own = {}, Folder* p = {}, bool hid = false, time_t CT = {});
	void  PrintCreationTime();
	void print();
	void addFile(File* F);
	void addFolder(Folder* F);
	void removeFile(File* F);
	void removeFolder(Folder* F);
	File* findFile(string FN);
	Folder* findFolder(string FN);
	string getName();
	void setName(string n);
	string getPath();
	Folder* getParent();
	~Folder();
};

