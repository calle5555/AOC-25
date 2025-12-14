#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Button {
    vector<int> affectedPositions;
};

class Machine {

public:
    int SolveTask1() {
        int n = 1;
        while (true) {
            vector<vector<Button>> combinations = GetButtonCombinationsOfLengthN(n);

            for (auto& combination : combinations) {
                vector<bool> currentState(goalStateIndicators.size(), false);
                for (auto& button : combination) {
                    ApplyButton(currentState, button);
                }
                if (currentState == goalStateIndicators) {
                    return n;
                }
            }
            n++;
        }
    }

private:
    vector<vector<Button>> GetButtonCombinationsOfLengthN(int n) {
        vector<vector<Button>> result;
        vector<Button> current;
        
        BacktrackCombinations(n, 0, current, result);
        return result;
    }

    void BacktrackCombinations(
        int n,
        int startIndex,
        vector<Button>& current,
        vector<vector<Button>>& result
    ) {
        if (current.size() == n) {
            result.push_back(current);
            return;
        }

        if (startIndex >= buttons.size()) {
            return;
        }

        for (int i = startIndex; i < buttons.size(); ++i) {
            current.push_back(buttons[i]);
            BacktrackCombinations(n, i + 1, current, result);
            current.pop_back();
        }
    }

    void ApplyButton(vector<bool>& currentState, Button& button) {
        for (int& affectedPosition : button.affectedPositions) {
            currentState[affectedPosition] = !currentState[affectedPosition];
        }
    }

public:
    vector<Button> buttons;
    vector<bool> goalStateIndicators;
    vector<int> goalStateJoltages;
};

vector<Machine> ParseInput() {
    vector<Machine> machines;

    ifstream file("input/input.txt");
    string str;
    while(getline(file, str)) {
        Machine machine;
        istringstream lineStream(str);
        string token;

        while (lineStream >> token) {

            // Inidicators
            if (token.front() == '[') {
                for (size_t i = 1; i + 1 < token.size(); ++i) {
                    if (token[i] == ']') break;

                    if (token[i] == '.') {
                        machine.goalStateIndicators.push_back(false);
                    } else if (token[i] == '#') {
                        machine.goalStateIndicators.push_back(true);
                    }
                }
            }

            // Buttons
            else if (token.front() == '(') {
                Button button;

                string inner = token.substr(1, token.size() - 2);
                stringstream values(inner);
                string value;

                while (getline(values, value, ',')) {
                    button.affectedPositions.push_back(stoi(value));
                }

                machine.buttons.push_back(button);
            }

            // Joltages
            else if (token.front() == '{') {
                string inner = token.substr(1, token.size() - 2);
                stringstream values(inner);
                string value;

                while (getline(values, value, ',')) {
                    machine.goalStateJoltages.push_back(stoi(value));
                }
            }
        }
        machines.push_back(machine);
    }
    return machines;
}

int Task1(vector<Machine>& machines) {
    int total = 0;
    for (Machine& machine : machines) {
        total += machine.SolveTask1();
    }
    return total;
}

int main() {
    vector<Machine> machines = ParseInput();
    cout << "Result from first task: " << Task1(machines) << endl;
    return 0;
}