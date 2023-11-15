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
	T.Print();
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
		string FileName = command.substr(3, command.length());
		if (T.DoesFolderExist(FileName))
			T.FindFolder(FileName)->print();
		else
			cout << "\nInvalid File Name.No such File exists" << endl;
	}
	else if (opr == "mkdir")
	{
		T.insert(new Folder(command.substr(6, command.length()), T.getCurrent()->getPath() + "\\" + T.getCurrent()->getName(), UserName, T.getCurrent(), false, CurrTime));
	}
	else if (opr == "cd")
	{
		string FolderName = command.substr(3, command.length());
		if (T.DoesFolderExist(FolderName))
			T.setCurrent(T.FindFolder(FolderName));
		else
			cout << "\nInvalid Directory Name.No such Directory exists" << endl;
	}
	else if (opr == "cd..")
	{
		if (T.getCurrent()->getParent())
			T.setCurrent(T.getCurrent()->getParent());
	}
	else if (opr == "cd\\")
	{
		if (T.getCurrent()->getParent())
			T.setCurrent(T.getRoot());
	}
	else if (opr == "create")
	{
		File* F = new File(command.substr(7, command.length()), "txt", T.getCurrent()->getPath() + "\\" + T.getCurrent()->getName(), UserName, T.getCurrent(), 0, 0, 0, CurrTime);
		T.getCurrent()->addFile(F);
	}
	else if (opr == "del")
	{
		File* F = T.getCurrent()->findFile(command.substr(4, command.length());
		if (F)
			T.getCurrent()->removeFile(F);
		else
			cout << "\nInvalid File Name.No such File exists" << endl;
	}
	else if (opr == "dir" || opr == "cd.")
	{
		T.getCurrent()->print();
	}
	else if (opr == "cls")
	{
		system("cls");
		print();
	}
	else if (opr == "format")
	{
		//T.getCurrent().EmptyFolder();
	}
	else if (opr == "prompt")
	{
		prompt = !prompt;
	}
	else if (opr == "rmdir")
	{
		Folder* CurrentFolder = T.getCurrent();
		T.setCurrent(T.getCurrent()->getParent());
		T.getCurrent()->removeFolder(CurrentFolder);
	}
	else if (opr == "exit")
	{
		return true;
	}
	else if (opr == "convert")
	{

	}
	else if (opr == "copy")
	{

	}
	else
	{
		return false;
	}
}