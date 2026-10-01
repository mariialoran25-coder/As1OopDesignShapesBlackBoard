#include "Shape.h"
#include "Line.h"

Line::Line(int xx, int yy, int length, bool isVertical, std::string mode, std::string color) : length_(length), isVertical_(isVertical), x(xx), y(yy), mode_(mode), color_(color) {}
   
    std::string Line::printList() const {
        return "[Line][X=" + std::to_string(x) + "][Y=" + std::to_string(y) + "]  [" + std::to_string(length_) + "][" + mode_ + "][" + color_ + "]\n";
    }
    void Line::framedraw(Board& board) {
        draw(board);
    }
    void Line::updPrmtrs(int newl, int none) {
        length_ = newl;
    }
    void Line::updCoordinates(int newX, int newY) {
        x = newX;
        y = newY;
    }
    void Line::setColor(const std::string& newColor) { color_ = newColor; }

    std::string Line::serialise()  {
        return "line " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(length_) + " " + std::to_string(isVertical_) + " " + mode_ + " " + color_ + "\n";
    }
    void Line::draw(Board& board) 
    {
        for (int i = 0; i < length_; ++i) {
            int current_x = x;
            int current_y = y;
            if (isVertical_) {
                current_y = y + i;
            }
            else {
                current_x = x + i;
            }
            if (current_x >= 0 && current_x < BOARD_WIDTH && current_y >= 0 && current_y < BOARD_HEIGHT)
                if (isVertical_) {
                    board.setSym(current_x, current_y, '|', color_);
                }
                else {
                    board.setSym(current_x, current_y, '-', color_);
                }
        }
    }
    bool Line::contains(int px, int py){
        if (isVertical_) {
            return (px == x && py >= y && py < y + length_);
        }
        else {
            return (py == y && px >= x && px < x+length_ );
        }
        
    }
