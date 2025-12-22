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


    long long result = 0;
	string line;
    vector<string> diagramTachyon;

    while (getline(fileRead, line)) {
    	diagramTachyon.push_back(line);
    }
    
    auto firstIndex = diagramTachyon[0].find('S');
    diagramTachyon[1][firstIndex] = '|';
    for (size_t i = 2; i < diagramTachyon.size(); ++i) {
    	for (size_t j = 0; j < diagramTachyon[i].size(); ++j) {
    		if (diagramTachyon[i - 1][j] == '|') {
    			if (diagramTachyon[i][j] == '^') {
    				result++;
	    			if (j > 0) {
	    				diagramTachyon[i][j - 1] = '|';
	    			}
	                if (j < (diagramTachyon[i].size() - 1)) {
	    				diagramTachyon[i][j + 1] = '|';
	    			}
	                continue;
                }
                diagramTachyon[i][j] = '|';
    	    } 
    	}
    }

    cout << "************ result " << result << endl;

	return 0;
}