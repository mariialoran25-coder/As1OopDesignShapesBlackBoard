#pragma once
#include "Shape.h"
class Board;
class Diamond : public Shape
{
private:
    int r_;
    int x, y;
    std::string mode_;
    std::string color_;
public:
    Diamond(int xx, int yy, int r, std::string mode, std::string color);
    std::string printList() const override;
    void updPrmtrs(int newr, int none) override;
    void updCoordinates(int newX, int newY) override;
    void setColor(const std::string& newColor)override;
    std::string serialise() override;
    void framedraw(Board& board) override;
    void draw(Board& board) override;
    bool contains(int px, int py)  override;
};
