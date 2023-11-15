#include "DOS.h"

DOS::DOS()
{

}

void DOS::toLower(string& A)
{
	for (int i = 0; i < A.length(); i++)
	{
		A[i] = tolower(A[i]);
	}
}

void DOS::print()
{
	cout << UserName << "\t59147\tDSA" << endl;
	//T.print();
}

void DOS::play()
{
	print();
	bool exit = false;
	while (!exit)
	{
		exit = Input();
	}
}

bool DOS::Input()
{
	string command;
	getline(cin, command);
	time_t CurrTime = time(0);
	string opr = command.substr(0, command.find(' '));
	toLower(opr);
	
	if (opr == "attrib")
	{

	}
	else if (opr == "mkdir")
	{
		//T.insert(new Folder(command.substr(6, command.length()), T.getCurrent()->getPath() + "\\" + T.getCurrent()->getName(), T.getCurrent()->getOwner(), T.getCurrent(),false,CurrTime);
	}
	else if (opr == "cd")
	{
		string folderName=
	}
	else if (opr == "cd.")
	{

	}
	else if (opr == "cd..")
	{

	}
	else if (opr == "cd\\")
	{

	}
	else if (opr == "convert")
	{

	}
	else if (opr == "copy")
	{

	}
	else if (opr == "create")
	{
		//File* F = new File(command.substr(7, command.length()), ".txt", T.getCurrent()->getPath() + "\\" + T.getCurrent()->getName(), UserName, T.getCurrent(), 0, 0, 0, CurrTime);
		//T.getCurrent()->insertFile(F);
	}
	else if (opr == "del")
	{

	}
	else if (opr == "dir")
	{

	}
	return true;
}