#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
#define Map vector<vector<int>>

struct RemovableRoll {
    int r;
    int c;
};

Map ReadPaperMap() {
    Map paperMap;

    std::ifstream file("input/input.txt");
    std::string str;
    while(std::getline(file, str)) {
        std::vector<int> mapRow(static_cast<int>(str.length()), 0);
        for(int i = 0; i < str.length(); i++) {
            mapRow[i] = str[i] == '@' ? 1 : 0;
        }
        paperMap.push_back(mapRow);
    }
    return paperMap;
}

vector<RemovableRoll> CalculateRemovableRolls(const Map& paperMap) {
    const int H = static_cast<int>(paperMap.size()), W = static_cast<int>(paperMap[0].size());
    const vector<std::pair<int,int>> offsets {{
        {-1,-1},{-1,0},{-1,1},
        {0,-1},               {0,1},
        {1,-1}, {1,0}, {1,1}
    }};

    vector<RemovableRoll> removableRolls;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (paperMap[r][c] == 0) continue;

            int sum = 0;
            for (auto [offsetR, offsetC] : offsets) {
                int nr = r + offsetR, nc = c + offsetC;
                if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                    sum += paperMap[nr][nc];
                    if (sum >= 4) break;
                }
            }
            if (sum < 4) removableRolls.push_back({r, c});
        }
    }
    return removableRolls;
}

int Task1(const Map& paperMap) {
    return static_cast<int>(CalculateRemovableRolls(paperMap).size());
}

int Task2(Map paperMap){
    int totalRemovedRolls = 0;

    vector<RemovableRoll> removableRolls;
    do {
        removableRolls = CalculateRemovableRolls(paperMap);
        totalRemovedRolls += static_cast<int>(removableRolls.size());

        for (const auto& [row, column] : removableRolls) {
            paperMap[row][column] = 0;
        }
    } while (!removableRolls.empty());

    return totalRemovedRolls;
}

int main() {
    const Map paperMap = ReadPaperMap();
    cout << "Result from first task: " << Task1(paperMap) << endl;
    cout << "Result from second task: " << Task2(paperMap) << endl;
    return 0;
}