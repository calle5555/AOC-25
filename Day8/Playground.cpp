#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

struct Coordinate {
    int x, y, z;

    double Distance(const Coordinate& other) const {
        const double dx = x - other.x;
        const double dy = y - other.y;
        const double dz = z - other.z;
        return dx*dx + dy*dy + dz*dz;
    }
};

class DSU {
    vector<int> parent, size;

public:
    DSU(const size_t n) {
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int Find(const int i) {
        return (parent[i] == i) ? i : (parent[i] = Find(parent[i]));
    }

    void Unite(const int x, const int y) {
        int s1 = Find(x), s2 = Find(y);
        if (s1 == s2) return;
        if (size[s1] < size[s2]) swap(s1, s2);
        parent[s2] = s1;
        size[s1] += size[s2];
    }

    int GetSize(const int x) {
        return size[Find(x)];
    }
};

vector<Coordinate> ParseInput() {
    vector<Coordinate> coordinates;

    ifstream file("input/input.txt");
    string str;
    Coordinate p{};
    char comma;
    while(getline(file, str)) {
        stringstream ss(str);
        ss >> p.x >> comma >> p.y >> comma >> p.z;
        coordinates.push_back(p);
    }
    return coordinates;
}

size_t Task1(const vector<Coordinate>& coordinates, const int pairsToConnect) {
    vector<pair<double, pair<int, int>>> pairs;
    for (size_t i = 0; i < coordinates.size(); i++) {
        for (size_t j = i + 1; j < coordinates.size(); j++) {
            pairs.push_back({coordinates[i].Distance(coordinates[j]), {i, j}});
        }
    }

    sort(pairs.begin(), pairs.end());

    DSU dsu(coordinates.size());

    int edgesConnected = 0;
    for (auto& edge : pairs) {
        dsu.Unite(edge.second.first, edge.second.second);
        edgesConnected++;

        if (pairsToConnect != -1 && edgesConnected == pairsToConnect) break;
    }

    vector<long long> circuitSizes;
    vector<bool> seen(coordinates.size(), false);
    for (int i = 0; i < coordinates.size(); ++i) {
        int root = dsu.Find(i);
        if (!seen[root]) {
            circuitSizes.push_back(dsu.GetSize(root));
            seen[root] = true;
        }
    }

    sort(circuitSizes.rbegin(), circuitSizes.rend());

    return circuitSizes[0] * circuitSizes[1] * circuitSizes[2];
}

unsigned long long Task2(const vector<Coordinate>& coordinates) {
    vector<pair<double, pair<int, int>>> pairs;
    for (size_t i = 0; i < coordinates.size(); i++) {
        for (size_t j = i + 1; j < coordinates.size(); j++) {
            pairs.push_back({coordinates[i].Distance(coordinates[j]), {i, j}});
        }
    }

    sort(pairs.begin(), pairs.end());

    DSU dsu(coordinates.size());

    size_t totalPoints = coordinates.size();
    for (auto& edge : pairs) {
        const int u = edge.second.first;
        const int v = edge.second.second;
        if (dsu.Find(u) == dsu.Find(v)) continue;

        dsu.Unite(u, v);

        if (--totalPoints == 1) {
            const Coordinate p1 = coordinates[u];
            const Coordinate p2 = coordinates[v];
            return static_cast<unsigned long long>(p1.x) * static_cast<unsigned long long>(p2.x);
        }
    }
    return 0;
}

int main() {
    const vector<Coordinate> coordinates = ParseInput();

    cout << "Result from first task: " << Task1(coordinates, 1000) << endl;
    cout << "Result from second task: " << Task2(coordinates) << endl;
    return 0;
}