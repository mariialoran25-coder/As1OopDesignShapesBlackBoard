#pragma once
#include <vector> 
#include <iostream>
#include "string"
#include "ColorCode.h"
#include "Board.h"

Board::Board() : grid(BOARD_HEIGHT, std::vector<forBoard>(BOARD_WIDTH)) {}
void Board::setSym(int x, int y, char symbol, const std::string& color) {
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
        grid[y][x].symbol = symbol;
        grid[y][x].color = color;
    }
}

void Board::print() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (!grid[i][j].color.empty()) {
                std::cout << ColorCode::GetColorCode(grid[i][j].color);
            }
            std::cout << grid[i][j].symbol;
            std::cout << "\033[0m";
        }
        std::cout << "\n";
    }
}

char Board::getSym(int x, int y) const {
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
        return grid[y][x].symbol;
    }
    return ' ';
}
