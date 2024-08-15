#include <iostream>
#include <vector>
#include <memory>

using std::vector, std::string, std::cout, std::unique_ptr, std::move;

class Canvas;

class CanvasMemento {
    friend class Canvas;
    const vector<string> shapes;
public:
    CanvasMemento(vector<string> shapes) : shapes(shapes) {};
};
typedef unique_ptr<CanvasMemento> cm_ptr;

class Canvas {
    vector<string> shapes;
    vector<cm_ptr> oldStates;
public:
    ~Canvas() {
        oldStates.clear();
    }
    void addShape(const string&  newShape) {
        oldStates.push_back(move(cm_ptr(new CanvasMemento(shapes))));
        shapes.push_back(newShape);
    };
    void undo() {
        cm_ptr previousState = move(oldStates.back());
        oldStates.pop_back();
        shapes = previousState->shapes;
    }
    void clearAll() {
        shapes.clear();
    };
    vector<string> getShapes() { return shapes; };
};
typedef unique_ptr<Canvas> canvas_ptr;

int main(int argc, const char * argv[]) {
    canvas_ptr canvas = canvas_ptr(new Canvas);
    
    canvas->addShape("rhombus");
    canvas->addShape("triangle");
    canvas->addShape("square");
    canvas->addShape("circle");
    
    for (auto shape : canvas->getShapes()) {
        cout << shape << ", ";
    };
    
    cout << "\n";
    
    canvas->undo();
    
    for (auto shape : canvas->getShapes()) {
        cout << shape << ", ";
    };
    
    cout << "\n";
    
    canvas->addShape("rhombus");
    canvas->addShape("triangle");
    canvas->addShape("square");
    canvas->addShape("circle");
    canvas->undo();
    
    for (auto shape : canvas->getShapes()) {
        cout << shape << ", ";
    };
    
    cout << "\n";

    return 0;
}
