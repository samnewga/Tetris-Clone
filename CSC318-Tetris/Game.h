#pragma once

#include "Shape.h"
#include "Board.h"
#include "Score.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

// Game class is used to manipulate the game state and handle the main gameplay loop
// Game class will also handle the frame updates and draw speed rates
class Game 
{
friend class Board;
public:
	// Constructors
    Game();

	// Methods
    void run(sf::RenderWindow& myWindow);

private:
    void proceed(Direction dir);
    void update(const sf::Time& dt, sf::RenderWindow& window);
    void rotate();
    void createTetromino(sf::RenderWindow& myRenderWindow);
    bool isValidMovement(std::array<sf::Vector2i, 4> block);
    bool isOccupied(int x, int y);
    void inputHandler(sf::RenderWindow& newWindow);
    void render(sf::RenderWindow& theWindow);

	// Attributes
    //sf::RenderWindow m_RenderWindow;
    sf::Texture m_Texture;
    std::unique_ptr<Shape> m_Tetromino;
    std::unique_ptr<Shape> m_Preview;
    std::unique_ptr<Board> m_Board;
    Score m_HighScore;
    sf::Time m_ElapsedTime;
    int m_ID;
};
