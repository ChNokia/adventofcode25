#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <set>
#include <queue>
#include <unordered_set>

#include <iterator>

using namespace std;

struct Goal {
    size_t bits;
    string symbols;
};

Goal getGoal(const string& rawGoal) {
    string strGoal = rawGoal.substr(1, rawGoal.size() - 2);
    size_t symbol = 0;

    for (size_t i = 0; i < strGoal.size(); ++i) {
        if (strGoal[i] == '.') {
            continue;
        }
        symbol = (symbol | (1 << i));
    }

    return Goal{symbol, strGoal};
}

size_t getButtons(const string& rawButtons) {
    string strButtons = rawButtons.substr(1, rawButtons.size() - 2);
    stringstream ss(strButtons);
    size_t buttons = 0;
    size_t num;

    while (ss >> num) {
        buttons = (buttons | (1 << num));

        char separator;
        ss >> separator;
    }

    return buttons;
}

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

    vector<Goal> goals;
    vector<vector<size_t>> buttonsLine;

    string line;
    while(getline(fileRead, line)) {
        stringstream ss(line);
        string asas;

        getline(ss, asas, ' ');
        goals.push_back(getGoal(asas));
        
        vector<size_t> buttons;

        getline(ss, asas, ' ');
        while (asas[0] != '{') {
            buttons.push_back(getButtons(asas));
            getline(ss, asas, ' ');
        }
        buttonsLine.push_back(buttons);
    }

    long long result = 0;

    for (size_t i = 0; i < goals.size() && i < buttonsLine.size(); ++i) {
        queue<pair<size_t, size_t>> states;
        unordered_set<size_t> visitedStates;

        states.push({0, 0});
        visitedStates.insert(0);

        while (!states.empty()) {
            auto [curentState, count] = states.front();
            states.pop();

            if (curentState == goals[i].bits) {
                result += count;
                break;
            }

            for (const auto& btn : buttonsLine[i]) {
                auto newState = (curentState ^ btn);

                if (!visitedStates.count(newState)) {
                    states.push({newState, count + 1});
                    visitedStates.insert(newState);
                }
            }
        }
    }

    cout << "result " << result << endl;


	return 0;
}
