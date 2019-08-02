#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "Direction.h"

class Shape : public sf::Drawable
{
public:
	// Constructors
    Shape(sf::Texture& texture, int id);
	// Deconstructors
    ~Shape() = default;
	// Methods
    void rotate();

    void move(Direction dir);
    void setPosition(const sf::Vector2i& position);
    void revertState();
    std::array<sf::Vector2i, 4> getBlockPositions() const;
    std::array<sf::Vector2i, 4> getFutureBlockPositions(Direction direction) const;
    int getID() const;
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	// Attributes
    sf::Vector2i m_Position;
    int m_CurrentRotation;
    int m_ID;
    std::array<sf::Vector2i, 4> m_Block;
    std::array<sf::Vector2i, 4> m_OldBlock;
    mutable sf::Sprite m_Sprite;
};