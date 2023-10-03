/**
 * @file    timeloop.cpp
 * @author  William Weston
 * @brief   Stuck In A Time Loop Problem From Kattis
 * @version 0.1
 * @date    2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/timeloop
 */

#include <cstdlib>
#include <iostream>

auto main() -> int
{
   constexpr auto magic_word = "Abracadabra";

   auto const magic_number = [] { int tmp; std::cin >> tmp; return tmp; }();

   for ( auto n = 0; n < magic_number; ++n )
      std::cout << n + 1 << ' ' << magic_word << '\n';
   
   
   return EXIT_SUCCESS;
}