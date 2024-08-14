#include <iostream>
#include <memory>

using std::string, std::cout, std::shared_ptr;

class Visitor {
public:
    virtual void handlePerson(const string & name, int age) = 0;
    virtual void handleLandmark(const string & name, const string & cityName) = 0;
    virtual void handleCar(const string & make, const string & model) = 0;
};
typedef shared_ptr<Visitor> visitor_ptr;

class DatabaseVisitor : public Visitor {
public:
    void handlePerson(const string & name, int age) override {
        cout << "Writing person to database: " << name << ", " << age << "\n";
    };
    void handleLandmark(const string & name, const string & cityName) override {
        cout << "Writing landmark to database: " << name << ", " << cityName << "\n";
    };
    void handleCar(const string & make, const string & model) override {
        cout << "Writing car to database: " << make << ", " << model << "\n";
    };
};

class TextFileVisitor : public Visitor {
public:
    void handlePerson(const string & name, int age) override {
        cout << "Writing person to file: " << name << ", " << age << "\n";
    };
    void handleLandmark(const string & name, const string & cityName) override {
        cout << "Writing landmark to file: " << name << ", " << cityName << "\n";
    };
    void handleCar(const string & make, const string & model) override {
        cout << "Writing car to file: " << make << ", " << model << "\n";
    };
};

class Person {
    string name;
    int age;
public:
    Person(const string & name, int age) : name(name), age(age) {};
    void accept(visitor_ptr v) { v->handlePerson(name, age); };
};

class Landmark {
    string name;
    string cityName;
public:
    Landmark(const string & name, const string & cityName) : name(name), cityName(cityName) {};
    void accept(visitor_ptr v) { v->handleLandmark(name, cityName); };
};

class Car {
    string make;
    string model;
public:
    Car(const string & make, const string & model) : make(make), model(model) {};
    void accept(visitor_ptr v) { v->handleCar(make, model); };
};

int main(int argc, const char* argv[]) {
    Person person("John", 40);
    Landmark landmark("Eiffel Tower", "Paris");
    Car car("Chevrolet", "Camaro");
    
    visitor_ptr dbv = shared_ptr<DatabaseVisitor>(new DatabaseVisitor);
    visitor_ptr tfv = shared_ptr<TextFileVisitor>(new TextFileVisitor);
    
    person.accept(dbv);
    landmark.accept(dbv);
    car.accept(dbv);
    
    person.accept(tfv);
    landmark.accept(tfv);
    car.accept(tfv);
    
    return 0;
}
