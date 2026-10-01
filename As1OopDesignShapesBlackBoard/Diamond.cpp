#include "Shape.h"
#include "Diamond.h"
Diamond::Diamond(int xx, int yy, int r, std::string mode, std::string color) : r_(r), x(xx), y(yy), mode_(mode), color_(color) {}
std::string Diamond::printList() const {
    return "[Diamond][X=" + std::to_string(x) + "][Y=" + std::to_string(y) + "]  [" + std::to_string(r_) + "][" + mode_ + "][" + color_ + "]\n";
}
void Diamond::updPrmtrs(int newr, int none) {
    r_ = newr;
}
void Diamond::updCoordinates(int newX, int newY) {
    x = newX;
    y = newY;
}
void Diamond::setColor(const std::string& newColor) { color_ = newColor; }
std::string Diamond::serialise() {
    return "diamond " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(r_) + " " + mode_ + " " + color_ + "\n";
}
void Diamond::framedraw(Board& board)  {
    for (int i = 0; i < r_; ++i) {
        int Stars = 2 * i + 1;
        int upcircle = x - i;

        for (int j = 0; j < Stars; ++j) {
            if (i == 0 || i == r_ - 1 || j == 0 || j == Stars - 1) {
                int positionUp = upcircle + j;
                if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                    BOARD_HEIGHT && (y + i) >= 0) {
                    board.setSym(positionUp, y + i, '*', color_);
                }
            }
        }
    }
    for (int i = 1; i < r_; ++i) {
        int Stars = 2 * (r_ - 1 - i) + 1;
        int downcircle = x - (r_ - 1 - i);
        for (int j = 0; j < Stars; ++j) {
            if (i == 0 || i == r_ - 1 || j == 0 || j == Stars - 1) {
                int position = downcircle + j;
                int posX = y + r_ + (i - 1);
                if (position >= 0 && position < BOARD_WIDTH && posX <
                    BOARD_HEIGHT && posX >= 0) {
                    board.setSym(position, posX, '*', color_);
                }
            }
        }
    }
};
void Diamond::draw(Board& board) 
{
    if (mode_ == "fill") {
        for (int i = 0; i < r_; ++i) {
            int Stars = 2 * i + 1;
            int upcircle = x - i;
            for (int j = 0; j < Stars; ++j) {
                int positionUp = upcircle + j;
                if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                    BOARD_HEIGHT && (y + i) >= 0) {
                    board.setSym(positionUp, y + i, '*', color_);

                }

            }
        }
        for (int i = 1; i <= r_; ++i) {
            int Stars = 2 * (r_ - 1 - i) + 1;
            int downcircle = x - (r_ - 1 - i);
            for (int j = 0; j < Stars; ++j) {
                int positionUp = downcircle + j;
                int posY = y + r_ + (i - 1);
                if (positionUp >= 0 && positionUp < BOARD_WIDTH && posY <
                    BOARD_HEIGHT && posY >= 0) {
                    board.setSym(positionUp, posY, '*', color_);

                }
            }
        }
    }
    else {
        Diamond::framedraw(board);
    }
}
bool Diamond::contains(int px, int py)   {
    if (px < x || py < y || px >= x - r_ + (2 * r_ + 1) || py >= y + r_ || px >= x - (r_ - 1 - r_) + (2 * (r_ - 1 - r_ + 1)) || py >= y + r_ + (r_ - 1)) {
        return false;
    }
    if (mode_ == "fill") {
        return true;
    }
    else if (py == y || py >= y + (r_ - 1) || px == x || px >= x - r_ + (2 * r_ + 1) - 1 || px >= x - (r_ - 1 - r_) + (2 * (r_ - 1 - r_) + 1) - 1 || py >= y + r_ + (r_ - 1)) {
    }
    return true;
}
