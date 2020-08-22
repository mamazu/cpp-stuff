#ifndef PLATFORMER_GRID_H
#define PLATFORMER_GRID_H

#include <array>
#include <cassert>
#include <boost/functional/hash.hpp>

enum Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH =2 ,
    WEST =3
};

template <size_t WIDTH, size_t HEIGHT>
class Grid {

public:
    Grid(unsigned x, unsigned y) {
        setEmpty(x, y);
        for(size_t i = 0; i < field.size(); ++i) {
            field[i] = i + 1;
        }
    };

    Grid(const Grid& grid) = default;

    [[nodiscard]] size_t getEmptySpot() const { return empty; }
    [[nodiscard]] unsigned int get(size_t x, size_t y) const;
    [[nodiscard]] std::array<int, WIDTH * HEIGHT> getField() const { return field; }

    void swap(Direction direction);
    [[nodiscard]] bool isSolved() const;
    [[nodiscard]] int solution() const;

    bool operator==(const Grid<WIDTH, HEIGHT>& other) const {
        if(other.empty != empty) {
            return false;
        }

        for (size_t i = 0; i < field.size(); ++i) {
            if(field[i] != other.field[i]) {
               return false;
            }
        }

        return true;
    }


private:
    std::array<int, WIDTH * HEIGHT> field;
    size_t empty = 0;

    void setEmpty(size_t x, size_t y);

    [[nodiscard]] bool isValidIndex(size_t x, size_t y) const;
};

template<size_t WIDTH, size_t HEIGHT>
unsigned int Grid<WIDTH, HEIGHT>::get(size_t x, size_t y) const {
    assert(isValidIndex(x, y));
    return field[WIDTH * y + x];
}

template<size_t WIDTH, size_t HEIGHT>
bool Grid<WIDTH, HEIGHT>::isValidIndex(const size_t x, const size_t y) const {
    return (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0);
}

template<size_t WIDTH, size_t HEIGHT>
void Grid<WIDTH, HEIGHT>::setEmpty(const size_t x, const size_t y) {
    assert(isValidIndex(x, y));

    empty = y * WIDTH + x;
}

template<size_t WIDTH, size_t HEIGHT>
void Grid<WIDTH, HEIGHT>::swap(Direction direction) {
    unsigned int nextIndex;
    switch (direction) {
        case NORTH:
            nextIndex = empty - WIDTH;
            break;
        case EAST:
            nextIndex = empty + 1;
            // Skip if empty cell is on the left of the board otherwise it would have wrapped around to the next line
            if (nextIndex % WIDTH == 0) {return;}
            break;
        case SOUTH:
            nextIndex = empty + WIDTH;
            break;
        case WEST:
            // Skip if empty cell is on the left of the board otherwise it would wrap around to a previous line
            if (empty % WIDTH == 0) {return;}
            nextIndex = empty - 1;
            break;
    }
    if(nextIndex < 0 || nextIndex >= WIDTH * HEIGHT) {
        return;
    }

    std::swap(field[nextIndex], field[empty]);
    empty = nextIndex;
}

template<size_t WIDTH, size_t HEIGHT>
bool Grid<WIDTH, HEIGHT>::isSolved() const {
    return std::is_sorted(field.begin(), field.end());
}

template<size_t WIDTH, size_t HEIGHT>
int Grid<WIDTH, HEIGHT>::solution() const {
    int solutionDegree = 0;
    for(size_t x = 0; x < WIDTH; x++) {
        for(size_t y = 0; y < HEIGHT; y++) {
            const int number = get(x, y) - 1;

            const auto expectedX = number % WIDTH;
            const auto expectedY = number / HEIGHT;

            solutionDegree += abs(x - expectedX) + abs(y - expectedY);
        }
    }

    return solutionDegree;
}

namespace std {
    template<size_t WIDTH, size_t HEIGHT>
    struct hash<Grid<WIDTH, HEIGHT>> {
        std::size_t operator()(Grid<WIDTH, HEIGHT> const& s) const noexcept
        {
            auto h1 = boost::hash_range(s.getField().begin(), s.getField().end());
            auto h2 = boost::hash_value(s.getEmptySpot());
            boost::hash_combine(h1, h2);

            return h1;
        }

    };
}

#endif
