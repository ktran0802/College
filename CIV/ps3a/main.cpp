#include <iostream>
#include "nbody.hpp"

const int window_side = 500;
const int window_height = 500;

int main(int argc, char* argv[])
{
  nbody test();
  nbody test2();
  
  std::cout << "Sup dawg.\n";
  
  sf::RenderWindow window(sf::VideoMode(window_side, window_height), "The Solar System");

  // Change the framerate to make it easier to see the image moving.
  window.setFramerateLimit(1);

  // Window loop
  while (window.isOpen())
  {
    // Process events
    sf::Event event;

    while(window.pollEvent(event))
    {
      // Close window : exit
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      // Pressing escape will quit the program.
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
    }

    window.clear();
    //window.draw(obj);   // Call the draw object in the sierpinkski class
    window.display();
  }
  
/*

  // Make sure we are given exactly 3 arguments
  if(argc < 3 || argc > 4)
  {
    // Let the user know the correct way of calling the program.
    cout << "./sierpinski [recursion-depth] [side-length] \n";
    return -1;
  }

  int depth = atoi(argv[1]);
  int side = atoi(argv[2]);

  cout << "depth: " << depth << endl;
  cout << "side: " << side << endl;

  // Added this since I do not think it would be logical to have negative (-2, -3, etc) recursion
  if(depth < 0)
  {
    cout << "depth should be greater than 0 - illogical to have negative recursion.\n";
    return -2;
  }

  // Sierpinkski object, calls default constructor
  Sierpinski obj(depth, side);

  int window_height = (int)(0.5*sqrt(3.0)*(float)side);

  sf::RenderWindow window(sf::VideoMode(side, window_height), "Sierpinkski");

  // Change the framerate to make it easier to see the image moving.
  window.setFramerateLimit(1);

  // Window loop
  while (window.isOpen())
  {
    // Process events
    sf::Event event;

    while(window.pollEvent(event))
    {
      // Close window : exit
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      // Pressing escape will quit the program.
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
    }

    window.clear();
    window.draw(obj);   // Call the draw object in the sierpinkski class
    window.display();
  }











*/
  
  return 0;
}