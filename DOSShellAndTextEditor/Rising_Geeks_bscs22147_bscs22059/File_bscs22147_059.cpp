#include"File_bscs22147_059.h"
File::File(string n, string type, string path, string own, Folder* p, bool RO, int _priority, int TTP, time_t CT)

{
	time(&this->CreationTime);
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
void  File::PrintCreationTime()
{
	
	
	struct tm timeInfo;
	localtime_s(&timeInfo, &CreationTime);

	char timeString[20];
	strftime(timeString, sizeof(timeString), "%m/%d/%y   %H:%M:%S", &timeInfo);

	cout << " " << timeString;

}

void File::print()
{
	cout <<"  " << this->Name << "   "; PrintCreationTime(); cout << "\t" << this->FileType;
}
File::~File()
{
	Parent = nullptr;
}
