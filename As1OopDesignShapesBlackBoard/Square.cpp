#include "Shape.h"
#include "Square.h"
Square::Square(int xx, int yy, int r, std::string mode, std::string color) : r_(r), x(xx), y(yy), mode_(mode), color_(color) {}
    std::string Square::printList() const  {
        return "[Square][X=" + std::to_string(x) + "][Y=" + std::to_string(y) + "]  [" + std::to_string(r_) + "][" + mode_ + "][" + color_ + "\n";
    }
    void Square::updPrmtrs(int newRadius, int none)  {
        r_ = newRadius;
    }
    void Square::updCoordinates(int newX, int newY)  {
        x = newX;
        y = newY;
    }
    void Square::setColor(const std::string& newColor) { color_ = newColor; }
    std::string Square::serialise()  {
        return "square " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(r_) + " " + mode_ + " " + color_ + "\n";
    }
    void Square::framedraw(Board& board)  {
        for (int i = 0; i < r_; ++i) {
            for (int j = 0; j < r_ * 2; ++j) {
                if (i == 0 || i == r_ - 1 || j == 0 || j == r_ * 2 - 2) {
                    int position = x + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        if (j % 2 == 0) {
                            board.setSym(position, y + i, '*', color_);
                        }
                        else {
                            board.setSym(position, y + i, ' ', color_);
                        }
                }
            }
        }
    }
    void Square::draw(Board& board) 
    {
        if (mode_ == "fill") {
            for (int i = 0; i < r_; ++i) {
                for (int j = 0; j < r_ * 2; ++j) {
                    int position = x + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        if (j % 2 == 0) {
                            board.setSym(position, y + i, '#', color_);
                        }
                        else {
                            board.setSym(position, y + i, ' ', color_);

                        }
                }
            }
        }
        else {
            framedraw(board);
        }
    }
    bool Square::contains(int px, int py)  {
        if (px < x || py < y || px >= x + (r_ * 2) || py >= y + r_) {
            return false;
        }

        if ((px - x) % 2 != 0) {
            return false;
        }
        if (mode_ == "fill") {
            return true;
        }
        return (py == y || py == y + r_ - 1 || px == x || px == x + r_ * 2 - 2);
    }


