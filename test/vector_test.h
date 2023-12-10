#pragma once

#include "../include/vector.h"
#include <string>

struct vector_test
{
private:

    const bool ctor() const
    {
        containers::vector<int> v1;
        containers::vector<bool> v2(4);
        containers::vector<int> v3(10, 24);

        return
            v1.capacity() == 8 &&
            v2.capacity() == 4 &&
            v3[9] == 24;
    }

    const bool push_back() const
    {
        containers::vector<std::string> v(10);

        std::string s = "ciao";
        v.push_back(s);
        v.push_back("1");

        return
            v[0] == "ciao" &&
            v[1] == "1" &&
            v.size() == 2;
    }

    const bool queries() const
    {
        //vector<std::string> v(20);

        return true;
    }

public:

    bool test_all()
    {
        return
            ctor() &&
            push_back() &&
            queries();
    }
};