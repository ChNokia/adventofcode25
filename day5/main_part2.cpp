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

    vector<pair<long long, long long>> mergeRanges;
    mergeRanges.push_back(ranges[0]);

    for (size_t i = 1; i < ranges.size(); ++i)
    {
        auto& lastMerged = mergeRanges.back();
        if (ranges[i].first <= lastMerged.second) {
            lastMerged.second = max(ranges[i].second, lastMerged.second);
        } else {
            mergeRanges.push_back(ranges[i]);
        }
    }

    for (const auto& elem : mergeRanges) {
        result += (elem.second - elem.first + 1);
    }

    cout << "result " << result << endl;


	return 0;
}
