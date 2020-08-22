#ifndef PLATFORMER_SOLVER_H
#define PLATFORMER_SOLVER_H

#include <vector>
#include "Grid.h"
#include <sstream>
#include <queue>
#include <unordered_set>

using Moves = std::vector<Direction>;

class Solver {
public:
    template<size_t WIDTH, size_t HEIGHT>
    Moves solve(const Grid<WIDTH, HEIGHT> &grid);

private:
    template<size_t WIDTH, size_t HEIGHT>
    Moves generateMoves(const Grid<WIDTH, HEIGHT> &grid) const;
};

template<size_t WIDTH, size_t HEIGHT>
struct GridToSolve {
    Grid<WIDTH, HEIGHT> grid;
    Moves moves;
    int priority;
};

template<size_t WIDTH, size_t HEIGHT>
Moves Solver::solve(const Grid<WIDTH, HEIGHT> &grid) {
    using GridAndMoves = GridToSolve<WIDTH, HEIGHT>;

    auto compare = [](GridAndMoves left, GridAndMoves right) {
        return left.priority > right.priority;
    };
    std::priority_queue<GridAndMoves, std::vector<GridAndMoves>, decltype(compare)> queue(compare);

    const GridAndMoves some_pair{grid, {}, std::numeric_limits<int>{}.min()};
    queue.push(some_pair);

    std::unordered_set<Grid<WIDTH, HEIGHT>> visited;

    while (!queue.empty()) {
        GridAndMoves entry = queue.top();
        queue.pop();

        if (entry.grid.isSolved()) {
            return entry.moves;
        }

        for (const auto &move: generateMoves(entry.grid)) {
            Grid<WIDTH, HEIGHT> newGrid = entry.grid;
            newGrid.swap(move);

            if (visited.find(newGrid) == visited.end()) {
                visited.emplace(newGrid);

                Moves newMoves = entry.moves;
                newMoves.emplace_back(move);

                queue.push({newGrid, newMoves, newGrid.solution()});
            }
        }
    }

    return Moves{};
}

template<size_t WIDTH, size_t HEIGHT>
Moves Solver::generateMoves(const Grid<WIDTH, HEIGHT> &grid) const {
    const auto empty = grid.getEmptySpot();

    unsigned int x = empty % WIDTH;
    unsigned int y = (int) (empty / WIDTH);
    Moves moves;
    if (x > 0) {
        moves.emplace_back(WEST);
    }
    if (x < WIDTH - 1) {
        moves.emplace_back(EAST);
    }
    if (y > 0) {
        moves.emplace_back(NORTH);
    }
    if (y < HEIGHT - 1) {
        moves.emplace_back(SOUTH);
    }
    return moves;
}

#endif
