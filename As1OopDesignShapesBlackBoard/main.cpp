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
    virtual std::string getName() const = 0;
    virtual void draw(Board& board) =0 ;
    virtual std::string printList() const = 0;
    virtual void framedraw(Board& board) = 0;

};


class Triangle : public Shape
{
private:
    int w_;
    int h_;
    int x,y;
    std::string mode_;
    std::string color_;

public :
    Triangle(int xx, int yy, int w, int h, std::string mode, std::string color) : w_(w), h_(h), x(xx), y(yy), mode_(mode), color_(color) {}
    std::string printList() const override {
        return "[Triangle][X=" + std::to_string(x) + "][Y=" +std::to_string(y) + "][W=" + std::to_string(w_) + "][H=" + std::to_string(h_) + "]\n";
    }
    std::string getName() const override {
        return "triangle";
    }

    void framedraw(Board& board) override {
        for (int i = 0; i < h_; ++i) {
            int numStars = 2 * i + 1;
            for (int j = 0; j < numStars; ++j) {
                if (i == 0 || i == h_ - 1 || j == 0 || j == numStars - 1) {
                    int position = x - i + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        board.grid[y + i][position] = '*';
                }
            }
        }
    }

    void draw(Board& board) override
    {
        if (mode_ == "fill") {
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
        else {
            framedraw(board);
        }
    }

};


class Rectangle : public Shape
{
private:
    int w_;
    int h_;
    int x, y;
    std::string mode_;
    std::string color_;
public:
    Rectangle(int xx, int yy, int w, int h, std::string mode, std::string color) : w_(w), h_(h), x(xx), y(yy), mode_(mode), color_(color) { }
    std::string printList() const override {
        return "[Rectangle][X=" + std::to_string(x) + "][Y=" + std::to_string(y) + "]  [" + std::to_string(w_) + "][" + std::to_string(h_) + "]\n";
    }
    std::string getName() const override {
        return "rectangle";
    }
    void framedraw(Board& board) override {
        for (int i = 0; i < h_; ++i) {
            for (int j = 0; j < w_; ++j) {
                if (i == 0 || i == h_ - 1 || j == 0 || j == w_ - 1) {
                    int position = x + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        board.grid[y + i][position] = '*';
                }
            }
        }
    }


