#pragma once
#include <vector>
#include <iostream>
#include "TextureManager.h"
using namespace std;

class Tile
{
	// Sprites
	sf::Sprite _hidden_tile;
	sf::Sprite _revealed_tile;
	sf::Sprite _flagged_tile;
	sf::Sprite _mine_tile;
	sf::Sprite _number_tile;

	// Boolean variables
	bool _flag;
	bool _revealed;
	bool _marked;
	bool _mine;

	// Integer variable
	unsigned int _adjacent_mines;

	//Vector of object pointers
	vector<Tile*> _adjacent_tiles;
	

public:

	// Constructor
	Tile(char bit);

	// Getters
	sf::Sprite& GetBaseSprite();
	sf::Sprite& GetFlagSprite();
	sf::Sprite& GetNumberSprite();
	sf::Sprite& GetMineSprite();
	bool GetMineStatus() const;
	bool GetFlagStatus() const;
	bool GetRevealStatus()const ;
	unsigned int GetAdjacentMines() const;
	vector<Tile*>& GetAdjacentTilesList();
	bool GetMarkStatus() const;
	bool Contains(float x, float y) const ;

	// Setters
	void SetPosition(float x, float y);
	void RevealTile();
	void HideTile();
	void Flag();
	void SetAdjacentMines(vector<Tile*> adjacent_tiles);
	void MarkTile();
	void RemoveMark();
	
};

