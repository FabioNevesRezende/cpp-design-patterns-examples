#include <iostream>
#include <vector>
#include <memory>

using std::vector, std::cout, std::unique_ptr, std::move;

class NumberIterator {
public:
    virtual ~NumberIterator() {};
    virtual int next() = 0;
    virtual bool isFinished() = 0;
};
typedef unique_ptr<NumberIterator> it_ptr;

class ForwardsIterator: public NumberIterator {
    int currentPosition;
    vector<int>& numbers;
public:
    ForwardsIterator(vector<int>& numbers) : currentPosition(0), numbers(numbers) {};
    int next() override {
        int current = numbers.at(currentPosition);
        currentPosition += 1;
        return current;
    }
    bool isFinished() override {
        return currentPosition >= numbers.size();
    }
};

class BackwardsIterator: public NumberIterator {
    int currentPosition;
    vector<int>& numbers;
public:
    BackwardsIterator(vector<int>& numbers) : currentPosition(0), numbers(numbers) {};
    int next() override {
        int current = numbers.at(numbers.size() - currentPosition - 1);
        currentPosition += 1;
        return current;
    }
    bool isFinished() override {
        return currentPosition >= numbers.size();
    }
};

class NumberCollection {
    vector<int> numbers;
public:
    NumberCollection(const vector<int>&  numbers) : numbers(numbers) {};
    it_ptr getForwardsIterator() { return move(it_ptr(new ForwardsIterator(numbers))); };
    it_ptr getBackwardsIterator() { return move(it_ptr(new BackwardsIterator(numbers))); };
};

int main(int argc, const char * argv[]) {
    vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7 };
    NumberCollection nc(numbers);
    
    const it_ptr fi = nc.getForwardsIterator();
    const it_ptr bi = nc.getBackwardsIterator();
    
   while (!fi->isFinished()) {
       cout << fi->next() << ", ";
   }
   
   cout << "\n";
   
   cout << "Iterating through the numbers backwards:\n";
   
   while (!bi->isFinished()) {
       cout << bi->next() << ", ";
   }
   
   cout << "\n";
    
    return 0;
}
