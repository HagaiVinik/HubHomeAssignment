//
// Created by user on 20/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_PLAYTERMINAL_HPP
#define HUBHOMEASSIGNMENT_PLAYTERMINAL_HPP

#include "BaseNode.hpp"

class PlayTerminal : public BaseNode
{
public:
    PlayTerminal(const std::string& terminal_name, uint32_t index) : BaseNode(terminal_name, index) {}
};


#endif //HUBHOMEASSIGNMENT_PLAYTERMINAL_HPP
