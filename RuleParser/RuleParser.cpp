//
// Created by user on 19/12/2021.
//

#include "RuleParser.hpp"


uint32_t RuleParser::reArrangeCRC(uint32_t num)
{
    /**     For some reason, CRC is reversed (big endianness), so it need to be swapped: */

    uint32_t res = 0;
    uint32_t b0 = (num & 0xff) << 24;        //; least significant to most significant
    uint32_t b1 = (num & 0xff00) << 8;       //; 2nd least sig. to 2nd most sig.
    uint32_t b2 = (num & 0xff0000) >> 8;     //; 2nd most sig. to 2nd least sig.
    uint32_t b3 = (num & 0xff000000) >> 24;  //; most sig. to least sig.
    res = b0 | b1 | b2 | b3 ;

    return res;
}


bool RuleParser::checkCRC(const std::string& path)
{
    std::vector<char> crc_str(READ_SIZE);
    std::ifstream fs(path, std::ios::binary);

    fs.read(crc_str.data(), READ_SIZE);
    uint32_t expected_crc = *(reinterpret_cast<uint32_t *>(crc_str.data()));

    _crc = reArrangeCRC(expected_crc);

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(fs), {});
    std::uint32_t crc = CRC::Calculate(buffer.data(), buffer.size(), CRC::CRC_32());

    return (_crc == crc);
}

void RuleParser::buildTest(uint32_t index, const std::string& test, std::ifstream& fs)
{
    std::vector<char> buffer(READ_SIZE);

    if (test == TESTS::GENRE)
    {
        fs.read(buffer.data(), READ_SIZE);
        uint32_t num_of_genre = *(reinterpret_cast<uint32_t *>(buffer.data()));
        std::list<std::string> list_of_genres;

        for(int i = 0; i < num_of_genre; i++)
        {
            std::string genre;
            std::getline(fs, genre, '\0');
            list_of_genres.push_back(genre);
        }

        _nodes.push_back(std::make_shared<GenreTest>(test, index, list_of_genres));
    }

    else if (test == TESTS::ARTIST)
    {
        fs.read(buffer.data(), READ_SIZE);
        uint32_t num_of_genre = *(reinterpret_cast<uint32_t *>(buffer.data()));
        std::list<std::string> list_of_artists;

        for(int i = 0; i < num_of_genre; i++)
        {
            std::string genre;
            std::getline(fs, genre, '\0');
            list_of_artists.push_back(genre);
        }

        _nodes.push_back(std::make_shared<ArtistTest>(test, index, list_of_artists));
    }

    else if (test == TESTS::BPM)
    {
        fs.read(buffer.data(), READ_SIZE);
        uint32_t value = *(reinterpret_cast<uint32_t *>(buffer.data()));

        _nodes.push_back(std::make_shared<BPMTest>(test, index, value));
    }

    else if (test == TESTS::LENGTH)
    {
        fs.read(buffer.data(), READ_SIZE);
        uint32_t value = *(reinterpret_cast<uint32_t *>(buffer.data()));

        _nodes.push_back(std::make_shared<LengthTest>(test, index, value));
    }
}

void RuleParser::buildTerminal(uint32_t index, const std::string& terminal)
{
    if (terminal == TERMINALS::PLAY)
    {
        _nodes.push_back(std::make_shared<PlayTerminal>(terminal, index));
    }
    else if (terminal == TERMINALS::SKIP)
    {
        _nodes.push_back(std::make_shared<SkipTerminal>(terminal, index));
    }
}

void RuleParser::printFile(const std::string &path)
{
    std::string buffer;
    std::ifstream fs(path);

    fs >> buffer;
    std::cout << buffer << std::endl;
}

std::vector<std::shared_ptr<BaseNode>> RuleParser::parseFile(const std::string &path)
{
    std::vector<char> buffer(READ_SIZE);
    std::ifstream fs(path);

    /**     Read CRC:   */
    fs.read(buffer.data(), READ_SIZE);
    _crc = *(reinterpret_cast<uint32_t *>(buffer.data()));

    _nodes.push_back({nullptr});
    while (!fs.eof())
    {
        /**     Read Index:   */
        fs.read(buffer.data(), READ_SIZE);
        uint32_t index = *(reinterpret_cast<uint32_t *>(buffer.data()));

        /**     Read  Node:   */
        std::string node;
        std::getline(fs, node, '\0');

        fillRedundantNodes(index);
        buildNode(index, node, fs);
    }
    return _nodes;
}

void RuleParser::fillRedundantNodes(uint32_t index)
{
    for (uint32_t i = _nodes.size(); i < index; ++i)
    {
        _nodes.push_back({nullptr});
    }
}

void RuleParser::buildNode(uint32_t index, const std::string& node, std::ifstream& fs)
{
    if (isTest(node))
    {
        buildTest(index,node, fs);
    }
    else if (isTerminal(node))
    {
        buildTerminal(index, node);
    }
}
