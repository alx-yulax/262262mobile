#include <iostream>
#include <vector>
#include <map>

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
        numbers.push_back(new Number(in_number));
    }

    ~Contact() {
        for (int i = 0; i < numbers.size(); ++i) {
            delete numbers[i];
        }
    }

    std::string getName() {
        return name;
    }

    void addNumber(std::string number) {
        numbers.push_back(new Number(number));
    }
};

class AddressBook {
    std::map<std::string, std::vector<Contact *> > address_book_sort_by_name;
    std::map<std::string, std::vector<Contact *> > address_book_sort_by_number;
public:
    ~AddressBook() {

        //for (int i = 0; i < contacts.size(); ++i) {
        //    delete contacts[i];
        //}
    }

    void add_contact(std::string name, std::string number) {
        bool create_contact = true;

        auto search_by_number = address_book_sort_by_number.find(number);
        if (search_by_number != address_book_sort_by_number.end()) {
            std::cout << "Number found at " << search_by_number->second.size() << " contacts:" << std::endl;
            for (int i = 0; i < search_by_number->second.size(); ++i) {
                std::cout << "#" << i << " " << search_by_number->second[i]->getName() << std::endl;
            }
            std::string answer;
            std::cout << "Create new contact? (y/n): ";
            std::cin >> answer;
            if (answer != "y" && answer != "yes") {
                create_contact = false;
            }
        }

        if (create_contact) {
            auto search_by_name = address_book_sort_by_name.find(name);
            if (search_by_name != address_book_sort_by_name.end()) {
                std::cout << "Name found at " << search_by_name->second.size() << " contacts:" << std::endl;
                for (int i = 0; i < search_by_name->second.size(); ++i) {
                    std::cout << "#" << i << " " << search_by_name->second[i]->getName() << std::endl;
                }
                std::string answerUpdateContact;
                std::cout << "Update contact? (y/n): ";
                std::cin >> answerUpdateContact;
                if (answerUpdateContact != "y" && answerUpdateContact != "yes") {
                    int answer;
                    do {
                        std::cout << "Input contact id (0): ";
                        std::cin >> answer;
                    } while ((answer < 0) || (answer > (search_by_name->second.size() - 1)));

                    search_by_name->second[answer]->addNumber(number);

                    if (search_by_number != address_book_sort_by_number.end()) {
                        bool address_book_sort_by_number_add = true;
                        for (int i = 0; i < search_by_number->second.size(); ++i) {
                            if (search_by_number->second[i] == search_by_name->second[answer]) {
                                address_book_sort_by_number_add = false;
                                break;
                            }
                        }
                        if (address_book_sort_by_number_add) {
                            search_by_number->second.push_back(search_by_name->second[answer]);
                        }
                    }

                    create_contact = false;
                }
            }
        }
        if (create_contact) {
            Contact *new_contact = new Contact(name, number);
            address_book_sort_by_name[name].push_back(new_contact);
            address_book_sort_by_number[number].push_back(new_contact);
        }
    }
};

class Mobile {
    AddressBook *addressBook = nullptr;
public:
    ~Mobile() {
        delete addressBook;
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
    }

    void call() {

    }

    void sms() {

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
        } else if (command == "show") {

        } else if (command == "sms") {
            iphone->sms();
        }

    } while (command != "exit");

    delete iphone;

    return 0;
}

