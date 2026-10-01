#include "Shape.h"
#include "Triangle.h"
Triangle::Triangle(int xx, int yy, int w, int h, std::string mode, std::string color) : w_(w), h_(h), x(xx), y(yy), mode_(mode), color_(color) {}
std::string Triangle::printList() const  {
    return "[Triangle][X=" + std::to_string(x) + "][Y=" + std::to_string(y) + "][W=" + std::to_string(w_) + "][H=" + std::to_string(h_) + "][" + mode_ + "][" + color_ + "]\n";
}
void Triangle::updPrmtrs(int newWidth, int newHeight)  {
    w_ = newWidth;
    h_ = newHeight;
}
void  Triangle::updCoordinates(int newX, int newY)  {
    x = newX;
    y = newY;
}
void  Triangle::setColor(const std::string& newColor) { color_ = newColor; }
std::string  Triangle::serialise()  {
    return "triangle " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(w_) + " " + std::to_string(h_) + " " + mode_ + " " + color_ + "\n";
}
void  Triangle::framedraw(Board& board) {
    for (int i = 0; i < h_; ++i) {
        int numStars = 2 * i + 1;
        for (int j = 0; j < numStars; ++j) {
            if (i == 0 || i == h_ - 1 || j == 0 || j == numStars - 1) {
                int position = x - i + j;
                if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                    BOARD_HEIGHT && (y + i) >= 0) {
                    board.setSym(position, y + i, '=', color_);
                    //board.grid[y + i][position].symbol = '#';
                    //board.grid[y + i][position].color = color_;
                }
            }
        }
    }
}
void  Triangle::draw(Board& board)
{
    if (mode_ == "fill") {
        for (int i = 0; i < h_; ++i) {
            int numStars = 2 * i + 1;
            int leftMost = x - i;
            for (int j = 0; j < numStars; ++j) {
                int position = leftMost + j;
                if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                    BOARD_HEIGHT && (y + i) >= 0) {
                    board.setSym(position, y + i, '#', color_);
                }
            }
        }
    }
    else {
        framedraw(board);
    }
}
bool  Triangle::contains(int px, int py) {
    if (px < x || py < y || px >= (x - h_) + 2 * h_ + 1 || py >= y + h_) {
        return false;
    }

    if (mode_ == "fill") {
        return true;
    }
    else if (py == y || py == y + (h_ - 1) || px == x || px == x - h_ + (2 * h_ + 1)) {
        return true;
    }
    return false;
};
