#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

pair<long long, long long> getRange(const string& line) {
    stringstream ss(line);
    string start;
    string end;

    getline(ss, start, '-');
    getline(ss, end);

    return make_pair(stoll(start), stoll(end));
}

bool ComparePair(const pair<long long, long long>& one, const pair<long long, long long>& two) {
    return one.first < two.first;
}

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

    auto comparePair = [](const pair<long long, long long>& one, const pair<long long, long long>& two) {
        return one.first < two.first;
    };

    vector<pair<long long, long long>> ranges;
    vector<long long> availableIDs;

	string line;
    bool isRanges = true;

    while(getline(fileRead, line)) {
        if (line.empty())
        {
            isRanges = false;
            continue;
        }
        if (isRanges) {
            ranges.push_back(getRange(line));

        } else {
            availableIDs.push_back(stoll(line));
        }
    }

    long long result = 0;

    sort(ranges.begin(), ranges.end(), comparePair);
    sort(availableIDs.begin(), availableIDs.end());

    size_t prevStart = 0;
    for (const auto& elem : availableIDs) {
        for (size_t i = prevStart; i < ranges.size(); ++i)
        {
            if (elem <= ranges[i].second && elem >= ranges[i].first) {
                result += 1;
                prevStart = i;
                break;
            }
        }
    }


	cout << "result " << result << endl;


	return 0;
}
