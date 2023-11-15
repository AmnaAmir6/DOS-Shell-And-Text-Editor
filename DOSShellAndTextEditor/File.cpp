#include "File.h"

File::File(string n, string type = ".txt", string path = "", string own = "", Folder* p = {}, bool RO = false, int _priority = 0, int TTP = 0, time_t CT = 0)
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
void  File::PrintCreationTime()
{
	
	time(&this->CreationTime);

	struct tm timeInfo;
	localtime_s(&timeInfo, &CreationTime);

	char timeString[20];
	strftime(timeString, sizeof(timeString), "%m/%d/%y   %H:%M:%S", &timeInfo);

	cout << " " << timeString;

}
