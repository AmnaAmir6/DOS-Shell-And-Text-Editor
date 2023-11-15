#include<iostream>
#include"Folder.h"
#include<time.h>
#include<conio.h>
#include<ctime>
#include<iomanip>
#include<vector>
#include <chrono>   // For std::chrono::seconds
#include <thread>   // F
using namespace std;
int main() {
    
    vector<Folder*>Folds;
    time_t c;
    c = time(0);
    for (int i = 0; i < 5; i++)
    {
        Folder* F;
       F = new Folder("F1", "ABCD", "abdul", nullptr, false, c);
        F->PrintCreationTime();
        cout << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }


    for(int i=0;i<Folds.size();i++)
    {
        Folds[i]->PrintCreationTime();
        cout << endl;
    }

    
    
    
    return 0;
}