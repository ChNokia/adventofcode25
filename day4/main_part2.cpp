#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


int main(int argc, char const *argv[])
{
    string filename = "data_test.txt";

    if (argc > 1) {
        filename = argv[1];
    }

    fstream fileRead(filename);

    if (!fileRead.is_open()) {
        cerr << "Error opening file " << filename<< "!" << std::endl;
        return 1;
    }

    vector<string> rolls;
    long long result = 0;

    string lineRolls;
    while(getline(fileRead, lineRolls)) {
        rolls.push_back(lineRolls);
    }

    char rollChar = '@';
    auto rollsTemp = rolls;
    long long circleResult = 0;

    do {
        circleResult = 0;

        for (size_t i = 0; i < rolls.size(); ++i) {
            for (size_t j = 0; j < rolls[i].size(); ++j) {
                if (rolls[i][j] == rollChar) {
                    int countF = 0;
                    //0
                    if (j > 0) {
                        if (rolls[i][j - 1] == rollChar) {
                            countF++;
                        }
                        
                       //1 
                        if (i > 0 && rolls[i-1][j-1] == rollChar) {
                            countF++;
                        }
                    }
                    //2
                    if (i > 0 && rolls[i - 1][j] == rollChar) {
                        countF++;
                    }
                    //4
                    if (j < (rolls[i].size() - 1)) {
                         if (rolls[i][j + 1] == rollChar) {
                            countF++;
                         }
                       //3 
                        if (i > 0 && rolls[i - 1][j + 1] == rollChar) {
                            countF++;
                        }
                        //5 
                        if (i < (rolls.size() - 1) && rolls[i+1][j+1] == rollChar) {
                            countF++;
                        }
                    }
                    
                    //6
                    if (i < (rolls.size() - 1) ) {
                        if (rolls[i + 1][j] == rollChar) {
                            countF++;
                        }
                        
                        //7
                         if (j > 0 && rolls[i + 1][j - 1] == rollChar) {
                             countF++;
                         }
                    }
                    
                    if (countF < 4) {
                        circleResult += 1;
                        rollsTemp[i][j] = '.';
                    }
                }
            }
        }

        result += circleResult;
        rolls = rollsTemp;
    } while (circleResult > 0);

    cout << "result " << result << endl;


    return 0;
}
