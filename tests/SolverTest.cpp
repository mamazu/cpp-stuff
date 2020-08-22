#include "../src/Solver.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(It_solves_a_solved_grid) {
    using DefaultGrid = Grid<5, 5>;

    Solver s;

    DefaultGrid g{2, 2};
    auto moves = s.solve(g);
    BOOST_CHECK(moves.empty());
}

BOOST_AUTO_TEST_CASE(It_solves_a_one_move_grid) {
    using DefaultGrid = Grid<5, 5>;

    Solver s;

    DefaultGrid g{1, 1};
    g.swap(Direction::NORTH);

    auto moves = s.solve(g);
    BOOST_CHECK(moves.size() == 1);
    BOOST_CHECK(moves[0] == Direction::SOUTH);
}
BOOST_AUTO_TEST_CASE(It_solves_a_small_grid_with_two_swaps) {
    using DefaultGrid = Grid<2, 2>;

    Solver s;

    DefaultGrid g{1, 1};
    g.swap(Direction::NORTH);
    g.swap(Direction::WEST);

    auto moves = s.solve(g);
    BOOST_CHECK(moves.size() == 2);
    BOOST_CHECK(moves[0] == Direction::EAST);
    BOOST_CHECK(moves[1] == Direction::SOUTH);
}

BOOST_AUTO_TEST_CASE(It_solves_a_grid_with_two_swaps) {
    using DefaultGrid = Grid<5, 5>;

    Solver s;

    DefaultGrid g{1, 1};
    g.swap(Direction::NORTH);
    g.swap(Direction::EAST);

    auto moves = s.solve(g);
    BOOST_CHECK(moves.size() == 2);
    BOOST_CHECK(moves[0] == Direction::WEST);
    BOOST_CHECK(moves[1] == Direction::SOUTH);
}

BOOST_AUTO_TEST_CASE(It_solves_a_more_complicated_grid) {
    using DefaultGrid = Grid<5, 5>;

    Solver s;

    DefaultGrid g{1, 1};
    g.swap(Direction::NORTH);
    g.swap(Direction::EAST);
    g.swap(Direction::EAST);
    g.swap(Direction::SOUTH);

    auto moves = s.solve(g);
    BOOST_CHECK(moves.size() == 4);
    BOOST_CHECK(moves[0] == Direction::NORTH);
    BOOST_CHECK(moves[1] == Direction::WEST);
    BOOST_CHECK(moves[2] == Direction::WEST);
    BOOST_CHECK(moves[3] == Direction::SOUTH);
}
