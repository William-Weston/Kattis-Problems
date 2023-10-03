/**
 * @file    gangur.cpp
 * @author  William Weston
 * @brief   Gangur Problem From Kattis
 * @version 0.1
 * @date    2023-09-19
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/gangur
 */


#include <algorithm>    // count
#include <cstdlib>
#include <iostream>
#include <iterator>     // next
#include <string>

auto 
main() -> int
{
   auto const hallway = [] { std::string tmp; std::getline( std::cin, tmp ); return tmp; }();

   constexpr auto right = '>';
   constexpr auto left  = '<';

   auto total_passes  = int{};
   auto const begin   = hallway.begin();
   auto const end     = hallway.end();

   for ( auto pos = hallway.find( right, 0 ); pos != std::string::npos; pos = hallway.find( right, pos + 1 ) )
   {
      auto const iter    = std::next( begin, pos );
      auto const passes  = std::count( iter, end, left );
      total_passes += passes;
   }

   std::cout << total_passes << '\n';
   
   return EXIT_SUCCESS;
}