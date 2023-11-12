#include "File.h"

File::File(string n, string type = ".txt", string path = "", string own = "", Folder* p = {}, bool RO = false, int _priority = 0, int TTP = 0, double CT = 0)
{
	this->Name = n;
	this->FileType = type;
	this->Path = path;
	this->Owner = own;
	this->ReadOnly = RO;
	this->Priority = _priority;
	this->Parent = p;
	this->TimeToPrint = TTP;
	this->CreationTime = CT;
}

string File::getName()
{
	return Name;
}
void File::setName(string n)
{
	Name = n;
}