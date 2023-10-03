/**
 * @file    baconeggsandspam.cpp
 * @author  William Weston
 * @brief   Bacon, Eggs, and Spam Problem From Kattis
 * @version 0.1
 * @date    2023-07-31
 *
 * @copyright Copyright (c) 2023
 *
 * Source: https://open.kattis.com/problems/baconeggsandspam
 */


#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

auto print( std::map<std::string, std::set<std::string>> const& data ) -> void;

auto main() -> int
{
   for ( int n; std::cin >> n; )
   {
      if ( n == 0 )
         break;

      std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

      auto data = std::map<std::string, std::set<std::string>>();

      while ( n-- )
      {
         auto line = std::string();
         std::getline( std::cin, line );

         auto iss = std::istringstream( line );
         auto name = std::string();
         iss >> name;

         for ( auto menu_item = std::string(); iss >> menu_item; )
         {
            data[menu_item].insert( name );
         }
      }

      print( data );

   }
   return EXIT_SUCCESS;
}

auto print( std::map<std::string, std::set<std::string>> const& data ) -> void
{
   for ( auto const& [item, customers] : data )
   {
      std::cout << item << ' ';
      for ( auto const& name : customers )
      {
         std::cout << name << ' ';
      }
      std::cout << '\n';
   }
   std::cout << '\n';
}