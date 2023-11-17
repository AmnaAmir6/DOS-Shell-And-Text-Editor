#include "DOS.h"
#include<vector>
#include<ios>
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

void InvertString(string&S)
{
	int si = 0; int ei = S.length() - 1;

	while(si<ei)
	{
		swap(S[si], S[ei]);
		si++; ei--;
	}
}
vector<string>Delimeter(string S,char delim)
{
	vector<string>Res; int si = 0, ei = 0;
	string temp = "";
	for (int i = 0; i < S.length(); i++)
	{
		temp += S[i];
		if (S[i] == delim)
		{
			temp.pop_back();
			Res.push_back(temp);
			temp = "";
		}
	}
	if (temp.length() > 0)
		Res.push_back(temp);
	return Res;
}
void RemoveTillCharFromBack(string& S, char f)
{
	while (!S.empty()&&S.back() != f )
		S.pop_back();
if(!S.empty())
	S.pop_back();
}

void DOS::Copy(string cmnd)
{
	string source = cmnd.substr(0, cmnd.find(' '));
	string dest = cmnd.substr(source.length() + 1, cmnd.length());
	InvertString(source);
	string fname = source.substr(0, source.find('\\'));
	InvertString(fname);
	InvertString(source);
	source = source.substr(source.find('\\')+1, source.length());
	//if (T.getCurrent() != T.getRoot())
	RemoveTillCharFromBack(source, '\\');
	dest = dest.substr(dest.find('\\') + 1, dest.length());
	vector<string>src_path = Delimeter(source, '\\');
	vector<string>dest_path = Delimeter(dest, '\\');
	Folder* Final_src_Folder = T.getRoot();
	Folder* Final_dest_Folder = T.getRoot();
	bool notfound = false;
	for (int i = 0; i < src_path.size(); i++)
	{
		Final_src_Folder = Final_src_Folder->findFolder(src_path[i]);
		if (!Final_src_Folder)
		{
			notfound = true;
			break;
		}
	}
	if (!notfound)
	{
		File* file = Final_src_Folder->findFile(fname);
		if (file)
		{
			for (int i = 0; i < dest_path.size(); i++)
			{
				Final_dest_Folder = Final_dest_Folder->findFolder(dest_path[i]);
				if (!Final_dest_Folder)
				{
					notfound = true;
					break;
				}
			}
			if (notfound)
				cout << "Invalid destination Folder Name.No such Folder exists!" << endl;
			else
				Final_dest_Folder->addFile(file);

		}
		else
			cout << "Invalid File Name.No such File exists!" << endl;
	}
	else
		cout << "Invalid source Foulder Name.No such Folder exists!" << endl;

}
void DOS::Move(string cmnd)
{
	string source = cmnd.substr(0, cmnd.find(' '));
	string dest = cmnd.substr(source.length() + 1, cmnd.length());
	InvertString(source);
	string fname = source.substr(0, source.find('\\'));
	InvertString(fname);
	InvertString(source);
	source = source.substr(source.find('\\')+1, source.length());
	//if (T.getCurrent() != T.getRoot())
	RemoveTillCharFromBack(source, '\\');
	dest = dest.substr(dest.find('\\')+1, dest.length());
	vector<string>src_path = Delimeter(source, '\\');
	vector<string>dest_path = Delimeter(dest, '\\');
	Folder* Final_src_Folder = T.getRoot();
	Folder* Final_dest_Folder = T.getRoot();
	bool notfound = false;
	for (int i = 0; i < src_path.size(); i++)
	{
		Final_src_Folder = Final_src_Folder->findFolder(src_path[i]);
		if (!Final_src_Folder)
		{
			notfound = true;
			break;
		}
	}
	if (!notfound)
	{
		File* file = Final_src_Folder->findFile(fname);
		if (file)
		{
			Final_src_Folder->removeFile(file);
			for (int i = 0; i < dest_path.size(); i++)
			{
				Final_dest_Folder = Final_dest_Folder->findFolder(dest_path[i]);
				if (!Final_dest_Folder)
				{
					notfound = true;
					break;
				}
			}
			if (notfound)
				cout << "Invalid destination Folder Name.No such Folder exists!" << endl;
			else
				Final_dest_Folder->addFile(file);

		}
		else
			cout << "Invalid File Name.No such File exists!" << endl;
	}
	else
		cout << "Invalid source Foulder Name.No such Folder exists!" << endl;

}
void DOS::Rename(string cmnd)
{
	string source = cmnd.substr(0, cmnd.find(' '));
	string new_name = cmnd.substr(source.length() + 1, cmnd.length());
	InvertString(source);
	string fname = source.substr(0, source.find('\\'));
	InvertString(fname);
	InvertString(source);
	source = source.substr(source.find('\\') + 1, source.length());
	//if (T.getCurrent() != T.getRoot())
	RemoveTillCharFromBack(source, '\\');
	vector<string>src_path = Delimeter(source, '\\');
	Folder* Final_src_Folder = T.getRoot();
	bool notfound = false;
	for (int i = 0; i < src_path.size(); i++)
	{
		Final_src_Folder = Final_src_Folder->findFolder(src_path[i]);
		if (!Final_src_Folder)
		{
			notfound = true;
			break;
		}
	}
	if (!notfound)
	{
		File* file = Final_src_Folder->findFile(fname);
		if (file)
		{
			file->setName(new_name);
		}
		else cout << "File Not Found!\n";

	}
	else cout << "File Not Found!\n";

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
		cout << "\n  1 directory created successfully\n";
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
		cout << "\n  1 file created successfully\n";

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
		if (CurrentFolder != T.getRoot())
		{
			T.setCurrent(T.getCurrent()->getParent());
			T.getCurrent()->removeFolder(CurrentFolder);

		}
		else cout << "Can't remove Root directory V\n";
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
		string cmnd = command.substr(opr.length() + 1, command.length());
		Copy(cmnd);
	}
	else if (opr == "move")
	{
		string cmnd = command.substr(opr.length() + 1, command.length());
		Move(cmnd);
	}
	else if (opr == "rename")
	{
		string cmnd = command.substr(opr.length() + 1, command.length());
			Rename(cmnd);
	}
	else
		cout << "No such command exists" << endl;

	if (opr != "cls")
	{
		if (prompt)
			T.Print("$");
		else
			T.Print();
	}
	return false;
}