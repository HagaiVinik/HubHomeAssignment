cmake_minimum_required(VERSION 3.20)
project(HubHomeAssignment)

set(CMAKE_CXX_STANDARD 17)

include_directories(/)
include_directories(Nodes)
include_directories(Nodes/BaseNode)
include_directories(Nodes/TestNodes)
include_directories(Nodes/TerminalNode)


add_executable(HubHomeAssignment main.cpp
        RuleParser/RuleParser.cpp
        RuleParser/RuleParser.hpp
        Nodes/BaseNode/BaseNode.hpp
        Nodes/TestNodes/GenreTest.hpp
        Nodes/TestNodes/BPMTest.hpp
        Nodes/TestNodes/LengthTest.hpp
        Nodes/TestNodes/ArtistTest.hpp
        Nodes/TerminalNode/PlayTerminal.hpp
        Nodes/TerminalNode/SkipTerminal.hpp
        RuleTester/RuleTester.cpp
        RuleTester/RuleTester.hpp pch.hpp)

