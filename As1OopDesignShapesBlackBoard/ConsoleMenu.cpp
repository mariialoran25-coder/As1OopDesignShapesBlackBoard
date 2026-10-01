#include "ConsoleMenu.h"
#include "Shape.h"
#include "Board.h"
#include "Triangle.h"
#include "Diamond.h"
#include "Square.h"
#include "Line.h"
#include "Rectangle.h"
#include <sstream>
#include <fstream>


ConsoleMenu::ConsoleMenu() {}
    void ConsoleMenu::printMenu() {
        std::cout << "\n --Shapes blackboard ----- \n";
        std::cout << "0.Exit\n";
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
    }
    void ConsoleMenu::run() {
        createdShapes();

        int choice = -1;
        while (true) {
            ConsoleMenu::printMenu();
            std::cout << "Choose an action: ";
            if (!(std::cin >> choice)) {
                std::cout << "Enter number from 1 to 12";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }
            std::cin.ignore();
            if (choice == 0) {
                break;
            }
            switch (choice) {
            case 1: Draw1(board);break;
            case 2: List2();break;
            case 3: Shapes3(); break;
            case 4: Add4();break;
            case 5: Select5();break;
            case 6: Remove6();break;
            case 7: Edit7();break;
            case 8: Paint8();break;
            case 9: Move9();break;
            case 10:Clean10();break;
            case 11:Save11();break;
            case 12:Load12();break;
            }
        }
    }

    Shape* ConsoleMenu::createShape(std::string& name, int x, int y, int p1, int p2, std::string& mode, std::string& color) {
    if (name == "triangle") return new Triangle(x, y, p1, p2, mode, color);
    if (name == "rectangle") return new Rectangle(x, y, p1, p2, mode, color);
    if (name == "square") return new Square(x, p1, p1, mode, color);
    if (name == "diamond") return new Diamond(x, p1, p1, mode, color);
    if (name == "line") return new Line(x, y, p1, true, mode, color);
    return nullptr;
}
void ConsoleMenu::createdShapes() {
    shapes.push_back(new Triangle(8, 2, 1, 5, "fill", ""));
    shapes.push_back(new Rectangle(20, 2, 9, 4, "fill", ""));
    shapes.push_back(new Diamond(25, 8, 5, "fill", "pink"));
    shapes.push_back(new Square(5, 10, 5, "fill", "pink"));
    shapes.push_back(new Line(1, 1, 5, true, "fill", "pink"));
}

void ConsoleMenu::Draw1(Board& board) {
    board = Board();
    for (int i = 0; i < shapes.size();++i) {
        shapes[i]->draw(board);
    }
    board.print();
}
void ConsoleMenu::List2() {
    std::cout << "----List----\n";
    for (int i = 0; i < shapes.size(); ++i) {
        std::cout << "[" << i + 1 << "]" << shapes[i]->printList() << "\n";
    }
}
void ConsoleMenu::Shapes3() {
    std::cout << "----Shapes----\n";
    std::cout << "Triangle -- [x][y][width][height] [fill Or Frame][color]\n";
    std::cout << "Rectangle -- [x][y][width][height] [fill Or Frame][color]\n";
    std::cout << "Square -- [x][y][radius] [fill Or Frame][color]\n";
    std::cout << "Diamond -- [x][y][radius] [fill Or Frame][color]\n";
    std::cout << "Line -- [x][y][length][if line is Vertical - TRUE else FALSE] [fill Or Frame][color]\n";
}
void ConsoleMenu::Add4() {
    std::string formShape;
    std::string fillOrFrame;
    std::string color;
    int px, py;
    int pa, pb;
    std::cout << "----ADD----\n";
    std::cout << "Enter Shape: ";
    if (!(std::cin >> formShape)) {
        std::cout << "Error: Enter again";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return;
    }



    std::cout << "Enter Fill or Frame: ";
    if (!(std::cin >> fillOrFrame)) {
        std::cout << "Error: Enter again";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return;
    }

    std::cout << "Enter Color: ";
    if (!(std::cin >> color)) {
        std::cout << "Error: Enter again color";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return;
    }

    std::cout << "Enter Location ('number1 x' 'num2 y'): ";
    if (!(std::cin >> px >> py)) {
        std::cout << "Enter 2 parametrs (numbers)";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return;
    }

    std::cout << "Enter Parameters : ";
    if (!(std::cin >> pa >> pb)) {
        std::cout << "Enter 2 parametrs (numbers)";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return;
    }

    std::cout << "Your Choice: [" << formShape << "][" << fillOrFrame << "][" << color << "][" << pa << "  " << pb << "]\n";
    if (px < 0 || px >= BOARD_WIDTH || py < 0 || py >= BOARD_HEIGHT) {
        std::cout << "Out of range";
        return;
    }
    Shape* newShape = createShape(formShape, px, py, pa, pb, fillOrFrame, color);
    if (newShape != nullptr) {
        shapes.push_back(newShape);
        std::cout << "Shapes added";
    }
    else {
        std::cout << "Shapes not added (Enter right properties)";
    }
}

