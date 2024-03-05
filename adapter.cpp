#include <iostream>
#include <memory>

using namespace std;

class Component{
public:
    virtual void run() = 0;
    virtual ~Component() = default;
};

class ComponentA : public Component
{
public:
    virtual void run() override
    {
        cout << "Executando ComponentA::run()" << endl;
    }    
};

class ComponentB : public Component
{
public:
    virtual void run() override
    {
        cout << "Executando ComponentB::run()" << endl;
    }    
};

class LegacyComponent{
public:
    void go()
    {
        cout << "Executando LegacyComponent::go()" << endl;
    }
};

class LegacyComponentAdapter : public Component, private LegacyComponent
{
public:
    virtual void run() override
    {
        cout << "Executando LegacyComponentAdapter::run()" << endl;
        go();
    }
};

int main(int argc, char* argv[])
{

    const unique_ptr<Component> components[]
    {
        make_unique<ComponentA>(),
        make_unique<ComponentB>(),
        make_unique<LegacyComponentAdapter>()
    };

    for(const unique_ptr<Component>& comp : components)
    {
        comp->run();
    }

    return 0;

}