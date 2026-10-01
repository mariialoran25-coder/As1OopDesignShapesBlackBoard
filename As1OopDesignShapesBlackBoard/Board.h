#pragma once
#include <vector> 
#include <iostream>
#include "string"
#include "ColorCode.h"

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

struct forBoard {
    char symbol = ' ';
    std::string color = "";
};


class Board {
private:
    std::vector<std::vector<forBoard>> grid;
public:
    Board();
    void setSym(int x, int y, char symbol, const std::string& color);
    void print();
    char getSym(int x, int y) const;
};
