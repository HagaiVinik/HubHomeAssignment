//
// Created by user on 20/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_LENGTHTEST_HPP
#define HUBHOMEASSIGNMENT_LENGTHTEST_HPP

#include "BaseNode.hpp"

class LengthTest : public BaseNode
{
public:
    LengthTest(const std::string& test_name, uint32_t index, uint32_t value) : BaseNode(test_name, index),
                                                                  _value(value)
    {}

    uint32_t getValue() const { return _value; }

    bool preformTest(uint32_t song_length) const
    {
        if (song_length <= _value)
        {
            return true;
        }
        return false;
    }

private:
    uint32_t _value;
};


#endif //HUBHOMEASSIGNMENT_LENGTHTEST_HPP
