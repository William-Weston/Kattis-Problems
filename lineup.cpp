/**
 * @file    lineup.cpp
 * @author  William Weston
 * @brief   Line Them Up Problem from Kattis
 * @version 0.1
 * @date    2023-06-16
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/lineup
 */

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

auto alphabetized( std::vector<std::string> const& players ) -> void;

auto
main() -> int
{
   int team_size;

   while ( std::cin >> team_size )
   {
      auto players = std::vector<std::string>();
      players.reserve( team_size );

      for ( auto player_number = 0; player_number < team_size; ++player_number)
      {
         auto name = std::string();
         std::cin >> name;
         players.push_back( std::move( name ) );
      }
      alphabetized( players );
   }

   return EXIT_SUCCESS;
}

auto 
alphabetized( std::vector<std::string> const& players ) -> void
{
   if ( std::is_sorted( players.begin(), players.end() ) )
   {
      std::cout << "INCREASING\n";
   }
   else if ( std::is_sorted( players.begin(), players.end(), std::greater{} ) )
   {
      std::cout << "DECREASING\n";
   }
   else
   {
      std::cout << "NEITHER\n";
   }
}