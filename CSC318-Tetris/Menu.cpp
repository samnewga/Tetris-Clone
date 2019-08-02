#include "stdafx.h"
#include "Menu.h"

Menu::Menu()
{

}

// Create the window to render our graphics in
// Checks for input and handles the corresponding events
// 0: Play
// 1: High Scores
// 2: Exit
void Menu::runMenu()
{
	sf::RenderWindow window(sf::VideoMode(330, 375), "Tetris");

	Button buttons(window.getSize().x, window.getSize().y);
	Game game;
	HighScores highScores("scores.txt");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
				{
					buttons.MoveUp();
					break;
				}
				case sf::Keyboard::Down:
				{
					buttons.MoveDown();
					break;
				}
				case sf::Keyboard::Return:
				{
					switch (buttons.GetPressedItem())
					{
					case 0:
					{
						game.run(window);
						break;
					}
					case 1:
					{
						window.clear();
						highScores.drawHighScores(window);
						break;
					}
					case 2:
					{
						window.close();
						break;
					}
					}
					break;
				}
				}
			}
			break;
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			}
		}
		window.clear();
		buttons.draw(window);
		window.display();
	}
}