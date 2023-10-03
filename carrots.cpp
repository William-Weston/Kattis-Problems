/**
 * @file    carrots.cpp
 * @author  William Weston
 * @brief   Solving for Carrots
 * @version 0.1
 * @date    2023-06-16
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/carrots
 */


#include <cstdlib>
#include <iostream>
#include <string>
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

auto 
main() -> int
{
   int number_of_contestants;

   while ( std::cin >> number_of_contestants )
   {
      int number_of_problems_solved;
      std::cin >> number_of_problems_solved;
      
      ignoreLine();        // ignore whitespace
      for ( auto contestant = 0; contestant < number_of_contestants; ++contestant )
      {
         auto description = std::string();
         std::getline( std::cin, description );
      }
      std::cout << number_of_problems_solved << '\n';
   }
   return EXIT_SUCCESS;
}