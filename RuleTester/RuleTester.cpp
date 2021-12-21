//
// Created by user on 20/12/2021.
//

#include "RuleTester.hpp"

void RuleTester::loadJsonSongsFile(const std::string &path)
{
    std::ifstream fs(path);
    fs >> _json_songs;
}

uint32_t RuleTester::getLeftSon(uint32_t index)
{
    return index * 2;
}

uint32_t RuleTester::getRightSon(uint32_t index)
{
    return (index * 2) + 1;
}

uint32_t RuleTester::calculateTime(const std::string& format)
{
    std::tm tm{};
    std::istringstream ss(format.data());
    ss >> std::get_time(&tm, "%M:%S");
    return ((tm.tm_min * 60) + tm.tm_sec);
}

void RuleTester::preformTest(nlohmann::json song)
{
    uint32_t index = 1;
    while (!isTerminal(_rule_list.at(index)->getName()))
    {
        std::string test_name = _rule_list.at(index)->getName();
        bool result = false;

        if (test_name == TESTS::GENRE)
        {
            auto genreTestPtr = std::static_pointer_cast<GenreTest>(_rule_list.at(index));
            result = genreTestPtr->preformTest(song[TESTS::GENRE]);

        }
        else if (test_name == TESTS::ARTIST)
        {
            auto artistTestPtr = std::static_pointer_cast<ArtistTest>(_rule_list.at(index));
            result = artistTestPtr->preformTest(song[TESTS::ARTIST]);
        }
        else if (test_name == TESTS::BPM)
        {
            auto BPMTestPtr = std::static_pointer_cast<BPMTest>(_rule_list.at(index));
            result = BPMTestPtr->preformTest(song[TESTS::BPM]);

        }
        else if (test_name == TESTS::LENGTH)
        {
            auto lengthTestPtr = std::static_pointer_cast<LengthTest>(_rule_list.at(index));
            std::string format = song[TESTS::LENGTH];
            uint32_t time_in_seconds = calculateTime(format);
            result = lengthTestPtr->preformTest(time_in_seconds);
        }

        if (result)
        {
            index = getLeftSon(index);
        }
        else
        {
            index = getRightSon(index);
        }
    }

    printResult(song ,_rule_list.at(index)->getName());

}

void RuleTester::test()
{
    /**     Preform test on each song:      */
    for (auto& song : _json_songs)
    {
        preformTest(song);
    }
}

void RuleTester::printResult(const nlohmann::json& song, const std::string& result)
{
    std::cout << "song: " << song << ", " << result << std::endl;
}

