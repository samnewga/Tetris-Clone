#include "stdafx.h"
#include "Game.h"
#include "Utility.h"
#include <SFML/Window/Event.hpp>
#include "Direction.h"
#include <iostream>
#include "Menu.h"
#include "HighScores.h"

// Game constructor. Everything after the solo : sets up default objects used by this class
Game::Game() : m_Texture(), m_Tetromino(nullptr), m_Preview(nullptr), m_Board(), m_HighScore(), m_ElapsedTime(sf::Time::Zero), m_ID(getRandomNumber(7))
{
	// load texture from file... This is how SFML handles loading textures
    if(!m_Texture.loadFromFile("Resources/Blocks.png"))
	{
        std::cout << "Game::Game() - could not load mTexture\n";
    }
	// Size of the board/grid
	sf::Vector2i gridSize = sf::Vector2i{ 10,21 };
    m_Board = std::make_unique<Board>(gridSize, *this);
}

// Main Game Loop
void Game::run(sf::RenderWindow& myWindow) 
{
    sf::Clock clock;
    sf::Time deltaTime{sf::Time::Zero};
    while(myWindow.isOpen())
	{
		// Timer for block falling rates
        sf::Time trigger{sf::seconds(85.f / (85.f + (m_HighScore.getLevel() * (m_HighScore.getLevel() * 5.f))))};
        deltaTime = clock.restart();
        m_ElapsedTime += deltaTime;
        inputHandler(myWindow);
        update(deltaTime, myWindow);
        if(m_ElapsedTime > trigger)
		{
            m_ElapsedTime = sf::Time::Zero;
            proceed(Direction::Down);
        }
		render(myWindow);
    }
}

// proceed to next frame
void Game::update(const sf::Time &dt, sf::RenderWindow& window) 
{
    m_Board->update(dt);
    m_HighScore.update(dt);
    if(!m_Tetromino) 
	{
        if(m_Board->isToRemoveBlocks())
		{
            return;
        }
        createTetromino(window);
    }
}

// rotate tetrominos (shapes)
void Game::rotate()
{
	if (!m_Tetromino) 
	{
		return;
	}
    m_Tetromino->rotate();
    if(!isValidMovement(m_Tetromino->getBlockPositions()))
	{
        m_Tetromino->revertState();
    }
}

// Input handler
void Game::inputHandler(sf::RenderWindow& newWindow) 
{
    sf::Event e;
    while (newWindow.pollEvent(e)) 
	{
		if (e.type == sf::Event::Closed)
		{
			newWindow.close();
		}
        else if (e.type == sf::Event::KeyPressed) 
		{
            if (e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down)
			{
                proceed(Direction::SoftDown);
            } 
			else if (e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right) 
			{
                proceed(Direction::Right);
            } 
			else if (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left) 
			{
                proceed(Direction::Left);
            } 
			else if (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up) 
			{
                rotate();
            } 
			else if (e.key.code == sf::Keyboard::Space || e.key.code == sf::Keyboard::RControl)
			{
				// Hard Drop
			}
			else if (e.key.code == sf::Keyboard::I) 
			{
                m_HighScore.addClearedLines(10);
            }
        }
    }
}

// Call all draw functions from all classes
void Game::render(sf::RenderWindow& theWindow)
{
	theWindow.clear(sf::Color::Black);
	m_Board->draw(theWindow);
    m_HighScore.draw(theWindow);
	if (m_Tetromino)
	{
		theWindow.draw(*m_Tetromino);
	}

	theWindow.draw(*m_Preview);
	theWindow.display();
}

// Next step in game loop and performs input commands
void Game::proceed(Direction dir) 
{
    if(!m_Tetromino) return;

    if(isValidMovement(m_Tetromino->getFutureBlockPositions(dir)))
	{
        m_Tetromino->move(dir);
    }
    else
	{
        if(dir == Direction::Down || dir == Direction::SoftDown) 
		{
            int id = m_Tetromino->getID();
            m_Board->addBlock(id, m_Tetromino->getBlockPositions());
            m_Tetromino.reset(nullptr);
        }
    }
}

// check is movement is valid
bool Game::isValidMovement(std::array<sf::Vector2i, 4> block) 
{
	// Loop through all 4 pieces of shape
    for(int i = 0; i < 4; ++i)
	{
		// if a block's x is less than 0 or greater than the board size or has a y position greater than grid size
        if(block[i].x < 0 ||block[i].x > m_Board->getSize().x - 1 || block[i].y > m_Board->getSize().y - 1)
		{
            return false;
        }
		// if a block's x or y position is occupied
        if(isOccupied(block[i].x, block[i].y))
		{
            return false;
        }
    }
    return true;
}

// check if the field our piece is trying to move is occupied
bool Game::isOccupied(int x, int y) 
{
    return m_Board->getField(x,y)->m_Occupied;
}

// Make new tetromino (shape)
void Game::createTetromino(sf::RenderWindow& myRenderWindow) 
{
   m_Tetromino.reset(new Shape{m_Texture, m_ID});
   // create new game if necessary
   if(m_Board->isOccupied(m_Tetromino->getBlockPositions()))
   {
		HighScores highscoresClass("scores.txt");
		highscoresClass.compareScores(m_HighScore.getScore());
		m_Board->clean();
		m_HighScore.reset();
		myRenderWindow.close();
		Menu menu;
		menu.runMenu();
   }
   // Generate random shape
    m_ID = getRandomNumber(7);
    m_Preview.reset(new Shape{m_Texture, m_ID});
	// Set position of future shape
	m_Preview->setPosition(sf::Vector2i{13,2});
}
