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

    const bool emplace_back() const
    {
        containers::vector<int> v;

        v.emplace_back(2);

        return
            v[0] == 2 &&
            v.size() == 1;
    }

    const bool range_loop() const
    {
        containers::vector<int> v3(10, 24);

        for (auto& i : v3)
        {
            i *= 2;
        }

        return true;
    }

public:

    bool test_all()
    {
        return
            ctor() &&
            push_back() &&
            emplace_back() &&
            range_loop();
    }
};