#include <iostream>
#include <memory>

using std::string, std::cout, std::shared_ptr;

class State;
typedef shared_ptr<State> state_ptr;

class State {
public:
    virtual string getDescription() = 0;
    virtual state_ptr getNextState() = 0;
};

class PurchasedState : public State {
    state_ptr nextState = nullptr;
public:
    PurchasedState(state_ptr nextState) : nextState(nextState) {};
    string getDescription() override {
        return "Current State: PURCHASED - Will be shipping soon\n";
    }
    state_ptr getNextState() override { return nextState; };
};
typedef shared_ptr<PurchasedState> purchased_state_ptr;

class InTransitState : public State {
    state_ptr nextState = nullptr;
public:
    InTransitState(state_ptr nextState) : nextState(nextState) {};
    string getDescription() override {
        return "Current State: IN_TRANSIT - Your item is on the way\n";
    }
    state_ptr getNextState() override { return nextState; };
};
typedef shared_ptr<InTransitState> in_transit_state_ptr;

class DeliveredState : public State {
    state_ptr nextState = nullptr;
public:
    DeliveredState(state_ptr nextState) : nextState(nextState) {};
    string getDescription() override {
        return "Current State: DELIVERED - Your item has arrived\n";
    }
    state_ptr getNextState() override { return nextState; };
};
typedef shared_ptr<DeliveredState> delivered_state_ptr ;

class Purchase {
    string productName;
    state_ptr currentState;
public:
    Purchase(const string & productName, state_ptr initialState)
        : productName(productName), currentState(initialState) {};
    string getDescription() {
        return currentState->getDescription();
    }
    void goToNextState() {
        if (currentState->getNextState()) {
            currentState = currentState->getNextState();
        } else {
            cout << "No more states!";
        }
    };
};

int main(int argc, const char * argv[]) {
    delivered_state_ptr  deliveredState = delivered_state_ptr (new DeliveredState(nullptr));
    in_transit_state_ptr inTransitState = in_transit_state_ptr(new InTransitState(deliveredState));
    purchased_state_ptr purchasedState = purchased_state_ptr(new PurchasedState(inTransitState));
    
    shared_ptr<Purchase> purchase = shared_ptr<Purchase>(new Purchase("Shoes", purchasedState));
    
    cout << purchase->getDescription() << "\n";
    
    purchase->goToNextState();
    cout << purchase->getDescription() << "\n";
    
    purchase->goToNextState();
    cout << purchase->getDescription() << "\n";
    
    return 0;
}
