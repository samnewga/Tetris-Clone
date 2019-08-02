#include "stdafx.h"
#include "Shape.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

/*
 * Block Shape 4 x 4
 *  [ 0   1     2   3]
 *  [ 4   5     6   7]
 *  [ 8   9     10  11]
 *  [ 12  13    14  15]
 * */

// 4 piece block settup
unsigned int BlockInfo4x4[7][4] = 
{
	{4, 5,  8,  9},     // O
    {5, 9, 13,  12},    // J
    {5, 9, 10,  14},    // Z
    {5, 9,  8,  12},    // S
    {5, 8,  9,  10},    // T
    {5, 9,  13, 14},    // L
    {1, 5,  9,  13},    // I
};

// Constructor, set up positions defaults
Shape::Shape(sf::Texture &texture, int id) : m_Position(sf::Vector2i{3, 0}), m_CurrentRotation(0), m_ID(id), m_Block(), m_Sprite(texture, sf::IntRect{(id % 7 )* 18, 0, 18, 18})
{
	//restrict ID, so it does not get out of bounds
    m_ID = m_ID % 7;
	// 4 is the number of possible rotations
    for(auto i = 0; i < 4; ++i)
	{
        m_Block[i].x = BlockInfo4x4[m_ID][i] % 4;
        m_Block[i].y = BlockInfo4x4[m_ID][i] / 4;
    }
}

// 
void Shape::rotate() 
{
    //store state of Block in case rotation turns out to be invalid
    m_OldBlock = m_Block;

    if(m_ID == 0)
	{ 
		//square: no need for rotation
        return;
    }
    if(m_ID == 6)
	{ // I: restrict "rotation" to two states (horizontal/vertical)
        m_CurrentRotation++;
        for(auto i = 0; i < 4; ++i) 
		{
            sf::Vector2i oldPoint = m_Block[i];    //pivot
            sf::Vector2i localVector = oldPoint - sf::Vector2i{1, 2};
            sf::Vector2i nextPoint{};
            if(m_CurrentRotation % 2 == 1)
			{
                // counter-clockwise
                nextPoint = sf::Vector2i{(0 * localVector.x) + (-1 * localVector.y), (1 * localVector.x) + (0 * localVector.y)};

            }
            else
			{
				// clock wise
                nextPoint = sf::Vector2i{(0 * localVector.x) + (1 * localVector.y), (-1 * localVector.x) + (0 * localVector.y)};

            }
            m_Block[i] = sf::Vector2i{1,2} + nextPoint;
        }
        return;
    }
    for(auto i = 0; i < 4; ++i)
	{
		sf::Vector2i oldPoint = m_Block[i]; //pivot
        sf::Vector2i localVector = oldPoint - sf::Vector2i{1,2}; // 1, 1

        /*//Rotation Matrix
         * [cos Degree    -sin Degree]
         * [sin Degree     cos Degree]
         * translates to
         * clockwise
         * [0   -1]
         * [1    0]
         * */

        sf::Vector2i nextPoint {(0 * localVector.x) + (-1 * localVector.y), (1 * localVector.x) + (0 * localVector.y)};
        m_Block[i] = sf::Vector2i{1,2} + nextPoint;
    }
}

// 
void Shape::move(Direction dir) 
{
    if(dir == Direction::Left)
	{
        m_Position.x--;
    }
    else if(dir == Direction::Right)
	{
        m_Position.x++;
    }
    else
	{
        m_Position.y++;
    }
}

// Shape while falling
void Shape::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    for(int i = 0; i < 4; ++i)
	{
		// number out front of function is the offsets. 9 is for X -9 is for Y. This compensates for the border of the board UI
        m_Sprite.setPosition(9+((m_Block[i].x * 18) + (m_Position.x * 18)), -9+((m_Block[i].y * 18) + (m_Position.y * 18)));
        target.draw(m_Sprite);
    }
}

// get the positions of all 4 blocks
std::array<sf::Vector2i, 4> Shape::getBlockPositions() const 
{
    std::array<sf::Vector2i, 4> blockPositions;
    for(auto i = 0; i < 4; ++i)
	{
        blockPositions[i] = sf::Vector2i{m_Block[i].x + m_Position.x, m_Block[i].y + m_Position.y };
    }
    return blockPositions;
}

// returns the blocks position if they were to move or rotate
std::array<sf::Vector2i, 4> Shape::getFutureBlockPositions(Direction direction) const 
{

    std::array<sf::Vector2i, 4> blockPositions;
    sf::Vector2i tempPosition{m_Position};
    if(direction == Direction::Left)
	{
        tempPosition.x--;
    }
    else if(direction == Direction::Right)
	{
        tempPosition.x++;
    }
    else 
	{
        tempPosition.y++;
    }
    for(auto i = 0; i < 4; ++i)
	{
        blockPositions[i] = sf::Vector2i{m_Block[i].x + tempPosition.x, m_Block[i].y + tempPosition.y};
    }
    return blockPositions;
}

// return the shape to the previous rotation and position if the rotation or position is invalid
void Shape::revertState() 
{
    m_Block = m_OldBlock;
}

// get the ID of the current shape
int Shape::getID() const 
{
    return m_ID;
}

// set position of shape
void Shape::setPosition(const sf::Vector2i& position) 
{
    m_Position = position;
}
