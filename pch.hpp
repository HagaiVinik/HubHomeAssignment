//
// Created by user on 20/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_PCH_HPP
#define HUBHOMEASSIGNMENT_PCH_HPP

#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <memory>
#include <string>

#include "json.hpp"
#include "CRC.h"

#include "TestNodes/GenreTest.hpp"
#include "TestNodes/ArtistTest.hpp"
#include "TestNodes/BPMTest.hpp"
#include "TestNodes/LengthTest.hpp"

#include "TerminalNode/PlayTerminal.hpp"
#include "TerminalNode/SkipTerminal.hpp"


struct TESTS
{
    static constexpr auto GENRE = "Genre";
    static constexpr auto LENGTH = "Length";
    static constexpr auto BPM = "BPM";
    static constexpr auto ARTIST = "Artist";
};

struct TERMINALS
{
    static constexpr auto PLAY = "Play";
    static constexpr auto SKIP = "Skip";
};

static bool isTest(const std::string& node_role)
{
    return (node_role == TESTS::GENRE || node_role == TESTS::LENGTH ||
            node_role == TESTS::BPM || node_role == TESTS::ARTIST);
}

static bool isTerminal(const std::string& node_role)
{
    return (node_role == TERMINALS::PLAY || node_role == TERMINALS::SKIP);
}

#endif //HUBHOMEASSIGNMENT_PCH_HPP
