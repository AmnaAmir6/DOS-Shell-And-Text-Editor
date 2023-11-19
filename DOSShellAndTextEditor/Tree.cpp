#include "Tree.h"
#include<iostream>
#include<fstream>
#include"Folder.h"
using namespace std;

Tree::Tree()
{
	this->root = new Folder("V");
	curr_folder = root;
}

void Tree::LoadFolder(Folder* F,ifstream& rdr)
{
	//int folders, files;
	//rdr >> folders;
	//rdr >> files;
	string FFs;
	getline(rdr, FFs);

	int folders, files;
	folders = stoi(FFs.substr(0, FFs.find(' ')));
	files= stoi(FFs.substr(FFs.find(' ')+1,FFs.length()));

	for (int i = 0; i < folders; i++)
	{
		string FN;
		getline(rdr, FN);
		Folder* NewFolder = new Folder(FN, F->Path + "\\" + F->Name, F->Owner, F, false, time(0));
		F->addFolder(NewFolder);
		LoadFolder(NewFolder, rdr);
	}
	for (int i = 0; i < files; i++)
	{
		string FN;
		getline(rdr, FN);
		File* NewFile = new File(FN,"txt", F->Path + "\\" + F->Name, F->Owner,F,false,0,0,time(0));
		F->addFile(NewFile);
	}
}

void Tree::LoadFromFile()
{
	ifstream rdr("tree.txt");
	string R;
	getline(rdr, R);
	this->root = new Folder(R);
	this->curr_folder = root;
	LoadFolder(root, rdr);
}

void Tree::SaveFolder(Folder* F, ofstream& wtr)
{
	int folders = F->Folders.size();
	int files = F->Files.size();
	wtr << folders << " " << files << endl;
	for (auto itr = F->Folders.begin(); itr != F->Folders.end(); itr++)
	{
		wtr << (*itr)->Name << endl;
		SaveFolder(*itr, wtr);
	}
	for (auto itr = F->Files.begin(); itr != F->Files.end(); itr++)
	{
		wtr << (*itr)->Name << endl;
	}
}

void Tree::SaveTree()
{
	ofstream wtr("SaveTree.txt");
	wtr << root->Name << endl;
	SaveFolder(root, wtr);
}

void Tree::insert(Folder * folder)
{
	curr_folder->addFolder(folder);
}
void Tree::Print(string Prompt)
{
	if(curr_folder->getName()=="V")
	{ 
		cout << "\nV:" << Prompt;
	}
	else
	{
		cout << "\nV:" << curr_folder->getPath().substr(2,curr_folder->getPath().length())<<"\\"<<curr_folder->getName()<<Prompt;
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
bool Tree::DoesFileExist(string fl)
{
	auto start = curr_folder->Files.begin();
	auto end = curr_folder->Files.end();

	for (auto i = start; i != end; i++)
	{
		if ((*i)->getName() == fl)return true;
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
bool Tree::DoesFolderExist(string fd)
{
	auto start = curr_folder->Folders.begin();
	auto end = curr_folder->Folders.end();

	for (auto i = start; i != end; i++)
	{
		if ((*i)->getName() == fd)return true;
	}

	return false;
}
Folder* Tree::getCurrent()
{
	return curr_folder;
}
Folder* Tree::getRoot()
{
	return root;
}
void Tree::setCurrent(Folder* F)
{
	curr_folder = F;
}

File* Tree::FindFile(string f)
{
	return curr_folder->findFile(f);
}
Folder* Tree::FindFolder(string f)
{
	return curr_folder->findFolder(f);
}

void Tree::TreePrint()
{
	cout << "\nFolder PATH listing" << endl;
	//cout << "V:" << endl;
	PrintFolder(curr_folder);
}

void Tree::PrintFolder(Folder* F, int spaces)
{
	for (int i = 0; i < spaces; i++)
	{
		cout << "   ";
	}
	cout << F->Name << endl;
	for (auto itr = F->Folders.begin(); itr != F->Folders.end(); itr++)
	{
		PrintFolder(*itr, spaces + 1);
	}
	for (auto itr = F->Files.begin(); itr != F->Files.end(); itr++)
	{
		for (int i = 0; i < spaces + 1; i++)
		{
			cout << "   ";
		}
		cout << (*itr)->Name << endl;
	}
}

void Tree::EraseTree()
{
	Folder* r = new Folder(root->Name, root->Path, root->Owner, nullptr, false, root->CreationTime);
	delete root;
	root = r;
	curr_folder = r;
	r = nullptr;
}