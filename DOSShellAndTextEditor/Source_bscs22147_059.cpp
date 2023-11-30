#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <set>
#include<vector>
using namespace std;
// Function to load words from a dictionary file into a set
 unordered_set< string> loadDictionary(const  string& filename) {
     ifstream file(filename);
     unordered_set< string> dictionary;

    if (file.is_open()) {
         string word;
        while (file >> word) {
            // Convert the word to lowercase for case-insensitive comparison
             transform(word.begin(), word.end(), word.begin(), ::tolower);
            dictionary.insert(word);
        }
        file.close();
    }
    else {
         cerr << "Error opening dictionary file." <<  endl;
    }

    return dictionary;
}

// Function to check if a given string is a meaningful word
bool isMeaningfulWord(const  string& word, const  unordered_set< string>& dictionary) {
    // Convert the input word to lowercase for case-insensitive comparison
     string lowercaseWord = word;
     transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);

    return dictionary.count(lowercaseWord) > 0;
}




set<string> generatePermutations(const string& str) {

    set<string> permutations;

    // Sort the string to ensure unique permutations
    string sortedStr = str;
    sort(sortedStr.begin(), sortedStr.end());

    do {
        permutations.insert(sortedStr);
    } while ( next_permutation(sortedStr.begin(), sortedStr.end()));

    return permutations;
}


int mai11n() {
    // Load a dictionary of words (replace "dictionary.txt" with the actual path to your dictionary file)
     unordered_set< string> dictionary = loadDictionary("dictionary.txt");

     string inputString;
     string inputString2;
     string inputString3;
     cout << "Enter a string: ";
     cin >> inputString;
     cin >> inputString2;
     cin >> inputString3;
    vector<string>inputs = {inputString,inputString2,inputString3};
     set< string> result = generatePermutations(inputString);
     set< string> result2 = generatePermutations(inputString2);
     set< string> result3 = generatePermutations(inputString3);
    vector<set<string>>results = {result,result2,result3};
    string MostMeaningful = "";
    int maxcount = 0;
    int count = 0;
    for(int i=0;i<3;i++)
    {

        for (const auto& perm : results[i])
        {
            if (isMeaningfulWord(perm, dictionary))
            {
                cout << perm << " is meaningful\n";
                   count++;;
            }            
            else
                cout << perm << " is not meaningful\n";

        }
        if (count > maxcount)
        {
            maxcount = count;
            MostMeaningful = inputs[i];
        }
        count = 0;
    }

    cout <<endl<<"Most Meaningful :" << MostMeaningful;
    cout <<endl<<"Max Count :" << maxcount;

    return 0;
}
#include <iostream>
#include <string>
#include <vector>

void generatePermutations(std::string& str, int n, std::vector<std::string>& permutations) {
    if (n == 1) {
        permutations.push_back(str);
        return;
    }

    for (int i = 0; i < n - 1; ++i) {
        generatePermutations(str, n - 1, permutations);

        if (n % 2 == 0) {
            std::swap(str[i], str[n - 1]);
        }
        else {
            std::swap(str[0], str[n - 1]);
        }
    }

    generatePermutations(str, n - 1, permutations);
}

int gmain() {
    std::string inputString = "encyclopedia";
    std::vector<std::string> permutations;

    generatePermutations(inputString, inputString.size(), permutations);

    // Now 'permutations' contains all unique permutations of 'inputString'

    std::cout << "Number of permutations: " << permutations.size() << std::endl;
    for (auto i = permutations.begin(); i !=permutations.end(); i++)
    {
        cout << *i << " \n";
    }

    return 0;
}

#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>

std::set<std::string> generateUniquePermutations(const std::string& str) {
    std::set<std::string> permutations;
    std::string sortedStr = str;

    std::sort(sortedStr.begin(), sortedStr.end());

    do {
        permutations.insert(sortedStr);
    } while (std::next_permutation(sortedStr.begin(), sortedStr.end()));

    return permutations;
}

std::set<std::string> generateUniquePermutationsWithFrequency(const std::string& str) {
    std::set<std::string> permutations;
    std::string sortedStr = str;

    std::sort(sortedStr.begin(), sortedStr.end());

    do {
        permutations.insert(sortedStr);
    } while (std::next_permutation(sortedStr.begin(), sortedStr.end()));

    return permutations;
}

int mainqqqqqqw() {
    std::string inputString = "encyclopedia";
    std::set<std::string> result = generateUniquePermutations(inputString);

    std::cout << "Number of permutations: " << result.size() << std::endl;
    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i << " \n";
    }

    return 0;
}
