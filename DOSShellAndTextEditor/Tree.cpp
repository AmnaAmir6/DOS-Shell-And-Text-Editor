#include "Tree.h"
#include<iostream>
#include"Folder.h"
using namespace std;

Tree::Tree()
{
	this->root = new Folder("V");
	curr_folder = root;
}

void Tree::insert(Folder * folder)
{
	curr_folder->addFolder(folder);
}
void Tree::Print(string Prompt)
{
	if(curr_folder->getName()=="V")
	{ 
		cout << "V:" << Prompt;
	}
	else
	{
		cout << "V:" << curr_folder->GetPath().substr(2,curr_folder->GetPath().length())<<"\\"<<curr_folder->getName()<<Prompt;
	}

}
bool Tree::DoesFileExist(File* fl)
{
	auto start = curr_folder->Files.begin();
	auto end = curr_folder->Files.end();

	for (auto i = start; i != end; i++)
	{
		if ((*i)->getName() == fl->getName())return true;
	}
	return false;
}
bool Tree::DoesFolderExist(Folder* fd)
{
	auto start = curr_folder->Folders.begin();
	auto end = curr_folder->Folders.end();

	for (auto i = start; i != end; i++)
	{
		if ((*i)->getName() == fd->getName())return true;
	}

	return false;
}