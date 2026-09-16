#include <iostream>
#include <vector> 

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
    virtual ~Shape()
    {

    }
    virtual double area() const = 0;
    virtual void draw(Board& board, int x, int y, int height) =0 ;
};


class Circle : public Shape
{
private:
    double r_;
public:
    Circle(double r)
        : r_(r)
    {
    }
    double area() const override
    {
        return 3.14159 * r_ * r_;
    }

    void draw(Board& board, int x, int y, int height) override
    {
      // to be continue 
    }
};


class Triangle : public Shape
{
private:
    double w_;
    double h_;
public :
    Triangle(double w, double h) : w_(w), h_(h){}
    double area() const override
    {
        return w_ * h_;
    }
    void draw(Board& board, int x, int y, int height) override
    {
        for (int i = 0; i < height; ++i) {
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
    double w_;
    double h_;
public:
    Rectangle(double w, double h)
        : w_(w), h_(h)
    {
    }
    double area() const override
    {
        return w_ * h_;
    }
};
void printArea(const Shape& s)
{
    std::cout << "area = " << s.area() << "\n";
}


class Square : public Shape 
{
private:
    double a_;
public:
    Square(double a) : a_(a){}
    double area() const override {
        return a_ * a_;
    }
};


int main()
{
    //Circle c(2.0);

    Board board;
    Triangle triangle(10.0, 5.0);    // Triangle at top-left corner 
    triangle.draw(board, 10, 2, 5);
    board.print();

    return 0;
};
