//
// Created by user on 20/12/2021.
//

#ifndef HUBHOMEASSIGNMENT_GENRETEST_HPP
#define HUBHOMEASSIGNMENT_GENRETEST_HPP

#include "BaseNode.hpp"

class GenreTest : public BaseNode
{
public:
    GenreTest(const std::string& test_name,uint32_t index, std::list<std::string> genres_list): BaseNode(test_name, index),
                                                                                                _genres_list(std::move(genres_list))
    {}
    std::list<std::string> getGenresList() const { return _genres_list; }

    bool preformTest(const std::string& some_genre) const
    {
        for(auto & genre : getGenresList())
        {
            if (some_genre == genre)
            {
                return true;
            }
        }
        return false;
    }

private:
    std::list<std::string> _genres_list;
};


#endif //HUBHOMEASSIGNMENT_GENRETEST_HPP
