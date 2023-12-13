#include "Tile.h"

Tile::Tile(char bit)
{
	_hidden_tile.setTexture(TextureManager::GetTexture("tile_hidden"));
	_revealed_tile.setTexture(TextureManager::GetTexture("tile_revealed"));
	_flagged_tile.setTexture(TextureManager::GetTexture("flag"));

	if (bit == '1')
	{
		_mine = true;
		_mine_tile.setTexture(TextureManager::GetTexture("mine"));
	}
	else
	{
		_mine = false;
	}	
	_revealed = false;
	_marked = false;
	_flag = false;
	_adjacent_mines = 0;
}

// Getters 

// function implementation taken from course materials. Credit to instructor.
sf::Sprite& Tile::GetBaseSprite()
{
	if (_revealed)
	{
		return _revealed_tile;
	} 
	else
	{
		return _hidden_tile;
	}
}

sf::Sprite& Tile::GetFlagSprite()
{
	return _flagged_tile;
}

sf::Sprite& Tile::GetNumberSprite()
{
	return _number_tile;
}

sf::Sprite& Tile::GetMineSprite()
{
	return _mine_tile;

}

unsigned int Tile::GetAdjacentMines() const
{
	return _adjacent_mines;
}

bool Tile::GetMineStatus() const
{
	return _mine;

}

bool Tile::GetFlagStatus() const
{
	return _flag;

}

bool Tile::GetRevealStatus() const
{
	return _revealed;
}

vector<Tile*>& Tile::GetAdjacentTilesList()
{
	return _adjacent_tiles;
}

bool Tile::GetMarkStatus() const
{
	return _marked;
}

bool Tile::Contains(float x, float y) const
{
	return _hidden_tile.getGlobalBounds().contains(x, y);
}

// Setters

// function implementation taken from course materials. Credit to instructor.
void Tile::SetPosition(float x, float y)
{
	_hidden_tile.setPosition(x, y);
	_revealed_tile.setPosition(x, y);
	_flagged_tile.setPosition(x, y);
	_mine_tile.setPosition(x, y);
	_number_tile.setPosition(x, y);
}

void Tile::RevealTile()
{
	_revealed = true;
}

void Tile::HideTile()
{
	_revealed = false;
}

void Tile::Flag()
{
	_flag = !_flag;
}

void Tile::SetAdjacentMines(vector<Tile*> adjacent_tiles)
{
	_adjacent_tiles = adjacent_tiles;
	for (unsigned int i = 0; i < _adjacent_tiles.size(); ++i)
	{
		if (_adjacent_tiles[i] != nullptr && _adjacent_tiles[i]->GetMineStatus())
		{
			_adjacent_mines += 1;
		}
	}
	
	// Adding texture based on number of adjacent mines.
	if (_adjacent_mines == 0)
	{
		_number_tile.setTexture(TextureManager::GetTexture("tile_revealed"));
	}
	else if (_adjacent_mines == 1)
	{
		_number_tile.setTexture(TextureManager::GetTexture("number_1"));
	}
	else if (_adjacent_mines == 2)
	{
		_number_tile.setTexture(TextureManager::GetTexture("number_2"));
	}
	else if (_adjacent_mines == 3)
	{
		_number_tile.setTexture(TextureManager::GetTexture("number_3"));
	}
	else if (_adjacent_mines == 4)
	{
		_number_tile.setTexture(TextureManager::GetTexture("number_4"));
	}
	else if (_adjacent_mines == 5)
	{
		_number_tile.setTexture(TextureManager::GetTexture("number_5"));
	}
	else if (_adjacent_mines == 6)
	{
		_number_tile.setTexture(TextureManager::GetTexture("number_6"));
	}
	else if (_adjacent_mines == 7)
	{
		_number_tile.setTexture(TextureManager::GetTexture("number_7"));
	}
	else if (_adjacent_mines == 8)
	{
		_number_tile.setTexture(TextureManager::GetTexture("number_8"));
	}
}

void Tile::MarkTile()
{
	_marked = true;
}

void Tile::RemoveMark()
{
	_marked = false;
}


