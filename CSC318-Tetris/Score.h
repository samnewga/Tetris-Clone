#pragma once

#include <SFML/Graphics.hpp>

// Score class is used to store and manipulate the score window information
class Score 
{
public:

	// Constructors
    Score();
    Score(const Score& other) = delete;

	// Methods
    Score& operator = (const Score& other) = delete;
    void draw(sf::RenderWindow& window);
    void reset();
    void addClearedLines(int num);
    void update(const sf::Time& dt);
    int getLevel() const;
	int getScore();
private:

	// Attributes
    sf::Font m_Font;
    sf::Text m_LevelText;
    sf::Text m_ScoreText;
    sf::Text m_ClearedLinesText;
    int m_Score;
    int m_LinesCleared;
};