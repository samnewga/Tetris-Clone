#pragma once
#include "stdafx.h"
#include "SFML/Graphics.hpp"

#define NUM_BUTTONS_MAX 3

class Button
{
public:
	// Constructors
	Button(float width, float height);
	// Deconstructors
	~Button();

	// Methods
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return menuIndex; }

private:
	// Attributes
	int menuIndex;
	sf::Font font;
	sf::Text buttons[NUM_BUTTONS_MAX];
	sf::Texture buttonTexture;
	sf::Sprite buttonSprites[NUM_BUTTONS_MAX];
	sf::Texture titleTexture;
	sf::Sprite titleSprite;

};