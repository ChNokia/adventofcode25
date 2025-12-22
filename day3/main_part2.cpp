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

    vector<vector<size_t>> joltages;
    size_t batteries = 11;
    long long result = 0;

    string line;
    while(getline(fileRead, line)) {
        vector<size_t> lineJolt;

        for (size_t i = 0; i < line.size(); ++i) {
            lineJolt.emplace_back(line[i] - '0');
        }

        joltages.push_back(lineJolt);
    }
     
     for (auto const& lineJolt : joltages) {
        auto maxFirst = max_element(lineJolt.begin(), lineJolt.end() - batteries);
         
         auto prev = maxFirst;
         string resultString = to_string(*maxFirst);
         
         for (size_t i = 0; i < batteries; ++i) {
             
             auto maxSecond = std::max_element(prev + 1, lineJolt.end() -(batteries - (i + 1)));

             if ((lineJolt.end() - maxSecond) >= (batteries - i)) {
                 resultString += to_string(*maxSecond);
             } else {
                 resultString += to_string(*prev);
             }
             
             prev = maxSecond;
         }

         result += stoll(resultString);

     }


    cout << "result " << result << endl;


    return 0;
}
