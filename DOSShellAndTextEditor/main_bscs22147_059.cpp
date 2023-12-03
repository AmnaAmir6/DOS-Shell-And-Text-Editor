#include<iostream>
#include"Folder_bscs22147_059.h"
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<vector>
#include <chrono>   // For std::chrono::seconds
#include <thread>   // F
#include"DOS_bscs22147_059.h"
#include"CurrentFile_bscs22147_059.h"
using namespace std;
int main()
{
    DOS D;
    D.play();
    return 0;
}
struct pos
{
	int ri, ci;
};
struct RectShape
{
	int width; int height;
	int r; int c;
	int clr;
	RectShape(int w, int h, int row, int col, int color)
	{
		width = w, height = h, r = row, c = col, clr = color;
	}
	bool contains(int mp_r, int mp_c)
	{
		if ((mp_r > r && mp_r < r + height) && (mp_c > c && mp_c < c + width))
			return true;
		return false;
	}
	void Draw()
	{
		SetClr(clr);

		for (int ri = r; ri < height + r; ri++)
		{
			for (int ci = c; ci < width + c; ci++)
			{
				gotoRowCol(ri, ci);
				cout << char(-37);
			}
			cout << endl;
		}
	}
	void setclr(int c)
	{
		clr = c;
	}
	pos GetPOsition()
	{
		pos P;
		P.ri = r; P.ci = c;
		return P;
	}
};
int main2()
{

	RectShape R(10, 10, 20, 30, 4);
		pos Ps;
		bool c = false;;
	while(1)
	{
		R.Draw();
		MygetRowColbyLeftClick2(Ps.ri, Ps.ci,c);
		if (R.contains(Ps.ri, Ps.ci))
			break;
	}
	cout << "GootWork";
    return 0;
}

int main44() 
{    
    vector<Folder*>Folds;
    time_t c;
    c = time(0);
    cout<<time(&c);
    return 0;
}

int main123()
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
    /*for (int i = 0; i < 255; i++)
    {
        SetClr(i);
        cout << i << endl;
    }*/    
    return 0;
}