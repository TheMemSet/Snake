#ifndef SNAKE_HPP_INCLUDED
#define SNAKE_HPP_INCLUDED

#include <vector>
#include <cinttypes>

enum Direction
{
    up = 0,
    right = 1,
    down = 2,
    left = 3
};

class Segment
{
    Direction next;
    uint16_t x, y;

public:

    Segment(){}
    Segment (uint16_t x, uint16_t y, Direction next)
    {
        this->x    = x;
        this->y    = y;
        this->next = next;
    }

    friend class Snake;
};

class Snake
{
    std::vector <Segment> segment;
    bool alive;
    uint16_t gridWidth, gridHeight;
    uint16_t headX, headY;

    int8_t offX [4];
    int8_t offY [4];

public:
    Snake(uint16_t gridWidth, uint16_t gridHeight);
    bool isAlive() const;
    void update();
    void reset();
    void getSnake (uint16_t &hX, uint16_t &hY, std::vector <uint16_t> &vectX, std::vector <uint16_t> &vectY) const;
    void changeDirection (Direction);
};

#endif // SNAKE_HPP_INCLUDED
