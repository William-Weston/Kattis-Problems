/**
 * @file    ladder.cpp
 * @author  William Weston
 * @brief   Ladder Problem From Kattis
 * @version 0.1
 * @date    2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/ladder
 */


#include <cmath>
#include <cstdlib>
#include <iostream>

auto degrees_to_radians( int degrees ) -> double;

auto main() -> int
{
   int h, v;   

   while ( std::cin >> h >> v )
   {
      auto const radians = degrees_to_radians( v );

      auto const ladder_length = static_cast<int>( std::ceil( h / std::sin( radians ) ) );

      std::cout << ladder_length << '\n';
   }
   return EXIT_SUCCESS;
}

auto degrees_to_radians( int const degrees ) -> double
{
   static constexpr auto pi = 3.1415926535897932384626433832795028841971693993751;

   auto const radians = degrees * pi / 180.0;
   return radians;
}