#include <iostream>
#include <vector>
#include <map>
#include <string>

class Number {
    std::string number;
public:
    Number(std::string in_number) : number(in_number) {}

    std::string getNumber() {
        return number;
    }
};

class Contact {
    std::string name;
    std::vector<Number *> numbers;
public:
    Contact(std::string in_name, std::string in_number) : name(in_name) {
        addNumber(in_number);
    }

    ~Contact() {
        for (int i = 0; i < numbers.size(); ++i) {
            delete numbers[i];
        }
        numbers.clear();
    }

    std::string getName() {
        return name;
    }

    std::vector<Number *> getNumbers() {
        return numbers;
    }

    void addNumber(std::string number) {
        if (!findNumber(number)) {
            numbers.push_back(new Number(number));
        }
    }

    bool findNumber(std::string number) {
        bool found = false;
        for (int i = 0; i < numbers.size(); ++i) {
            if (numbers[i]->getNumber() == number) {
                found = true;
                break;
            }
        }
        return found;
    }
};

class AddressBook {
    std::map<std::string, Contact *> addressBook_sort_name;
public:
    ~AddressBook() {
        for (auto it = addressBook_sort_name.begin(); it != addressBook_sort_name.end(); ++it) {
            for (int j = 0; j < it->second->getNumbers().size(); ++j) {
                delete it->second;
            }
        }
        addressBook_sort_name.clear();
    }

    void add_contact(std::string name, std::string number) {
        bool add = true;
        if (findContactByNumber(number)) {
            std::cout << "The number is already in the address book. Add it? (y/n)" << std::endl;
            add = answer_yes();
        }
        if (add) {
            Contact *foundContact = findContactByName(name);
            if (foundContact != nullptr) {
                std::cout << "The contact name is already in the address book. Add it? (y/n)" << std::endl;
                if (answer_yes()) {
                    foundContact->addNumber(number);
                }
                add = false;
            }
        }
        if (add) {
            addressBook_sort_name[name] = new Contact(name, number);
        }
    }

    bool answer_yes() {
        std::string answer;
        std::cin >> answer;
        if (answer == "y" || answer == "yes") {
            return true;
        } else {
            return false;
        }
    }

    Contact *findContactByName(std::string name) {
        Contact *found = nullptr;
        auto search_by_name = addressBook_sort_name.find(name);
        if (search_by_name != addressBook_sort_name.end()) {
            found = search_by_name->second;
        }
        return found;
    }

    Contact *findContactByNumber(std::string number) {
        Contact *found = nullptr;
        for (auto it = addressBook_sort_name.begin(); it != addressBook_sort_name.end(); ++it) {
            if (it->second->findNumber(number)) {
                found = it->second;
                break;
            }
        }
        return found;
    }

    /*void show_addressBook() {
        for (auto it = addressBook_sort_name.begin(); it != addressBook_sort_name.end(); ++it) {
            std::cout << it->first << std::endl;
            for (int j = 0; j < it->second->getNumbers().size(); ++j) {
                std::cout << it->second->getNumbers()[j]->getNumber() << std::endl;
            }
        }
    }*/

};

class Mobile {
    AddressBook *addressBook = nullptr;
public:
    ~Mobile() {
        delete addressBook;
        addressBook = nullptr;
    }

    Mobile() {
        addressBook = new AddressBook();
    }

    void add() {
        std::string name, number;
        std::cout << "Input name: ";
        std::cin >> name;
        do {
            std::cout << "Input number (+79876543210): ";
            std::cin >> number;
        } while (!check_number(number));
        addressBook->add_contact(name, number);
        //addressBook->show_addressBook();
    }

    void call() {
        if (findContact() == nullptr) {
            std::cout << "No contact found!" << std::endl;
        } else {
            std::cout << "CALL! CALL! CALL!" << std::endl;
        }
    }

    void sms() {
        if (findContact() == nullptr) {
            std::cout << "No contact found!" << std::endl;
        } else {
            std::string text;
            std::cout << "Input text: ";
            std::cin.ignore();
            std::getline(std::cin, text);
            std::cout << "SMS: " << text << std::endl;
        }
    }

    Contact *findContact() {
        Contact *found = nullptr;

        std::string name_number, name, number;
        std::cout << "Input name or number: ";
        std::cin >> name_number;
        if (check_number(name_number)) {
            found = addressBook->findContactByNumber(name_number);
            if (found != nullptr) {
                number = name_number;
            }
        } else {
            found = addressBook->findContactByName(name_number);
            if (found != nullptr) {
                if (found->getNumbers().size() > 1) {
                    for (int i = 0; i < found->getNumbers().size(); ++i) {
                        std::cout << "#" << i << " " << found->getNumbers()[i]->getNumber() << std::endl;
                    }

                    int choice;
                    do {
                        std::cout << "Choice number (0-" << found->getNumbers().size() - 1 << "): ";
                        std::cin >> choice;
                    } while ((choice < 0) || (choice > (found->getNumbers().size() - 1)));
                    number = found->getNumbers()[choice]->getNumber();
                } else {
                    number = found->getNumbers()[0]->getNumber();
                }
            }
        }
        if (found != nullptr) {
            std::cout << "Contact name: " << found->getName() << "  number:" << number << std::endl;
        }
        return found;
    }

    bool check_number(std::string in_number) {
        bool result = false;
        if (in_number.length() == 12) {
            if (in_number[0] == '+' && in_number[1] == '7') result = true;
        }
        for (int i = 1; i < in_number.length() && result; ++i) {
            if (!std::isdigit(in_number[i])) {
                result = false;
            }
        }
        return result;
    }

};

int main() {

    std::string command;
    Mobile *iphone = new Mobile();
    do {
        std::cout << "Input command: ";
        std::cin >> command;

        if (command == "add") {
            iphone->add();
        } else if (command == "call") {
            iphone->call();
        } else if (command == "sms") {
            iphone->sms();
        }
    } while (command != "exit");

    delete iphone;
   iphone = nullptr;

    return 0;
}