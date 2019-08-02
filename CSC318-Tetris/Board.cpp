#include "stdafx.h"
#include "Board.h"
#include "Game.h"
#include "Utility.h"
#include <iostream>
#include <algorithm>
#include <fstream>

// Set up field info when populated with a block
FieldInfo::FieldInfo(sf::Texture& texture, int id) 
{
    sf::IntRect rect{(id % 7) * 18, 0, 18,18};
    m_Sprite.setTexture(texture);
    m_Sprite.setTextureRect(rect);
}

// Set up field inside grid
Field& Field::operator=(const Field& field) 
{
    this->m_Occupied = field.m_Occupied;
    this->m_Visible = field.m_Visible;
    this->m_Info = field.m_Info;
    return *this;
}

// set up board class with defaults and load resources
Board::Board(sf::Vector2i size, Game& game) : m_Game(game), m_Fields(), m_FieldInfos(), m_Size(size),m_YCleaned(), m_ElapsedTime(0.f), m_ToRemoveBlocks(false)
{
	// Load the board background to set up the play area
	if (!m_BoardTexture.loadFromFile("Resources/TetrisUI.png"))
	{
		std::cout << "Board::draw Could not load texture" << std::endl;
	}
	// Make texture into sprite
	m_BoardSprite.setTexture(m_BoardTexture);
    for(int x = 0; x < size.x; ++x)
	{
        for(int y = 0; y < size.y; ++y)
		{
            m_Fields[convert2D_to_1D(x,y)] = std::make_unique<Field>();
        }
    }
    for(int id = 0; id < 7; ++id)
	{
        m_FieldInfos[id] = std::make_unique<FieldInfo>(m_Game.m_Texture, id);
    }
}

// Add a block to the field in the board when a block lands
void Board::addBlock(int id, std::array<sf::Vector2i, 4> block) 
{
    for (int i = 0; i < 4; ++i) 
	{
        auto field = getField(block[i].x, block[i].y);
        field->m_Occupied = true;
        field->m_Info = m_FieldInfos[id].get();
    }
}

// Convert a vector2 into a single int
int Board::convert2D_to_1D(int x, int y) 
{
    return y * m_Size.x + x;
}

// render to the screen the board background we will be playing on.
void Board::draw(sf::RenderWindow &window) 
{
	window.draw(m_BoardSprite);
    for(int x = 0; x < m_Size.x; ++x)
	{
        for(int y = 0; y < m_Size.y; ++y)
		{

            auto field = getField(x,y);
            // if field has not been occupied yet, mInfo would be assigned to nullptr
            if(field->m_Occupied && field->m_Visible)
			{
				// position the sprite gets when it is placed into field
				// Offset for borders of Board UI + (position * 18f). 18f is sprite size X or Y
                field->m_Info->m_Sprite.setPosition(9+(x * 18.f), -9+(y * 18.f));
                window.draw(field->m_Info->m_Sprite);
            }
        }
    }
}

// Get field
Field* Board::getField(int x, int y) 
{
    return m_Fields[convert2D_to_1D(x,y)].get();
}

// get size of board, returning vector2i, which is only integers
sf::Vector2i Board::getSize()
{
	return m_Size;
}

// clear the board
void Board::clean() 
{
    for(int x = 0; x < m_Size.x; ++x)
	{
        for(int y = 0; y < m_Size.y; ++y) 
		{
            auto field = getField(x,y);
            field->m_Occupied = false;
            field->m_Visible = true;
            field->m_Info = nullptr;
        }
    }
}

// Check if there are blocks to remove and send those fields to the clearLines function
void Board::markLinesForRemoval() 
{
    if(m_ToRemoveBlocks) return;
    int countClearedLines{0};
    for (int y = m_Size.y - 1; y > 0; --y) 
	{
        int counter = 0;
        for (int x = 0; x < m_Size.x; ++x) 
		{
            auto field = getField(x, y);
            if (field->m_Occupied) 
			{
                counter++;
            }
            if (counter == 10) { // Line full
                m_YCleaned.push_back(y);
                m_ToRemoveBlocks = true;
                countClearedLines++;
            }
        }
        counter = 0;
    }
    m_Game.m_HighScore.addClearedLines(countClearedLines);
    std::sort(m_YCleaned.begin(), m_YCleaned.end(), [](int left, int right) { return left < right; });
}

// Clear the filled lines
void Board::cleanLines()
{
    if (m_YCleaned.empty()) return;

    for (auto i : m_YCleaned) 
	{
        for (auto y = i; y >= 0; --y) 
		{
            for(auto x = 0; x < m_Size.x; ++x)
			{
                int up = y - 1;
                if(up < 0) continue;
                *getField(x,y) = *getField(x,up);
            }
        }
    }
    m_YCleaned.clear();
    m_ToRemoveBlocks = false;
}

// runs update called from game to update every frame we call it
void Board::update(const sf::Time &dt) 
{
    markLinesForRemoval();
    if(m_ToRemoveBlocks)
	{
        m_ElapsedTime += dt.asSeconds();
        blink();
        if(m_ElapsedTime > 0.6f)
		{
            m_ElapsedTime = 0.f;
            cleanLines();
        }
    }
}

// Makes lines that are supposed to be cleared blink, to give a more polished effect
void Board::blink() 
{
    // speeds up blinking
    int num = int(m_ElapsedTime * 5.f);
    for (auto y : m_YCleaned) 
	{
        for (int x = 0; x < m_Size.x; ++x) 
		{
            getField(x,y)->m_Visible = (num % 2 != 0);
        }
    }
}

// returns if a block is filled or not
bool Board::isOccupied(std::array<sf::Vector2i, 4> block) 
{
    for(int i = 0; i < 4; ++i) 
	{
        auto  field = getField(block[i].x, block[i].y);
        if (field->m_Occupied)
		{
            return true;
        }
    }
    return false;
}
