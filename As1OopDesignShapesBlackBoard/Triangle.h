#pragma once
#include "Shape.h"
class Board;
class Triangle : public Shape
{
private:
    int w_;
    int h_;
    int x, y;
    std::string mode_;
    std::string color_;
public:
    Triangle(int xx, int yy, int w, int h, std::string mode, std::string color) ;
    std::string printList() const override;
    void updPrmtrs(int newWidth, int newHeight) override;
    void updCoordinates(int newX, int newY) override;
    void setColor(const std::string& newColor)override;
    std::string serialise() override;
    void framedraw(Board& board) override;
    void draw(Board& board) override;
    bool contains(int px, int py)  override;
};
