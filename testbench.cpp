
#include "testbench.h"

#include "dictionary.h"

void testbench() {
    // create
    names<std::string, int32_t> test;
    std::cout << "Dictionary created" << std::endl;

    // add
    try {
        test.set("Ivan", 23);
        std::cout << "Record successfully added to the dictionary" << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    try {
        test.set("Petr", 21);
        std::cout << "Record successfully added to the dictionary" << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    try {
        test.set("Oleg", 27);
        std::cout << "Record successfully added to the dictionary" << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    // illegal add
    try {
        test.set("Ivan", 19); // A value with this key already exists
        std::cout << "Record successfully added to the dictionary" << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }

    // get
    try {
        auto age1 = test.get("Petr");
        std::cout << "Value " << age1 << " getted successfully "
                                         "from dictionary" << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    // illegal get
    try {
        auto age2 = test.get("Don"); // Element with such key does not exist
        std::cout << "Value " << age2 << " getted successfully "
                                         "from dictionary" << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }

    // check existing
    bool is_exist1 = test.is_set("Petr");
    std::cout << "Existing element: " << is_exist1 << std::endl;
    bool is_exist2 = test.is_set("Victor");
    std::cout << "Existing element: " << is_exist2 << std::endl;
}
