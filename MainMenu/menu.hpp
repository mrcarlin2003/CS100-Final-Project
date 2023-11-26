#ifndef MENU_HPP
#define MENU_HPP
#include <string>
#include <iostream>
#include "../inputmanager.hpp"

using namespace std;

class Menu : public InputManager {
    private:
        string menuDisplay = "2048 \n \n Start Game \n Settings \n Leaderboard \n Quit";
    public:
        void print();
        void getInput();
        char returnInput();
        void clearInput();
        string getMenuDisplay(); // for testing
};

#endif