/**
 * @file    metronome.cpp
 * @author  William Weston
 * @brief   Metronome Problem From Kattis
 * @version 0.1
 * @date    2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/metronome
 */

#include <cstdlib>
#include <iomanip>      // fixed, set_precision
#include <iostream>


auto main() -> int
{
   constexpr auto tpr = 4.0;         // ticks per revolution
   auto const ticks   = [] { int tmp; std::cin >> tmp; return tmp; }();

   std::cout << std::fixed << std::setprecision( 2 )
             << ticks / tpr 
             << '\n';

   return EXIT_SUCCESS;
}