void ConsoleMenu::Select5() {
    std::cout << "----Select----\n";
    std::cout << "1.Select by Id\n";
    std::cout << "2.Select by coordinate\n";
    std::cout << "Enter your option: \n";
    int selectedType;
    if (!(std::cin >> selectedType)) {
        std::cout << "Error: Enter  valid option 1 or 2";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return;
    }


    if (selectedType == 1) {
        int id;
        std::cout << "Enter ID ('number'): ";
        if (!(std::cin >> id)) {
            std::cout << "Enter number";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            return;
        }
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
        for (int i = static_cast<int>(shapes.size()) - 1; i >= 0; --i) {
            if (shapes[i]->contains(px, py)) {
                std::cout << shapes[i]->printList();
                selectedShape = shapes[i];
                std::cout << "Shapes are found!";
                found = true;
                return;
            }
        }
        if (!found) {
            std::cout << "shape was not found";
        }
    }
}


void ConsoleMenu::Remove6() {
    std::cout << "----Remove----\n";
    if (selectedShape == nullptr) {
        std::cout << "No shape is selected";
        return;
    }

    for (int i = 0; i < shapes.size();++i) {
        if (shapes[i] == selectedShape) {
            shapes.erase(shapes.begin() + i);
            selectedShape = nullptr;
            std::cout << "Shape is removed";

            board = Board();
            return;
        }
    }
}

void ConsoleMenu::Edit7() {
    std::cout << "----Edit----\n";
    if (selectedShape == nullptr) {
        std::cout << "No shape is selected";
        return;
    }
    for (int i = 0; i < shapes.size();++i) {
        if (shapes[i] == selectedShape) {
            std::cout << "Enter new parameters : \n";
            int a, b;
            if (!(std::cin >> a >> b)) {
                std::cout << "Error: Enter again";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                return;
            }
            if (a<0 || a > BOARD_WIDTH || b<0 || b > BOARD_HEIGHT) {
                std::cout << "error: shape will go out of the board";
                return;
            }
            selectedShape->updPrmtrs(a, b);
            std::cout << "Size of box changed";
            return;
        }
    }
    return;
}
void ConsoleMenu::Paint8() {
    std::cout << "----Paint----\n";
    if (selectedShape == nullptr) {
        std::cout << "No shape is selected";
        return;
    }
    for (int i = 0; i < shapes.size();++i) {
        if (shapes[i] == selectedShape) {
            std::cout << "What color do you want? : \n";
            std::string color;
            if (!(std::cin >> color)) {
                std::cout << "Error: Enter again";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                return;
            }
        
            selectedShape->setColor(color);
            std::cout << "Shape is painted \n";
        }
    }
}

