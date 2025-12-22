#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	// string filename = "data_test.txt";
	string filename = "data.txt";

	ifstream fileRead(filename);
	// ifstream fileRead("data.txt");

	if (!fileRead.is_open()) {
		cerr << "Error opening file " << filename<< "!" << std::endl;
        return 1;
	}

	string line;
	vector<string> moves;

	while(getline(fileRead, line)) {	
		moves.emplace_back(line);
	}

	long long start = 50;
	long long max = 100;
	long long sum1 = 0;
	long long sum2 = 0;

	for (const auto& move : moves) {
		long long num = stol(move.substr(1));

		sum2 += num / max;
		// cout << start << " " << move << " ";
		if (move[0] == 'R') {
			if (start != max && (start + (num % max)) >= max) {
				sum2++;
			}
			start = (start + (num % max)) % max;
		} else {
			if (start != 0 && (start - (num % max)) <= 0) {
				sum2++;
			}
			start = (max + (start - (num % max))) % max;
		}

        if ((start % max) == 0) {
            sum1++;	
        }
		
		// cout << start << " sum " << sum << endl;

	}

    cout << "sum1 = " << sum1 << "  sum2 = " << sum2 <<endl;

	return 0;
}