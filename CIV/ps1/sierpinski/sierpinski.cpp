#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "sierpinski.hpp"

using namespace std;

/*
         _top
           .
          / \
         /   \
        /     \
    p1 .-------. p3
      / \     / \
     /   \   /   \
    /     \ /     \
   .-------.-------.
 _left    p2     _right

 The above is an ASCII representation of what this code does.
 We have _top, _left, _right member variables we use to
 to draw the triangle in the middle using p1/p2/p3

 */

// Constructor                               (Initialize private variables)
Sierpinski::Sierpinski(int depth, int side) : _depth (depth)
{
  // Initialize other member variables - top, left, right
  _top = sf::Vector2f(side / 2, 0);

  // Calculate the height using triangle geometry
  float height = .5 * sqrt(3.0) * (float) side;

  _left = sf::Vector2f(0, height);
  _right = sf::Vector2f(side-1, height);

  /* Call the constructor that accepts 3 points.
   * First find p1, p2, p3.
   * To do so, use the midpt formula:
   *
   * ( ( (x1 + x2) / 2) , ( (y1 + y2) / 2) )
   *
   */


  _p1 = sf::Vector2f( ((_top.x + _left.x) / 2), ((_top.y + _left.y) / 2) );
  _p2 = sf::Vector2f( ((_left.x + _right.x) / 2), ((_left.y + _right.y) / 2) );
  _p3 = sf::Vector2f( ((_top.x + _right.x) / 2), ((_top.y + _right.y) / 2) );

  // Now that we have the points, create 3 triangles
  _triangle1 = new Sierpinski(_p1, _left, _p2, depth - 1);
  _triangle2 = new Sierpinski(_top, _p1, _p3, depth - 1);
  _triangle3 = new Sierpinski(_p3, _p2, _right, depth - 1);
}


Sierpinski::Sierpinski(sf::Vector2f top, sf::Vector2f left,
                       sf::Vector2f right, int depth) : _depth (depth)
{
  // End of the recurrsion.
  if(_depth == 0)
  {
    // Set the 3 triangle pointers to null
    _triangle1 = NULL;
    _triangle2 = NULL;
    _triangle3 = NULL;

    return;
  }

  // Set member variables - points of the triangle
  _top = top;
  _left = left;
  _right = right;

  // Set the filled triangle points
  _p1 = sf::Vector2f( ((top.x + left.x) / 2), ((top.y + left.y) / 2) );
  _p2 = sf::Vector2f( ((left.x + right.x) / 2), ((left.y + right.y) / 2) );
  _p3 = sf::Vector2f( ((top.x + right.x) / 2), ((top.y + right.y) / 2) );

  // Now that we have the points, create 3 triangles
  _triangle1 = new Sierpinski(_p1, left, _p2, depth - 1);
  _triangle2 = new Sierpinski(top, _p1, _p3, depth - 1);
  _triangle3 = new Sierpinski(_p3, _p2, right, depth - 1);
}


// Destructor
Sierpinski::~Sierpinski()
{
  // Need to destroy all the objects that were created


}


// Generates a vector of Sierpinski triangles to draw.
vector <sf::ConvexShape> Sierpinski::make_vector(Sierpinski* const& tri, vector<sf::ConvexShape>& triangles) const
{
  // Check for the end of the recursion
  if(tri->_depth == 0)
  {
    return triangles;
  }

  // Check the dimensions of the triangle
//   cout << "_depth is: " << tri->_depth << endl;
//   cout << "_top is: (" << tri->_top.x << ", " << _top.y << ") \n";
//   cout << "_left is (" << tri->_left.x << ", " << _left.y << ") \n";
//   cout << "_right is (" << tri->_right.x << ", " << _right.y << ") \n";

  // Otherwise free to make points and add them to the vector.
  sf::ConvexShape triangle;
  triangle.setPointCount(3);
  triangle.setPoint(0, tri->_p1);
  triangle.setPoint(1, tri->_p2);
  triangle.setPoint(2, tri->_p3);
  triangle.setFillColor(sf::Color::Black);

  triangles.push_back(triangle);   // Add to the back of the vector

  // Recursive calls
  triangles = make_vector(tri->_triangle1, triangles);
  triangles = make_vector(tri->_triangle2, triangles);
  triangles = make_vector(tri->_triangle3, triangles);

  return triangles;
}


void Sierpinski::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Check the beginning dimensions of the overall triangle
//   cout << "_depth is: " << _depth << endl;
//   cout << "_top is: (" << _top.x << ", " << _top.y << ") \n";
//   cout << "_left is (" << _left.x << ", " << _left.y << ") \n";
//   cout << "_right is (" << _right.x << ", " << _right.y << ") \n";

  // This vector will hold all the triangles we want to draw.
  vector <sf::ConvexShape> vec_triangle;

  // The outside triangle.
  sf::ConvexShape triangle;
  triangle.setPointCount(3);
  triangle.setPoint(0, _left);
  triangle.setPoint(1, _right);
  triangle.setPoint(2, _top);

  // The filled upside down triangle.
  sf::ConvexShape triangle2;
  triangle2.setPointCount(3);
  triangle2.setPoint(0, _p1);
  triangle2.setPoint(1, _p2);
  triangle2.setPoint(2, _p3);
  triangle2.setFillColor(sf::Color::Black);

  // Draw the two triangles above.
  target.draw(triangle);
  target.draw(triangle2);

  // Now generate a vector to draw all the other triangles (if any)
  vec_triangle = make_vector(_triangle1, vec_triangle);
  vec_triangle = make_vector(_triangle2, vec_triangle);
  vec_triangle = make_vector(_triangle3, vec_triangle);

  // Now we can draw everything in the vector

  // Test the size of the vector.
  cout << "Size of the vector is: " << vec_triangle.size() << endl;

  for(vector<sf::ConvexShape>::iterator it = vec_triangle.begin();
      it != vec_triangle.end(); it++)
      {
        target.draw(*it);
      }
}
