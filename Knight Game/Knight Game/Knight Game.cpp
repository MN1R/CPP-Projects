#include <iostream>
#include <string>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <signal.h>
#include <Windows.h>

#include "Knight.h"
#include "Errors.h"


//system("CLS") is clearing the console
void clearConsole()
{
    system("CLS");
}

//detecting Ctrl + C
void getSignalCallback(int signal_number)
{
    std::cout << "\nCltr + C detected by signal number: " << signal_number;

    exit(COPY_SIGNAL_DETECTED);
}

//gettign random numbers over min and max values
int getRandomNumber(const int minimal_value, const int maximal_value)
{
    std::random_device rd;
    std::mt19937 mersenne(rd());

    return (mersenne() % maximal_value) + minimal_value;
}


//returning the result of starting question
std::string getStartAnswer()
{
    std::string answer_for_request;
    std::cin >> answer_for_request;
    
    //checking for user input
    while (std::cin.fail() || (answer_for_request != "yes" && answer_for_request != "no"))
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');

        std::cout << "Enter the correct answer: ";
        std::cin >> answer_for_request;
    }

    return answer_for_request;
}

//showing, should we start the game or not
bool shouldStartGame()
{
    std::cout << "Do u wanna play the game? Answer yes or no: ";

    return getStartAnswer() == "yes";
}


//getting how hard will be our text
int getLevelOfHard()
{
    std::cout << "Select level of hard over 1 to 5: ";
    
    int level_of_hard;
    std::cin >> level_of_hard;

    while (std::cin.fail() || (level_of_hard < 1 || level_of_hard > 5))
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');

        std::cout << "Enter the correct answer: ";
        std::cin >> level_of_hard;
    }
    
    return level_of_hard;
}

//returning the word, which u should text 
std::string getTaskWord(const int level_of_hard)
{
    const char CHARS_ARRAY[]{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'
                              ,'n','o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    const int CHARS_ARRAY_LENGTH = sizeof(CHARS_ARRAY) / sizeof(CHARS_ARRAY[0]);
    
    const int CHARS_BY_LEVEL_OF_HARD = 5;
    std::string task_word = "";


    for (int current_char = 0; current_char < CHARS_BY_LEVEL_OF_HARD * level_of_hard; ++current_char)
    {
        task_word += CHARS_ARRAY[getRandomNumber(0, CHARS_ARRAY_LENGTH)];
    }

    return task_word;
}


bool isTaskCompleted(const std::string &task_word, const float time_limit)
{
    //its has time and word correct check
    std::string user_word;
    time_t start_time = std::time(NULL);

    std::cin >> user_word;
    time_t time_after_writting = std::time(NULL);

    return user_word == task_word && (time_after_writting - start_time < time_limit);
}


int main()
{
    //detecting ctrl+c
    signal(SIGINT, getSignalCallback);

    Knight my_knight;

    //continue game while knight is alive
    while(shouldStartGame() && my_knight.getHealth() > 0)
    {   
        //starting
        std::string task_word = getTaskWord(getLevelOfHard());

        //calculating given time
        const float TIME_FOR_CHAR = 0.8;
        float task_time = task_word.length() * TIME_FOR_CHAR;

        std::cout << "Faster!!! Text this word:   " << task_word << "   u have " << task_time << " seconds to do that: ";

        //updating knight data after win/lose
        if (isTaskCompleted(task_word, task_time))
        {
            std::cout << "Good job, you won!\n";

            int EXPIRIENCE_BY_WIN = 5;
            my_knight.setExpirience(my_knight.getExpirience() + EXPIRIENCE_BY_WIN);

            int HEALTH_BY_WIN = 3;
            my_knight.setHealth(my_knight.getHealth() + HEALTH_BY_WIN);
        }
        else
        {
            std::cout << "Try agian, you losed!\n";

            int EXPIRIENCE_BY_LOSE = -3;
            my_knight.setExpirience(my_knight.getExpirience() + EXPIRIENCE_BY_LOSE);

            int HEALTH_BY_LOSE = -2;
            my_knight.setHealth(my_knight.getHealth() + HEALTH_BY_LOSE);
        }

        std::cout << "Now your knight has: " << my_knight.getHealth() << " health and " << my_knight.getExpirience() << " expirience.\n";
        
        Sleep(1500);
        clearConsole();
    }

    std::cout << "See you later!";
    exit(GAME_HAS_NOT_STARTED);
}
