#include <iostream>
#include <vector>
#include <memory>

using std::string, std::vector, std::cout, std::unique_ptr, std::move;

class Command {
public:
    virtual ~Command() {};
    virtual void execute() = 0;
};

class Canvas {
    vector<string> shapes;
public:
    void addShape(const string & newShape) {
        shapes.push_back(newShape);
    };
    void clearAll() {
        shapes.clear();
    };
    vector<string> getShapes() { return shapes; };
};

class AddShapeCommand: public Command {
    string shapeName;
    unique_ptr<Canvas> canvas;
public:
    AddShapeCommand(const string & shapeName, Canvas* canvas) : shapeName(shapeName), canvas(unique_ptr<Canvas>(canvas)) {};
    void execute() {
        canvas->addShape(shapeName);
    }
};

class ClearCommand: public Command {
    unique_ptr<Canvas> canvas;
public:
    ClearCommand(Canvas* canvas) : canvas(unique_ptr<Canvas>(canvas)) {};
    void execute() {
        canvas->clearAll();
    }
};

class Button {
    unique_ptr<Command> command;
public:
    Button(Command *command) : command(unique_ptr<Command>(command)) {}
    ~Button() { };
    virtual void click() {
        command->execute();
    };
};

string vectorToString(vector<string> v) {
    string result = "";
    for(int i=0; i < v.size(); i++) {
        result.append(v.at(i) + ", ");
    }
    return result;
}

int main(int argc, const char * argv[]) {
    Canvas *canvas = new Canvas;
    
    Button *addTriangleButton = new Button(new AddShapeCommand("triangle", canvas));
    Button *addSquareButton = new Button(new AddShapeCommand("square", canvas));
    Button *clearButton = new Button(new ClearCommand(canvas));
    
    addTriangleButton->click();
    cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    addSquareButton->click();
    addSquareButton->click();
    addTriangleButton->click();
    cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    clearButton->click();
    cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    
    delete canvas;

    return 0;
}
