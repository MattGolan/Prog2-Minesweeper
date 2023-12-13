#include "Board.h"
using namespace std;

Board::Board(unsigned int mine_count, unsigned int width, unsigned int height)
{
	_mine_count = mine_count;
	_width = width;
	_height = height;
	Reset();
}

Board::Board(ifstream & file, unsigned int width, unsigned int height)
	{
		_width = width;
		_height = height;
		_mine_count = 0;
		for (unsigned int i = 0; i < _height; ++i)
		{
			string string_line;
			getline(file, string_line);
			vector<Tile> row;
			for (unsigned j = 0; j < _width; ++j)
			{
				Tile current_tile(string_line[j]);
				if (string_line[j] == '1')
					_mine_count += 1;
				current_tile.SetPosition(j * 32, i * 32);
				row.push_back(current_tile);
			}
			tiles.push_back(row);
		}
		_counter_of_mines = _mine_count;

		for (unsigned int i = 0; i < tiles.size(); ++i)
		{
			for (unsigned int j = 0; j < tiles[i].size(); ++j)
			{
				vector<Tile*> adjacent_tiles;
				Tile* upper_left = nullptr;
				Tile* upper_middle = nullptr;
				Tile* upper_right = nullptr;
				Tile* middle_left = nullptr;
				Tile* middle_right = nullptr;
				Tile* lower_left = nullptr;
				Tile* lower_middle = nullptr;
				Tile* lower_right = nullptr;
				if (i > 0)
				{
					upper_middle = &tiles[i - 1][j];
					if (j > 0)
					{
						upper_left = &tiles[i - 1][j - 1];
					}
					if (j < tiles[i].size() - 1)
					{
						upper_right = &tiles[i - 1][j + 1];
					}
				}
				if (j > 0)
				{
					middle_left = &tiles[i][j - 1];
				}
				if (j < tiles[i].size() - 1)
				{
					middle_right = &tiles[i][j + 1];
				}
				if (i < tiles.size() - 1)
				{
					lower_middle = &tiles[i + 1][j];
					if (j > 0)
					{
						lower_left = &tiles[i + 1][j - 1];
					}
					if (j < tiles[i].size() - 1)
					{
						lower_right = &tiles[i + 1][j + 1];
					}
				}
				adjacent_tiles.push_back(upper_left);
				adjacent_tiles.push_back(upper_middle);
				adjacent_tiles.push_back(upper_right);
				adjacent_tiles.push_back(middle_left);
				adjacent_tiles.push_back(middle_right);
				adjacent_tiles.push_back(lower_left);
				adjacent_tiles.push_back(lower_middle);
				adjacent_tiles.push_back(lower_right);

				tiles[i][j].SetAdjacentMines(adjacent_tiles);

			}
		}
	}

void Board::Reset()
{
	// Determines random locations for mines.
	tiles.clear();
	_game_status = 0;
	map<unsigned int, unsigned int> mine_locations;
	_counter_of_mines = _mine_count;

	while (mine_locations.size() < _mine_count)
	{
		unsigned int random_number = Random::RandomInt(0, (_width * _height) - 1);
		mine_locations[random_number] = random_number;
	}

	unsigned int counter = 0;

	for (unsigned int i = 0; i < _height; ++i)
	{
		vector<Tile> row;
		for (unsigned j = 0; j < _width; ++j)
		{
			char current_bit;
			if (mine_locations.find(counter) != mine_locations.end())
			{
				current_bit = '1';
			}
			else
			{
				current_bit = '0';
			}
			counter += 1;
			Tile current_tile(current_bit);
			current_tile.SetPosition(j * 32, i * 32);
			row.push_back(current_tile);
		}
		tiles.push_back(row);
	}

	// Creates pointers to adjacent tiles.
	for (unsigned int i = 0; i < tiles.size(); ++i)
	{
		for (unsigned int j = 0; j < tiles[i].size(); ++j)
		{
			vector<Tile*> adjacent_tiles;
			Tile* upper_left = nullptr;
			Tile* upper_middle = nullptr;
			Tile* upper_right = nullptr;
			Tile* middle_left = nullptr;
			Tile* middle_right = nullptr;
			Tile* lower_left = nullptr;
			Tile* lower_middle = nullptr;
			Tile* lower_right = nullptr;
			if (i > 0)
			{
				upper_middle = &tiles[i - 1][j];
				if (j > 0)
				{
					upper_left = &tiles[i - 1][j - 1];
				}
				if (j < tiles[i].size() - 1)
				{
					upper_right = &tiles[i - 1][j + 1];
				}
			}
			if (j > 0)
			{
				middle_left = &tiles[i][j - 1];
			}
			if (j < tiles[i].size() - 1)
			{
				middle_right = &tiles[i][j + 1];
			}
			if (i < tiles.size() - 1)
			{
				lower_middle = &tiles[i + 1][j];
				if (j > 0)
				{
					lower_left = &tiles[i + 1][j - 1];
				}
				if (j < tiles[i].size() - 1)
				{
					lower_right = &tiles[i + 1][j + 1];
				}
			}
			adjacent_tiles.push_back(upper_left);
			adjacent_tiles.push_back(upper_middle);
			adjacent_tiles.push_back(upper_right);
			adjacent_tiles.push_back(middle_left);
			adjacent_tiles.push_back(middle_right);
			adjacent_tiles.push_back(lower_left);
			adjacent_tiles.push_back(lower_middle);
			adjacent_tiles.push_back(lower_right);

			tiles[i][j].SetAdjacentMines(adjacent_tiles);

		}
	}
}

