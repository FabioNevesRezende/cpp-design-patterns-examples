#include <iostream>
#include <memory>

using std::string, std::cout, std::endl, std::cin, std::unique_ptr, std::move;

//Door Objects
class Door
{
public:
	Door()
	{
	}
	virtual void Open() = 0;
};
typedef unique_ptr<Door> door_ptr;

class GasCarDoor : public Door
{
public:
	GasCarDoor()
	{
		cout << "Making a door for a gas car." << endl;
	}
	void Open()
	{
		cout << "click" << endl;
	}
};

class ElectricCarDoor : public Door
{
public:
	ElectricCarDoor()
	{
		cout << "Making a door for an electric car" << endl;
	}
	void Open()
	{
		cout << "shhhhh" << endl;
	}
};

//Engine objects
class Engine
{
protected:
	string _sound;
public:
	Engine()
	{
        _sound = "";
	}
	virtual void Run() = 0;
};
typedef unique_ptr<Engine> engine_ptr;

class GasEngine : public Engine
{
public:
	GasEngine()
	{
        _sound = "vroom";
		cout << "Making a gas engine." << endl;
	}
	void Run()
	{
		cout << _sound << endl;
	}
};

class ElectricEngine : public Engine
{
public:
	ElectricEngine()
	{
		_sound = "SHHHH";
		cout << "Making an electric engine." << endl;
	}
	void Run()
	{
		cout << _sound << endl;
	}
};

//Factories
class CarFactory
{
public:
	virtual door_ptr BuildDoor() = 0;
	virtual engine_ptr BuildEngine() = 0;
};
typedef unique_ptr<CarFactory> factory_ptr;

class GasCarFactory :public CarFactory
{
public:
	door_ptr BuildDoor()
	{
		return move(door_ptr(new GasCarDoor()));
	}
	engine_ptr BuildEngine()
	{
		return move(engine_ptr(new GasEngine()));
	}
};

class ElectricCarFactory :public CarFactory
{
public:
	door_ptr BuildDoor()
	{
		return move(door_ptr(new ElectricCarDoor()));
	}
	engine_ptr BuildEngine()
	{
		return move(engine_ptr(new ElectricEngine()));
	}
};

int main()
{
	factory_ptr CarPlant;
	int choice;

	cout << "Select a car type: " << endl;
	cout << "1: Gasoline" << endl;
	cout << "2: Electric" << endl;
	cout << "Selection: ";
	cin >> choice;
	cout << endl;

	switch (choice)
	{
	case 1:
		CarPlant = factory_ptr(new GasCarFactory);
		break;
	case 2:
		CarPlant = factory_ptr(new ElectricCarFactory);
		break;
	default:
		cout << "Invalid Selection" << endl;
		CarPlant = NULL;
		break;
	}

	if (CarPlant != NULL)
	{
		door_ptr myDoor = CarPlant->BuildDoor();
		engine_ptr myEngine = CarPlant->BuildEngine();

		myDoor->Open();
		myEngine->Run();

	}

    return 0;
}

