#include <iostream>
#include <stdio.h>
#include <memory>

using std::string, std::cout, std::unique_ptr, std::move, std::runtime_error;

class Logger {
public:
    virtual ~Logger() {};
    virtual void log(const string&  message) = 0;
};
typedef unique_ptr<Logger> logger_ptr;

class ConsoleLogger : public Logger {
public:
    void log(const string&  message) override {
        cout << message << "\n";
    }
};

class FileLogger :  public Logger {
    string filePath;
public:
    FileLogger(const string&  filePath) : filePath(filePath) {};
    void log(const string&  message) override {
        cout << "Printing message to file " << filePath << ": " << message << "\n";
    }
};

class ApiLogger : public Logger {
    string url;
public:
    ApiLogger(const string&  url) : url(url) {};
    void log(const string&  message) override {
        cout << "Sending message to api " << url << ": " << message << "\n";
    }
};

class NullLogger : public Logger {
public:
    void log(const string&  message) override {};
};

class SomeTask {
    logger_ptr logger = nullptr;
public:
    SomeTask() {
        logger = logger_ptr(new NullLogger);
    }
    SomeTask(logger_ptr l)
    {
        if(l == nullptr)
            throw runtime_error("Trying to instantiate with a null pointer when it's expectin an initialized logger");
        logger = move(l);
    };
    ~SomeTask() { };
    void execute() {
        // Do some stuff...
        
        logger->log("Did some stuff");
        
        // Do some other stuff...

        logger->log("Did some other stuff");
        
        // One last thing...
        
        logger->log("Task complete!");
    }
};

int main(int argc, const char * argv[]) {
    SomeTask task1(logger_ptr(new ConsoleLogger));
    SomeTask task2(logger_ptr(new FileLogger("logs.txt")));
    SomeTask task3(logger_ptr(new ApiLogger("loggingsite.com/api/logs")));
    SomeTask task4;
    
    task1.execute();
    task2.execute();
    task3.execute();
    task4.execute();

    SomeTask task5(nullptr);
    SomeTask task6(0);
    SomeTask task7(NULL);

    task5.execute();
    task6.execute();
    task7.execute();
    
    return 0;
}
