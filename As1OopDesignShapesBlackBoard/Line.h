#pragma once
#include "Shape.h"
class Board;
class Line :public Shape
{
private:
    int length_;
    bool isVertical_;
    int x, y;
    std::string mode_;
    std::string color_;

public:
    Line(int xx, int yy, int length, bool isVertical, std::string mode, std::string color);
    std::string printList() const override;
    void framedraw(Board& board) override;
    void updPrmtrs(int newl, int none) override;
    void updCoordinates(int newX, int newY) override;
    void setColor(const std::string& newColor)override;
    std::string serialise() override;
    void draw(Board& board) override;
    bool contains(int px, int py)  override;
};