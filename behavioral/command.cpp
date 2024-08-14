#include <iostream>
#include <vector>
#include <memory>

using std::string, std::vector, std::cout, std::unique_ptr, std::shared_ptr, std::move;

class Command {
public:
    virtual ~Command() {};
    virtual void execute() = 0;
};
typedef unique_ptr<Command> command_ptr;

class Canvas {
    vector<string> shapes;
public:
    void addShape(const string& newShape) {
        shapes.push_back(newShape);
    };
    void clearAll() {
        shapes.clear();
    };
    vector<string> getShapes() { return shapes; };
};
typedef shared_ptr<Canvas> canvas_ptr;

class AddShapeCommand: public Command {
    string shapeName;
    canvas_ptr canvas;
public:
    AddShapeCommand(const string& shapeName, canvas_ptr& canvas) : shapeName(shapeName), canvas(canvas) {};
    void execute() {
        canvas->addShape(shapeName);
    }
};

class ClearCommand: public Command {
    canvas_ptr canvas;
public:
    ClearCommand(canvas_ptr& canvas) : canvas(canvas) {};
    void execute() {
        canvas->clearAll();
    }
};

class Button {
    command_ptr command;
public:
    Button(command_ptr command) : command(move(command)) {}
    ~Button() { };
    virtual void click() {
        command->execute();
    };
};
typedef unique_ptr<Button> button_ptr;

string vectorToString(vector<string> v) {
    string result = "";
    for(int i=0; i < v.size(); i++) {
        result.append(v.at(i) + ", ");
    }
    return result;
}

int main(int argc, const char * argv[]) {
    canvas_ptr canvas = canvas_ptr(new Canvas);
    
    button_ptr addTriangleButton = button_ptr(new Button(command_ptr(new AddShapeCommand("triangle", canvas))));
    button_ptr addSquareButton = button_ptr(new Button(command_ptr(new AddShapeCommand("square", canvas))));
    button_ptr clearButton = button_ptr(new Button(command_ptr(new ClearCommand(canvas))));
    
    addTriangleButton->click();
    cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    addSquareButton->click();
    addSquareButton->click();
    addTriangleButton->click();
    cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    clearButton->click();
    cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    
    return 0;
}
