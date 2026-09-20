#include <iostream>
#include "string"
#include <vector> 
#include <sstream>
#include <fstream>

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

 
class Board {
public:
    std::vector<std::vector<char>> grid;
    Board() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

    void print() {
        for (auto& row : grid) {
            for (char c : row) {
                std::cout << c;
            }
            std::cout << "\n";
        }
    }
};

class Shape
{
private:
    int id_shape = 0;
public:
    virtual ~Shape() {}
    virtual void draw(Board& board, int x, int y) =0 ;
    virtual std::string printInfo() const = 0;

};


class Triangle : public Shape
{
private:
    int w_;
    int h_;

public :
    Triangle( int w, int h) : w_(w), h_(h){}
    std::string printInfo() const override {
        return "[Triangle][" + std::to_string(w_) + "][" + std::to_string(h_) + "]\n";
    }
    void draw(Board& board, int x, int y) override
    {
        for (int i = 0; i < h_; ++i) {
            int numStars = 2 * i + 1;
            int leftMost = x - i;
            for (int j = 0; j < numStars; ++j) {
                int position = leftMost + j;
                if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                    BOARD_HEIGHT && (y + i) >= 0)
                    board.grid[y + i][position] = '*';
            }
        }
    }
};


class Rectangle : public Shape
{
private:
    int w_;
    int h_;
public:
    Rectangle(int w, int h) : w_(w), h_(h){ }
    std::string printInfo() const override {
        return "[Rectangle][" + std::to_string(w_) + "][" + std::to_string(h_) + "]\n";
    }
    void draw(Board& board, int x, int y) override
    {
        for (int i = 0; i < h_; ++i) {
            for (int j = 0; j < w_; ++j) {
                int position = x + j;
                if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                    BOARD_HEIGHT && (y + i) >= 0)
                    board.grid[y + i][position] = '*';
            }
        }
    }
};

class Square : public Shape
{
private:
    int r_;
public:
    Square(int r) : r_(r) {}
    std::string printInfo() const override {
         return "[Square][" + std::to_string(r_) + "]\n";
    }
    void draw(Board& board, int x, int y) override
    {
        for (int i = 0; i < r_; ++i) {
            for (int j = 0; j < r_*2; ++j) {
                int position = x + j;
                if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                    BOARD_HEIGHT && (y + i) >= 0)
                    if (j % 2 == 0) {
                        board.grid[y + i][position] = '*';
                    }
                    else {
                        board.grid[y + i][position] = ' ';
                    }
            }
        }
    }
};



class Diamond : public Shape
{
private:
    int r_;
public:
    Diamond(int r): r_(r){}
    std::string printInfo() const override {
        return "[Diamond][" + std::to_string(r_) + "]\n";
    }
    void fordraw(Board& board, int x, int y) 
    {
        for (int i = 0; i < r_; ++i) {
            int Stars = 2 * i + 1;
            int upcircle = x - i;
            for (int j = 0; j < Stars; ++j) {
                int positionUp = upcircle + j;
                if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                    BOARD_HEIGHT && (y + i) >= 0)
                    board.grid[y+ i][positionUp] = '*';
            }
        }
    }
    void draw(Board& board, int x, int y)override
    {
        fordraw(board,x,y);
        for (int i = 1; i <= r_; ++i) {
            int Stars = 2 * (r_ -1- i) + 1;
            int downcircle = x - (r_-1 - i);
            for (int j = 0; j < Stars; ++j) {
                int positionUp = downcircle + j;
                if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                    BOARD_HEIGHT && (y + i) >= 0)
                    board.grid[y +r_+(i-1)][positionUp] = '*';
            }
        }
    }
};


class Line :public Shape
{
private:
    int length_;
    bool isVertical_;

public:
    Line(int length, bool isVertical) : length_(length), isVertical_(isVertical) {}
    std::string printInfo() const override {
        return "[Line][" + std::to_string(length_) + "]\n";
    }
    void draw(Board& board, int x, int y) override
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
                board.grid[current_y][current_x] = '*';
        }
    }
};

int main()
{
    Board board;

    Triangle triangle(1, 5);
    Rectangle rectangle(8, 2);
    Diamond diamond(5);
    Square square(5);
    Line line(5, true);


    std::vector<Shape*> shapes;
    shapes.push_back(&triangle);
    shapes.push_back(new Triangle( 1, 10));
    shapes.push_back(&rectangle);
    shapes.push_back(&diamond);
    shapes.push_back(&square);
    shapes.push_back(&line);

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n --Shapes blackboard ----- \n";
        std::cout << "1.Draw (Draw blackboard to the console )\n";
        std::cout << "2.List (Print all added shapes)\n";
        std::cout << "3.Shapes (Print a list of all available shapes and parameters for add call ) \n";
        std::cout << "4.Add (Add shape with specified colour and fill mode to the blackboard )\n";
        std::cout << "5.select (Select a shape with an ID or foreground shape by the selected coordinates)\n";
        std::cout << "6.remove (Remove the selected shape from the blackboard )\n";
        std::cout << "7.edit (Allows to modify the parameters of the selected figure. )\n";
        std::cout << "8.paint (Change the colour of the selected figure )\n";
        std::cout << "9.move (Move the selected shape to the coordinates. )\n";
        std::cout << "10.clear (Remove all shapes from blackboard )\n";
        std::cout << "11.save (Save to the file)\n";
        std::cout << "12.load (Load to the file)\n";
        std::cout << "Choose an action: ";
        std::cin >> choice;
        std::cin.ignore();


        switch (choice) {
        case 1: {
            //for (int i = 0; i < shapes.size();++i) {
            //    shapes[i]->draw(board,);
            //}
            triangle.draw(board, 8, 2);
            rectangle.draw(board, 20, 2);
            diamond.draw(board, 25, 8);
            square.draw(board, 5, 10);
            line.draw(board, 1, 1);

            board.print();
            break;
        }
        case 2: {
            std::cout << "----Info----\n";
            for (int i = 0; i < shapes.size(); ++i) {
                std::cout << "["<< i + 1<<"]" << shapes[i]->printInfo() << "\n";
            }
            break;
        }
        case 3: {
            break;
        }
              return 0;
        };
    }
}