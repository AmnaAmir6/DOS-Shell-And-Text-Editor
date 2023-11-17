#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

#include"Folder.h"
#include"Tree.h"

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
};

