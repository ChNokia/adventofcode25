#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <set>
#include <regex>

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
    vector<vector<string>> stringData;
    vector<string> mathAction;

    vector<string> allDada;
    string line;


    while(getline(fileRead, line)) {
        allDada.emplace_back(line);
    }

    auto actionsString = allDada.back();
    allDada.pop_back();
    
    string action = "";
    action += actionsString[0];

    for (size_t i = 1; i < actionsString.size(); ++i) {
        if (actionsString[i] != ' ') {
            mathAction.emplace_back(action.substr(0, action.size() - 1));
            action = "";
        }
        action += actionsString[i];
    }
    mathAction.emplace_back(action);


    bool isFirstLine = true;
    for (const auto& item : allDada) {
        istringstream iss(item);

        for (size_t i = 0; i < mathAction.size(); ++i) {
            char skip;
            vector<char> buffer(mathAction[i].size());

            iss.read(buffer.data(), mathAction[i].size());
            if (!iss.eof())
            {
                iss.read(&skip, sizeof(char));
            }
            
            replace(buffer.begin(), buffer.end(), ' ', 'x');

            if (!isFirstLine) {
                stringData[i].push_back(string(buffer.begin(), buffer.end()));  
            } else {
                stringData.push_back({string(buffer.begin(), buffer.end())});
            }
        }

        isFirstLine = false;
    }

    for (size_t i = 0; i < mathAction.size(); ++i)
    {
        long long temp = mathAction[i][0] == '+' ? 0 : 1;

        auto column = stringData[i];
        size_t width = mathAction[i].size();

        for (size_t j = 0; j < width; ++j) {
            string value = "";
            for (const auto& item : column)
            {
                if (item[j] != 'x')
                {
                    value += item[j];
                }
            }

            if (mathAction[i][0] == '+') {    
                temp += stoll(value);
            } else {
                temp *= stoll(value);
            }
        }

        result += temp;
    }

	cout << "result " << result << endl;


	return 0;
}
