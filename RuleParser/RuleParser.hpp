//
// Created by user on 19/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_RULEPARSER_HPP
#define HUBHOMEASSIGNMENT_RULEPARSER_HPP

#include "pch.hpp"


class RuleParser
{
public:
    static constexpr auto READ_SIZE = 4;

    uint32_t reArrangeCRC(uint32_t num);
    bool checkCRC(const std::string& path);

    std::vector<std::shared_ptr<BaseNode>> parseFile(const std::string& path);
    void printFile(const std::string& path);

private:
    uint32_t _crc;
    std::vector<std::shared_ptr<BaseNode>> _nodes;

    void buildNode(uint32_t index, const std::string& node, std::ifstream& fs);
    void buildTest(uint32_t index, const std::string& test, std::ifstream& fs);
    void buildTerminal(uint32_t index, const std::string& terminal);
    void fillRedundantNodes(uint32_t index);
};


#endif //HUBHOMEASSIGNMENT_RULEPARSER_HPP
