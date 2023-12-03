#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include"utility_bscs22147_059.h"
#include"Tree_bscs22147_059.h"
#include"File_bscs22147_059.h"
using namespace std;


class DOS
{
	Tree T;
	string UserName = "Amna Amir | Abdul Moqeet";
	bool prompt = false;
	void toLower(string& A);
public:
	DOS();
	void print();
	void play();
	bool Input();
	void Copy(string S);
	void Move(string S);
	void ConvertExtension(Folder* F, string Extension, string NewExtension);
	void Rename(string cmnd);
	File* FindFile(string name);
	void FindFile(Folder* root,string name,bool &found,File*&file);
	void Edit(string cmnd);
};

