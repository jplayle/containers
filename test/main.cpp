#include "vector_test.h"

#include <iostream>

int main()
{
    vector_test a;

    bool r = a.test_all();

    std::string success = "All tests passed.";
    std::string failure = "One or more tests failed.";

    std::cout << (r ? success : failure) << '\n';

    return r;
}