#include<iostream>
#include"Folder.h"
#include<time.h>
#include<ctime>

using namespace std;
int main1() {
    
    //Folder* F;

    //F = new Folder("F1", "ABCD",nullptr ;
    
    
    
    
    return 0;
}
#include <iostream>
#include <chrono>
#include <ctime>

int main() {
    // Get the current time point
    auto currentTimePoint = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);

    // Convert the time_t to a local time string
    char timeString[100];
    struct tm timeInfo;

    // Use std::localtime_s to avoid C4996 warning
    if (localtime_s(&timeInfo, &currentTime) == 0) {
        std::strftime(timeString, sizeof(timeString), "%H:%M:%S", &timeInfo);

        // Print the current time
        std::cout << "Current Time: " << timeString << std::endl;
    }
    else {
        // Handle the error (failed to get local time)
        std::cerr << "Failed to get local time." << std::endl;
    }

    return 0;
}
