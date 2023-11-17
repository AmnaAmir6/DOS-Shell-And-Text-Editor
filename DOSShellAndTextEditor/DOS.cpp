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
	cout << UserName << "  | 59147  |  DSA\n" << endl;
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
		string FileName = command.substr(opr.length() + 1, command.length());
		if (T.DoesFileExist(FileName))
			T.FindFile(FileName)->print();
		else
			cout << "\nInvalid File Name.No such File exists" << endl;
	}
	else if (opr == "mkdir")
	{
		T.insert(new Folder(command.substr(opr.length() + 1, command.length()), (T.getCurrent()->getPath() + "\\" + T.getCurrent()->getName()), UserName, T.getCurrent(), false, CurrTime));
		cout << "\n     1 directory created successfully\n";
	}
	else if (opr == "cd")
	{
		string FolderName = command.substr(opr.length() + 1, command.length());
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
		File* F = new File(command.substr(opr.length() + 1, command.length()), "txt", T.getCurrent()->getPath() + "\\" + T.getCurrent()->getName(), UserName, T.getCurrent(), 0, 0, 0, CurrTime);
		T.getCurrent()->addFile(F);
		cout << "\n    1 file created successfully\n";

	}
	else if (opr == "del")
	{
		File* F = T.getCurrent()->findFile(command.substr(opr.length() + 1, command.length()));
		if (F)
			T.getCurrent()->removeFile(F);
		else
			cout << "Invalid File Name.No such File exists" << endl;
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
	else if (opr == "copy")
	{

	}
	
	else
	{
		cout << "No such command exists" << endl;
	}

	if (opr != "cls")
	{
		if (prompt)
			T.Print("$");
		else
			T.Print();
	}
	return false;
}

