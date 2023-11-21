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
    ci = (*ri).Line.begin();
}
void CurrentFile::Set_Max_and_Count(Lines& L)
{

    if (L.Line.empty())
    {
        L.SetWord_Count(0);
        L.SetLongestWordLength(0);
        return;
    }

    if (L.Line.size() == 1 )
    {
        if ((*L.Line.begin()) != ' ')
        {
            L.SetWord_Count(1);
            return;
        }
        L.SetWord_Count(0);
        return;
    }
    int word_count = 0;
    auto i = L.Line.begin();
    auto prev = L.Line.begin();
    i++;
    for (; i != L.Line.end(); i++,prev++)
    {
        if (*prev!=' ' && *i == ' ')
            word_count++;
    }
    int max_length = 0;
    int length = 0;
    for (auto i = L.Line.begin(); i != L.Line.end(); i++)
    {
        if (i != L.Line.begin() && *i == ' ')
        {
            if (length > max_length)
                max_length = length;
            length = 0;
            i++;
        }    
        length++;
    } 
    if (length > max_length)max_length = length;
    L.SetLongestWordLength(max_length);
    L.SetWord_Count(word_count);
}
void CurrentFile::Print()
{
    SetClr(255);
    system("cls");
    int ri = 0;
    for (auto i = text.begin(); i != text.end(); i++,ri++)
    {
        (*i).PrintLine(ri);
    }
    gotoRowCol(Curr_row, Curr_col);
}


void CurrentFile::Insert()
{

	SetClr(255);
    system("cls");
	char key = {};
    while (true) 
    {
      
        key = _getch(); 
        if (key == 13)//enter key
        {
            Lines text_line;
            if (!(*ri).Line.empty() && ci != (*ri).Line.end())
            {               
                auto i = ci;
                list<char>temp(++i, (*ri).Line.end());
                text_line.Line.swap(temp);
                (*ri).Line.erase(i, (*ri).Line.end());
            
                Set_Max_and_Count(text_line);
                ri++;
                text.insert(ri, text_line);
                Curr_col = 0;
                Curr_row++;
                gotoRowCol(Curr_row, Curr_col);
            }
            else
            {
                text.push_back(text_line);
                ri++;
                Curr_col = 0;
                Curr_row++;
                ci = text.back().Line.begin();
            }
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
                ci = (*ri).Line.begin();

                break;
            }
            case 80://down
            {
                Curr_col = 0;
                Curr_row++;
                ri++;
                ci = (*ri).Line.begin();
                break;
            }
            case 75://left
            {
                Curr_col--;
                ci--;

                break;
            }
            case 77://right
            {
                Curr_col++;
                ci++;

                break;
            }
            default:
                std::cout << "Unknown arrow key pressed." << std::endl;
            }
        }
        else 
        {
            if ((*ri).Line.size() == 1 && (*ci) == ' ')
            {
                *ci = key;
            }
            else
            {    (*ri).Line.push_back(key);           
                ci++;
            }
            Curr_col++;           
        }
        Print();
    }


}