#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <queue>
#include <stack>
#include <set>

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


    const size_t width = diagramTachyon[0].size();
    const size_t height = diagramTachyon.size();

    auto firstIndex = diagramTachyon[0].find('S');

    vector<vector<size_t>> visited;
    visited.assign(height, vector<size_t>(width, 0));
    visited[0][firstIndex] = 1;

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            if (visited[y][x] == 0) {
                continue;
            }

            if (y >= height - 1)
            {
                result += visited[y][x];
                continue;
            }

            auto nextY = y + 1;

            if (diagramTachyon[nextY][x] == '^')
            {
                if (x > 0) {
                    visited[nextY][x - 1] += visited[y][x];
                }
                if (x + 1 < width) {
                    visited[nextY][x + 1] += visited[y][x];
                }
            } else {
                visited[nextY][x] += visited[y][x];
            }
            
        }
    }

    cout << "********** " << result << endl;
    
    return 0;
}