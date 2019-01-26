#ifndef __TEST_SUITE_HPP__
#define __TEST_SUITE_HPP__

#define COUT_FORMAT std::cout << "TEST_SUITE(" << __FUNCTION__ << ") - "
#define BEFORE() try {
#define AFTER()                                               \
    COUT_FORMAT << "Passed!" << std::endl;                    \
    }                                                         \
    catch (std::exception & e) {                              \
        COUT_FORMAT << "Failed -> " << e.what() << std::endl; \
    };

void assert(int cond1, int cond2) {
    if ((cond1) != (cond2))
        throw std::runtime_error("Expecting: " + std::to_string(cond1) +
                                 "; Found: " + std::to_string(cond2) + ".");
}

void assert(std::string cond1, std::string cond2) {
    if ((cond1) != (cond2))
        throw std::runtime_error("Expecting: " + cond1 +
                                 "; Found: " + cond2 + ".");
}

#endif