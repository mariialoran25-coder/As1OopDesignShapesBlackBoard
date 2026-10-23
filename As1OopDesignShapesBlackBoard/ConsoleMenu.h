#pragma once
#include "Shape.h"
#include "Board.h"
class ConsoleMenu {
private:
    std::vector<std::unique_ptr<Shape>> shapes;
    Board board;
    Shape* selectedShape = nullptr;
    std::unique_ptr<Shape> createShape(const std::string& shapeName, std::istream& in);
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