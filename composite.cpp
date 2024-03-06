#include <iostream>
#include <vector>

using namespace std;


class Product
{
public:
    virtual double price() const = 0;
    virtual ~Product() = default;
};

class Book : public Product
{
public:
    Book(const string& title, double price) : m_Title(title), m_Price(price) {}
    double price() const override
    {
        cout << "Getting \"" << m_Title << "\" book price" << endl;
        return m_Price;
    }

private:
    double m_Price;
    string m_Title;

};


class Toy : public Product
{
public:
    Toy(const string& name, double price) : m_Name(name), m_Price(price) {}
    double price() const override
    {
        cout << "Getting \"" << m_Name << "\" toy price" << endl;
        return m_Price;
    }

private:
    double m_Price;
    string m_Name;

};

class Box : public Product
{
private:
    string m_Name;
    vector<Product*> m_Products;
public:
    explicit Box(const string& name) : m_Name(name) {}

    void addProduct(Product& prod)
    {
        m_Products.push_back(&prod);
    }

    double price() const override
    {
        cout << "Opening " << m_Name << endl;
        double totalPrice = 0;

        for(const auto& prod: m_Products)
        {
            totalPrice += prod->price();
        }

        return totalPrice;
    }
};

int main(int argc, char* argv[])
{
    Book book1{"Robinson Crusoe", 4.99};
    Toy toy1{"Star Trooper", 39.99};
    Toy toy2{"Barbie Dreamhouse", 59.99};

    Box smallBox("Small box");

    smallBox.addProduct(book1);
    smallBox.addProduct(toy1);

    Box bigBox("Big box");

    bigBox.addProduct(toy2);
    bigBox.addProduct(smallBox);

    cout << "Calculating total price." << endl 
    << bigBox.price() << endl;

    return 0;
}
