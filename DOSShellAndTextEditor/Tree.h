#pragma once
#include<iostream>
#include"Folder.h"

class Tree
{

	Folder* root;
	Folder* curr_folder;

public:
	Tree();
	void insert(Folder*);
	void Print(string Prompt="\\");
	bool DoesFileExist(File*);
	bool DoesFileExist(string f);
	bool DoesFolderExist(Folder*);
	bool DoesFolderExist(string f);
	Folder* getCurrent();
	Folder* getRoot();
	void setCurrent(Folder* F);
	File* FindFile(string f);
	Folder* FindFolder(string f);
};

