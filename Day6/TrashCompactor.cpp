#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Problem {
    vector<string> numbers;
    string operator_;
};

vector<Problem> ParseInput() {
    vector<Problem> Problems;

    vector<string> lines;
    ifstream file("input/input.txt");
    string str;
    while(std::getline(file, str)) {
        str.erase(std::remove(str.begin(), str.end(), '\0'), str.end());
        lines.push_back(str);
    }

    vector<string> numbers{lines.size()-1, ""};
    string operator_;
    for (int i = 0; i <= lines[0].size(); i++) {
        for (int j = 0; j < lines.size(); j++) {
            if (j == lines.size() - 1) {
                if (lines[j][i] != ' ') {
                    operator_ = lines[j][i];
                }
                continue;
            } else {
                numbers[j] += lines[j][i];
            }

            bool allBlankSpace = true;
            bool allSameLength = true;
            size_t lastLength = numbers[0].size();
            for (string& number : numbers) {
                if (number.back() != ' ') {
                    allBlankSpace = false;
                }
                if (lastLength != number.size()) {
                    allSameLength = false;
                }

                lastLength = number.size();

                if (!allBlankSpace || !allSameLength) break;
            }

            if(i == lines[0].size() && j == lines.size() - 2) {
                for (string& number : numbers) {
                    number.pop_back();
                }
                Problems.push_back({numbers, operator_});
                break;
            }

            if (allBlankSpace && allSameLength) {
                for (string& number : numbers) {
                    number.pop_back();
                }
                Problems.push_back({numbers, operator_});

                operator_ = "";
                numbers = vector<string>(lines.size()-1, "");
            }
        }
    }

    return Problems;
}

long long PerformOperation(const string& operation, const long long& a, const long long& b) {
    long long result = 0;
    if (operation == "+") {
        result =  a + b;
    }
    else if (operation == "-") {
        result =  a - b;
    }
    else if (operation == "*") {
        result =  a * b;
    }
    else if (operation == "/") {
        result =  a / b;
    }
    return result;
}

long long Task1(const vector<Problem>& Problems) {
    long long totSum = 0;
    for (const Problem& Problem : Problems) {
        long long sum = stoll(Problem.numbers[0]);
        for (int i = 1; i < Problem.numbers.size(); i++) {
            sum = PerformOperation(Problem.operator_, sum, stoll(Problem.numbers[i]));
        }
        totSum += sum;
    }
    return totSum;
}

long long Task2(const vector<Problem>& Problems) {
    long long totSum = 0;
    for (const Problem& Problem : Problems) {
        long long sum = -1;

        int i = static_cast<int>(Problem.numbers[0].length()) - 1;
        while(i > -1) {

            string tmp;
            for (const auto & number : Problem.numbers) {
                tmp += number.substr(i, 1);
            }

            if (sum == -1) {
                sum = stoll(tmp);
            } else {
                sum = PerformOperation(Problem.operator_, sum, stoll(tmp));
            }
            i--;
        }
        totSum += sum;
    }
    return totSum;
}

int main() {
    const vector<Problem> Problems = ParseInput();

    cout << "Result from first task: " << Task1(Problems) << endl;
    cout << "Result from second task: " << Task2(Problems) << endl;
    return 0;
}