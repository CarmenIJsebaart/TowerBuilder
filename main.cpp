#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>

void check_movement_direction(sf::RectangleShape build_block, const int window_width, const int block_size, bool &block_move_right, bool &block_move_left);
void draw_blocks(sf::RenderWindow &window, sf::RectangleShape &build_block, std::vector<sf::RectangleShape> block_vector);
void move_block(sf::RectangleShape &build_block, bool block_move_right, bool block_move_left);

int main()
{
   const int window_height = 600;
   const int window_width = 300;
   sf::RenderWindow window(sf::VideoMode(window_width, window_height), "TowerBuilder", sf::Style::Titlebar | sf::Style::Close);

   sf::RectangleShape build_block;
   const int block_size = 50;
   const int build_block_x_position = 0;
   int build_block_y_position = 20;

   build_block.setSize(sf::Vector2f(block_size, block_size));
   build_block.setPosition(build_block_x_position, build_block_y_position);
   build_block.setFillColor(sf::Color::Red);

   sf::Clock clock;

   std::vector<sf::RectangleShape> block_vector;

   bool block_move_right = true;
   bool block_move_left = false;

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
                build_block.move(0, window_height - block_size - build_block_y_position);
                block_vector.push_back(build_block);
                build_block.setPosition(0, 20);
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
     draw_blocks(window, build_block, block_vector);
     window.display();

     check_movement_direction(build_block, window_width, block_size, block_move_right, block_move_left);
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
