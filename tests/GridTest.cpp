#include "../src/Grid.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Hashing_two_identical_grids)
{
    using DefaultGrid = Grid<10, 10>;
    DefaultGrid g{0, 0};
    DefaultGrid h{0, 0};

    auto hasher = std::hash<DefaultGrid>{};
    BOOST_CHECK(hasher(g) == hasher(h));
}

BOOST_AUTO_TEST_CASE(Hashing_two_identical_grids_with_different_starting_points)
{
    using DefaultGrid = Grid<10, 10>;
    DefaultGrid g{0, 0};
    DefaultGrid h{2, 3};

    auto hasher = std::hash<DefaultGrid>{};
    BOOST_CHECK(hasher(g) != hasher(h));
}

BOOST_AUTO_TEST_CASE(Hashing_grid_that_have_been_moved)
{
    using DefaultGrid = Grid<10, 10>;
    DefaultGrid g{0, 0};
    DefaultGrid h{0, 0};

    h.swap(Direction::SOUTH);
    h.swap(Direction::EAST);
    h.swap(Direction::NORTH);
    h.swap(Direction::WEST);

    auto hasher = std::hash<DefaultGrid>{};
    BOOST_CHECK(hasher(g) != hasher(h));
}


BOOST_AUTO_TEST_CASE(Equality_for_two_identical_grids)
{
    using DefaultGrid = Grid<10, 10>;
    DefaultGrid g{0, 0};
    DefaultGrid h{0, 0};

    BOOST_CHECK(g == h);
}

BOOST_AUTO_TEST_CASE(Equality_for_two_identical_grids_with_different_starting_points)
{
    using DefaultGrid = Grid<10, 10>;
    DefaultGrid g{0, 0};
    DefaultGrid h{2, 3};

    BOOST_CHECK(!(g == h));
}

BOOST_AUTO_TEST_CASE(Comparing_grid_that_have_been_moved)
{
    using DefaultGrid = Grid<10, 10>;
    DefaultGrid g{0, 0};
    DefaultGrid h{0, 0};

    h.swap(Direction::SOUTH);
    h.swap(Direction::EAST);
    h.swap(Direction::NORTH);
    h.swap(Direction::WEST);

    BOOST_CHECK(!(g == h));
}

BOOST_AUTO_TEST_CASE(Solved_grid_returns_0)
{
    using DefaultGrid = Grid<10, 10>;
    for(size_t x = 0; x < 10; x++) {
        for(size_t y = 0; y < 10; y++) {
            DefaultGrid g{(unsigned int)x, (unsigned int) y};
            const int solutionDegree = g.solution();
            BOOST_CHECK(solutionDegree == 0);
        }
    }
}