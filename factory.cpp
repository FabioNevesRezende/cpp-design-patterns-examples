// 03_02_FactoryImp_End.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <format>

using namespace std;

// Product from which the concrete products will inherit from 
class Coffee
{
protected:
	string _type;
public:
	Coffee()
	{
	}
	const string getType() const
	{
		return _type;
	}

    ~Coffee()
    {
        cout << "Deleting pointer to " <<  getType() << " coffee object" << endl;
    }
};

// One concrete class
class Espresso : public Coffee
{
public:
	Espresso() : Coffee()
	{
        _type = "Espresso";
		cout << endl << "Making a cup of espresso" << endl;
		cout << "Grind and brew one scoop of espresso beans." << endl;
	}
};

// Another concrete class
class Cappuccino : public Coffee
{
public:
	Cappuccino() : Coffee()
	{
		_type = "Cappuccino";
		cout << endl << "Making a cup of cappuccino" << endl;
		cout << "Grind and brew one scoop of espresso beans." << endl;
		cout << "Heat and foam milk." << endl;
	}
};

class CoffeeMakerFactory
{
public:
	Coffee* GetCoffee()
	{
		int choice;

		cout << "Select type of coffee to make: " << endl;
		cout << "1: Espresso" << endl;
		cout << "2: Cappuccino" << endl;
		cout << "Selection: " << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			return new Espresso;
		case 2:
			return new Cappuccino;
		default:
			cout << "Invalid Selection" << endl;
			return NULL;
		}
	}
};

int main()
{
    CoffeeMakerFactory coffeMachine;

    auto c1 = coffeMachine.GetCoffee();
    delete c1;

}