#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

pair<long long, long long> gepPairIds(const string& ids) {
	long long startId = 0;
	long long endId = 0;
	char sym;
    stringstream ss(ids);

    ss >> startId;
    ss >> sym;
    ss >> endId;

    return make_pair(startId, endId);
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

	vector<pair<long long, long long>> dataIds;
	long long result = 0;

    string pairId;
	while(getline(fileRead, pairId)) {
		stringstream lineIds(pairId);
		string pair;

		while(getline(lineIds, pair, ',')) {
			dataIds.push_back(gepPairIds(pair));
		}
	}

	for (const auto& pair : dataIds) {
		for (auto i = pair.first; i <= pair.second; ++i) {
            string check = std::to_string(i);
            if (check.size() % 2 == 0) {
                auto half = check.size() / 2;
                string sub1 = check.substr(0, half);
                string sub2 = check.substr(half, half);
                
                if ( sub1 == sub2) {
                    result += i;
                }
            }
        }
	}

	cout << "result " << result << endl;


	return 0;
}
