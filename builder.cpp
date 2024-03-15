#include <iostream>
#include <format>

using namespace std;

#pragma region Entrees
// Base Entree class
class Entree
{
protected:
	string _entree;
public:
	const string& getEntree()
	{
		return _entree;
	}
};

// Derived Buger class
class Burger : public Entree
{
public:
	Burger()
	{
		cout << "\n Grill burger patty, add tomatoes and place them in a bun";
		_entree = "hamburger";
	}
};

// Derived Hotdog class
class Hotdog : public Entree
{
public:
	Hotdog()
	{
		cout << "\n Cook sausage and place it in a bun";
		_entree = "hotdog";
	}
};
#pragma endregion Entrees

#pragma region Sides
// Base Side class
class Side
{
protected:
	string _side;
public:
	string& getSide()
	{
		return _side;
	}
};

//Derived Fries class
class Fries : public Side
{
public:
	Fries()
	{
		cout << "\n Fry and season potatoes";
		_side = "fries";
	}
};

//Derived Salad class
class Salad : public Side
{
public:
	Salad()
	{
		cout << "\n Toss greens and dressing together";
		_side = "salad";
	}
};
#pragma endregion Sides

class Drink
{
protected:
	string _drink;
public:
	Drink()
	{
		cout << "\n Fill cup with soda" << endl;
		_drink = "soda";
	}
	string& getDrink()
	{
		return _drink;
	}
};

// Complex MealCombo object that contains an Entree, a Side and a Drink object
class MealCombo
{
private:
	Entree * entree;
	Side *side;
	Drink *drink;
	string _bag;

public:
	MealCombo(const string type)
	{
        _bag = format("\n {} meal combo:", type);
	}
	void setEntree(Entree *e)
	{
		entree = e;
	}
	void setSide(Side *s)
	{
		side = s;
	}
	void setDrink(Drink *d)
	{
		drink = d;
	}
	const string& openMealBag()
	{
        _bag = format("{} {}, {}, {}", _bag, entree->getEntree(), side->getSide(), drink->getDrink());
		return _bag;
	}

    ~MealCombo()
    {
        cout << "Dealocating entree, side and drink\n";
        delete entree, side, drink;
    }
};

#pragma region Builders
// Base Builder
class MealBuilder
{
protected:
	MealCombo * _meal;
public:
	virtual void cookEntree() {};
	virtual void cookSide() {};
	virtual void fillDrink() {};
	MealCombo* getMeal()
	{
		return _meal;
	}

    ~MealBuilder()
    {
        cout << "Dealocating _meal\n";
        delete _meal;
    }
};

//Concrete Builder for a Burger Meal which has a burger, fries and a drink
class BurgerMeal : public MealBuilder
{
public:
	BurgerMeal()
	{
		_meal = new MealCombo("Burger");
	}
	void cookEntree()
	{
		Burger *burger = new Burger;
		_meal->setEntree(burger);
	}
	void cookSide()
	{
		Fries *fries = new Fries;
		_meal->setSide(fries);
	}
	void fillDrink()
	{
		Drink *drink = new Drink;
		_meal->setDrink(drink);
	}
};


//Concrete Builder for a Hotdog Meal which has a hotdog, salad and a drink
class HotdogMeal : public MealBuilder
{
public:
	HotdogMeal()
	{
		_meal = new MealCombo("Hotdog");
	}
	void cookEntree()
	{
		Hotdog *hotdog = new Hotdog;
		_meal->setEntree(hotdog);
	}
	void cookSide()
	{
		Salad *caesar = new Salad;
		_meal->setSide(caesar);
	}
	void fillDrink()
	{
		Drink *drink = new Drink;
		_meal->setDrink(drink);
	}
};
#pragma endregion Builders

int main()
{
	MealBuilder* cook = new MealBuilder;
	MealCombo* meal;
	int choice;

	// Prompt user for their meal choice
	cout << "Select a meal: " << endl;
	cout << "1: Hamburger Meal" << endl;
	cout << "2: Hotdog Meal" << endl;
	cout << "Selection: ";
	cin >> choice;
	cout << endl;

	// Instantiate the appropriate builder based on user input
	switch (choice)
	{
	case 1:
		cook = new BurgerMeal;
		break;
	case 2:
		cook = new HotdogMeal;
		break;
	default:
		cout << "Invalid Selection" << endl;
		cook = NULL;
		break;
	}

	cout << "Making selected meal" << endl;

	// Build the complex object
	cook->cookEntree();
	cook->cookSide();
	cook->fillDrink();
	meal = cook->getMeal();
	cout << meal->openMealBag() << endl;

    delete cook, meal;

}