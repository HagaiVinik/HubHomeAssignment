//
// Created by user on 20/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_RULETESTER_HPP
#define HUBHOMEASSIGNMENT_RULETESTER_HPP

#include "pch.hpp"

class RuleTester
{
public:
    explicit RuleTester(std::vector<std::shared_ptr<BaseNode>>& nodes) : _rule_list(nodes)
    {}

    void loadJsonSongsFile(const std::string& path);
    void test();

private:
    std::vector<std::shared_ptr<BaseNode>> _rule_list;
    nlohmann::json _json_songs;

    uint32_t getLeftSon(uint32_t index);
    uint32_t getRightSon(uint32_t index);
    uint32_t calculateTime(const std::string& format);

    void preformTest(nlohmann::json song);
    void printResult(const nlohmann::json& song, const std::string& result);
};


#endif //HUBHOMEASSIGNMENT_RULETESTER_HPP
