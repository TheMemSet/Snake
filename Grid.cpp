#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream> // TEMPORARY
#include "Grid.hpp"

Grid::Grid (uint16_t width, uint16_t height)
{
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed (seed);

    this->width = width;
    this->height = height;

    vertArray.setPrimitiveType (sf::Quads);

    cell.resize (width);

    for (uint16_t i = 0;i < width;++i)
    {
        cell [i].resize (height, sf::Color::Black);
    }

    alive = true;
}

void Grid::reset()
{
    for (uint16_t i = 0;i < width;++i)
    {
        for (uint16_t j = 0;j < height;++j)
        {
            cell [i] [j] = sf::Color::Black;
        }
    }
}

sf::Color Grid::getCell (uint16_t x, uint16_t y) const
{
    return cell [x] [y];
}

void Grid::setCell (uint16_t x, uint16_t y, const sf::Color &color)
{
    cell [x] [y] = color;
}

void Grid::resetCell (uint16_t x, uint16_t y)
{
    cell [x] [y] = sf::Color::Black;
}

void Grid::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw (vertArray, states);
}

void Grid::update()
{
    vertArray.clear();

    for (uint16_t i = 0;i < fruit.size();++i)
    {
        vertArray.append (sf::Vertex (sf::Vector2f (CELLSIZE * fruit [i].first, CELLSIZE * fruit [i].second), sf::Color::Green));
        vertArray.append (sf::Vertex (sf::Vector2f (CELLSIZE * (fruit [i].first + 1) - GRID_GAP, CELLSIZE * fruit [i].second), sf::Color::Green));
        vertArray.append (sf::Vertex (sf::Vector2f (CELLSIZE * (fruit [i].first + 1) - GRID_GAP, CELLSIZE * (fruit [i].second + 1) - GRID_GAP), sf::Color::Green));
        vertArray.append (sf::Vertex (sf::Vector2f (CELLSIZE * fruit [i].first, CELLSIZE * (fruit [i].second + 1) - GRID_GAP), sf::Color::Green));
    }

    for (uint16_t i = 0;i < width;++i)
    {
        for (uint16_t j = 0;j < height;++j)
        {
            if (cell [i] [j] != sf::Color::Black)
            {
                vertArray.append (sf::Vertex (sf::Vector2f (CELLSIZE * i, CELLSIZE * j),
                this->getCell (i, j)));

                vertArray.append (sf::Vertex (sf::Vector2f (CELLSIZE * (i + 1) - GRID_GAP, CELLSIZE * j),
                this->getCell (i, j)));

                vertArray.append (sf::Vertex (sf::Vector2f (CELLSIZE * (i + 1) - GRID_GAP, CELLSIZE * (j + 1) - GRID_GAP),
                this->getCell (i, j)));

                vertArray.append (sf::Vertex (sf::Vector2f (CELLSIZE * i, CELLSIZE * (j + 1) - GRID_GAP),
                this->getCell (i, j)));
            }
        }
    }
}

bool Grid::isAlive() const
{
    return alive;
}

void Grid::terminate()
{
    alive = false;
}

void Grid::addFruit()
{
    int16_t rnd = generator() % (64 * 36) + 1; // CONST

    for (uint16_t xx = 0;xx < width;++xx)
    {
        for (uint16_t yy = 0;yy < height;++yy)
        {
            if (cell [xx] [yy] == sf::Color::Black)
            {
                --rnd;
            }

            if (!rnd)
            {
                fruit.push_back (std::make_pair (xx, yy));
                return;
            }
        }
    }
}

