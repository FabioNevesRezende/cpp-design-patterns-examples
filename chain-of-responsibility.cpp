#include <iostream>
#include <vector>
#include <regex>

using std::string, std::cout, std::vector;

class StringValidator {
public:
    virtual StringValidator *setNext(StringValidator *nextValidator) = 0;
    virtual ~StringValidator() {};
    virtual string validate(string) = 0;
};

class BaseValidator : public StringValidator {
protected:
    StringValidator *next = nullptr;
public:
    ~BaseValidator() { delete next; };
    StringValidator *setNext(StringValidator *nextValidator) override {
        next = nextValidator;
        return nextValidator;
    }
    virtual string validate(string testString) override {
        if (this->next) {
            return this->next->validate(testString);
        }
        return "Success!";
    }
};

class NotEmptyValidator: public BaseValidator {
public:
    string validate(string testString) override {
        cout << "Checking if empty...\n";
        
        if (testString.empty()) {
            return "Please enter a value";
        }
        
        return BaseValidator::validate(testString);
    }
};

class LengthValidator: public BaseValidator {
    int minLength;
public:
    LengthValidator(int minLength) : minLength(minLength) {};
    string validate(string testString) override {
        cout << "Checking if length equals: " << minLength << "...\n";
        
        if (testString.length() < minLength) {
            return "Please enter a value longer than " + std::to_string(minLength);
        }
        
        return BaseValidator::validate(testString);
    }
};

class RegexValidator: public BaseValidator {
    string patternName;
    string regexString;
public:
    RegexValidator(string patternName, string regexString)
    : patternName(patternName), regexString(regexString) {};
    string validate(string testString) override {
        cout << "Checking if string is a valid " << patternName << "...\n";
        
        if (!std::regex_match(testString, std::regex(regexString))) {
            return "The value entered is not a valid " + patternName;
        }
        
        return BaseValidator::validate(testString);
    }
};

bool in_vector(const string &value, const vector<string> &v) {
    return std::find(v.begin(), v.end(), value) != v.end();
}

class HistoryValidator: public BaseValidator {
    vector<string> historyItems;
public:
    HistoryValidator(vector<string> historyItems) : historyItems(historyItems) {};
    string validate(string testString) override {
        cout << "Checking if string is in history...\n";
        
        if (in_vector(testString, historyItems)) {
            return "Please enter a value that you haven't entered before";
        }
        
        return BaseValidator::validate(testString);
    }
};

int main(int argc, const char* argv[]) {
    vector<string> oldPasswords = { "abc123", "123456", "hello" };
    
    BaseValidator *emailValidator = new BaseValidator;
    BaseValidator *passwordValidator = new BaseValidator;
    
    emailValidator
        ->setNext(new NotEmptyValidator)
        ->setNext(new RegexValidator("email address", "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$"));
    
        cout << "Checking Emails ---------------\n";
        cout << "Input: \n" << emailValidator->validate("") << "\n\n";
        cout << "Input: shaun\n" << emailValidator->validate("shaun") << "\n\n";
        cout << "Input: shaun@test.com\n" << emailValidator->validate("shaun@test.com") << "\n\n";

    passwordValidator
        ->setNext(new NotEmptyValidator)
        ->setNext(new LengthValidator(6));
    

    cout << "Checking passwords ---------------\n";
    cout << "Input: \n" << passwordValidator->validate("") << "\n\n";
    cout << "Input: abc123\n" << passwordValidator->validate(oldPasswords[0]) << "\n\n";
    cout << "Input: hello\n" << passwordValidator->validate(oldPasswords[2]) << "\n\n";

    delete emailValidator;
    delete passwordValidator;
    
    return 0;
}
