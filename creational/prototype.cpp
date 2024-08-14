#include <iostream>
#include <memory>
#include <format>

using namespace std;


// Abstract Animal class
class Animal
{
protected:
	string _hairColor;
	int _hairLength, _tail, _weight, _height, _age;
	int _intelligence, _stubbornness, _agressiveness;

public:
    void printAnimal()
    {
        cout << format("Hair color: {}, Hair Length: {}, Tail: {}, Weight: {}, Height: {}, Age: {}\nIntelligence: {}, Stubbornness: {}, Aggr: {}\n",
        _hairColor,	 _hairLength, _tail, _weight, _height, _age, _intelligence, _stubbornness, _agressiveness
        );
    }

	void setHairLength(int length)
	{
		_hairLength = length;
	}

	void setHairColor(const string color)
	{
		_hairColor = color;
	}

	void setTail(int length)
	{
		_tail = length;
	}

	void setWeight(int kg)
	{
		_weight = kg;
	}

	void setHeight(int m)
	{
		_height = m;
	}

	void setAge(int age)
	{
		_age = age;
	}

    ~Animal()
    {
        cout << "Dealocating animal\n";
    }

};

// Derived Sheep class
class Sheep : public Animal
{
public:
	Sheep()
	{
		_hairLength = 5;
		_stubbornness = 3;
		_agressiveness = 2;
		_intelligence = 7;
	}
	unique_ptr<Sheep> clone()
	{
		return unique_ptr<Sheep>(new Sheep(*this));
	}
	void shearing()
	{
		_hairLength -= 2;
	}
};

// Derived Cow class
class Cow : public Animal
{
public:
	Cow()
	{
		_stubbornness = 6;
		_agressiveness = 5;
		_intelligence = 8;
	}
	unique_ptr<Cow> clone()
	{
		return unique_ptr<Cow>(new Cow(*this));
	}
};

int main()
{
	//create initial instance of a Sheep
	unique_ptr<Sheep> sheep0 = unique_ptr<Sheep>(new Sheep);
	sheep0->setHairColor("white");
	sheep0->setTail(5);
	sheep0->setWeight(90);
	sheep0->setHeight(1);
	sheep0->setAge(5);

	//create initial instance of a Cow
	unique_ptr<Cow> cow0 = unique_ptr<Cow>(new Cow);
	cow0->setHairColor("brown");
	cow0->setTail(20);
	cow0->setWeight(790);
	cow0->setHeight(2);
	cow0->setAge(8);

	unique_ptr<Animal> farm[3];

	//use cloning to populate the farm
	farm[0] = sheep0->clone();
	farm[1] = cow0->clone();

	//change a cow property
	farm[1]->setWeight(1000);

	//shear a Sheep and clone it
	sheep0->shearing();
	farm[2] = sheep0->clone();

    sheep0->printAnimal();
    cow0->printAnimal();
    for(const auto& an : farm)
    {
        an->printAnimal();
    }

}

