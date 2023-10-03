/**
 * @file    reversebinary.cpp
 * @author  William Weston
 * @brief   Reversed Binary Numbers Problem by Kattis
 * @version 0.1
 * @date    2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/reversebinary
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>


auto reverse_binary( int N )                -> std::string;
auto from_binary( std::string_view binary ) -> int;

auto
main() -> int
{
   int N;
   while ( std::cin >> N )
   {
      std::cout << from_binary( reverse_binary( N ) ) << '\n';
   }

   return EXIT_SUCCESS;
}

auto 
reverse_binary( int N ) -> std::string
{
   auto result = std::string();

   while ( N > 0 )
   {
      auto const remainer    = N % 2;
      auto const binary_char = '0' + remainer;

      result += binary_char;
      N      /= 2;
   }

   return result;
}

auto 
from_binary( std::string_view binary ) -> int
{
   auto place  = 0;
   auto result = 0;

   for ( auto rfirst = binary.rbegin(), rlast = binary.rend(); rfirst != rlast; ++rfirst )
   {
      if ( *rfirst == '1' )
         result += std::pow( 2, place );      

      ++place;
   }

   return result;
}