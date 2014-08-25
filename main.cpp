#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Snake.hpp"
#include <iostream> // TEMPORARY

void update (Grid*);
void userInput (Snake*);

int main()
{
    sf::RenderWindow window (sf::VideoMode (1280, 720), "Temporary title");
    window.setFramerateLimit (30);

    Grid grid (64, 36);

    sf::Thread updateThread (&update,&grid);

    sf::Event ev;

    updateThread.launch();
    while (window.isOpen ())
    {
        while (window.pollEvent (ev))
        {
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
                window.close ();
            if (ev.type == sf::Event::Closed)
                window.close ();
        }

        grid.update(); // Only updates the vertex array,
                       // so it makes sense to use it in
                       // the drawing thread
        window.clear (sf::Color (120, 120, 120));
        window.draw (grid);
        window.display ();
    }
    grid.terminate();
    updateThread.wait();

    return 0;
}

void update (Grid *grid)
{
    sf::Time durationGoal = sf::seconds (1. / 8);
    sf::Time elapsedTime;
    sf::Clock clock;

    uint16_t headX, headY;
    std::vector <uint16_t> snakeX, snakeY;

    Snake snake (64, 36);

    sf::Thread userInputThread (&userInput, &snake);

    clock.restart();
    userInputThread.launch();
    while (grid->isAlive())
    {
        //// Snake and grid updates start here
        snake.update();

        if (!snake.isAlive())
        {
            grid->terminate();
            break;
        }

        snake.getSnake (headX, headY, snakeX, snakeY);
        grid->reset();

        grid->setCell (headX, headY, sf::Color::Red);

        for (uint16_t i = 1;i < snakeX.size();++i)
        {
            grid->setCell (snakeX [i], snakeY [i], sf::Color::Yellow);
        }

        //// Time updates start here
        elapsedTime = clock.restart();

        if ((durationGoal - elapsedTime) > sf::Time::Zero)
        {
            sf::sleep (durationGoal - elapsedTime);
        }
        clock.restart();
    }
    snake.terminate();
    userInputThread.wait();
}

void userInput (Snake *snake)
{
    sf::Keyboard::Key lastKeyPressed = sf::Keyboard::Right;

    while (snake->isAlive())
    {
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up) && lastKeyPressed != sf::Keyboard::Up)
        {
            snake->changeDirection (up);
            lastKeyPressed = sf::Keyboard::Up;
        }
        else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right) && lastKeyPressed != sf::Keyboard::Right)
        {
            snake->changeDirection (right);
            lastKeyPressed = sf::Keyboard::Right;
        }
        else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down) && lastKeyPressed != sf::Keyboard::Down)
        {
            snake->changeDirection (down);
            lastKeyPressed = sf::Keyboard::Down;
        }
        else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left) && lastKeyPressed != sf::Keyboard::Left)
        {
            snake->changeDirection (left);
            lastKeyPressed = sf::Keyboard::Left;
        }

        sf::sleep (sf::milliseconds (10));
    }
}
