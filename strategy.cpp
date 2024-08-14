//
//  main.cpp
//  strategy-pattern
//

#include <iostream>
#include <memory>

using std::string, std::cout, std::shared_ptr;

class GreetingStrategy {
public:
    virtual ~GreetingStrategy() {};
    virtual void greet(const string& name) = 0;
};
typedef shared_ptr<GreetingStrategy> strategy_ptr;

class FormalGreetingStrategy : public GreetingStrategy {
public:
    void greet(const string& name) {
        cout << "Good morning " << name << ", how do you do?\n";
    }
};

class NormalGreetingStrategy : public GreetingStrategy {
public:
    void greet(const string& name) {
        cout << "Hi " << name << ", how are you?\n";
    }
};

class InformalGreetingStrategy : public GreetingStrategy {
public:
    void greet(const string& name) {
        cout << "Hey " << name << ", what's up?\n";
    }
};

class Person {
    strategy_ptr greetingStrategy;
public:
    Person(const strategy_ptr& greetingStrategy) : greetingStrategy(greetingStrategy) {};
    ~Person() { cout << "Deleting person...\n"; };
    void greet(const string& name) {
        greetingStrategy->greet(name);
    }
};

int main(int argc, const char * argv[]) {
    auto formalStrategy = strategy_ptr(new FormalGreetingStrategy());
    auto normalStrategy = strategy_ptr(new NormalGreetingStrategy());
    auto informalStrategy = strategy_ptr(new InformalGreetingStrategy());

    Person businessPerson(formalStrategy);
    Person normalPerson(normalStrategy);
    Person coolPerson(informalStrategy);
    Person politician(formalStrategy);
    
    cout << "The businessperson says: ";
    businessPerson.greet("Fabio");
    
    cout << "The normal person says: ";
    normalPerson.greet("Fabio");
    
    cout << "The cool person says: ";
    coolPerson.greet("Fabio");
    
    cout << "The politician says: ";
    politician.greet("Fabio");
    
    return 0;
}
