#pragma once
#include "Rectangle.h"
Rectangle::Rectangle(int xx, int yy, int w, int h, std::string mode, std::string color) : w_(w), h_(h), x(xx), y(yy), mode_(mode), color_(color) {}
  
    std::string Rectangle::printList() const {
        return "[Rectangle][X=" + std::to_string(x) + "][Y=" + std::to_string(y) + "]  [" + std::to_string(w_) + "][" + std::to_string(h_) + "][" + mode_ + "][" + color_ + "\n";
    }
    void Rectangle::updPrmtrs(int newWidth, int newHeight) {
        w_ = newWidth;
        h_ = newHeight;
    }
    void Rectangle::updCoordinates(int newX, int newY) {
        x = newX;
        y = newY;
    }
    void Rectangle::setColor(const std::string& newColor) { color_ = newColor; }
    std::string Rectangle::serialise() {
        return "rectangle " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(w_) + " " + std::to_string(h_) + " " + mode_ + " " + color_ + "\n";
    }
    void Rectangle::framedraw(Board& board) {
        for (int i = 0; i < h_; ++i) {
            for (int j = 0; j < w_; ++j) {
                if (i == 0 || i == h_ - 1 || j == 0 || j == w_ - 1) {
                    int position = x + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                    {
                        board.setSym(position, y + i, '=', color_);
                    }
                }
            }
        }
    }
    void Rectangle::draw(Board& board)
    {
        if (mode_ == "fill") {
            for (int i = 0; i < h_; ++i) {
                for (int j = 0; j < w_; ++j) {
                    int position = x + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0) {
                        board.setSym(position, y + i, '=', color_);
                    }
                }
            }
        }
        else {
            framedraw(board);
        }
    }
    bool Rectangle::contains(int px, int py)  {
        if (px < x || py < y || px >= x + w_ || py >= y + h_) {
            return false;
        }

        if (mode_ == "fill") {
            return true;
        }
        else if (py == y || py == y + h_ - 1 || px == x || px == x + w_ - 1) {
            return true;
        }
        return false;
    }

