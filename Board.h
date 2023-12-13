#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Random.h"
#include "Tile.h"
using namespace std;

class Board
{
	// 2D vector of tiles
	vector<vector<Tile>> tiles;

	// Integer variables
	unsigned int _mine_count;
	unsigned int _width;
	unsigned int _height;
	unsigned int _game_status;
	int _counter_of_mines;

public:

	// Constructors 
	Board(unsigned int mine_count, unsigned int width, unsigned int height);
	Board(ifstream& file, unsigned int width, unsigned int height);

	// Behaviors
	void Reset();
	void Clear();
	void LeftClick(int x, int y);
	void RightClick(int x, int y);
	void DrawTiles(sf::RenderWindow& window);
	void ShowMines(sf::RenderWindow& window);
	void GameOver(sf::RenderWindow& window);
	void MarkTiles(vector<Tile*>& _adjacent_tiles);
	void RevealMarkedTiles();
	bool CheckGameWon();

	// Getters
	int GetCounterData() const;
	unsigned int GetGameStatus() const;
	
};

