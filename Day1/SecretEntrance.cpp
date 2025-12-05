#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int Task1(int dial_value)
{
    int amount_of_zeros = 0;
    
    int direction;
    int steps;

    std::ifstream file("input/task1.txt");
    std::string str;
    while(std::getline(file, str))
    {
        direction = (str.at(0) == 'L') ? -1 : 1;
        steps = stoi(str.erase(0,1)) % 100;
        
        dial_value = (dial_value + direction * steps) % 100;
        if(dial_value == 0) amount_of_zeros++;
    }
    return amount_of_zeros;
}

int Task2(int dial_value)
{
    int amount_of_zeros = 0;

    std::ifstream file("input/task1.txt");
    std::string str;
    
    int direction;
    int steps;
    int prev_dial;
    while(std::getline(file, str))
    {
        direction = (str.at(0) == 'L') ? -1 : 1;
        steps = stoi(str.erase(0,1));

        amount_of_zeros += int(steps/100);
        steps %= 100;

        prev_dial = dial_value;
        dial_value += direction * steps;
        if(dial_value < 0){
            if(prev_dial != 0) amount_of_zeros++;
            dial_value += 100;
        } 
        else if(dial_value > 100){
            dial_value = dial_value - 100;
            amount_of_zeros++;
        } else if(dial_value == 100){
            dial_value = dial_value - 100;
        }

        if(dial_value == 0) amount_of_zeros++;
    }
    return amount_of_zeros;
}

int main()
{
    int start_value = 50;
    std::cout << "Result Task 1: " << Task1(start_value) << std::endl;
    std::cout << "Result Task 2: " << Task2(start_value) << std::endl;

    return 0;
}