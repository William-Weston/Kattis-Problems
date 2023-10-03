/**
 * @file    veci.cpp
 * @author  William Weston
 * @brief   Veci Problem From Kattis
 * @version 0.1
 * @date    2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/veci
 * 
 *    Your program will be given an integer X. 
 *    Find the smallest number larger than X consisting of the same digits as X.
 */


#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>


auto string_to_int( std::string_view number ) -> int;

auto main() -> int
{
   for ( auto X = std::string(); std::cin >> X; )
   {
      auto const integer = string_to_int( X );

      std::sort( X.begin(), X.end() );
      
      auto min = std::numeric_limits<int>::max();
      do 
      {
         auto const permutation = string_to_int( X );
         if ( permutation > integer )
         {
            if ( permutation < min )
               min = permutation;
         }
      } 
      while ( std::next_permutation( X.begin(), X.end() ) );


      std::cout << ( min == std::numeric_limits<int>::max() ? 0 : min ) << '\n';
   }

   return EXIT_SUCCESS;
}

auto string_to_int( std::string_view number ) -> int
{
   auto const first = number.data();
   auto const last  = first + number.size();

   int return_value;

   std::from_chars( first, last, return_value );

   return return_value;
}