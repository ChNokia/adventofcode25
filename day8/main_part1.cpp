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

struct point3d {
    long long x, y, z;
};

struct circle {
    size_t i, j;

    long long disnace;
};

istream& operator>>(istream& in, point3d& p) {
    char skip;
    return in >> p.x >> skip >> p.y >> skip >> p.z;
}

long long disnaceBetweenPoints(const point3d& p1, const point3d& p2) {
    long long dx = p1.x -p2.x;
    long long dy = p1.y -p2.y;
    long long dz = p1.z -p2.z;
    return dx * dx + dy * dy + dz * dz;
}

int main(int argc, char const *argv[])
{
	string filename = "data_test.txt";
    size_t count = 10; 

    if (argc > 1)
    {
        filename = argv[1];
        count = 1000;
    }

    fstream fileRead(filename);

    if (!fileRead.is_open())
    {
        cerr << "Error opening file " << filename<< "!" << std::endl;
        return 1;
    }
    
    vector<point3d> points{istream_iterator<point3d>(fileRead), {}};

    vector<circle> disnaces;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            disnaces.push_back({i, j, disnaceBetweenPoints(points[i], points[j])});
        }
    }

    sort(disnaces.begin(), disnaces.end(), [](const circle& c1, const circle& c2) {
        return c1.disnace < c2.disnace;
    });

    vector<size_t> pointParents(points.size());
    vector<size_t> junctions(points.size(), 1);

    iota(pointParents.begin(), pointParents.end(), 0);

    auto findParent = [&pointParents](const size_t a) -> size_t {
        size_t child = a;
        while(child != pointParents[child]) {
            child = pointParents[child];
        }
        return child;
    };
    auto checkConnection = [&pointParents, &junctions, findParent](const size_t first, const size_t second) {
        size_t parentFirst = findParent(first);
        size_t parentSecond = findParent(second);

        if (parentFirst == parentSecond) {
            return;
        }

        if (junctions[parentFirst] < junctions[parentSecond]) {
            swap(parentFirst, parentSecond); // union by size
        }

        pointParents[parentSecond] = parentFirst;
        junctions[parentFirst] += junctions[parentSecond];
    };

    for (size_t i = 0; i < count && i < disnaces.size(); ++i) {
        checkConnection(disnaces[i].i, disnaces[i].j);
    }

    long long result = 1;
    sort(junctions.begin(), junctions.end(), greater<>{});
    for (size_t i = 0; i < 3 && i < junctions.size(); ++i) {
        result *= junctions[i];
    }
    
    cout << "result " << result << endl;


	return 0;
}
