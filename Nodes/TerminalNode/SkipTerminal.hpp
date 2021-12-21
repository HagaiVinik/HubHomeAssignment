//
// Created by user on 20/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_SKIPTERMINAL_HPP
#define HUBHOMEASSIGNMENT_SKIPTERMINAL_HPP

#include "BaseNode.hpp"

class SkipTerminal : public BaseNode
{
public:
    SkipTerminal(const std::string& terminal_name, uint32_t index) : BaseNode(terminal_name, index) {}
};


#endif //HUBHOMEASSIGNMENT_SKIPTERMINAL_HPP
