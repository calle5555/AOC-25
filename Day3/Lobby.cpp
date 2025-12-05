#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int FindLargestNumberInStringIndex(std::string str) {
    int maxJoltage = 0;
    int index = 0;
    for (int i = 0; i < str.length(); i++) {
        int curJoltage = std::stoi(str.substr(i, 1));
        if (curJoltage > maxJoltage) {
            maxJoltage = curJoltage;
            index = i;
        }
    }
    return index;
}

long long SolveTask(int amountOfBatteries) {
    long long totalJoltage = 0;

    std::ifstream file("input/input.txt");
    std::string str;
    while(std::getline(file, str)) {

        std::string maxJoltage = "";
        std::vector<int> indices{};
        for(int i = 0; i < amountOfBatteries; i++) {
            int lastIndex = indices.empty() ? -1 : indices.back();

            int maxJoltIndex = lastIndex + 1 + FindLargestNumberInStringIndex(str.substr(lastIndex + 1));
            while (str.length() - maxJoltIndex < amountOfBatteries - i) {
                maxJoltIndex = lastIndex + 1 + FindLargestNumberInStringIndex(str.substr(lastIndex + 1, maxJoltIndex - lastIndex - 1));
            }

            indices.push_back(maxJoltIndex);
            maxJoltage.append(str.substr(maxJoltIndex, 1));
        }
        totalJoltage += std::stoll(maxJoltage);
    }
    return totalJoltage;
}

int main() {
    std::cout << "Result from first task: " << SolveTask(2) << std::endl;
    std::cout << "Result from second task: " << SolveTask(12) << std::endl;
    return 0;
}