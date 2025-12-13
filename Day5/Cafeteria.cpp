#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct FreshRange {
    long long min;
    long long max;

    bool operator<(const FreshRange& other) const {
        return min < other.min;
    }
};

int Task1() {
    vector<FreshRange> freshRanges;
    int freshCount = 0;

    ifstream file("input/input.txt");
    string str;
    while(std::getline(file, str)) {
        const size_t delimIndex = str.find('-');
        if (delimIndex != string::npos) {
            const long long min = std::stoll(str.substr(0, delimIndex));
            const long long max = std::stoll(str.substr(delimIndex + 1));
            freshRanges.push_back({min, max});
        } else if (!str.empty()) {
            long long ingredientId = std::stoll(str);
            for (const auto& [min, max] : freshRanges) {
                if (ingredientId >= min && ingredientId <= max) {
                    freshCount++;
                    break;
                }
            }
        }
    }
    return freshCount;
}

long long Task2() {
    vector<FreshRange> freshRanges;

    ifstream file("input/input.txt");
    string str;
    while(getline(file, str)) {
        const size_t delimIndex = str.find('-');
        if (delimIndex == string::npos) continue;

        const long long min = std::stoll(str.substr(0, delimIndex));
        const long long max = std::stoll(str.substr(delimIndex + 1));

        freshRanges.push_back({min, max});
    }

    sort(freshRanges.begin(), freshRanges.end());

    vector<FreshRange> merged;
    merged.push_back(freshRanges[0]);

    for (int i = 1; i < freshRanges.size(); i++) {
        auto& last = merged.back();
        auto& cur = freshRanges[i];

        if (cur.min <= last.max + 1) {
            last.max = max(cur.max, last.max);
        } else {
            merged.push_back(cur);
        }
    }

    long long freshIdsCount = 0;
    for (const auto& [min, max] : merged) {
        freshIdsCount += max - min + 1;
    }
    return freshIdsCount;
}

int main() {
    cout << "Result from first task: " << Task1() << endl;
    cout << "Result from second task: " << Task2() << endl;
    return 0;
}