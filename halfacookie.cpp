/**
 * @file    halfacookie.cpp
 * @author  William Weston
 * @brief   Half a Cookie Problem From Kattis
 * @version 0.1
 * @date    2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/halfacookie
 * 
 * Formula: r * r * acos( 1.0 - h/r ) - (r - h) * sqrt(2 * r * h - h * h)
 *             
 *             where: r = radius, h = height
 * 
 * From: https://en.wikipedia.org/wiki/Circular_segment#Arc_length_and_area
 */


#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>


auto main() -> int
{
   constexpr auto pi = 3.1415926535897932384626433832795028841971693993751;
   
   double radius, x, y;

   while ( std::cin >> radius >> x >> y )
   {
      if ( auto const apothem = std::sqrt( x * x + y * y ); radius < apothem )
         std::cout << "miss\n";
      else
      {
         auto const circle_area    = pi * radius * radius;
         auto const height         = radius - apothem;
         auto const segment_area   = radius * radius * std::acos( 1.0 - ( height / radius ) ) - ( radius - height ) * std::sqrt( 2 * radius * height - height * height );
         auto const remaining_area = circle_area - segment_area;

         std::cout << std::fixed << std::setprecision( 6 );
          if ( segment_area < remaining_area )
            std::cout <<  remaining_area << ' ' << segment_area << '\n';
         else
            std::cout << segment_area << ' ' << remaining_area << '\n';
      }
   }

   return EXIT_SUCCESS;
}
