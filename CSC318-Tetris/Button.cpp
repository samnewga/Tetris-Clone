#include "stdafx.h"
#include "Button.h"
#include <iostream>

// Set up defaults
Button::Button(float width, float height)
{
	if (!titleTexture.loadFromFile("Resources/TetrisTitle.png"))
	{
		std::cout << "Button Title Texture not loaded" << std::endl;
	}
	if (!font.loadFromFile("Resources/Timeless-Bold.ttf"))
	{
		std::cout << "Font not found: Button" << std::endl;
	}
	if (!buttonTexture.loadFromFile("Resources/Button.png"))
	{
		std::cout << "Button Texture not loaded" << std::endl;
	}
	titleSprite.setTexture(titleTexture);

	for (int i = 0; i < NUM_BUTTONS_MAX; i++)
	{
		buttonSprites[i].setTexture(buttonTexture);
	}

	// Set title HERE
	titleSprite.setPosition(60,80);

	buttons[0].setFont(font);
	buttons[0].setFillColor(sf::Color::Cyan);
	buttons[0].setString("Play");
	buttons[0].setPosition(140,185);
	buttonSprites[0].setPosition(75,175);

	buttons[1].setFont(font);
	buttons[1].setFillColor(sf::Color::White);
	buttons[1].setString("High Scores");
	buttons[1].setPosition(90,250);
	buttonSprites[1].setPosition(75,240);

	buttons[2].setFont(font);
	buttons[2].setFillColor(sf::Color::White);
	buttons[2].setString("Exit");
	buttons[2].setPosition(140,315);
	buttonSprites[2].setPosition(75,305);

	menuIndex = 0;
}

// Default deconstructor
Button::~Button()
{
}

// render the buttons
void Button::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < NUM_BUTTONS_MAX; i++)
	{
		window.draw(titleSprite);
		window.draw(buttonSprites[i]);
		window.draw(buttons[i]);
	}
}

// Move up the button array
void Button::MoveUp()
{
	if (menuIndex - 1 >= 0)
	{
		buttons[menuIndex].setFillColor(sf::Color::White);
		menuIndex--;
		buttons[menuIndex].setFillColor(sf::Color::Cyan);
	}
}

// Move down the button array
void Button::MoveDown()
{
	if (menuIndex + 1 < NUM_BUTTONS_MAX)
	{
		buttons[menuIndex].setFillColor(sf::Color::White);
		menuIndex++;
		buttons[menuIndex].setFillColor(sf::Color::Cyan);
	}
}