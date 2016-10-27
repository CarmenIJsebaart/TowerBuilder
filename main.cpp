#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>

void check_collision(int &build_block_y_position, std::vector<sf::RectangleShape> block_vector, sf::RectangleShape build_block, const int block_size, bool &game_over_screen);
void check_movement_direction(sf::RectangleShape build_block, const int window_width, const int block_size, bool &block_move_right, bool &block_move_left);
void draw_blocks(sf::RenderWindow &window, sf::RectangleShape &build_block, std::vector<sf::RectangleShape> block_vector);
void move_block(sf::RectangleShape &build_block, bool block_move_right, bool block_move_left);

int main()
{
   const int window_height = 600;
   const int window_width = 300;
   sf::RenderWindow window(sf::VideoMode(window_width, window_height), "TowerBuilder", sf::Style::Titlebar | sf::Style::Close);

   std::vector<sf::RectangleShape> block_vector;

   sf::RectangleShape initial_block;
   const int initial_block_size = 50;
   const int initial_block_x_position = (window_width - initial_block_size) / 2; //in the middle of the screen
   const int initial_block_y_position = window_height - initial_block_size; //at the bottom of the screen

   initial_block.setSize(sf::Vector2f(initial_block_size, initial_block_size));
   initial_block.setPosition(initial_block_x_position, initial_block_y_position);
   initial_block.setFillColor(sf::Color::Yellow);

   block_vector.push_back(initial_block);

   sf::RectangleShape build_block;
   int block_size = 50;
   int build_block_x_position = 0;
   int build_block_y_position = 20;

   build_block.setSize(sf::Vector2f(block_size, block_size));
   build_block.setPosition(build_block_x_position, build_block_y_position);
   build_block.setFillColor(sf::Color::Red);

   sf::Clock clock;

   bool block_move_right = true;
   bool block_move_left = false;

   bool game_over_screen = false;
   sf::Font font;
   font.loadFromFile("arial.ttf");
   sf::Text game_over_tekst("Game Over", font);
   game_over_tekst.setPosition(0, 175);
   game_over_tekst.setCharacterSize(55);
   game_over_tekst.setStyle(sf::Text::Bold);
   game_over_tekst.setColor(sf::Color::Black);
   sf::Text game_over_tekst2("Press Space To \n    Start Over", font);
   game_over_tekst2.setPosition(0, 275);
   game_over_tekst2.setCharacterSize(40);
   game_over_tekst2.setStyle(sf::Text::Bold);
   game_over_tekst2.setColor(sf::Color::Black);

   while(window.isOpen())
   {
     sf::Event event;

     while(window.pollEvent(event))
     {
       switch(event.type)
       {
         case sf::Event::Closed:
           window.close();
           break;
         case sf::Event::KeyPressed:
           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
           {
              check_collision(build_block_y_position, block_vector, build_block, block_size, game_over_screen);
              build_block.setPosition(build_block.getPosition().x, build_block_y_position);
              block_vector.push_back(build_block);
              build_block.setPosition(0, 20);
              build_block_y_position = 20;
           }
           break;
         default:
           break;
        }
     }

     const double update_time = 10; //milliseconds

     if(clock.getElapsedTime().asMilliseconds() >= update_time)
     {
       move_block(build_block, block_move_right, block_move_left);
       clock.restart();
     }

     window.clear();
     window.draw(initial_block);
     if(game_over_screen == false)
     {
       draw_blocks(window, build_block, block_vector);
     }
     else
     {
       window.clear(sf::Color::Magenta);
       window.draw(game_over_tekst);
       window.draw(game_over_tekst2);
     }
     window.display();

     check_movement_direction(build_block, window_width, block_size, block_move_right, block_move_left);
   }
}

void check_collision(int &build_block_y_position, std::vector<sf::RectangleShape> block_vector, sf::RectangleShape build_block, const int block_size, bool &game_over_screen)
{
  int size = block_vector.size();

  if(build_block.getPosition().x >= block_vector[size - 1].getPosition().x - block_size &&
     build_block.getPosition().x <= block_vector[size - 1].getPosition().x + block_size)
  {
    do
    {
      build_block_y_position += 1;
    }
    while(build_block_y_position < block_vector[size - 1].getPosition().y - 50);
  }
  else
  {
    game_over_screen = true;
  }
}

void check_movement_direction(sf::RectangleShape build_block, const int window_width, const int block_size, bool &block_move_right, bool &block_move_left)
{
  if(build_block.getPosition().x >= window_width - block_size && block_move_right == true)
  {
    block_move_right = false;
    block_move_left = true;
    assert(block_move_right == true || block_move_left == true);
    assert(block_move_right == false || block_move_left == false);
  }
  else if(build_block.getPosition().x <= 0 && block_move_left == true)
  {
    block_move_left = false;
    block_move_right = true;
    assert(block_move_right == true || block_move_left == true);
    assert(block_move_right == false || block_move_left == false);
  }
}

void draw_blocks(sf::RenderWindow &window, sf::RectangleShape &build_block, std::vector<sf::RectangleShape> block_vector)
{
  window.draw(build_block);
  for(const auto &blocks : block_vector)
  {
    window.draw(blocks);
  }
}

void move_block(sf::RectangleShape &build_block, bool block_move_right, bool block_move_left)
{
  if(block_move_right == true)
  {
    build_block.move(1, 0);
  }
  else if(block_move_left == true)
  {
    build_block.move(-1, 0);
  }
}
