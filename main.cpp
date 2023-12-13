#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include "TextureManager.h"
#include "Random.h"
#include "Board.h"
using namespace std;

/*                          ==================      Credits      ================== 
*  Credit to Professor Fox for TextureManager and Random.
* Tile, Board, and Project3 were implemented using concepts from COP3503C course materials and 
SFML tutorial materials (see https://www.sfml-dev.org/tutorials/2.6/ ). Credit to all authors of educational materials */

// Function declarations.
void DrawCounter(sf::RenderWindow& window, Board* current_board, vector<sf::Sprite> numbers, unsigned int height);

int main()
{
    // Read data from config file to create default board.
    ifstream config_board_file;
    config_board_file.open("boards/config.cfg");
    unsigned int width;
    unsigned int height;
    unsigned int mine_count;
    config_board_file >> width;
    config_board_file >> height;
    config_board_file >> mine_count;
    Board config_board(mine_count, width, height);
    Board* current_board = &config_board;

    // Read board files from input folders. Set to the same width and height as the config board. (Project Overview, Page 9)
    ifstream test_board_1_file;
    test_board_1_file.open("boards/testboard1.brd");
    ifstream test_board_2_file;
    test_board_2_file.open("boards/testboard2.brd");
    ifstream test_board_3_file;
    test_board_3_file.open("boards/testboard3.brd");
    Board test_board_1(test_board_1_file, width, height);
    Board test_board_2(test_board_2_file, width, height);
    Board test_board_3(test_board_3_file, width, height);
    
    // Setup Game: declare bool for settings, create window, create buttons.
    bool debug_status = false;
    bool game_continues = true;
    float button_length = 64;
    unsigned int center_width_var = ((width * 32) - button_length) / 2;
    sf::RenderWindow window(sf::VideoMode(width * 32, (height * 32) + 100), "Minesweeper");
    sf::Sprite debug_button(TextureManager::GetTexture("debug"));
    debug_button.setPosition(center_width_var + 128, height * 32);
    sf::Sprite test_button_1(TextureManager::GetTexture("test_1"));
    test_button_1.setPosition(center_width_var + 194, height * 32);
    sf::Sprite test_button_2(TextureManager::GetTexture("test_2"));
    test_button_2.setPosition(center_width_var + 256, height * 32);
    sf::Sprite test_button_3(TextureManager::GetTexture("test_3"));
    test_button_3.setPosition(center_width_var + 320, height * 32);
    sf::Sprite happy_face_button(TextureManager::GetTexture("face_happy"));
    happy_face_button.setPosition(center_width_var, height * 32);
    sf::Sprite face_win_button(TextureManager::GetTexture("face_win"));
    face_win_button.setPosition(center_width_var, height * 32);
    sf::Sprite face_lose_button(TextureManager::GetTexture("face_lose"));
    face_lose_button.setPosition(center_width_var, height * 32);

    // Creates a vector of sprites for the counter.
    vector<sf::Sprite> numbers;
    sf::Texture digits_texture;
    digits_texture.loadFromFile("images/digits.png");

    sf::Sprite zero_sprite(digits_texture);
    zero_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    numbers.push_back(zero_sprite);

    sf::Sprite one_sprite(digits_texture);
    one_sprite.setTextureRect(sf::IntRect(21, 0, 21, 32));
    numbers.push_back(one_sprite);
 
    sf::Sprite two_sprite(digits_texture);
    two_sprite.setTextureRect(sf::IntRect(42, 0, 21, 32));
    numbers.push_back(two_sprite);

    sf::Sprite three_sprite(digits_texture);
    three_sprite.setTextureRect(sf::IntRect(63, 0, 21, 32));
    numbers.push_back(three_sprite);

    sf::Sprite four_sprite(digits_texture);
    four_sprite.setTextureRect(sf::IntRect(84, 0, 21, 32));
    numbers.push_back(four_sprite);

    sf::Sprite five_sprite(digits_texture);
    five_sprite.setTextureRect(sf::IntRect(105, 0, 21, 32));
    numbers.push_back(five_sprite);

    sf::Sprite six_sprite(digits_texture);
    six_sprite.setTextureRect(sf::IntRect(126, 0, 21, 32));
    numbers.push_back(six_sprite);

    sf::Sprite seven_sprite(digits_texture);
    seven_sprite.setTextureRect(sf::IntRect(147, 0, 21, 32));
    numbers.push_back(seven_sprite);

    sf::Sprite eight_sprite(digits_texture);
    eight_sprite.setTextureRect(sf::IntRect(168, 0, 21, 32));
    numbers.push_back(eight_sprite);

    sf::Sprite nine_sprite(digits_texture);
    nine_sprite.setTextureRect(sf::IntRect(189, 0, 21, 32));
    numbers.push_back(nine_sprite);

    sf::Sprite negative_sprite(digits_texture);
    negative_sprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
    numbers.push_back(negative_sprite);

    //Draw initial board before entering loop.
    current_board->DrawTiles(window);
    window.draw(happy_face_button);
    window.draw(test_button_1);
    window.draw(test_button_2);
    window.draw(test_button_3);
    window.draw(debug_button);
    if (current_board->GetCounterData() != 0)
    {
        DrawCounter(window, current_board, numbers, height);
    }
    window.display();
    
    // Loops through game-related events until the window is closed. 
    while (window.isOpen())
    { 
        // Outer event loop.
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // Credit to educational materials for general structor of click event branches.
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    current_board->RightClick(mousePosition.x, mousePosition.y);
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    current_board->LeftClick(mousePosition.x, mousePosition.y);

                    if (happy_face_button.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        current_board = &config_board;
                        current_board->Reset();
                    }
                    else if (debug_button.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        debug_status = !debug_status;
                    }
                    else if (test_button_1.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        current_board = &test_board_1;
                        current_board->Clear();

                    }
                    else if (test_button_2.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        current_board = &test_board_2;
                        current_board->Clear();
                    }
                    else if (test_button_3.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        current_board = &test_board_3;
                        current_board->Clear();
                    }
                }
            }
            // Clears window
            window.clear();
            // Draws sprites
            current_board->DrawTiles(window);
            window.draw(happy_face_button);
            window.draw(test_button_1);
            window.draw(test_button_2);
            window.draw(test_button_3);
            window.draw(debug_button);
            if (debug_status)
                current_board->ShowMines(window);
            if (current_board->GetGameStatus() == 0)
                window.draw(happy_face_button);
            else if (current_board->GetGameStatus() == 1)
            {
                window.draw(face_lose_button);
                game_continues = false;
                current_board->GameOver(window);
            }
            if (current_board->CheckGameWon())
            {
                window.draw(face_win_button);
                game_continues = false;
                current_board->GameOver(window);
            }
            // Draws counter.
            if (current_board->GetCounterData() != 0)
            {
                DrawCounter(window, current_board, numbers, height);
            }
            // Catches edge case when the counter is zero.
            else
            {
                zero_sprite.setPosition(21, height * 32);
                window.draw(zero_sprite);
            }
            // Displays all drawn sprites.
            window.display();
            while (!game_continues)
            {
                // Inner event loop for when the game ends.
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                            if (happy_face_button.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                            {
                                test_board_1.Clear();
                                test_board_2.Clear();
                                test_board_3.Clear();
                                current_board = &config_board;
                                current_board->Reset();
                                game_continues = true;
                            }
                            else if (test_button_1.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                            {
                                test_board_2.Clear();
                                test_board_3.Clear();
                                config_board.Reset();
                                current_board = &test_board_1;
                                current_board->Clear();
                                game_continues = true;
                            }
                            else if (test_button_2.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                            {
                                test_board_1.Clear();
                                test_board_3.Clear();
                                config_board.Reset();
                                current_board = &test_board_2;
                                current_board->Clear();
                                game_continues = true;
                            }
                            else if (test_button_3.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                            {
                                test_board_1.Clear();
                                test_board_2.Clear();
                                config_board.Reset();
                                current_board = &test_board_3;
                                current_board->Clear();
                                game_continues = true;
                            }
                        }
                    }
                }
            }
        }
    }
    // Clear out any textures before the program ends
    TextureManager::Clear();

    return 0;
}

// Function definition.
void DrawCounter(sf::RenderWindow& window, Board* current_board, vector<sf::Sprite> numbers, unsigned int height)
{
    int current_count = current_board->GetCounterData();
    unsigned int  digit_width= 21;
    unsigned int position = 0;
    // Checks sign. Adds a negative if necessary.
    if (current_count < 0)
    {
        numbers[10].setPosition(position * digit_width, height * 32);
        window.draw(numbers[10]);
    }
    position += 1;
    // Table 3.6.1 includes list of math functions.
    current_count = fabs(current_count);

    // Creates a vector of individual digits.
    vector<int> individual_digits;
    while (current_count > 0)
    {
        int last_digit = current_count % 10;
        individual_digits.push_back(last_digit);
        current_count = current_count / 10;
    }

    // Iterates through vector of digits and draws corresponding sprite.
    for (int i = individual_digits.size() - 1; i >= 0; --i)
    {
        numbers[individual_digits[i]].setPosition(position * digit_width, height * 32);
        window.draw(numbers[individual_digits[i]]);
        position += 1;
    }
}