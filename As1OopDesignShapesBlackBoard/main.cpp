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
    virtual ~Shape() {}
    virtual double area() const = 0;
    virtual void draw(Board& board, int x, int y) =0 ;
};


class Triangle : public Shape
{
private:
    int w_;
    int h_;
public :
    Triangle(int w, int h) : w_(w), h_(h){}
    double area() const override
    {
        return w_ * h_;
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
    double area() const override
    {
        return w_ * h_;
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
    double area() const override
    {
        return r_ * r_;
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
    double area() const override
    {
        return 3.14159 * r_ * r_;
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
    double area() const override
    {
        return length_;
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



void printArea(const Shape& s)
{
    std::cout << "area = " << s.area() << "\n";
}

//void listOfShapes(const Shape& s) 
//{
//    std::vector<Shape> tokens = lexer.tokenize();
//        for (size_t i = 0; i < tokens.size();++i) {
//            if (tokens[i].type != TokenType::EndOfFile) {
//                std::cout << " Token: " << tokens[i].value << std::endl;
//            }
//        }
//}


int main()
{

    Board board;
    //відступ по х, відступ згори 
    
    Triangle triangle(1, 5);    
    triangle.draw(board, 8, 2);

    Rectangle rectangle(8, 2);
    rectangle.draw(board, 20, 2);

    Diamond diamond(5);
    diamond.draw(board, 25, 8);

    Square square(5);
    square.draw(board, 5, 10);

    Line line(5, true);
    line.draw(board, 1, 1);

    board.print();



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
        std::cout << "Choose an action";
        std::cin >> choice;
        std::cin.ignore();


        switch (choice) {
        case 1: {
            board.print();
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
              return 0;
        };
    }
}
//
//
//class Circle : public Shape
//{
//private:
//    int r_;
//public:
//    Circle(int r) : r_(r) {}
//    double area() const override
//    {
//        return 3.14159 * r_ * r_;
//    }
//    void fordraw(Board& board, int x, int y)
//    {
//        for (int i = 0; i <= r_; ++i) {
//            int Stars = 2 * i + 1;
//            int upcircle = x - i;
//            for (int j = 0; j < Stars; ++j) {
//                int positionUp = upcircle + j;
//                if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
//                    BOARD_HEIGHT && (y + i) >= 0)
//                    board.grid[y - r_ + i][positionUp] = '*';
//            }
//        }
//    }
//    void draw(Board& board, int x, int y)override
//    {
//        fordraw(board, x, y);
//        for (int i = 0; i <= r_; ++i) {
//            int Stars = 2 * (r_ - 1 - i) + 1;
//            int downcircle = x - (Stars / 2);
//            for (int j = 0; j < Stars; ++j) {
//                int positionUp = downcircle + j;
//                if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
//                    BOARD_HEIGHT && (y + i) >= 0)
//                    board.grid[y + 1][positionUp] = '*';
//            }
//        }
//    }
//
//};

//Circle circle(4);
//circle.draw(board, 10, 5);