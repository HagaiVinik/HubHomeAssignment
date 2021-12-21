//
// Created by user on 20/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_ARTISTTEST_HPP
#define HUBHOMEASSIGNMENT_ARTISTTEST_HPP

#include <list>
#include <string>

#include "BaseNode.hpp"


class ArtistTest : public BaseNode
{
public:
    ArtistTest(const std::string& test_name,uint32_t index, std::list<std::string> artists_list):
            BaseNode(test_name, index),
            _artists_list(std::move(artists_list))
    {}
    std::list<std::string> getArtistsList() const { return _artists_list; }

    bool preformTest(const std::string& some_artist) const
    {
        for(auto & artist : getArtistsList())
        {
            if (some_artist == artist)
            {
                return true;
            }
        }
        return false;
    }

private:
    std::list<std::string> _artists_list;
};


#endif //HUBHOMEASSIGNMENT_ARTISTTEST_HPP
