#pragma once
#include "Board.h"
class Shape
{
private:
    int id_shape = 0;
public:
    virtual ~Shape() {}
    virtual void draw(Board& board) = 0;
    virtual std::string printList() const = 0;
    virtual void framedraw(Board& board) = 0;
    virtual bool contains(int px, int py) = 0;
    virtual void updPrmtrs(int newWidth, int newHeight) = 0;
    virtual void updCoordinates(int newX, int newY) = 0;
    virtual void setColor(const std::string& newColor) = 0;
    virtual std::string serialise() = 0;

};

