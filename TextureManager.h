#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

// TextureManager class taken from Project 3 materials. Credit to instructor for approach.
class TextureManager
{
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string textureName);
public:
	static sf::Texture& GetTexture(string textureName);
	static void Clear(); 
};

