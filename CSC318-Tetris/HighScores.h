#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>

class HighScores
{
public:
	// Constructor
	HighScores(std::string);

	// Methods
	void retrieveHighScores();
	void compareScores(int);
	void printScores();
	void drawHighScores(sf::RenderWindow& window);
	int getScore1();
	int getScore2();
	int getScore3();
private:
	// Attributes
	std::fstream scoreFile;
	std::string fileName;
	int score1, score2, score3;
	sf::Text m_score1Text, m_score2Text, m_score3Text;
	sf::Font m_font;
	sf::Text highScoreTitle;
	

	// Methods
	void openScoreFile(std::ios_base::openmode);
	void closeScoreFile();
	void updateScoreFile();
};