void Board::Clear()
{
	_counter_of_mines = _mine_count;
	_game_status = 0;

	for (unsigned int i = 0; i < tiles.size(); ++i)
	{
		for (unsigned int j = 0; j < tiles[i].size(); ++j)
		{
			if (tiles[i][j].GetFlagStatus())
			{
				tiles[i][j].Flag();
			}
			if (tiles[i][j].GetRevealStatus())
			{
				tiles[i][j].HideTile();
			}

		}
	}

}

void Board::LeftClick(int x, int y)
	{
		for (unsigned int i = 0; i < tiles.size(); ++i)
		{
			for (unsigned int j = 0; j < tiles[i].size(); ++j)
			{
				if (tiles[i][j].Contains(x, y) && !tiles[i][j].GetFlagStatus())
				{
					tiles[i][j].RevealTile();
					if (tiles[i][j].GetMineStatus())
					{
						_game_status = 1;
					}
					else if (tiles[i][j].GetAdjacentMines() == 0)
					{
						MarkTiles(tiles[i][j].GetAdjacentTilesList());
						for (unsigned int i = 0; i < 100; ++i)
						{
							RevealMarkedTiles();
						}
					}
					break;
				}

			}

		}
	}
	
void Board::RightClick(int x, int y)
{
	for (unsigned int i = 0; i < tiles.size(); ++i)
	{
		for (unsigned int j = 0; j < tiles[i].size(); ++j)
		{
			if (tiles[i][j].Contains(x, y))
			{
				if (tiles[i][j].GetFlagStatus())
				{
					_counter_of_mines += 1;
				}
				else
				{
					_counter_of_mines -= 1;
				}
				tiles[i][j].Flag();
				break;
			}
		}
	}
}

void Board::DrawTiles(sf::RenderWindow& window)
{
	// Draw base tile.
	for (unsigned int i = 0; i < tiles.size(); ++i)
	{
		for (unsigned int j = 0; j < tiles[i].size(); ++j)
		{
			window.draw(tiles[i][j].GetBaseSprite());
			if (tiles[i][j].GetRevealStatus())
			{
				if (tiles[i][j].GetMineStatus())
				{
					window.draw(tiles[i][j].GetMineSprite());
				}
				else if (tiles[i][j].GetAdjacentMines() > 0)
				{
					window.draw(tiles[i][j].GetNumberSprite());
				}

			}
			else
			{
				if (tiles[i][j].GetFlagStatus())
				{
					window.draw(tiles[i][j].GetFlagSprite());
				}
			}
			
		}
	}
}

void Board::ShowMines(sf::RenderWindow& window)
{
	if (!CheckGameWon())
	{
		for (unsigned int i = 0; i < tiles.size(); ++i)
		{
			for (unsigned int j = 0; j < tiles[i].size(); ++j)
			{
				if (tiles[i][j].GetMineStatus())
				{
					window.draw(tiles[i][j].GetMineSprite());
				}
			}
		}
	}
}

void Board::GameOver(sf::RenderWindow& window)
{
	if (!CheckGameWon())
	{
		for (unsigned int i = 0; i < tiles.size(); ++i)
		{
			for (unsigned int j = 0; j < tiles[i].size(); ++j)
			{
				if (tiles[i][j].GetMineStatus())
				{
					tiles[i][j].RevealTile();
					window.draw(tiles[i][j].GetBaseSprite());
				}
			}
		}

		ShowMines(window);
	}
	else
	{
		for (unsigned int i = 0; i < tiles.size(); ++i)
		{
			for (unsigned int j = 0; j < tiles[i].size(); ++j)
			{
				if (tiles[i][j].GetFlagStatus())
				{
					window.draw(tiles[i][j].GetFlagSprite());
				}
			}
		}
	}


}

void Board::MarkTiles(vector<Tile*>& _adjacent_tiles)
{
	for (unsigned int i = 0; i < _adjacent_tiles.size(); ++i)
	{
		if (_adjacent_tiles[i] != nullptr && !_adjacent_tiles[i]->GetMineStatus() && !_adjacent_tiles[i]->GetFlagStatus())
		{
			_adjacent_tiles[i]->MarkTile();
		}
	}
}

void Board::RevealMarkedTiles()
{
	for (unsigned int i = 0; i < tiles.size(); ++i)
	{
		for (unsigned int j = 0; j < tiles[i].size(); ++j)
		{
			if (tiles[i][j].GetMarkStatus() && !tiles[i][j].GetFlagStatus())
			{
				tiles[i][j].RevealTile();
				tiles[i][j].RemoveMark();
				if (tiles[i][j].GetAdjacentMines() == 0)
				{
					MarkTiles(tiles[i][j].GetAdjacentTilesList());
				}
			}
		}
	}
} 

bool Board::CheckGameWon()
{
	for (unsigned int i = 0; i < tiles.size(); ++i)
	{
		for (unsigned int j = 0; j < tiles[i].size(); ++j)
		{
			if (!tiles[i][j].GetMineStatus() && !tiles[i][j].GetRevealStatus())
				return false;
		}
	}
	for (unsigned int i = 0; i < tiles.size(); ++i)
	{
		for (unsigned int j = 0; j < tiles[i].size(); ++j)
		{
			if (tiles[i][j].GetMineStatus() && !tiles[i][j].GetFlagStatus())
				tiles[i][j].Flag();
				
		}
	}
	_counter_of_mines = 0;
	return true;
}

// Getters

int Board::GetCounterData() const
{
	return _counter_of_mines;
}

unsigned int Board::GetGameStatus() const
{
	return _game_status;
}

