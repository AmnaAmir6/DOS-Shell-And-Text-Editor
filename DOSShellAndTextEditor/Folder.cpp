#include "Folder.h"
Folder::Folder(string n, string path = "", string own = "", Folder* p = {}, bool hid = false, time_t CT = 0)
{
	this->Name = n;
	this->Path = path;
	this->Owner = own;
	this->Parent = p;
	this->Hidden = hid;
	this->CreationTime = CT;

}
void Folder::print()//todo
{
	cout << "\nDirectory Of " << Path << "\\" << Name << "\\" << endl<<endl;

	for (auto fl = this->Files.begin(); fl != Files.end(); fl++)
	{
		(**fl).PrintCreationTime();
		cout << "\t" << "     " << "\t\t" << (**fl).getName();
		cout << endl;

	}
	for (auto fd = this->Folders.begin(); fd != Folders.end(); fd++)
	{
		(**fd).PrintCreationTime();
		cout << "\t" << "<DIR>" << "\t\t" << (**fd).getName();
		cout << endl;

	}



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
void  Folder::PrintCreationTime()
{

	time(&this->CreationTime);

	struct tm timeInfo;
	localtime_s(&timeInfo, &CreationTime);

	char timeString[20];
	strftime(timeString, sizeof(timeString), "%m/%d/%y   %H:%M:%S", &timeInfo);

	cout << " " << timeString ;

}