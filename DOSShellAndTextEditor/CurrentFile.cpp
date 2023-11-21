#include "CurrentFile.h"
#include<iomanip>
#include<conio.h>
#include<string>

CurrentFile::CurrentFile(string FileName)
{
	Curr_col = 0;
	Curr_row = 0;
    Lines l1;   
    text.push_back(l1);
    ri = text.begin();
    ci = (*ri).Line.begin();
    Name = FileName;
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
            auto t = ci;
            if (!(*ri).Line.empty() && ++t!=(*ri).Line.end())
            {               
                auto i = ci;
                list<char>temp(++i, (*ri).Line.end());
                text_line.Line.swap(temp);
                (*ri).Line.erase(i, (*ri).Line.end());            
                Set_Max_and_Count(text_line);
                ri++;
                text.insert(ri, text_line);
                ri--;
                ci = (*ri).Line.begin();
                Curr_col = 0;
                Curr_row++;
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
        else if (key == 19) 
        { // Ctrl + S
            SaveFile();
        }
        else if (key == 15)
        { // Ctrl + O
            LoadFile();
        }
        else if (key == 26)
        { // Ctrl + Z
            DoUndo();
        }
        else if (key == 25)
        { // Ctrl + Y
            DoRedo();
        }
        else if (key == 8) 
        { // Backspace key
            auto t = ci;
            if(ci!=(*ri).Line.begin())
            {
                ci--;
                Curr_col--;
                (*ri).Line.erase(t);           
            }
            else  if (ci == (*ri).Line.begin()&&*ci!=' ')
            {
                *ci = ' ';
                Curr_col--;
                
            }
        }
        else if (key == 27) 
        { // Escape key
            std::cout << "Escape key pressed. Exiting..." << std::endl;
            break;
        }
        else if (key == -32) { // Arrow keys have a two-character sequence, start with 224
            key = _getch(); // Read the second character of the sequence
            switch (key) 
            {
            case 72://up
            {
                if(ri!=text.begin())
                {                   
                    Curr_row--;
                    ri--;
                    ci = (*ri).Line.begin();
                    int i = 0;
                    for (; i < Curr_col&& ci != (*ri).Line.end(); i++)
                    {
                        ci++;
                    }
                    if (ci == (*ri).Line.end())ci--;
                    Curr_col = i;
                }
                break;
            }
            case 80://down
            {
                if (ri != text.end())
                {
                    Curr_row++;
                    ri++;
                    if (ri == text.end())
                    {
                        Curr_row--;
                        ri--;
                    }
                    ci = (*ri).Line.begin();
                    int i = 0;
                    for (; i < Curr_col && ci != (*ri).Line.end(); i++)
                    {
                        ci++;
                    }
                    if (ci == (*ri).Line.end())ci--;

                    Curr_col = i;
                }
                break;
            }
            case 75://left
            {
                if(ci!=(*ri).Line.begin())
                {
                    Curr_col--;
                    ci--;
                }
                break;
            }
            case 77://right
            {
                auto t = ci;
                t++;
                if (t!=(*ri).Line.end())
                {
                    Curr_col++;
                    ci++;
                }
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
            {   
                //(*ri).Line.push_back(key);    //this inserts value at the end of line always independent of where the cursor is
                //ci++;

                auto temp = ci;
                ci++;
                (*ri).Line.insert(ci, key);
                ci = ++temp;
            }
            Curr_col++;     
            SaveState();
        }
        Print();
    }


}

void CurrentFile::SaveFile()
{
    ofstream wtr(Name);
    wtr << Curr_row << " " << Curr_col << endl;
    for (auto row = text.begin(); row != text.end(); row++)
    {
        for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
        {
            wtr << (*col);
        }
        wtr << endl;
    }
}

void CurrentFile::LoadFile()
{
    ifstream rdr(Name);
    string CursorIndex;

    getline(rdr, CursorIndex);

    Curr_row = stoi(CursorIndex.substr(0, CursorIndex.find(' ')));
    Curr_col = stoi(CursorIndex.substr(CursorIndex.find(' ') + 1, CursorIndex.length()));
    char ch;
    while (rdr >> ch)
    {
        if (ch != '\n')
        {
            if ((*ri).Line.size() == 1 && (*ci) == ' ')
            {
                *ci = ch;
            }
            else
            {
                (*ri).Line.push_back(ch);
                ci++;
            }
        }
        else
        {
            /*Lines text_line;
            text.push_back(text_line);*/
            text.push_back(Lines());
            ri++;
        }
    }
    int cri = 0, cci = 0;
    for (auto row = text.begin();row != text.end(); row++, cri++)
    {
        if (cri == Curr_row)
        {
            ri = row;
            break;
        }
    }
    for (auto col = (*ri).Line.begin(); col != (*ri).Line.end(); col++, cci++)
    {
        if (cci == Curr_col)
        {
            ci = col;
            break;
        }
    }
}
void CurrentFile::SaveState()
{
    FileState S(*this);
    if (Undo.size() > 5)
        Undo.erase(Undo.begin());
    Undo.push_back(S);
}
void CurrentFile::LoadState(const FileState& S)
{
    text = S.text;
    Curr_row = S.CRow;
    Curr_col = S.CCol;
    ri = S.RowIndex;
    ci = S.ColIndex;
    
}
void CurrentFile::DoUndo()
{
    if (!Undo.empty())
    {
        FileState CState(*this);
        Redo.push(CState);
        auto S = Undo.back();
        LoadState(S);
        Undo.pop_back();//this is deleting the object S
    }
}
void CurrentFile::DoRedo()
{
    if (!Redo.empty())
    {
        auto S = Redo.top();
        Undo.push_back(S);
        Redo.pop();
        LoadState(S);
    }
}


