#pragma once
#include<list>
#include<iostream>
#include<fstream>
#include<queue>
#include<stack>
#include"Lines.h"
#include"utility.h"
using namespace std;

class CurrentFile
{
	list<Lines>text;
	list<Lines>::iterator ri;
	int Curr_row, Curr_col;
	list<char>::iterator ci;
	string Name;
	int max_col_length;
	struct FileState
	{
		int CCol, CRow;
		list<Lines>text;
		list<Lines>::iterator RowIndex;
		list<char>::iterator ColIndex;
		FileState(const CurrentFile& CF) 
		{
			CCol = CF.Curr_col;
			CRow = CF.Curr_row;
			text.push_back(Lines());
			auto itr = text.begin();
			for (auto row = CF.text.begin(); row != CF.text.end(); row++,itr++)
			{
				for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
				{
					if (row == CF.text.begin() && col == (*row).Line.begin())
						*((*itr).Line.begin()) = *col;
					else
						(*itr).Line.push_back(*col);
				}
			}
			RowIndex = text.begin();
			ColIndex = (*RowIndex).Line.begin();
			int cri = 0, cci = 0;
			for (auto row = text.begin(); row != text.end(); row++, cri++)
			{
				if (cri == CCol)
				{
					RowIndex = row;
					break;
				}
			}
			for (auto col = (*RowIndex).Line.begin(); col != (*RowIndex).Line.end(); col++, cci++)
			{
				if (cci == CRow)
				{
					ColIndex = col;
					break;
				}
			}

		}
		FileState(const FileState& FS)
		{
			CCol = FS.CCol;
			CRow = FS.CRow;
			text.push_back(Lines());
			auto itr = text.begin();
			for (auto row = FS.text.begin(); row != FS.text.end(); row++, itr++)
			{
				for (auto col = (*row).Line.begin(); col != (*row).Line.end(); col++)
				{
					if (row == FS.text.begin() && col == (*row).Line.begin())
						*((*itr).Line.begin()) = *col;
					else
						(*itr).Line.push_back(*col);
				}
			}
			RowIndex = text.begin();
			ColIndex = (*RowIndex).Line.begin();
			int cri = 0, cci = 0;
			for (auto row = text.begin(); row != text.end(); row++, cri++)
			{
				if (cri == CCol)
				{
					RowIndex = row;
					break;
				}
			}
			for (auto col = (*RowIndex).Line.begin(); col != (*RowIndex).Line.end(); col++, cci++)
			{
				if (cci == CRow)
				{
					ColIndex = col;
					break;
				}
			}
		}
		/*FileState(int col, int row, list<Lines>t, list<Lines>::iterator Ri, list<char>::iterator Ci) :CCol(col), CRow(row), text(t), RowIndex(Ri), ColIndex(Ci)
		{
		}*/
	};
	deque<FileState>Undo;
	stack<FileState>Redo;
	struct pos
	{
		int ri, ci;
	};
	struct RectShape
	{
		int width; int height;
		int r; int c;
		int clr;
		RectShape(int w,int h,int row,int col,int color)
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
	struct Word
	{
		list<char>::iterator start;
		list<char>::iterator end;
		list<Lines>::iterator starting_Line;
		list<Lines>::iterator ending_Line;
	};
	RectShape* SearchBox;
	queue<Word> SelectedWords;
	bool finding;
 public:

	 CurrentFile(string FileName);
	 void Insert();
	 void Set_Max_and_Count(Lines& L);
	 void Print();
	 void SaveFile();
	 void LoadFile();
	 void LoadState(const FileState& S);
	 void SaveState();
	 void DoUndo();
	 void DoRedo();
	 float GetAvgWordLength();
	 int GetParagraphCount();
	 void FindWords(string name);
	 void HighlightWords(string name);
	 void ToUpperOrLower(string cast);
	 void AddPrefixtoWord(string word, string Prefix);
	 void AddPostfixtoWord(string word, string Postfix);
	 int SpecialCharCount();
};

