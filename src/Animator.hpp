#ifndef PLATFORMER_ANIMATOR_H
#define PLATFORMER_ANIMATOR_H

#include "Grid.h"
#include "Solver.h"

constexpr float SPEED_CHANGE = .1f;

class Animator {
public:
    template<size_t WIDTH, size_t HEIGHT>
    void solve(const Grid<WIDTH, HEIGHT> &grid) {
        moves = std::move(solver.solve(grid));
        index = 0;
    }

    template<size_t WIDTH, size_t HEIGHT>
    void update(Grid<WIDTH, HEIGHT> &grid) {
        if (index < moves.size() && clock.getElapsedTime().asSeconds() > speed) {
            grid.swap(moves[index]);
            index++;
            clock.restart();
        }
    }

    std::optional<unsigned int> getMovesLeft() const {
            if(moves.empty()) {
                return std::nullopt;
            }

            return moves.size() - index;
    }

    void increaseSpeed() {
        speed -= SPEED_CHANGE;
    }

    void decreaseSpeed() {
        speed += SPEED_CHANGE;
    }

private:
    sf::Clock clock;
    Moves moves;
    size_t index = 0;
    Solver solver;
    float speed = 1;
};

#endif