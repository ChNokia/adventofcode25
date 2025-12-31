#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

int main(int argc, char const *argv[])
{
	string filename = "data_test.txt";

    if (argc > 1)
    {
        filename = argv[1];
    }

    fstream fileRead(filename);

    if (!fileRead.is_open())
    {
        cerr << "Error opening file " << filename<< "!" << std::endl;
        return 1;
    }
    
    long long result = 0;
    vector<vector<long long>> stringData;
    vector<char> mathAction;

    string line;

    getline(fileRead, line);
    long long number;
    istringstream ss(line);
    while(ss >> number) {
        vector<long long> col;
        col.emplace_back(number);
        stringData.emplace_back(col);
    }

    while(getline(fileRead, line)) {
        long long number;
        istringstream strem(line);
        size_t index = 0;

        while(strem >> number) {
            stringData[index].emplace_back(number);
            ++index;
        }
        if (!strem.eof()) {
            strem.clear();
            strem.str(line);
            char action;

            while(strem >> action) {
                if (action != ' ')
                {
                    mathAction.emplace_back(action);
                }
            }
        }
    }

    for (size_t i = 0; i < mathAction.size(); ++i)
    {
        long long temp = 1;
        if (mathAction[i] == '+') {
            temp = accumulate(stringData[i].cbegin(), stringData[i].cend(), 0);
        } else {
            for (const auto& item : stringData[i])
            {
                temp *= item;
            }
        }
        result += temp;
    }

	cout << "result " << result << endl;


	return 0;
}
