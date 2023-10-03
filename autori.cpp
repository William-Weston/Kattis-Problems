/**
 * @file    autori.cpp
 * @author  William Weston
 * @brief   Autori Problem From Kattis
 * @version 0.1
 * @date    2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/autori
 */


#include <cctype>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>

auto is_upper( char c ) -> bool { return std::isupper( static_cast<unsigned char>( c ) ); }

auto main() -> int
{
   for ( auto input = std::string(); std::cin >> input; )
   {  
      auto const op     = [] ( std::string const& lhs, char rhs ) { return ( is_upper( rhs ) ) ? lhs + rhs : lhs; };
      auto const result = std::accumulate( input.begin(), input.end(), std::string(), op );

      std::cout << result << '\n';
   }

   return EXIT_SUCCESS;
}