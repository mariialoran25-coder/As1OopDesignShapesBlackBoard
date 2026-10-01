#pragma once
#include "Shape.h"
#include "Board.h"
class ConsoleMenu {
private:
    std::vector<Shape*> shapes;
    Board board;
    Shape* selectedShape = nullptr;
    static Shape* createShape(std::string& name, int x, int y, int p1, int p2, std::string& mode, std::string& color);
public:
    ConsoleMenu();
    void run();
    void printMenu();

    void createdShapes();
    void Draw1(Board& board);
    void List2();
    void Shapes3();
    void Add4();
    void Select5();
    void Remove6();
    void Edit7();
    void Paint8();
    void Move9();
    void Clean10();
    void Save11();
    void Load12();
};