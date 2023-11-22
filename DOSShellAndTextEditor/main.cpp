#include<iostream>
#include"Folder.h"
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<vector>
#include <chrono>   // For std::chrono::seconds
#include <thread>   // F
#include"DOS.h"
#include"CurrentFile.h"
using namespace std;
int mwain()
{
    DOS D;
    D.play();
    return 0;
}

int main44() {
    
    vector<Folder*>Folds;
    time_t c;
    c = time(0);

    cout<<time(&c);

    
    
    return 0;
}

int main()
{
    /*char ch;
    	while (true)
    	{
    
    		if (_kbhit())
    		{
    
    			ch = _getch();
    			{
    				cout << ch << "  Asci  " << int(ch)<<endl;
    			}
    		}
    	}*/
    CurrentFile* file= new CurrentFile("file1.txt");
    file->Insert();
    return 0;
}