#include <iostream>
#include <memory>

using std::string, std::shared_ptr, std::cout, std::unique_ptr;

class Mediator {
public:
    virtual void mediate(const string& event) = 0;
};
typedef shared_ptr<Mediator> mptr;

class InterfaceElement {
protected:
    mptr mediator;
    string name;
    bool isVisible = true;
public:
    InterfaceElement(const string& name, bool isVisible, mptr mediator) : name(name), isVisible(isVisible), mediator(mediator) {};
    void setVisibility(bool isVisible) { this->isVisible = isVisible; };
    string getDescription() {
        return isVisible
            ? name + " is visible"
            : name + " is NOT visible";
    }

    ~InterfaceElement(){
        cout << "Destroying InterfaceElement " << name << "\n";
    }
};

class ButtonElement : public InterfaceElement {
public:
    ButtonElement(const string& name, bool isVisible, mptr mediator) : InterfaceElement(name, isVisible, mediator) {};
    virtual ~ButtonElement() {};
    virtual void click() {
        mediator->mediate(name + " clicked");
    };
};

class TextBox : public InterfaceElement {
    string textValue = "";
public:
    TextBox(const string& name, bool isVisible, mptr mediator) : InterfaceElement(name, isVisible, mediator) {};
    virtual ~TextBox() {};
    virtual void changeText(const string& newValue) {
        textValue = newValue;
        if (newValue.empty()) {
            mediator->mediate(name + " empty");
        } else {
            mediator->mediate(name + " not empty");
        }
    };
};

class CheckBox : public InterfaceElement {
    bool isChecked = false;
public:
    CheckBox(const string& name, bool isVisible, mptr mediator) : InterfaceElement(name, isVisible, mediator) {};
    virtual ~CheckBox() {};
    virtual void setIsChecked(bool isChecked) {
        this->isChecked = isChecked;
        
        if (isChecked) {
            mediator->mediate(name + " is checked");
        } else {
            mediator->mediate(name + " is unchecked");
        }
    };
};

class UserInterface : public Mediator {
    shared_ptr<TextBox> nameTextBox;
    shared_ptr<CheckBox> isMarriedCheckbox;
    shared_ptr<TextBox> spousesNameTextBox;
    shared_ptr<ButtonElement> submitButton;
public:
    UserInterface() {
        nameTextBox = shared_ptr<TextBox>(new TextBox("Name textbox", true, shared_ptr<Mediator>(this)));
        isMarriedCheckbox = shared_ptr<CheckBox>(new CheckBox("Is married checkbox", true, shared_ptr<Mediator>(this)));
        spousesNameTextBox = shared_ptr<TextBox>(new TextBox("Spouse's name textbox", false, shared_ptr<Mediator>(this)));
        submitButton = shared_ptr<ButtonElement>(new ButtonElement("Submit button", false, shared_ptr<Mediator>(this)));
    }
    ~UserInterface() {
        cout << "Destroying UserInterface\n";
    }
    void mediate(const string& event) override {
        cout << "Mediating event: " << event << "...\n";
        
        if (event == "Name textbox is empty") {
            submitButton->setVisibility(false);
        } else if (event == "Name textbox is not empty") {
            submitButton->setVisibility(true);
        } else if (event == "Is married checkbox is checked") {
            spousesNameTextBox->setVisibility(true);
        } else if (event == "Is married checkbox is unchecked") {
            spousesNameTextBox->setVisibility(false);
        } else if (event == "Submit button clicked") {
            cout << "Submitted!\n";
        } else {
            cout << "Unrecognized event!";
        }
    }
    shared_ptr<TextBox> getNameTextBox() { return nameTextBox; };
    shared_ptr<CheckBox> getIsMarriedCheckbox() { return isMarriedCheckbox; };
    shared_ptr<TextBox> getSpousesNameTextBox() { return spousesNameTextBox; };
    shared_ptr<ButtonElement> getSubmitButton() { return submitButton; };
};
typedef unique_ptr<UserInterface> uiptr;

int main(int argc, const char * argv[]) {
    uiptr ui = uiptr(new UserInterface);
    
    shared_ptr<InterfaceElement> elements[] = {
        ui->getNameTextBox(),
        ui->getIsMarriedCheckbox(),
        ui->getSpousesNameTextBox(),
        ui->getSubmitButton(),
    };
    
    for (auto element : elements) {
        cout << element->getDescription() << "\n\n";
    }
    
    ui->getIsMarriedCheckbox()->setIsChecked(true);
    
    for (auto element : elements) {
        cout << element->getDescription() << "\n";
    }

    cout << "finishing...\n";
    return 0;
}

