#include<iostream>
#include"Folder.h"
#include<time.h>
#include<conio.h>
#include<ctime>
#include<iomanip>
#include<vector>
#include <chrono>   // For std::chrono::seconds
#include <thread>   // F
#include"DOS.h"
using namespace std;
int main()
{
    DOS D;
    D.play();
    return 0;
}

int main2() {
    
    vector<Folder*>Folds;
    time_t c;
    c = time(0);

    cout<<time(&c);

    
    
    return 0;
}
