#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

#define ull unsigned long long

struct Edge {
    int x1, y1, x2, y2;
};

vector<pair<int, int>> ParseInput() {
    vector<pair<int, int>> coordinates;

    ifstream file("input/input.txt");
    string str;
    pair<int, int> p;
    char comma;
    while(getline(file, str)) {
        stringstream ss(str);
        ss >> p.first >> comma >> p.second;
        coordinates.push_back(p);
    }
    return coordinates;
}

ull Task1(const vector<pair<int, int>>& coordinates) {
    ull largestArea = 0;
    for (size_t i = 0; i < coordinates.size(); i++) {
        for (size_t j = i + 1; j < coordinates.size(); j++) {
            const ull dx = 1 + abs(coordinates[j].first - coordinates[i].first);
            const ull dy = 1 + abs(coordinates[j].second - coordinates[i].second);
            ull area = dx * dy;

            if (area > largestArea) largestArea = area;
        }
    }
    return largestArea;
}

bool DoesIntersect(const vector<Edge>& edges, const int minX, const int minY, const int maxX, const int maxY){
    for (const auto& e : edges) {
        const int minX_ = min(e.x1, e.x2);
        const int minY_ = min(e.y1, e.y2);
        const int maxX_ = max(e.x1, e.x2);
        const int maxY_ = max(e.y1, e.y2);

        if (minX < maxX_ && maxX > minX_ && minY < maxY_ && maxY > minY_) {
            return true;
        }
    }
    return false;
}

ull CalculateDistance(const pair<int, int>& a, const pair<int, int>& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

ull Task2(const vector<pair<int, int>>& coordinates) {
    const size_t n = coordinates.size();

    vector<Edge> edges;
    for (size_t i = 0; i < n - 1; ++i) {
        auto [fx, fy] = coordinates[i];
        auto [tx, ty] = coordinates[i + 1];
        edges.push_back({fx, fy, tx, ty});
    }

    edges.push_back({
        coordinates.front().first,
        coordinates.front().second,
        coordinates.back().first,
        coordinates.back().second
    });

    ull result = 0;
    for (size_t i = 0; i < coordinates.size() - 1; ++i) {
        for (size_t j = i; j < coordinates.size(); ++j) {
            const auto& from = coordinates[i];
            const auto& to= coordinates[j];

            const int minX = min(from.first, to.first);
            const int minY = min(from.second, to.second);
            const int maxX = max(from.first, to.first);
            const int maxY = max(from.second, to.second);

            ull md = CalculateDistance(from, to);
            if (md * md <= result) continue;

            if (!DoesIntersect(edges, minX, minY, maxX, maxY)) {
                const ull dx = 1 + abs(to.first - from.first);
                const ull dy = 1 + abs(to.second - from.second);
                ull area = dx * dy;
                result = max(result, area);
            }
        }
    }
    return result;
}

int main() {
    const vector<pair<int, int>> coordinates = ParseInput();
    cout << "Result from first task: " << Task1(coordinates) << endl;
    cout << "Result from second task: " << Task2(coordinates) << endl;
    return 0;
}