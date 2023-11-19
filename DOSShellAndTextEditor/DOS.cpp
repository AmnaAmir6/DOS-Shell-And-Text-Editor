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

void DOS::Copy(string cmnd)
{
	string source = cmnd.substr(cmnd.find('\\')+1, cmnd.find(' ')-3);
	string dest = cmnd.substr(cmnd.find(' ')+1+ cmnd.find('\\')+1, cmnd.length());
	vector<string>src_path = Delimeter(source, '\\');
	vector<string>dest_path = Delimeter(dest, '\\');
	string fname = src_path.back(); src_path.pop_back();
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
			{
				Final_dest_Folder->addFile(file);
				cout << "file copied successfully!" << endl;

			}

		}
		else
			cout << "Invalid File Name.No such File exists!" << endl;
	}
	else
		cout << "Invalid source Foulder Name.No such Folder exists!" << endl;

}
void DOS::Move(string cmnd)
{
	string source = cmnd.substr(cmnd.find('\\') + 1, cmnd.find(' ') - 3);
	string dest = cmnd.substr(cmnd.find(' ') + 1 + cmnd.find('\\') + 1, cmnd.length());
	vector<string>src_path = Delimeter(source, '\\');
	vector<string>dest_path = Delimeter(dest, '\\');
	string fname = src_path.back(); src_path.pop_back();
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
			{
				Final_dest_Folder->addFile(file);
				cout << "file moved successfully!" << endl;

			}

		}
		else
			cout << "Invalid File Name.No such File exists!" << endl;
	}
	else
		cout << "Invalid source Folder Name.No such Folder exists!" << endl;

}
void DOS::ConvertExtension(Folder* F, string Extension, string NewExtension)
{
	for (auto itr = F->Folders.begin(); itr != F->Folders.end(); itr++)
	{
		ConvertExtension(*itr, Extension, NewExtension);
	}
	for (auto itr = F->Files.begin(); itr != F->Files.end(); itr++)
	{
		if ((*itr)->FileType == Extension)
			(*itr)->FileType = NewExtension;
	}
}
void DOS::Rename(string cmnd)
{
	string source = cmnd.substr(cmnd.find('\\') + 1, cmnd.find(' ') - 3);
	string new_name = cmnd.substr(cmnd.find(' ') + 1, cmnd.length());
	vector<string>src_path = Delimeter(source, '\\');
	string fname = src_path.back(); src_path.pop_back();
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
			cout << "file renamed successfully!" << endl;

		}
		else cout << "File Not Found!\n";

	}
	else cout << "File Not Found!\n";

}
void DOS::FindFile(Folder* root, string name,bool& found,File* &res)
{
	File* f = root->findFile(name);
	if (f)
	{
		found = true;
		res = f;
		return;
	}

	for (auto i = root->Folders.begin(); i != root->Folders.end(); i++)
	{
		FindFile(*i, name,found,res);
		if (found)  return;
	}
}
File* DOS::FindFile(string name)
{
	bool found = false;
	File* f = {};
	FindFile(T.getRoot(), name, found, f);
	return f;
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
	else if (opr == "ver")
	{
		cout << "\n\tMicrosoft Windows[Version 10.0.19045.3448]" << endl;
	}
	else if (opr == "rename")
	{
		string cmnd = command.substr(opr.length() + 1, command.length());
		Rename(cmnd);
	}
	else if (opr == "convert")
	{
		string Extension = command.substr(opr.length() + 1, command.find(' '));
		string NewExtension = command.substr(Extension.length() + 1, command.length());
		ConvertExtension(T.getCurrent(), Extension, NewExtension);
	}
	else if (opr == "tree")
	{
		T.TreePrint();
	}
	else if (opr == "loadtree")
	{
		T.LoadFromFile();
	}
	else if (opr == "save")
	{
		T.SaveTree();
	}
	else if (opr == "format")
	{
		T.EraseTree();		
	}
	else if (opr == "find")
	{
		string name = command.substr(opr.length() + 1, command.length());
		File* file = FindFile(name);
		if (file)
			cout << "File "<<file->Name<<"."<<file->FileType<< " Found at path " << file->Path << endl;
		else cout << "File not Found!"<<endl;
	}
	else if (opr == "help")
	{

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

