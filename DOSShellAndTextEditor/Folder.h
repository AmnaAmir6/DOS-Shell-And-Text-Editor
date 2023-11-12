#pragma once
#include<string>
#include<iostream>
#include<list>
#include"File.h"
using namespace std;
class Folder
{
	string Name;
	list<Folder*> Folders;
	list<File*> Files;
	Folder* Parent;
	int CreationTime;
	string Path;
	string Owner;
	bool Hidden;
public:
	Folder(string n, string path = "", string own = "", Folder* p = {}, bool hid = false);
	void print();
	void addFile(File* F);
	void addFolder(Folder* F);
	void removeFile(File* F);
	void removeFolder(Folder* F);
	File* findFile(string FN);
	Folder* findFolder(string FN);
	string getName();
	void setName(string n);
};

