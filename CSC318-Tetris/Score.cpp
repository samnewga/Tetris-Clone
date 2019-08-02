#include "stdafx.h"
#include "Score.h"

// Set up defaults
Score::Score() : m_Font(), m_LevelText(), m_ScoreText(), m_ClearedLinesText(), m_Score(0), m_LinesCleared(0)
{
	sf::Vector2f scoreTextPosition = { 230,160 };
	sf::Vector2f levelTextPosition = { 230,200 };
	sf::Vector2f clearedLinesTextPosition = { 230,240 };

    m_Font.loadFromFile("Resources/Timeless-Bold.ttf");
    m_ScoreText.setFont(m_Font);
    m_ScoreText.setCharacterSize(15);
	m_ScoreText.setPosition(scoreTextPosition);

    m_LevelText.setFont(m_Font);
    m_LevelText.setCharacterSize(15);
    m_LevelText.setPosition(levelTextPosition);

    m_ClearedLinesText.setFont(m_Font);
    m_ClearedLinesText.setCharacterSize(15);
    m_ClearedLinesText.setPosition(clearedLinesTextPosition);
}

// update called from Game, updated every frame
void Score::update(const sf::Time &dt) 
{
    m_LevelText.setString(std::string{"Level:\n" + std::to_string(m_LinesCleared / 10)});
    m_ScoreText.setString(std::string{"Score:\n" + std::to_string(m_Score)});
    m_ClearedLinesText.setString(std::string{"Lines:\n" + std::to_string(m_LinesCleared)});
}

// Reset scores and lines to default
void Score::reset() 
{
    m_LinesCleared = 0;
    m_Score = 0;
}

// Draw score, lines cleared and level to screen
void Score::draw(sf::RenderWindow &window) 
{
    window.draw(m_LevelText);
    window.draw(m_ScoreText);
    window.draw(m_ClearedLinesText);
}

// add number of lines cleared.
// set score
void Score::addClearedLines(int num) 
{
    m_LinesCleared += num;
    int level = m_LinesCleared / 10;
    switch (num)
	{
        case (1): 
		{
            m_Score += 40 * (level + 1);
            break;
        }
        case (2): 
		{
            m_Score += 100 * (level + 1);
            break;
        }
        case (3): 
		{
            m_Score += 300 * (level + 1);
            break;
        }
        case (4):
		{
            m_Score += 1200 * (level + 1);
            break;
        }
    }
}

// returns int for current level.
// Reducing the divide by number will decrease number of lines required to level up
int Score::getLevel() const 
{
    return m_LinesCleared / 10;
}
int Score::getScore()
{
	return m_Score;
}