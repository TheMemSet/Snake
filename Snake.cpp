#include "Snake.hpp"
#include <iostream> // TEMPORARY

Snake::Snake(uint16_t gridWidth, uint16_t gridHeight)
{
    this->gridWidth  = gridWidth;
    this->gridHeight = gridHeight;

    offX [0] = 0;
    offX [1] = 1;
    offX [2] = 0;
    offX [3] = -1;

    offY [0] = -1;
    offY [1] = 0;
    offY [2] = 1;
    offY [3] = 0;

    reset();
}

bool Snake::isAlive() const
{
    return alive;
}

void Snake::reset()
{
    headX = 4;
    headY = 0;

    segment.resize (5);

    for (uint8_t i = 0;i < 5;++i)
    {
        segment [i] = Segment (4 - i, 0, right);
    }

    alive = true;
}

void Snake::getSnake (uint16_t &hX, uint16_t &hY, std::vector <uint16_t> &vectX, std::vector <uint16_t> &vectY) const
{
    hX = headX;
    hY = headY;

    vectX.resize (segment.size());
    vectY.resize (segment.size());

    for (uint16_t i = 0;i < segment.size();++i)
    {
        vectX [i] = segment [i].x;
        vectY [i] = segment [i].y;
    }
}

void Snake::update()
{
    headX += offX [segment [0].next];
    headY += offY [segment [0].next];

    if ((headX < 0) || (headX >= gridWidth) || (headY < 0) || (headY >= gridHeight))
    {
        this->alive = false;
        return;
    }

    for (uint16_t i = 0;i < segment.size();++i)
    {
        segment [i].x += offX [segment [i].next];
        segment [i].y += offY [segment [i].next];
    }

    for (uint16_t i = segment.size() - 1;i > 0;--i)
    {
        segment [i].next = segment [i - 1].next;
    }
}

void Snake::changeDirection (Direction newDir)
{
    if (((newDir == up) || (newDir == down)) && ((segment [0].next == left) || (segment [0].next == right)))
    {
        segment [0].next = newDir;
    }
    else if (((newDir == left) || (newDir == right)) && ((segment [0].next == up) || (segment [0].next == down)))
    {
        segment [0].next = newDir;
    }
}
