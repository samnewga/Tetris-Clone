#include "stdafx.h"
#include "HighScores.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Menu.h"

// Default constructor. Requires a file name for the score 
HighScores::HighScores(std::string fileName)
{
	if (!m_font.loadFromFile("Resources/Timeless-Bold.ttf"))
	{
		std::cout << "Font not found: Button" << std::endl;
	}
	this->fileName = fileName;
	retrieveHighScores();
}

// Opens the high score file with the given input/output modes
void HighScores::openScoreFile(std::ios_base::openmode modes)
{
	scoreFile.open("scores.txt", modes);
}

// Closes the high score file
void HighScores::closeScoreFile()
{
	scoreFile.close();
}

// Gets the high scores from the file, and stores them in the HighScores object
void HighScores::retrieveHighScores()
{
	openScoreFile(std::ios::in | std::ios::out);
	// If the high score file doesn't exist, creates a new one with default high scores
	if (!scoreFile.good())
	{
		std::ofstream createFile(fileName);
		createFile << "100\n50\n1";
		createFile.close();
		openScoreFile(std::ios::in | std::ios::out);
	}
	scoreFile >> score1 >> score2 >> score3;
	closeScoreFile();
}

// Compares a new score against the high scores. Inserts the new scores into the list if it's a top 3 score, and updates the external file.
void HighScores::compareScores(int newScore)
{
	// #1 score
	if (newScore > score1)
	{
		score3 = score2;
		score2 = score1;
		score1 = newScore;
	}
	// #2 score
	else if (newScore > score2)
	{
		score3 = score2;
		score2 = newScore;
	}
	// #3 score
	else if (newScore > score3)
	{
		score3 = newScore;
	}
	// Not a high score
	else
	{
		return;
	}
	updateScoreFile();
}

// Outputs the new high scores to the score file
void HighScores::updateScoreFile()
{
	openScoreFile(std::ios::out | std::ios::trunc);
	scoreFile << score1 << "\n" << score2 << "\n" << score3;
	closeScoreFile();
}

// Prints the high scores to the console (used for debugging)
void HighScores::printScores()
{
	std::cout << score1 << ", " << score2 << ", " << score3 << "\n";
}

// Return score 1
int HighScores::getScore1()
{
	return score1;
}
// Return score 2
int HighScores::getScore2()
{
	return score2;
}
// Return score 3
int HighScores::getScore3()
{
	return score3;
}

// Draw high scores to window
// Return to main menu when enter is released
void HighScores::drawHighScores(sf::RenderWindow& myWindow)
{
	highScoreTitle.setFont(m_font);
	highScoreTitle.setCharacterSize(36);
	highScoreTitle.setString("Top Scores");
	highScoreTitle.setFillColor(sf::Color::White);
	highScoreTitle.setPosition(70,30);

	m_score1Text.setFont(m_font);
	m_score1Text.setString("1. " + std::to_string(score1));
	m_score1Text.setPosition(40, 140);
	m_score1Text.setFillColor(sf::Color::Red);

	m_score2Text.setFont(m_font);
	m_score2Text.setString("2. " + std::to_string(score2));
	m_score2Text.setPosition(40, 190);
	m_score2Text.setFillColor(sf::Color::Red);

	m_score3Text.setFont(m_font);
	m_score3Text.setString("3. " + std::to_string(score3));
	m_score3Text.setPosition(40, 240);
	m_score3Text.setFillColor(sf::Color::Red);

	sf::Text returnInfo;
	returnInfo.setFont(m_font);
	returnInfo.setCharacterSize(14);
	returnInfo.setString("Press Enter To Return To Main Menu");
	returnInfo.setFillColor(sf::Color::White);
	returnInfo.setPosition(40,350);

	myWindow.draw(returnInfo);
	myWindow.draw(highScoreTitle);
	myWindow.draw(m_score1Text);
	myWindow.draw(m_score2Text);
	myWindow.draw(m_score3Text);
	myWindow.display();

	while (myWindow.isOpen())
	{
		sf::Event e;
		while (myWindow.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				myWindow.close();
			}
			else if (e.type == sf::Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Return)
				{
					myWindow.close();
					Menu menu;
					menu.runMenu();
				}
			}
		}
	}
}