#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Input {
    pair<int, int> start;
    vector<vector<char>> diagram;
};

Input ParseInput() {
    Input input;

    ifstream file("input/input.txt");
    string str;
    while(getline(file, str)) {
        vector<char> row;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == 'S') {
                input.start = {0, i};
            }
            row.push_back(str[i]);
        }
        input.diagram.push_back(row);
    }
    return input;
}

void PrintDiagram(const vector<vector<char>> diagram) {
    for (const auto& row : diagram) {
        for (const auto& c : row) {
            cout << c;
        }
        cout << endl;
    }
}

void dfs1 (Input& input, vector<pair<int,int>>& splittersUsed, const pair<int,int> currentSplitter) {
    splittersUsed.push_back(currentSplitter);

    const vector<int> directions{-1, 1};
    for (const auto& direction : directions) {
        pair<int, int> newPosition = { currentSplitter.first, currentSplitter.second + direction };

        if (input.diagram[newPosition.first][newPosition.second] == '|') continue;

        bool bottom = false;
        while (input.diagram[newPosition.first][newPosition.second] == '.') {
            input.diagram[newPosition.first][newPosition.second] = '|';
            newPosition.first++;

            if (newPosition.first == input.diagram.size()) {
                bottom = true;
                break;
            }
        }
        if (!bottom && input.diagram[newPosition.first][newPosition.second] == '^') {
            dfs1(input, splittersUsed, newPosition);
        }
    }
}

int Task1(Input input) {
    vector<pair<int,int>> splittersUsed;
    pair<int, int> start = input.start;
    while (input.diagram[start.first][start.second] != '^') {
        if (input.diagram[start.first][start.second] == 'S') {
            start.first++;
            continue;
        }

        input.diagram[start.first][start.second] = '|';
        start.first++;
    }

    dfs1(input, splittersUsed, start);

    return splittersUsed.size();
}

unsigned long long EncodePosition(pair<int, int> pos) {
    return ( (unsigned long long)( (unsigned long long)(unsigned)pos.first ) << 32 ) | (unsigned)pos.second;
}

long long dfs2 (Input& input, unordered_map<unsigned long long, long long>& memory, const pair<int,int> currentSplitter) {
    unsigned long long encodedPosition = EncodePosition(currentSplitter);
    auto it = memory.find(encodedPosition);
    if (it != memory.end()) return it->second;

    long long total = 0;
    const vector<int> directions{-1, 1};
    for (const auto& direction : directions) {
        pair<int, int> newPosition = { currentSplitter.first, currentSplitter.second + direction };

        while (true) {
            if (newPosition.first >= input.diagram.size()) {
                total++;
                break;
            }

            const char character = input.diagram[newPosition.first][newPosition.second];
            if (character == '.') {
                newPosition.first++;
                continue;
            }

            if (character == '^') {
                total += dfs2(input, memory, newPosition);
                break;
            }

            total++;
            break;
        }
    }

    memory[encodedPosition] = total;
    return total;
}

long long Task2(Input input) {
    pair<int, int> start = input.start;
    while (input.diagram[start.first][start.second] != '^') {
        start.first++;
    }

    unordered_map<unsigned long long, long long> memory;
    return dfs2(input, memory, start);
}

int main() {
    const Input input = ParseInput();
    cout << "Result from first task: " << Task1(input) << endl;
    cout << "Result from second task: " << Task2(input) << endl;
    return 0;
}