    void draw(Board& board) override
    {
        if (mode_ == "fill") {
            for (int i = 0; i < h_; ++i) {
                for (int j = 0; j < w_; ++j) {
                    int position = x + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        board.grid[y + i][position] = '*';
                }
            }
        }
        else {
            framedraw(board);
        }
    }
};

class Square : public Shape
{
private:
    int r_;
    int x, y;
    std::string mode_;
    std::string color_;
public:
    Square(int xx, int yy, int r, std::string mode, std::string color) : r_(r), x(xx), y(yy), mode_(mode), color_(color) {}
    std::string printList() const override {
         return "[Square][X=" + std::to_string(x) + "][Y=" + std::to_string(y) + "]  [" + std::to_string(r_) + "]\n";
    }
    std::string getName() const override {
        return "square";
    }
    void framedraw(Board& board) override {
        for (int i = 0; i < r_; ++i) {
            for (int j = 0; j < r_ * 2; ++j) {
                if (i == 0 || i == r_ - 1 || j == 0 || j == r_ * 2 - 2) {
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
    }
    void draw(Board& board) override
    {
        if (mode_ == "fill") {
            for (int i = 0; i < r_; ++i) {
                for (int j = 0; j < r_ * 2; ++j) {
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
        else {
            framedraw(board);
        }
    }
};



class Diamond : public Shape
{
private:
    int r_;
    int x, y;
    std::string mode_;
    std::string color_;
public:
    Diamond(int xx, int yy, int r, std::string mode, std::string color) : r_(r), x(xx), y(yy), mode_(mode), color_(color) {}
    std::string printList() const override {
        return "[Diamond][X=" + std::to_string(x) + "][Y=" + std::to_string(y) + "]  [" + std::to_string(r_) + "]\n";
    }
    std::string getName() const override {
        return "diamond";
    }
    void framedraw(Board& board) override {
        for (int i = 0; i < r_; ++i) {
            int Stars = 2 * i + 1;
            int upcircle = x - i;
            for (int j = 0; j < Stars; ++j) {
                if (i == 0 || i == r_ - 1 || j == 0 || j == Stars - 1) {
                    int positionUp = upcircle + j;
                    if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        board.grid[y + i][positionUp] = '*';
                }
            }
        }
        for (int i = 1; i < r_; ++i) {
            int Stars = 2 * (r_ - 1 - i) + 1;
            int downcircle = x - (r_ - 1 - i);
            for (int j = 0; j < Stars; ++j) {
                if (i == 0 || i == r_ - 1 || j == 0 || j == Stars - 1) {
                    int position = downcircle + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        board.grid[y + r_ + (i - 1)][position] = '*';
                }
            }
        }
    }
    void draw(Board& board)override
    {
        if (mode_ == "fill") {
            for (int i = 0; i < r_; ++i) {
                int Stars = 2 * i + 1;
                int upcircle = x - i;
                for (int j = 0; j < Stars; ++j) {
                    int positionUp = upcircle + j;
                    if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        board.grid[y + i][positionUp] = '*';
                }
            }
            for (int i = 1; i <= r_; ++i) {
                int Stars = 2 * (r_ - 1 - i) + 1;
                int downcircle = x - (r_ - 1 - i);
                for (int j = 0; j < Stars; ++j) {
                    int positionUp = downcircle + j;
                    if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        board.grid[y + r_ + (i - 1)][positionUp] = '*';
                }
            }
        }
        else {
            framedraw(board);
        }
    }
};


class Line :public Shape
{
private:
    int length_;
    bool isVertical_;
    int x, y;
    std::string mode_;
    std::string color_;

public:
    Line(int xx, int yy, int length, bool isVertical, std::string mode, std::string color) : length_(length), isVertical_(isVertical), x(xx), y(yy), mode_(mode), color_(color) {}
    std::string printList() const override {
        return "[Line][X=" + std::to_string(x) + "][Y=" + std::to_string(y) + "]  [" + std::to_string(length_) + "]\n";
    }
    std::string getName() const override {
        return "line";
    }
    void framedraw(Board& board) override {
        draw(board);
    }
    void draw(Board& board) override
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
    // x y w h
    Triangle triangle(8, 2, 1, 5, "fill", "pink");
    Rectangle rectangle(20, 2, 9, 4, "fill", "pink");
    Diamond diamond(25, 8, 5, "fill", "pink");
    Square square( 5, 10,5, "fill", "pink");
    Line line(1, 1, 5, true, "fill", "pink");


    std::vector<Shape*> shapes;
    shapes.push_back(&triangle);
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
            for (int i = 0; i < shapes.size();++i) {
                shapes[i]->draw(board);
            }
           

            //triangle.draw(board);
            //rectangle.draw(board);
            //diamond.draw(board);
            //square.draw(board);
            //line.draw(board);

            board.print();
            break;
        }
        case 2: {
            std::cout << "----List----\n";
            for (int i = 0; i < shapes.size(); ++i) {
                std::cout << "["<< i + 1<<"]" << shapes[i]->printList() << "\n";
            }
            break;
        }
        case 3: {
            std::cout << "----Shapes----\n";
            std::cout << "Triangle -- [x][y][width][height]\n";
            std::cout << "Rectangle -- [x][y][width][height]\n";
            std::cout << "Square -- [x][y][radius]\n";
            std::cout << "Diamond -- [x][y][radius]\n";
            std::cout << "Line -- [x][y][length][if line is Vertical - TRUE else FALSE]\n";
            break;
        }
        case 4 : {
            std::string formShape;
            std::string fillOrFrame;
            std::string color;
            int px, py;
            int pa , pb;
            std::cout << "----ADD----\n";
            std::cout << "Enter Shape: ";
            std::cin >> formShape;
            
            std::cout << "Enter Fill or Frame: ";
            std::cin >> fillOrFrame;

            std::cout << "Enter Color: ";
            std::cin >> color;

            std::cout << "Enter Location ('number1 x' 'num2 y'): ";
            std::cin >> px >> py;

            std::cout << "Enter Parameters : ";
            std::cin >> pa >> pb;

            std::cout << "Your Choice: [" << formShape << "][" << fillOrFrame << "][" << color << "][" << pa <<"  "<< pb << "]\n";
            
            
            if (formShape == "triangle") {
                shapes.push_back(new Triangle(px,py,pa,pb,fillOrFrame, color) );
            }
            if (formShape == "rectangle") {
                shapes.push_back(new Rectangle(px, py, pa, pb, fillOrFrame, color));
            }
            if (formShape == "square") {
                shapes.push_back(new Square(px, py, pa, fillOrFrame, color));
            }
            if (formShape == "diamond") {
                shapes.push_back(new Diamond(px, py, pa, fillOrFrame, color));
            }
            if (formShape == "line") {
                shapes.push_back(new Line(px, py, pa ,true, fillOrFrame, color));
            }

            break;

        }
        case 5: {
            for (int i = 0; i < shapes.size();++i) {
                shapes[i]->framedraw(board);
            }
            board.print();
            break;
        }
        case 10: {
            //shapes.clear();
            board = Board();
            std::cout << "Board is clear\n";
            break;
        }
               return 0;
        };
    }
}