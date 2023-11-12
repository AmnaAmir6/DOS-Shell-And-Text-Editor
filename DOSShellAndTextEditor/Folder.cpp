#include "Folder.h"
Folder::Folder(string n, string path = "", string own = "", Folder* p = {}, bool hid = false)
{
	this->Name = n;
	this->Path = path;
	this->Owner = own;
	this->Parent = p;
	this->Hidden = hid;
}
void Folder::print()//todo
{
	cout << "\nDirectory Of " << Path << "\\" << Name << "\\" << endl;
}
void Folder::addFile(File* F)
{
	Files.push_back(F);
}
void Folder::addFolder(Folder* F)
{
	Folders.push_back(F);
}
void Folder::removeFile(File* F)
{
	Files.remove(F);
}
void Folder::removeFolder(Folder* F)
{
	Folders.remove(F);
}
File* Folder::findFile(string FN)
{
	for (auto itr = Files.begin(); itr != Files.end(); itr++)
	{
		if ((*itr)->getName() == FN)
			return *itr;
	}
	return nullptr;
}
Folder* Folder::findFolder(string FN)
{
	for (auto itr = Folders.begin(); itr != Folders.end(); itr++)
	{
		if ((*itr)->getName() == FN)
			return *itr;
	}
	return nullptr;
}

string Folder::getName()
{
	return Name;
}
void Folder::setName(string n)
{
	Name = n;
}