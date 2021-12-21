//
// Created by user on 20/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_BASENODE_HPP
#define HUBHOMEASSIGNMENT_BASENODE_HPP

#include <cstdint>

class BaseNode
{
public:
    BaseNode(const std::string& test_name , uint32_t index) : _node_name(test_name), _index(index) {}
    virtual ~BaseNode() = default;
    std::string getName() const { return _node_name; }
    uint32_t getIndex() const { return _index; }

private:
    std::string _node_name;
    uint32_t _index;
};


#endif //HUBHOMEASSIGNMENT_BASENODE_HPP
