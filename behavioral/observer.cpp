//
//  main.cpp
//  observer-pattern
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::shared_ptr, std::vector, std::string, std::cout, std::move;

class Subscriber {
public:
    virtual void notify(const string & publisherName, const string & message) = 0;
    virtual string getName() = 0;
};

typedef shared_ptr<Subscriber> subscriber_ptr;
typedef vector<subscriber_ptr>::iterator subscribers_it;

class Publisher {
public:
    virtual void subscribe(subscriber_ptr& subscriber) = 0;
    virtual void unsubscribe(subscriber_ptr subscriber) = 0;
    virtual void publish(const string & message) = 0;
};

class ChatGroup : public Publisher {
    string groupName;
    vector<subscriber_ptr> subscribers;
public:
    ChatGroup(const string & name) : groupName(name) {};
    void subscribe(subscriber_ptr& subscriber) override {
        this->subscribers.push_back(subscriber);
    };
    void unsubscribe(subscriber_ptr subscriber) override {
        for(subscribers_it it = subscribers.begin() ; it != subscribers.end(); ++it)
        {
            if((*it)->getName() == subscriber->getName())
            {
                subscribers.erase(it);
            }
        }
    };
    void publish(const string & message) override {
        for(subscribers_it it = subscribers.begin() ; it != subscribers.end(); ++it)
        {
            (*it)->notify(groupName, message);
        }
    };
};
typedef shared_ptr<ChatGroup> chatgroup_ptr;

class ChatUser : public Subscriber {
    string userName;
public:
    ChatUser(const string & userName) : userName(userName) {};
    void notify(const string & publisherName, const string & message) override {
        cout << userName << " received a new message from " << publisherName << ": " << message << "\n";
    }
    string getName() override { return userName; };
};
typedef shared_ptr<ChatUser> chatuser_ptr;

int main(int argc, const char * argv[]) {
    subscriber_ptr user1 = chatuser_ptr(new ChatUser("Jim"));
    subscriber_ptr user2 = chatuser_ptr(new ChatUser("Barb"));
    subscriber_ptr user3 = chatuser_ptr(new ChatUser("Hannah"));
    
    chatgroup_ptr group1 = chatgroup_ptr(new ChatGroup("Gardening group"));
    chatgroup_ptr group2 = chatgroup_ptr(new ChatGroup("Dog-lovers group"));
    
    group1->subscribe(user1);
    group1->subscribe(user2);
    
    group2->subscribe(user2);
    group2->subscribe(user3);
    
    group1->publish("Special sale on gardening supplies!");
    group2->publish("It's national dog day everyone!");
    
    
    return 0;
}
