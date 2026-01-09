#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <set>

#include <iterator>

using namespace std;

struct point {
    long long x, y;
};

istream& operator>>(istream& in, point& p) {
    char skip;

    return in >> p.x >> skip >> p.y;
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

    vector<point> points{istream_iterator<point>(fileRead), {}};

    


    long long result = 0;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            auto square = (abs(points[i].x - points[j].x) + 1) * (abs(points[i].y - points[j].y) + 1);
            if (result < square) {
                result = square;
            }
        }
    }
    
    cout << "result " << result << endl;


	return 0;
}
