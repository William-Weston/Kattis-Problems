/**
 * @file    everywhere.cpp
 * @author  William Weston
 * @brief   EveryWhere Problem from Kattis
 * @version 0.1
 * @date    2023-06-16
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/everywhere
 */


#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>

auto
main() -> int
{
   int test_cases;
   while ( std::cin >> test_cases )
   {
      for ( auto test_case = 0; test_case < test_cases; ++test_case )
      { 
         int number_of_trips;
         std::cin >> number_of_trips;

         auto cities_visited = std::unordered_set<std::string>();

         for ( auto trip = 0; trip < number_of_trips; ++trip )
         {
            auto city = std::string();
            std::cin >> city;

            cities_visited.insert( std::move( city ) );
         }

         std::cout << cities_visited.size() << '\n';
      }
   }

   return EXIT_SUCCESS;
}