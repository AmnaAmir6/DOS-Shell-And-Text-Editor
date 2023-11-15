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
	bool DoesFolderExist(Folder*);


};

