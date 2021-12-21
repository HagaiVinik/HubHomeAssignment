//
// Created by user on 20/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_BPMTEST_HPP
#define HUBHOMEASSIGNMENT_BPMTEST_HPP

#include "BaseNode.hpp"

class BPMTest : public BaseNode
{
public:
    BPMTest(const std::string& test_name, uint32_t index, uint32_t value) : BaseNode(test_name, index),
                                                                            _value(value)
    {}

    uint32_t getValue() const { return _value; }

    bool preformTest(uint32_t bpm_value) const
    {
        if (bpm_value <= _value)
        {
            return true;
        }
        return false;
    }

private:
    uint32_t _value;
};


#endif //HUBHOMEASSIGNMENT_BPMTEST_HPP
