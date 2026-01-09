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

    

    auto isInRectangle = [&points](const point& pointA, const point& pointB) -> bool {
        point leftTop = point{min(pointA.x, pointB.x), min(pointA.y, pointB.y)};
        point rightBottom = point{max(pointA.x, pointB.x), max(pointA.y, pointB.y)};

        for (size_t i = 0; i < points.size(); ++i) {
            auto start = points[i];
            auto end = points[(i + 1) % points.size()];

            point edgeStart = point{min(start.x, end.x), min(start.y, end.y)};
            point edgeEnd = point{max(start.x, end.x), max(start.y, end.y)};

            if (rightBottom.x < edgeStart.x || leftTop.x > edgeEnd.x
                || leftTop.y > edgeEnd.y || rightBottom.y < edgeStart.y) {
                continue;
            }

            //cross our rectancle top(-) with vertical edge(|)
            if(edgeStart.y <= leftTop.y && edgeEnd.y > leftTop.y && edgeStart.x > leftTop.x && edgeEnd.x < rightBottom.x) return false;

            //cross our rectancle right(|) with horiz. edge(-) => |-
            if(edgeStart.x < rightBottom.x && edgeEnd.x >= rightBottom.x && edgeStart.y > leftTop.y && edgeEnd.y < rightBottom.y) return false;

            //cross our rectancle bottom(-) with vertical edge(|) => _|_
            if(edgeEnd.y <= rightBottom.y && edgeStart.y < rightBottom.y && edgeStart.x > leftTop.x && edgeEnd.x < rightBottom.x) return false;

            //cross our rectancle left(|) with horiz. edge(-) => -|
            if(edgeStart.x <= leftTop.x && edgeEnd.x > leftTop.x && edgeStart.y > leftTop.y && edgeEnd.y < rightBottom.y) return false;
        }

        return true;
    };

    long long result = 0;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            if(points[i].x == points[j].x || points[i].y == points[j].y) continue;

            if (isInRectangle(points[i], points[j])) {
                auto square = (abs(points[i].x - points[j].x) + 1) * (abs(points[i].y - points[j].y) + 1);
                if (result < square) {
                    result = square;
                }
            }
            
        }
    }
    
    cout << "result " << result << endl;


    return 0;
}