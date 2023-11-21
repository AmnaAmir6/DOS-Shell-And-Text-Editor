#include "CurrentFile.h"
#include<iomanip>
#include<conio.h>
CurrentFile::CurrentFile()
{
	Curr_col = 0;
	Curr_row = 0;
    Lines l1;
   
    text.push_back(l1);
    ri = text.begin();

}


void CurrentFile::Insert()
{

	SetClr(255);
    system("cls");
	char key = {};
    while (true) 
    {
      
        key = _getch(); 
        if (key == 13)
        {
            Lines line;
            text.push_back(line);
            ri++;
            Curr_col = 0;
            Curr_row++;
            ci= text.back().GetBegin();
        }
            
        else if (key == 8) 
        { // Backspace key
            Curr_col--;
            (*ri).Line.remove(*ci);
            ci--;

        }
        else if (key == 27) 
        { // Escape key
            std::cout << "Escape key pressed. Exiting..." << std::endl;
            break;
        }
        else if (key == -32) { // Arrow keys have a two-character sequence, start with 224
            key = _getch(); // Read the second character of the sequence
            switch (key) {
            case 72://up
            {
                Curr_col = 0;
                Curr_row--;
                ri--;
                ci = (*ri).GetBegin();
                gotoRowCol(Curr_row, Curr_col);

                break;
            }
            case 80://down
            {
                Curr_col = 0;
                Curr_row++;
                ri++;
                ci = (*ri).GetBegin();
                gotoRowCol(Curr_row, Curr_col);
                break;
            }
            case 75://left
            {
                Curr_col--;
                ci--;
                gotoRowCol(Curr_row, Curr_col);

                break;
            }
            case 77://right
            {
                Curr_col++;
                ci++;
                gotoRowCol(Curr_row, Curr_col);

                break;
            }
            default:
                std::cout << "Unknown arrow key pressed." << std::endl;
            }
        }
        else 
        {
            (*ri).Line.push_back(key);
            ci= (*ri).Line.end();
            ci--;
            Curr_col++;
            gotoRowCol(Curr_row, Curr_col);
            SetClr(250);
            cout << key;
        }

    }


}