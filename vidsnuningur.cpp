/**
 * @file    vidsnuningur.cpp
 * @author  William Weston
 * @brief   Viðsnúningur Problem From Kattis
 * @version 0.1
 * @date    2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/vidsnuningur
 */


#include <cstdlib>
#include <iostream>
#include <string>

auto main() -> int
{
   auto const line = [] { std::string tmp; std::getline( std::cin, tmp ); return tmp; }();

   for ( auto riter = line.rbegin(); riter != line.rend(); ++riter )
      std::cout << *riter;

   std::cout << '\n';
   return EXIT_SUCCESS;
}