#include"utility_bscs22147_059.h"
#include "CurrentFile_bscs22147_059.h"
#include"Lines_bscs22147_059.h"
#include<iomanip>
#include<conio.h>
#include<string>
#include<stack>

CurrentFile::CurrentFile(string FileName)
{
	Curr_col = 0;
	Curr_row = 0;
    Lines l1;   
    text.push_back(l1);
    ri = text.begin();
    ci = (*ri).Line.begin();
    Name = FileName;
    max_col_length = 20;//
    finding = false;
    replacing = false;
    SearchBox = new RectShape(25,2,4,120,0);
}
void CurrentFile::Set_Max_and_Count(Lines& L)
{

    if (L.Line.size()==1&&L.Line.front()==' ')
    {
        L.SetWord_Count(0);
        L.SetLongestWordLength(0);
        return;
    }
    int word_count = 0;
    auto prev = L.Line.begin();
    bool word_started = false;
    auto i = L.Line.begin();
    for (; i != L.Line.end(); i++,prev++)
    {
        if (*i != ' ' && !word_started)
        {
            word_count++;
            word_started = true;
        }
        else if(*i==' ')
            word_started = false;
    }
    int max_length = 0;
    int min_length = 0;
    int length = 0;
    int sum_of_lengths=0;
    for (auto i = L.Line.begin(); i != L.Line.end(); i++)
    {
        if (i != L.Line.begin() && *i == ' ')
        {
            if (length > max_length)
                max_length = length;
             if (length < min_length)
                min_length = length;
            else if (min_length == 0 && length > 0)
                min_length = length;
             sum_of_lengths += length;
            length = 0;
            i++;
            if (i == L.Line.end())break;
        }    
        length++;
    } 
    if (length > 0)
        sum_of_lengths += length;
    if (length > max_length)max_length = length;
    if (max_length > 0 && min_length == 0)min_length = max_length;
    else if (length < min_length&&length>0)min_length = length;
    L.SetLongestWordLength(max_length);
    L.SetWord_Count(word_count);
    L.SetMinWordLength(min_length);
    L.SetSumOfLengths(sum_of_lengths);
}
void CurrentFile::ToUpperOrLower(string cast)
{
    
     auto temp_ci = ci;
     auto temp_ri = ri;
     auto si = ci;
    int cr = Curr_col;
    while (*ci != ' ')
    {
        if (cast == "upper")
        *ci = toupper(static_cast<unsigned char>(*ci));
        else if(cast=="lower")
            *ci = tolower(static_cast<unsigned char>(*ci));

        ci++;
        if (ci == (*ri).Line.end())
        {
            ri++;
            if (ri == text.end())break;
            si = (*ri).Line.begin();
        }
    }
    ci = temp_ci;
    ri = temp_ri;
    while (*ci != ' ')
    {
        if (cast == "upper")
            *ci = toupper(static_cast<unsigned char>(*ci));
        else if (cast == "lower")
            *ci = tolower(static_cast<unsigned char>(*ci));

        if (ci == (*ri).Line.begin() && ri != text.begin())
        {
            ri--;
            ci = (*ri).Line.end();
            ci--;
        }
        else if (ci == (*ri).Line.begin() && ri == text.begin())
        {
            break;
        }
        else ci--;
    }

    ci = temp_ci; ri = temp_ri;



}
void CurrentFile::FindWords(string name)
{
    int i = 1; auto start = (*text.begin()).Line.begin();
    auto st_line = text.begin();
    auto end_line = text.begin();
    auto end = start; bool started = false; bool completed = false;
    string temp = "";
    Word W;
    for (auto ri = text.begin(); ri != text.end(); ri++)
    {
        for (auto ci = (*ri).Line.begin(); ci != (*ri).Line.end(); ci++)
        {
            if (*ci == name[0]&&!started)
            {
                temp += *ci;
                start = ci;
                st_line = ri;
                if(name!=temp)
                started = true;
                else
                {
                    end = ci;
                    end_line = ri;
                    W.start = start;
                    W.end = end;
                    W.starting_Line = st_line;
                    W.ending_Line = end_line;
                    SelectedWords.push(W);
                    temp = "";
                    started = false;
                }
                continue;
            }
            if (*ci != name[i])
            {  
                started = false; completed = false;
                temp = "";
                i = 1;
            }
            if (started)
            {
                temp += *ci;
                i++;
                if (temp.length() == name.length())
                {
                    if (temp == name)
                    {
                        end = ci;
                        end_line = ri;
                        W.start = start;
                        W.end = end;
                        W.starting_Line = st_line;
                        W.ending_Line = end_line;
                        SelectedWords.push(W);    
                    }
                    started = false;
                    temp = "";
                    i = 1;
                }                
            }
            
        }
    }

}
void CurrentFile::Rearrange()
{
    auto tr_prev = ri;
    auto tr_forw = ri;
    tr_forw++;
    while (tr_forw != text.end())
    {
        auto b = (*tr_prev).Line.back();
        (*tr_forw).Line.push_front(b); Set_Max_and_Count(*tr_forw);
        (*tr_prev).Line.pop_back();    Set_Max_and_Count(*tr_prev);
        if (((*tr_forw).Line.size() <= max_col_length) || tr_forw == text.end())
            break;
        tr_prev = tr_forw;
        tr_forw++;
    }
    //ri = tr_forw;
  //  ci = (*ri).Line.begin();
    if (tr_forw == text.end())
    {
        Lines temp_l;
        text.insert(tr_forw, temp_l);
        tr_forw--;
        auto i = (*tr_prev).Line.back();
        (*tr_prev).Line.pop_back();
        *(*tr_forw).Line.begin() = i;
        Set_Max_and_Count(*tr_forw);
        Set_Max_and_Count(*tr_prev);
    }
    if (Curr_col >= max_col_length)
    {
        Curr_row++;
        ri++;
        Curr_col = 1;
        ci = (*ri).Line.begin();

    }
    else Curr_col++;

}
void CurrentFile::FindFirstAppearance(string name)
{
    int i = 1; auto start = (*text.begin()).Line.begin();
    auto st_line = text.begin();
    auto end_line = text.begin();
    auto end = start; bool started = false; bool completed = false;
    string temp = "";
    Word W;
    for (auto ri = text.begin(); ri != text.end(); ri++)
    {
        for (auto ci = (*ri).Line.begin(); ci != (*ri).Line.end(); ci++)
        {
            if (*ci == name[0] && !started)
            {
                temp += *ci;
                start = ci;
                st_line = ri;
                if (name != temp)
                    started = true;
                else
                {
                    end = ci;
                    end_line = ri;
                    W.start = start;
                    W.end = end;
                    W.starting_Line = st_line;
                    W.ending_Line = end_line;
                    SelectedWords.push(W);
                    return;
                }
                continue;
            }
            if (*ci != name[i])
            {
                started = false; completed = false;
                temp = "";
                i = 1;
            }
            if (started)
            {
                temp += *ci;
                i++;
                if (temp.length() == name.length())
                {
                    if (temp == name)
                    {
                        end = ci;
                        end_line = ri;
                        W.start = start;
                        W.end = end;
                        W.starting_Line = st_line;
                        W.ending_Line = end_line;
                        SelectedWords.push(W);
                        return;
                    }
                    started = false;
                    temp = "";
                    i = 1;
                }
            }

        }
    }

}
void CurrentFile::Print()
{
    SetClr(255);
    system("cls");


    int ri = 0;
    for (auto i = text.begin(); i != text.end(); i++,ri++)
    {
        //if(i==this->ri)
        (*i).PrintLine(ri);
        //cout<<"max "<<(*i).GetLongestWordLength() << " WC " << (*i).GetWord_Count()<<" min "<<(*i).GetMinWordLength()<< endl;
    }
    SearchBox->Draw();
    SetClr(240);
    gotoRowCol(1, 120);   
    cout << "AVERAGE WORD LENGTH : " << GetAvgWordLength();
    gotoRowCol(2, 120);   
    cout << "ParaGrapgh Count : " << GetParagraphCount();
    gotoRowCol(SearchBox->GetPOsition().ri + 2, SearchBox->GetPOsition().ci + 3);
    SetClr(240);
    cout << " ( press TAB+F )";

    gotoRowCol(Curr_row, Curr_col);

}
//void CurrentFile::HighlightWords()
//{
//    SetClr(255);
//    system("cls");
//    int ri = 0; int ci = 0;
//    Word W = SelectedWords.front();
//    SelectedWords.pop();
//    bool lineFound = false;
//    bool started = false;
//    for (auto i = text.begin(); i != text.end(); i++, ri++)
//    {
//        if(W.starting_Line==W.ending_Line)
//        { 
//            if (W.starting_Line == i)
//                lineFound = true;
//        }
//        for (auto c = (*i).Line.begin(); c != (*i).Line.end(); c++,ci++)
//        {
//            if (lineFound && W.start == c&&!started)
//                started = true;
//            if (started)
//                SetClr(4);
//            else
//            SetClr(240);
//            if (c == W.end)
//            {
//                started = false;
//                if(!SelectedWords.empty())
//                {
//                    W = SelectedWords.front();
//                    SelectedWords.pop();
//                }
//            }
//
//            gotoRowCol(ri, ci);
//            cout << *c;
//        }
//    }
//    SearchBox->Draw();
//    SetClr(240);
//    gotoRowCol(1, 120);
//    cout << "AVERAGE WORD LENGTH : " << GetAvgWordLength();
//    gotoRowCol(2, 120);
//    cout << "ParaGrapgh Count : " << GetParagraphCount();
//    gotoRowCol(Curr_row, Curr_col);
//}
void CurrentFile::HighlightWords(string name,bool changes_made)
{
    SetClr(255);
    system("cls");
    int ri = 0;
    Word W;
    bool started = false;
    bool selected = false;
    
    for (auto i = text.begin(); i != text.end(); i++, ri++)
    {
        int ci = 0;
        for (auto c = (*i).Line.begin(); c != (*i).Line.end(); c++, ci++)
        {

            if (!selected)
            {
                if (!SelectedWords.empty())
                {
                    W = SelectedWords.front();
                    SelectedWords.pop();
                    selected = true;
                }
            }

            if (selected && i==W.starting_Line&&c == W.start)
                started = true;
            if (selected&& started&&i==W.ending_Line && c == W.end)
            {
                SetClr(176);
                gotoRowCol(ri, ci);
                cout << *c;
                started = false;
                selected = false;
                SetClr(240);
                continue;
            }
            if (started)
                SetClr(176);
            else
                SetClr(240);
            gotoRowCol(ri, ci);
            cout << *c;
        }
    }
    SearchBox->Draw();
    SetClr(240);
    gotoRowCol(1, 120);
    cout << "AVERAGE WORD LENGTH : " << GetAvgWordLength();
    gotoRowCol(2, 120);
    cout << "ParaGrapgh Count : " << GetParagraphCount();       
        pos P;
        P = SearchBox->GetPOsition();
    if(changes_made)
    {
        gotoRowCol(P.ri + 3, P.ci + 2);
        cout << "No changes were made!";
    }
    gotoRowCol(P.ri, P.ci);
    SetClr(15);
    cout << name;
    SetClr(240);
    gotoRowCol(Curr_row, Curr_col);
}
float  CurrentFile::GetAvgWordLength()
{
    float  Word_count = 0;
    float  total_length = 0;
    for (auto i = text.begin(); i != text.end(); i++)
    {
        Word_count += (*i).GetWord_Count();
        total_length += (*i).GetSumOfLengths();
    }
    return total_length / Word_count;
}
int CurrentFile::GetParagraphCount()
{
    int para_count = 0;
    for (auto i = text.begin(); i != text.end(); i++)
    {
        if (((*i).Line.size() > 1 && (*i).Line.size() < max_col_length))
        {
            para_count++;
        }
        else if (((*i).Line.size() > 1 && (*i).Line.size() == max_col_length))
        {
            auto t = i; t++;
            if (t == text.end())para_count++;
        }
        else if ((*i).Line.size() == 1 && (*i).Line.front() != ' ')para_count++;
    }
    return para_count;
}
void CurrentFile::Insert()
{
	SetClr(255);
    system("cls");
	char key = {};
    Print();
    while (true) 
    {
        /*
        int rpos; int cpos;
        MygetRowColbyLeftClick2(rpos, cpos);
        if (SearchBox->contains(rpos, cpos))
            SearchBox->setclr(15);*/
        key = _getch(); 
        if(!replacing)
        {
            finding = false;
        }

        if (key == 13)//enter key
        {
            Lines text_line;
            auto t = ci;
            if (!(*ri).Line.empty() && ++t!=(*ri).Line.end()&&Curr_col>0)
            {               
                auto i = ci;
                list<char>temp(++i, (*ri).Line.end());
                text_line.Line.swap(temp);
                (*ri).Line.erase(i, (*ri).Line.end());                            
                Set_Max_and_Count(*ri);
                Set_Max_and_Count(text_line);
                ri++;
                text.insert(ri, text_line);
                ri--;
                ci = (*ri).Line.begin();
                Curr_col = 0;
                Curr_row++;
            }
            else if (!(*ri).Line.empty() && Curr_col == 0)
            {
                text.insert(ri,text_line);
                Curr_row++;
                //ci = text.back().Line.begin();
            }
            else
            {
                ri++;
                text.insert(ri,text_line);
                ri--;
                Curr_col = 0;
                Curr_row++;
                ci = (*ri).Line.begin();
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
            continue;
        }
        else if (key == 25)
        { // Ctrl + Y
            DoRedo();
        }
        else if (key == 21)
        {//Ctrl+U
            
            ToUpperOrLower("upper");

        }
        else if (key == 12)
        {//Ctrl+L

            ToUpperOrLower("lower");

        }
        else if (key == 9)
        {//tab
            char c = _getch();
            
            if (c == 114)//tab+r to findandReplace
            {
                pos P; string fname; string word;
                P = SearchBox->GetPOsition();
                gotoRowCol(P.ri, P.ci + 1);
                SetClr(15);
                getline(cin, word);
                finding = true;
                replacing = true;
                FindWords(word);
                HighlightWords(word);
                SearchBox->Draw();
                gotoRowCol(P.ri, P.ci + 1);
                SetClr(15);
                getline(cin, fname);
                replacing = false;
                FindWords(word);
                FindandReplace(word, fname);
                FindWords(fname);
                HighlightWords(fname);
                //AddPrefixtoWord("moqeet", fname);
            }
            
            if (c == 102)//tab+f to find
            {
                pos P; string fname;
                P = SearchBox->GetPOsition();
                gotoRowCol(P.ri, P.ci + 1);
                SetClr(15);
                getline(cin, fname);
                FindWords(fname);
                if (!SelectedWords.empty())
                    finding = true;
                HighlightWords(fname);

            }
            if (c == 112)//tab+p to addprefix
            {
                pos P; string fname;
                P = SearchBox->GetPOsition();
                gotoRowCol(P.ri, P.ci + 1);
                
                SetClr(15);
                getline(cin, fname);
                finding = true;
                AddPrefixtoWord("moqeet", fname);
            }
            if (c == 115)//tab+s to addpostfix
            {
                pos P; string fname;
                P = SearchBox->GetPOsition();
                gotoRowCol(P.ri, P.ci + 1);
                SetClr(15);
                getline(cin, fname);
                finding = true;
                AddPostfixtoWord("abdul", fname);
                
            }
        }
        else if (key == 8) 
        {
            // Backspace key
            if (Curr_col == 0&&ri!=text.begin())
            {               
                auto t = ri;
                ri--;
                ci = (*ri).Line.end(); ci--;
                Curr_col = (*ri).Line.size() ;
                if (Curr_col < 0)Curr_col = 0;
                Curr_row--;
                if ((*t).Line.size()==1&&(*t).Line.front()==' ')
                {
                    text.erase(t);
                }
                
            }
            auto t = ci;
            if (Curr_col > 0 && ci == (*ri).Line.begin())
            {
                Curr_col--;           
                if ((*ri).Line.size() == 1)
                    *ci = ' ';
                else
                {
                    ci++;
                    (*ri).Line.pop_front();
                }
            }
            else if (Curr_col > 0)
            {
                ci--;
                Curr_col--;
                (*ri).Line.erase(t);
            }       
            Set_Max_and_Count(*ri);
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
                    if(ci!=(*ri).Line.begin())
                    ci--;
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
                    if (ci != (*ri).Line.begin()&&Curr_col!=0)
                    ci--;
                    Curr_col = i;
                }
                break;
            }
            case 75://left
            {
                if (Curr_col == 0&&ri!=text.begin())
                {
                    ri--;
                    ci = (*ri).Line.end();
                    ci--;
                    Curr_row--;
                    Curr_col = (*ri).Line.size();
                    break;
                }
                if(ci!=(*ri).Line.begin())
                {
                    Curr_col--;
                    ci--;
                }                
                else
                {
                    Curr_col = 0;
                }
                break;
            }
            case 77://right
            {
                auto tri = ri; tri++;
                if (Curr_col==(*ri).Line.size() && tri != text.end())
                {
                    ri++;
                    ci = (*ri).Line.begin();
                    Curr_row++;
                    Curr_col =0;
                    break;
                }
                
                if (Curr_col == 0&&ci==(*ri).Line.begin())
                    Curr_col++;
                else
                {
                    auto t = ci;
                    t++;
                    if (t != (*ri).Line.end())
                    {
                        Curr_col++;
                        ci++;
                    }
                }
                break;
            }
            default:
                std::cout << "Unknown arrow key pressed." << std::endl;
            }
        }
        else 
        {
                if ((*ri).Line.size() == 1 && (*ci) == ' '&&Curr_col==0)
                {
                    *ci = key;
                    (*ri).SetWord_Count(1);
                    (*ri).SetLongestWordLength(1);
                }
                else if (!(*ri).Line.empty() && Curr_col == 0)
                {
                    (*ri).Line.insert(ci, key);
                    ci--;
                }
                else
                {
                    ci++;
                    (*ri).Line.insert(ci, key);
                    ci--;
                }

                Set_Max_and_Count(*ri);
                //insert an element and then check if the 
                // line size has exceeded the 
                // limit and shift last character to the 
                // start of next line ok DASH ITU
                if ((*ri).Line.size() > max_col_length)
                {
                    Rearrange();
                }
                else Curr_col++;
                
        }
        if(!finding)
        {
            Print();
        }
}
}
void CurrentFile::RearrangeAll()
{
    for (auto row = text.begin(); row != text.end(); row++)
    {
        for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
        {
            if ((*row).Line.size() > max_col_length)
            {
                auto CurrRow = row;
                auto NextRow = row;
                NextRow++;
                while (NextRow != text.end())
                {

                    while ((*CurrRow).Line.size() > max_col_length)
                    {
                        char ch = (*CurrRow).Line.back();
                        (*CurrRow).Line.pop_back();
                        (*NextRow).Line.push_front(ch);
                    }
                    if ((*NextRow).Line.size() <= max_col_length)
                        break;
                    CurrRow = NextRow;
                    NextRow++;
                }
                if (NextRow == text.end())
                {
                    Lines L;
                    text.insert(NextRow, L);
                    NextRow--;
                    while ((*CurrRow).Line.size() > max_col_length)
                    {
                        char ch = (*CurrRow).Line.back();
                        (*CurrRow).Line.pop_back();
                        (*NextRow).Line.push_front(ch);
                    }
                }

            }

        }
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
//void CurrentFile::LoadFile()
//{
//    ifstream rdr(Name);
//    string CursorIndex;
//
//    getline(rdr, CursorIndex);
//
//    Curr_row = stoi(CursorIndex.substr(0, CursorIndex.find(' ')));
//    Curr_col = stoi(CursorIndex.substr(CursorIndex.find(' ') + 1, CursorIndex.length()));
//    char ch;
//    while (rdr >> ch)
//    {
//        if (ch != '\n')
//        {
//            if ((*ri).Line.size() == 1 && (*ci) == ' ')
//            {
//                *ci = ch;
//            }
//            else
//            {
//                (*ri).Line.push_back(ch);
//                ci++;
//            }
//        }
//        else
//        {
//            /*Lines text_line;
//            text.push_back(text_line);*/
//            text.push_back(Lines());
//            ri++;
//        }
//    }
//
//    int cri = 0, cci = 0;
//    for (auto row = text.begin();row != text.end(); row++, cri++)
//    {
//        if (cri == Curr_row)
//        {
//            ri = row;
//            break;
//        }
//    }
//    for (auto col = (*ri).Line.begin(); col != (*ri).Line.end(); col++, cci++)
//    {
//        if (cci == Curr_col)
//        {
//            ci = col;
//            break;
//        }
//    }
//}
void CurrentFile::LoadFile()
{
    ifstream rdr(Name);
    string CursorIndex;

    getline(rdr, CursorIndex);

    Curr_row = stoi(CursorIndex.substr(0, CursorIndex.find(' ')));
    Curr_col = stoi(CursorIndex.substr(CursorIndex.find(' ') + 1, CursorIndex.length()));

    string LineText;
    while (getline(rdr, LineText))
    {
        for (int i = 0; i < LineText.length(); i++)
        {
            if ((*ri).Line.size() == 1 && (*ci) == ' ')
            {
                *ci = LineText[i];
            }
            else
            {
                (*ri).Line.push_back(LineText[i]);
                ci++;
            }
        }
        text.push_back(Lines());
        ri++;
        ci = (*ri).Line.begin();
    }

    int cri = 0, cci = 0;
    for (auto row = text.begin(); row != text.end(); row++, cri++)
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
    //FileState S(*this);
    FileState* S = new FileState(*this);
    if (Undo.size() > 5)
        Undo.erase(Undo.begin());
    Undo.push_back(*S);
}
void CurrentFile::LoadState(const FileState& S)
{
    text = S.text;
    Curr_row = S.CRow;
    Curr_col = S.CCol;
    ri = S.RowIndex;
    ci = S.ColIndex;
    
}
//void CurrentFile::DoUndo()
//{
//    if (!Undo.empty())
//    {
//        FileState CState(*this);
//        Redo.push(CState);
//        auto S = Undo.back();
//        LoadState(S);
//        Undo.pop_back();//this is deleting the object S
//    }
//}
void CurrentFile::DoUndo()
{
    if (!Undo.empty())
    {
        FileState *CState= new FileState(*this);
        Redo.push(*CState);
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
//void CurrentFile::AddPrefixtoWord(string word, string Prefix)
//{
//    Word W;
//    bool selected = false;
//    bool started = false;
//    for (auto row = text.begin(); row != text.end(); row++)
//    {
//        for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
//        {
//            if (!selected)
//            {
//                if (!SelectedWords.empty())
//                {
//                    W = SelectedWords.front();
//                    SelectedWords.pop();
//                    selected = true;
//                }
//            }
//            if (selected && row == W.starting_Line && col == W.start)
//            {
//                for(int i=0;i<Prefix.length();i++)
//                {
//                    (*row).Line.insert(col, Prefix[i]);
//                    //col++;
//                }
//           
//                started = false;
//                selected = false;
//                continue;
//            }
//        }
//    }
//    string NewWord = Prefix + word;
//    FindWords(NewWord);
//    HighlightWords(NewWord);
//    /*FindWords(word);
//    HighlightWords(word);*/
//}
void CurrentFile::AddPrefixtoWord(string word, string Prefix)
{
    if (word.back() != ' ')word.push_back(' ');
    if (word[0] != ' ')word.insert(word.begin(), ' ');
    Word W;
    bool selected = false;
    bool started = false;
    bool done = false;
    bool changes_made = false;
    auto st = (*text.begin()).Line.begin();
    if (*st != ' ')
        (*text.begin()).Line.insert(st,' ');
    auto r_end = text.end(); r_end--;
    auto c_end = ((*r_end).Line.end());
    c_end--;
    if (*c_end != ' ')
    {
        c_end++;
        (*r_end).Line.insert(c_end, ' ');
        if ((*r_end).Line.size() > max_col_length)
        {
            text.push_back(Lines());
            auto b = (*r_end).Line.back();
            (*r_end).Line.pop_back();
            r_end++;
            (*r_end).Line.push_back(b);
        }
    }
        FindFirstAppearance(word);
        if (SelectedWords.empty())
            changes_made = true;

    for (auto row = text.begin(); row != text.end(); row++)
    {
        if (done)break;
        for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
        {
            if (!selected)
            { 
                if (!SelectedWords.empty())
                {
                    W=SelectedWords.front();
                    SelectedWords.pop();
                    selected = true;
                }
            }
            if (selected  && row == W.starting_Line && col == W.start)
            {
                auto temp = col;
                temp++;
                for (int i = 0; i < Prefix.length(); i++)
                {
                 
                    (*row).Line.insert(temp, Prefix[i]);
                    //col++;
                }
                if ((*row).Line.size() > max_col_length)
                {
                    auto CurrRow = row;                    
                    auto NextRow = row;
                    NextRow++;
                    while (NextRow!= text.end())
                    {

                        while ((*CurrRow).Line.size() > max_col_length)
                        {
                            char ch = (*CurrRow).Line.back();
                            (*CurrRow).Line.pop_back();
                            (*NextRow).Line.push_front(ch);
                        }                   
                        if ((*NextRow).Line.size() <= max_col_length)
                            break;
                        CurrRow = NextRow;
                        NextRow++;
                    }
                    if (NextRow == text.end())
                    {
                            Lines L;
                            text.insert(NextRow,L);
                            NextRow--;
                            while ((*CurrRow).Line.size() > max_col_length)
                            {
                                char ch = (*CurrRow).Line.back();
                                (*CurrRow).Line.pop_back();
                                (*NextRow).Line.push_front(ch);
                            }                    
                    }

                }
                started = false;
                selected = false;
                FindFirstAppearance(word);
                if (SelectedWords.empty())
                {
                    done = true;
                    break;
                }
                //continue;
            }
        }
    }
    if ((*text.begin()).Line.front() == ' ' && (*text.begin()).Line.size() > 1)
        (*text.begin()).Line.pop_front();
    Curr_col = (*ri).Line.size();
    ci = (*ri).Line.end();
    if (ci != (*ri).Line.begin())
    ci--;
    word.erase(word.begin());
    string NewWord = Prefix + word;
    FindWords(NewWord);
    HighlightWords(NewWord,changes_made);
    /*FindWords(word);
    HighlightWords(word);*/
}
void CurrentFile::AddPostfixtoWord(string word, string Postfix)
{
    if (word.back() != ' ')word.push_back(' ');
    if (word[0] != ' ')word.insert(word.begin(), ' ');
    Word W;
    bool selected = false;
    bool started = false;
    bool done = false;
    bool changes_made = false;
    auto st = (*text.begin()).Line.begin();
    if (*st != ' ')
        (*text.begin()).Line.insert(st, ' ');
    auto r_end = text.end(); r_end--;
    auto c_end = ((*r_end).Line.end());
    c_end--;
    if (*c_end != ' ')
    {
        c_end++;
        (*r_end).Line.insert(c_end, ' ');
        if ((*r_end).Line.size() > max_col_length)
        {
            text.push_back(Lines());
            auto b = (*r_end).Line.back();
            (*r_end).Line.pop_back();
            r_end++;
            (*r_end).Line.push_back(b);
        }
    }
    FindFirstAppearance(word);
    if (SelectedWords.empty())
    {
        changes_made = true;
    }
    for (auto row = text.begin(); row != text.end(); row++)
    {
        if (done)break;
        for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
        {
            if (!selected)
            {
                if (!SelectedWords.empty())
                {
                    W = SelectedWords.front();
                    SelectedWords.pop();
                    selected = true;
                }
            }
            if (selected && row == W.ending_Line && col == W.end)
            {
                
                for (int i = 0; i < Postfix.length(); i++)
                {

                    (*row).Line.insert(col, Postfix[i]);
                    //col++;
                }
                if ((*row).Line.size() > max_col_length)
                {
                    auto CurrRow = row;
                    auto NextRow = row;
                    NextRow++;
                    while (NextRow != text.end())
                    {

                        while ((*CurrRow).Line.size() > max_col_length)
                        {
                            char ch = (*CurrRow).Line.back();
                            (*CurrRow).Line.pop_back();
                            (*NextRow).Line.push_front(ch);
                        }
                        if ((*NextRow).Line.size() <= max_col_length)
                            break;
                        CurrRow = NextRow;
                        NextRow++;
                    }
                    if (NextRow == text.end())
                    {
                        Lines L;
                        text.insert(NextRow, L);
                        NextRow--;
                        while ((*CurrRow).Line.size() > max_col_length)
                        {
                            char ch = (*CurrRow).Line.back();
                            (*CurrRow).Line.pop_back();
                            (*NextRow).Line.push_front(ch);
                        }
                    }

                }
                started = false;
                selected = false;
                FindFirstAppearance(word);
                if (SelectedWords.empty())
                {
                    done = true;
                    break;
                }
                //continue;
            }
        }
    }
    if ((*text.begin()).Line.front() == ' ' && (*text.begin()).Line.size() > 1)
        (*text.begin()).Line.pop_front();
    Curr_col = (*ri).Line.size();
    ci = (*ri).Line.end();
    if (ci != (*ri).Line.begin())
    ci--;
    word.erase(word.begin());
    word.pop_back();
    string NewWord = word+Postfix;
    FindWords(NewWord);
    HighlightWords(NewWord,changes_made);

}
int CurrentFile::SpecialCharCount()
{
    int count = 0;
    for (auto row = text.begin(); row != text.end(); row++)
    {
        for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
        {
            char ch = *col;
            if ((ch < 'A' || (ch > 'Z' && ch < 'a') || ch > 'z') && (ch < '0' || ch > '9') && ch != ' ' && ch != '.' && ch != ',')
                count++;
        }
    }
    return count;
}
//void CurrentFile::FindandReplace(string word, string RP_word)
//{
//    RP_word.push_back(' ');
//    if (word.back() != ' ')word.push_back(' ');
//    if (word[0] != ' ')word.insert(word.begin(), ' ');
//    Word W;
//    bool selected = false;
//    bool started = false;
//    bool done = false;
//    bool changes_made = false;
//    auto st = (*text.begin()).Line.begin();
//    if (*st != ' ')
//        (*text.begin()).Line.insert(st, ' ');
//    auto r_end = text.end(); r_end--;
//    auto c_end = ((*r_end).Line.end());
//    c_end--;
//    if (*c_end != ' ')
//    {
//        c_end++;
//        (*r_end).Line.insert(c_end, ' ');
//        if ((*r_end).Line.size() > max_col_length)
//        {
//            text.push_back(Lines());
//            auto b = (*r_end).Line.back();
//            (*r_end).Line.pop_back();
//            r_end++;
//            (*r_end).Line.push_back(b);
//        }
//    }
//    FindFirstAppearance(word);
//    if (SelectedWords.empty())
//        changes_made = true;
//
//    for (auto row = text.begin(); row != text.end(); row++)
//    {
//        if (done)break;
//        for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
//        {
//            if (!selected)
//            {
//                if (!SelectedWords.empty())
//                {
//                    W = SelectedWords.front();
//                    SelectedWords.pop();
//                    selected = true;
//                }
//            }
//            if (selected && row == W.starting_Line && col == W.start)
//            {
//                auto temp = col;
//                temp++;
//                for (int i = 0; i < RP_word.length(); i++)
//                {
//
//                    (*row).Line.insert(temp, RP_word[i]);
//                    //col++;
//                }
//                auto tci = temp;                
//                auto tri = row;
//                if (tci == (*tri).Line.end())
//                {
//                    tri++;
//                    if (tri != text.end())
//                    tci = (*tri).Line.begin();
//                }
//                while (tri != text.end())
//                {
//                    auto pc = tci;
//                    tci++;
//                    (*tri).Line.erase(pc);               
//                    if (tci == (*tri).Line.end())
//                    {
//                        tri++;
//                        if (tri == text.end())break;
//                        tci = (*tri).Line.begin();
//                    }
//                    
//                    if (tri == W.ending_Line && tci == W.end)
//                    {
//                        (*tri).Line.erase(tci);
//                        break;
//                    }
//                }
//
//                if ((*row).Line.size() > max_col_length)
//                {
//                    auto CurrRow = row;
//                    auto NextRow = row;
//                    NextRow++;
//                    while (NextRow != text.end())
//                    {
//
//                        while ((*CurrRow).Line.size() > max_col_length)
//                        {
//                            char ch = (*CurrRow).Line.back();
//                            (*CurrRow).Line.pop_back();
//                            (*NextRow).Line.push_front(ch);
//                        }
//                        if ((*NextRow).Line.size() <= max_col_length)
//                            break;
//                        CurrRow = NextRow;
//                        NextRow++;
//                    }
//                    if (NextRow == text.end())
//                    {
//                        Lines L;
//                        text.insert(NextRow, L);
//                        NextRow--;
//                        while ((*CurrRow).Line.size() > max_col_length)
//                        {
//                            char ch = (*CurrRow).Line.back();
//                            (*CurrRow).Line.pop_back();
//                            (*NextRow).Line.push_front(ch);
//                        }
//                    }
//
//                }
//                started = false;
//                selected = false;
//                FindFirstAppearance(word);
//                if (SelectedWords.empty())
//                {
//                    done = true;
//                    break;
//                }
//                //continue;
//            }
//        }
//    }
//    if ((*text.begin()).Line.front() == ' ' && (*text.begin()).Line.size() > 1)
//        (*text.begin()).Line.pop_front();
//    Curr_col = (*ri).Line.size();
//    ci = (*ri).Line.end();
//    ci--;
//    RP_word.pop_back();
//    FindWords(RP_word);
//    HighlightWords(RP_word, changes_made);
//}
void CurrentFile::FindandReplace(string word, string RP_word)
{
    Word W;
    bool selected = false;
    bool started = false;
    bool done = false;
    bool changes_made = false;
    auto st = (*text.begin()).Line.begin();   
    if (SelectedWords.empty())
        changes_made = true;

    for (auto row = text.begin(); row != text.end()&&!changes_made; row++)
    {
        if (done)break;
        for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
        {
            if (!selected)
            {
                if (!SelectedWords.empty())
                {
                    W = SelectedWords.front();
                    SelectedWords.pop();
                    selected = true;
                }
            }
            if (selected && row == W.starting_Line && col == W.start)
            {
                auto temp = col;                
                //temp++;
                for (int i = 0; i < RP_word.length(); i++)
                {

                    (*row).Line.insert(temp, RP_word[i]);
                    //col++;
                }
                col--;
                auto tci = temp;
                auto tri = row;
                if (tci == (*tri).Line.end())
                {
                    tri++;
                    if (tri != text.end())
                        tci = (*tri).Line.begin();
                }
                if (W.starting_Line==W.ending_Line&& W.start == W.end)
                 (*tri).Line.erase(tci);
                 else
                {
                    while (tri != text.end())
                    {
                        auto pc = tci;
                        tci++;
                        (*tri).Line.erase(pc);
                        if (tci == (*tri).Line.end())
                        {
                            tri++;
                            if (tri == text.end())break;
                            tci = (*tri).Line.begin();
                        }

                        if (tri == W.ending_Line && tci == W.end)
                        {
                            (*tri).Line.erase(tci);
                            break;
                        }
                    }
                }

                started = false;
                selected = false;
                if (SelectedWords.empty())
                {
                    done = true;
                    break;
                }
                //continue;
            }
        }
    }
    RearrangeAll();
    ri = text.end();
    ri--;
    Curr_col = (*ri).Line.size();
    ci = (*ri).Line.end();
    if (ci != (*ri).Line.begin())
        ci--;
    else Curr_col = 0;
    Curr_row = text.size()-1;
    FindWords(RP_word);
    HighlightWords(RP_word, changes_made);
}
