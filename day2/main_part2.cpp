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

bool checkSubstring(const std::string& mainString, const std::string& subString) {
    if (subString.empty()) {
        return mainString.empty();
    }
    if (mainString.length() % subString.length() != 0) {
        return false;
    }

    int numRepeat = mainString.length() / subString.length();

    for (int i = 0; i < numRepeat; ++i) {
        if (mainString.substr(i * subString.length(), subString.length()) != subString) {
            return false;
        }
    }
    return true;
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
			cout << pair << endl;
			dataIds.push_back(gepPairIds(pair));
		}
	}

    for (auto const& pair : dataIds) {
        for (auto i = pair.first; i <= pair.second; ++i) {
            string check = std::to_string(i);

            if (check.size() % 2 == 0) {
                auto half = check.size() / 2;
                string sub1 = check.substr(0, half);
                string sub2 = check.substr(half, half);
                
                if (sub1 == sub2) {
                    result += i;
                } else {
                    for (size_t k = 1; k < half; ++k) {
                        if (checkSubstring(check, check.substr(0, k))) {
                            result += i;
                        }
                    }
                }
            } else if (check.size() > 1) {
                bool isSame = true;

                for (size_t j = 1; j < check.size(); ++j) {
                    if (check[0] != check[j]) {
                        isSame = false;
                        break;
                    }
                }
                if (isSame) {
                    result += i;
                } else {
                    for (size_t k = 1; k < (check.size() / 2); ++k) {
                        if (checkSubstring(check, check.substr(0, k))) {
                            result += i;
                        }
                    }
                }
            }
        }
    }

	cout << "result " << result << endl;


	return 0;
}
