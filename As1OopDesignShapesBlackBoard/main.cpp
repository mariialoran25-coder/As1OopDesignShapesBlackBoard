#include <iostream>
#include "string"
#include <vector> 
#include <sstream>
#include <fstream>

class ColorCode {
private:
    struct ColorPair {
        std::string name;
        std::string code;
    };
public:
    static std::string GetColorCode(const std::string& colorName) {
        if (colorName == "red") return "\033[31m";
        if (colorName == "blue")return "\033[34m";
        if (colorName == "yellow") return "\033[33m";
        if (colorName == "green") return "\033[32m";
        if (colorName == "black") return "\033[30m";
        if (colorName == "pink") return "\033[38;2;255;192;203m";
        return "\033[0m";
    }
};

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

struct forBoard {
    char symbol = ' ';
    std::string color = "";
};
 
class Board {
public:
    std::vector<std::vector<forBoard>> grid;
    Board() : grid(BOARD_HEIGHT, std::vector<forBoard>(BOARD_WIDTH)) {}
    void print() {
        for (int i = 0; i < BOARD_HEIGHT; ++i) {
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                if (!grid[i][j].color.empty()) {
                    std::cout << ColorCode::GetColorCode(grid[i][j].color);
                }
                std::cout << grid[i][j].symbol;
                std::cout << "\033[0m";
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
    virtual bool contains(int px, int py)=0;
    virtual void updPrmtrs(int newWidth,int newHeight ) = 0;
    virtual void updCoordinates(int newX, int newY) = 0;
    virtual void setColor(const std::string& newColor) = 0;



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
    void updPrmtrs(int newWidth, int newHeight) override {
            w_ = newWidth;
            h_ = newHeight;
    }
    void updCoordinates(int newX, int newY) override {
        x = newX;
        y = newY;
    }
    void setColor(const std::string& newColor)override { color_ = newColor; }

    void framedraw(Board& board) override {
        for (int i = 0; i < h_; ++i) {
            int numStars = 2 * i + 1;
            for (int j = 0; j < numStars; ++j) {
                if (i == 0 || i == h_ - 1 || j == 0 || j == numStars - 1) {
                    int position = x - i + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        board.grid[y + i][position].symbol = '#';
                        board.grid[y + i][position].color = color_;
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
                        
                        board.grid[y + i][position].symbol = '#';
                        board.grid[y + i][position].color = color_;
                        
                }
            }
        }
        else {
            framedraw(board);
        }
    }
    bool contains(int px, int py)  override {
        if (px < x || py < y || px >= (x - h_)+2*h_+1 || py >= y + h_) {
            return false;
        }

        if (mode_ == "fill") {
            return true;
        }
        else if (py == y || py == y + (h_ - 1) || px == x || px == x - h_ + (2 * h_ + 1)) {
            return true;
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
    void updPrmtrs(int newWidth, int newHeight) override {
        w_ = newWidth;
        h_ = newHeight;
    }
    void updCoordinates(int newX, int newY) override {
        x = newX;
        y = newY;
    }
    void setColor(const std::string& newColor)override { color_ = newColor; }
    void framedraw(Board& board) override {
        for (int i = 0; i < h_; ++i) {
            for (int j = 0; j < w_; ++j) {
                if (i == 0 || i == h_ - 1 || j == 0 || j == w_ - 1) {
                    int position = x + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                    
                        board.grid[y + i][position].symbol = '=';
                        board.grid[y + i][position].color = color_;
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
                        board.grid[y + i][position].symbol = '=';
                        board.grid[y + i][position].color = color_;
                }
            }
        }
        else {
            framedraw(board);
        }
    }
    bool contains(int px, int py)  override {
        if (px < x || py < y || px >= x + w_ || py >= y + h_) {
            return false;
        }

        if (mode_ == "fill") {
            return true;
        }
        else if (py == y || py == y + h_ -1 || px == x || px == x + w_ - 1) {
            return true;
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
    void updPrmtrs(int newRadius, int none) override {
        r_ = newRadius;
    }
    void updCoordinates(int newX, int newY) override {
        x = newX;
        y = newY;
    }
    void setColor(const std::string& newColor)override { color_ = newColor; }
    void framedraw(Board& board) override {
        for (int i = 0; i < r_; ++i) {
            for (int j = 0; j < r_ * 2; ++j) {
                if (i == 0 || i == r_ - 1 || j == 0 || j == r_ * 2 - 2) {
                    int position = x + j;
                    if (position >= 0 && position < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        if (j % 2 == 0) {
                            board.grid[y + i][position].symbol = '*';
                            board.grid[y + i][position].color = color_;
                        }
                        else {
                            board.grid[y + i][position].symbol = ' ';
                            //board.grid[y + i][position].color = color_;
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
                           // board.grid[y + i][position] = '#';
                            board.grid[y + i][position].symbol = '#';
                            board.grid[y + i][position].color = color_;
                        }
                        else {
                            //board.grid[y + i][position] = ' ';
                            board.grid[y + i][position].symbol = ' ';
                            board.grid[y + i][position].color = color_;
                        }
                }
            }
        }
        else {
            framedraw(board);
        }
    }
    bool contains(int px, int py)  override {
        if (px < x || py < y || px >= x + (r_ * 2) || py >= y + r_) {
            return false;
        }

        if ((px -x ) % 2 != 0) {
            return false;
        }
        if (mode_ == "fill") {
            return true;
        }
        return (py == y || py == y + r_ - 1 || px == x || px == x + r_ * 2 - 2);
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
    void updPrmtrs(int newr, int none) override {
        r_ = newr;
    }
    void updCoordinates(int newX, int newY) override {
        x = newX;
        y = newY;
    }
    void setColor(const std::string& newColor)override { color_ = newColor; }
    void framedraw(Board& board) override {
        for (int i = 0; i < r_; ++i) {
            int Stars = 2 * i + 1;
            int upcircle = x - i;
            for (int j = 0; j < Stars; ++j) {
                if (i == 0 || i == r_ - 1 || j == 0 || j == Stars - 1) {
                    int positionUp = upcircle + j;
                    if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                       // board.grid[y + i][positionUp] = '*';
                        board.grid[y + i][positionUp].symbol = '*';
                        board.grid[y + i][positionUp].color = color_;
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
                      //  board.grid[y + r_ + (i - 1)][position] = '*';
                    board.grid[y + r_ + (i - 1)][position].symbol = '*';
                    board.grid[y + r_ + (i - 1)][position].color = color_;
                }
            }
        }
    };
    void draw(Board& board) override
    {
        if (mode_ == "fill") {
            for (int i = 0; i < r_; ++i) {
                int Stars = 2 * i + 1;
                int upcircle = x - i;
                for (int j = 0; j < Stars; ++j) {
                    int positionUp = upcircle + j;
                    if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                       // board.grid[y + i][positionUp] = '*';
                    board.grid[y +i][positionUp].symbol = '*';
                    board.grid[y + i][positionUp].color = color_;


                }
            }
            for (int i = 1; i <= r_; ++i) {
                int Stars = 2 * (r_ - 1 - i) + 1;
                int downcircle = x - (r_ - 1 - i);
                for (int j = 0; j < Stars; ++j) {
                    int positionUp = downcircle + j;
                    if (positionUp >= 0 && positionUp < BOARD_WIDTH && (y + i) <
                        BOARD_HEIGHT && (y + i) >= 0)
                        //board.grid[y + r_ + (i - 1)][positionUp] = '*';
                        board.grid[y + r_ + (i - 1)][positionUp].symbol = '*';
                        board.grid[y + r_ + (i - 1)][positionUp].color = color_;

                }
            }
        }
        else {
            framedraw(board);
        }
    }
    bool contains(int px, int py)  override {
        if (px<x || py<y || px >= x-r_+(2*r_+1) || py>=y+r_ || px >=x-(r_-1-r_)+(2*(r_-1-r_+1)) || py>=y+r_+(r_-1)) {
            return false;
        }
        if (mode_ == "fill") {
            return true;
        }
        else if (py==y||py>=y+(r_-1) || px==x || px>=x-r_+(2*r_+1)-1 || px>=x-(r_-1-r_)+(2*(r_- 1-r_)+1)-1 || py>=y+r_+(r_-1)) {
        }
        return true;
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
    void updPrmtrs(int newl, int none) override {
        length_ = newl;
    }
    void updCoordinates(int newX, int newY) override {
        x = newX;
        y = newY;
    }
    void setColor(const std::string& newColor)override { color_ = newColor; }
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
                if (isVertical_) {
                   // board.grid[current_y][current_x] = '|';
                    board.grid[current_y][current_x].symbol = '|';
                    board.grid[current_y][current_x].color = color_;

                }
                else {
                  //  board.grid[current_y][current_x] = '-';
                    board.grid[current_y][current_x].symbol = '-';
                    board.grid[current_y][current_x].color = color_;
                }
        }
    }
    bool contains(int px, int py)  override {
        if (isVertical_) {
            return (px == x && py >= y && py < y + length_);
        }
        else {
            return (py == y && px >= x && px < x+length_ );
        }
        
    }
};

int main()
{
    Board board;

    // x y w h
    Triangle triangle(8, 2, 1, 5, "fill", "");
    Rectangle rectangle(20, 2, 9, 4, "fill", "");
    Diamond diamond(25, 8, 5, "fill", "pink");
    Square square( 5, 10,5, "fill", "pink");
    Line line(1, 1, 5, true, "fill", "pink");
    Shape* selectedShape = nullptr;

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
            std::cout << "Triangle -- [x][y][width][height] [fill Or Frame][color]\n";
            std::cout << "Rectangle -- [x][y][width][height] [fill Or Frame][color]\n";
            std::cout << "Square -- [x][y][radius] [fill Or Frame][color]\n";
            std::cout << "Diamond -- [x][y][radius] [fill Or Frame][color]\n";
            std::cout << "Line -- [x][y][length][if line is Vertical - TRUE else FALSE] [fill Or Frame][color]\n";
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
            std::cout << "----Select----\n";
            std::cout << "1.Select by Id\n";
            std::cout << "2.Select by coordinate\n";
            std::cout << "Enter your option: \n";
            int selectedType;
            std::cin >> selectedType;

            if (selectedType == 1) {
                int id;
                std::cout << "Enter ID ('number'): ";
                std::cin >> id;

                bool idFound = false;
                for (int i = 0; i < shapes.size();++i) {
                    if (i + 1 == id) {
                        std::cout << "[" << (i + 1) << "]" << shapes[i]->printList();
                        selectedShape = shapes[i];
                        std::cout << "Shapes are found!\n";
                        idFound = true;
                        break;
                    }
                }
                if (!idFound) {
                    std::cout << "shape was not found";
                }
            }
            else {

                int px, py;
                std::cout << "Enter coordinate to select ('x' and 'y'): ";
                std::cin >> px >> py;

                bool found = false;
                for (int i = shapes.size() - 1; i >= 0; --i) {
                    if (shapes[i]->contains(px, py)) {
                        std::cout << shapes[i]->printList();
                        selectedShape = shapes[i];
                        std::cout << "Shapes are found!";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "shape was not found";
                }
            }
            break;
        }
        case 6: {
            std::cout << "----Remove----\n";
            if (selectedShape == nullptr) {
                std::cout << "No shape is selected";
                break;
            }
            
            for (int i = 0; i < shapes.size();++i) {
                if (shapes[i] == selectedShape) {
                    shapes.erase(shapes.begin()+i);
                    selectedShape = nullptr;
                    std::cout << "Shape is removed";

                    board = Board();
                    //for (int i = 0; i < shapes.size();++i) {
                    //    shapes[i]->draw(board);
                    //}
                    break;
                }
            }
            break;
        }
        case 7: {
            std::cout << "----Edit----\n";
            if (selectedShape == nullptr) {
                std::cout << "No shape is selected";
                break;
            }
            for (int i = 0; i < shapes.size();++i) {
                if (shapes[i] == selectedShape) {
                    std::cout << "Enter new parameters : \n";
                    int a,b;
                    std::cin >> a >> b;
                    if (a > BOARD_WIDTH || b > BOARD_HEIGHT) {
                        std::cout << "error: shape will go out of the board";
                    }
                    selectedShape->updPrmtrs(a,b);
                    std::cout << "Size of box changed";
                    break;
                }
            }
            board.print();
            break;
        }
        case 8: {
            std::cout << "----Paint----\n";
            if (selectedShape == nullptr) {
                std::cout << "No shape is selected";
                break;
            }
            for (int i = 0; i < shapes.size();++i) {
                if (shapes[i] == selectedShape) {
                    std::cout << "What color do you want? : \n";
                    std::string color;
                    std::cin >> color;
                    selectedShape->setColor(color);
                    std::cout << "Shape is painted \n";
                }
            }
            break;
        }
        case 9: {
            std::cout << "----Move----\n";
            if (selectedShape == nullptr) {
                std::cout << "No shape is selected";
                break;
            }

            for (int i = 0; i < shapes.size();++i) {
                if (shapes[i] == selectedShape) {
                    std::cout << "Enter new coordinates (x,y) : \n";
                    int x, y;
                    std::cin >> x >> y;
                    if (x > BOARD_WIDTH || y > BOARD_HEIGHT) {
                        std::cout << "error: shape will go out of the board";
                    }
                    selectedShape->updCoordinates(x, y);

                    board = Board();
                    for (int i = 0; i < shapes.size();++i) {
                        shapes[i]->draw(board);
                    }
                   
                    std::cout << "Coordinates of box changed";
                    break;
                }
            }
            break;
        }
        case 10: {
            //for (int i = 0; i < shapes.size();++i) {
            //    shapes.erase(shapes.begin() + i);
            //    selectedShape = nullptr;
            //}
            shapes.clear();
            selectedShape = nullptr;
            board = Board();
            std::cout << "Board is clear\n";
            break;
        }
               return 0;
        };
    }
}