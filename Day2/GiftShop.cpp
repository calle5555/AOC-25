#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define very_large_type unsigned long long

struct Input {
    very_large_type firstId;
    very_large_type lastId;
};

std::vector<Input> ParseInputFile() {
    std::ifstream file("input/input.txt");
    std::string str;

    std::vector<Input> input;
    while(std::getline(file, str, ',')){
        const int delimIndex = str.find('-');
        const very_large_type firstId = std::stoll(str.substr(0, delimIndex));
        const very_large_type lastId = std::stoll(str.substr(delimIndex + 1));
        input.push_back({firstId, lastId});
    }
    return input;
}

very_large_type Task1(const std::vector<Input>& input) {
    very_large_type invalidSum = 0;
    for (const auto&[firstId, lastId] : input) {
        for (very_large_type j = firstId; j <= lastId; j++) {
            std::string curNum = std::to_string(j);
            if (curNum.length() % 2 == 1) continue;

            std::string str1 = curNum.substr(0, (curNum.length() / 2));
            std::string str2 = curNum.substr(curNum.length() / 2);

            if (str1 == str2) {
                invalidSum += j;
            }
        }
    }
    return invalidSum;
}

very_large_type Task2(const std::vector<Input>& input) {
    very_large_type invalidSum = 0;

    std::vector<std::string> invalidStrings;
    for (const auto&[firstId, lastId] : input) {
        for (very_large_type j = firstId; j <= lastId; j++) {

            std::string curNum = std::to_string(j);
            for (int k = 1; k <= curNum.length()/2; k++) {
                if (curNum.length() % k != 0) continue;

                std::vector<std::string> splits;
                int curIndex = 0;
                while (curIndex < curNum.length()) {
                    splits.push_back(curNum.substr(curIndex, k));
                    curIndex += k;
                }

                bool isInvalid = true;
                std::string curString = splits[0];
                for (int i = 1; i < splits.size(); i++) {
                    if (curString == splits[i]) continue;

                    isInvalid = false;
                    break;
                }

                if (isInvalid) {
                    invalidStrings.push_back(curNum);
                    invalidSum += j;
                    break;
                }
            }
        }
    }
    return invalidSum;
}

int main() {
    const std::vector<Input> input = ParseInputFile();
    std::cout << "Result from first Task: " << Task1(input) << std::endl;
    std::cout << "Result from second Task: " << Task2(input) << std::endl;
    return 0;
}