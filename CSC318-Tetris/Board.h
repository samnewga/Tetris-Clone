#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <unordered_map>
#include <memory>

// This is a flyweight pattern to reuse the same texture in order to preserve space in memory and render time
class Game;

// FieldInfo defines the information stored in the field
struct FieldInfo
{
    FieldInfo(sf::Texture& texture, int id);
    sf::Sprite m_Sprite;
};

// Field defines the individual spaces on the board
struct Field
{
    Field& operator=(const Field& field);
    bool m_Occupied = false;
    bool m_Visible = true;
    FieldInfo* m_Info = nullptr;
};

// Board is a class to store information about the play area
class Board
{
public:
	
	// Constructors
    Board(sf::Vector2i size, Game& game);
    Board(const Board& other) = delete;
    Board& operator= (const Board& other) = delete;

	// Methods
    void update(const sf::Time& dt);
    void clean();
    void addBlock(int id, std::array<sf::Vector2i, 4> block);
    bool isOccupied(std::array<sf::Vector2i, 4> block);
    void draw(sf::RenderWindow& window);
    inline bool isToRemoveBlocks() const { return m_ToRemoveBlocks;}
    Field* getField(int x, int y);
	sf::Vector2i getSize();

private:
    int convert2D_to_1D(int x, int y);
    void cleanLines();
    void markLinesForRemoval();
    void blink();

	// Attributes
    Game& m_Game;
    std::unordered_map<unsigned int, std::unique_ptr<Field>> m_Fields;
    std::unordered_map<unsigned int, std::unique_ptr<FieldInfo>> m_FieldInfos;
    sf::Vector2i m_Size;
    std::vector<int> m_YCleaned;
    float m_ElapsedTime;
    bool m_ToRemoveBlocks;

	sf::Sprite m_BoardSprite;
	sf::Texture m_BoardTexture;
};