void ConsoleMenu::Move9() {
    std::cout << "----Move----\n";
    if (selectedShape == nullptr) {
        std::cout << "No shape is selected";
        return;
    }

    for (int i = 0; i < shapes.size();++i) {
        if (shapes[i] == selectedShape) {
            std::cout << "Enter new coordinates (x,y) : \n";
            int x, y;
            if (!(std::cin >> x >> y)) {
                std::cout << "Error: Enter again";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                return;
            }
        
            if (x<0 || x > BOARD_WIDTH || y<0 || y > BOARD_HEIGHT) {
                std::cout << "error: shape will go out of the board";
                return;
            }
            selectedShape->updCoordinates(x, y);
            board = Board();

            std::cout << "Coordinates of box changed";
            return;
        }
    }
}
void ConsoleMenu::Clean10() {
    std::cout << "----Clear----\n";
    shapes.clear();
    selectedShape = nullptr;
    board = Board();
    std::cout << "Board is clear\n";
}

void ConsoleMenu::Save11() {
    std::cout << "----Save----\n";
    std::string path;

    std::cout << "Enter filename to save ";
    std::getline(std::cin, path);

    board = Board();
    for (int i = 0; i < shapes.size(); ++i) {
        shapes[i]->draw(board);
    }

    std::ofstream outFile(path, std::ios::binary);
    if (outFile.is_open()) {
        std::string serialised = "";

        serialised += std::to_string(shapes.size()) + "\n";
        for (int i = 0; i < shapes.size(); ++i) {
            serialised += shapes[i]->serialise();
        }
        for (int i = 0; i < BOARD_HEIGHT; ++i) {
            for (int j = 0; j < BOARD_WIDTH; ++j) {

                char sym = board.getSym(j, i);
                if (sym == '\0') sym = ' ';
                serialised += sym;
            }
            serialised += "\n";
        }
        outFile.write(serialised.c_str(), serialised.size());
        outFile.close();
        std::cout << "[Success] Document saved\n";
    }
    else
    {
        std::cout << "[Error] File not opening \n";
    }
}

void ConsoleMenu::Load12() {
    std::cout << "----Load----\n";
    std::string path;
    std::cout << "Enter filename to load ";
    std::getline(std::cin, path);

    std::ifstream inFile(path, std::ios::binary | std::ios::ate);
    if (inFile.is_open()) {
        std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();
        std::stringstream ss(content);


        int shapecount = 0;
        if (ss >> shapecount) {
            board = Board();
            shapes.clear();
            selectedShape = nullptr;
            size_t count = 0;
            if (ss >> count) {
                for (size_t i = 0; i < count; ++i) {
                    std::string shapeName;
                    ss >> shapeName;
                    int x = 0, y = 0, w = 0, h = 0;
                    std::string mode, color;
                    if (shapeName == "triangle" || shapeName == "rectangle") {
                        ss >> x >> y >> w >> h >> mode >> color;
                        shapes.push_back(createShape(shapeName, x, y, w, h, mode, color));
                    }
                    else if (shapeName == "square" || shapeName == "diamond") {
                        ss >> x >> y >> w >> mode >> color;
                        shapes.push_back(createShape(shapeName, x, y, w, 0, mode, color));
                    }
                    else if (shapeName == "line") {
                        int len, isVert;
                        ss >> x >> y >> len >> isVert >> mode >> color;
                        shapes.push_back(new Line(x, y, len, isVert, mode, color));

                    }
                }
            }

            ss.get();
            for (int i = 0; i < BOARD_HEIGHT; ++i) {
                for (int j = 0; j < BOARD_WIDTH; ++j) {
                    char symbol;
                    if (ss.get(symbol)) {

                        if (i < BOARD_HEIGHT && j < BOARD_WIDTH) {
                            board.setSym(j, i, symbol, "");
                        }
                    }
                }
                char newLine;
                ss.get(newLine);
            }


            std::cout << "[Success] Document loaded\n";
        }
        inFile.close();
    }
    else {
        std::cout << "[Error] File not opening \n";
    }
};

