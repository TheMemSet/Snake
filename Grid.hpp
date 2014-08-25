#ifndef GRID_HPP_INCLUDED
#define GRID_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <cinttypes>

class Grid : public sf::Drawable
{
    std::vector <std::vector <sf::Color>> cell;
    uint16_t width, height;
    sf::VertexArray vertArray;

    const uint16_t CELLSIZE = 20;
    const uint8_t GRID_GAP = 1;
    bool alive;

    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;

public:
    Grid                (uint16_t width, uint16_t height);

    void      reset();
    sf::Color getCell   (uint16_t x, uint16_t y) const;
    void      setCell   (uint16_t x, uint16_t y, const sf::Color &color);
    void      resetCell (uint16_t x, uint16_t y);
    void      update();
    bool      isAlive() const;
    void      terminate();
};

#endif // GRID_HPP_INCLUDED
