#include "RuleParser/RuleParser.hpp"
#include "RuleTester/RuleTester.hpp"


int main()
{
    static constexpr auto RULE_PATH = "../trees/example";
    static constexpr auto SONGS_PATH = "../songs.json";

    RuleParser ruleParser;
    if(!ruleParser.checkCRC(RULE_PATH))
    {
        std::cout << "CRC is wrong! file could be corrupted." << std::endl;
        return 1;
    }

    std::cout << "CRC is OK, Testing Rule: " << std::endl;

    auto rule_list = ruleParser.parseFile(RULE_PATH);
    RuleTester ruleTester(rule_list);
    ruleTester.loadJsonSongsFile(SONGS_PATH);
    ruleTester.test();

    return 0;
}

