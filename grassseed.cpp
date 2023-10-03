/**
 * @file    grassseed.cpp
 * @author  William Weston
 * @brief   Grass Seed Inc. Problem From Kattis
 * @version 0.1
 * @date    2023-09-24
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/grassseed
 */


#include <cstdlib>
#include <iomanip>
#include <iostream>


auto 
main() -> int
{
   auto const cost_per_sq_m   = [] { double tmp; std::cin >> tmp; return tmp; }();
   auto const number_of_lawns = [] { int tmp; std::cin >> tmp; return tmp; }();

   auto total_cost = double{};

   for ( auto i = 0; i < number_of_lawns; ++i )
   {
      auto const width  = [] { double tmp; std::cin >> tmp; return tmp; }();
      auto const length = [] { double tmp; std::cin >> tmp; return tmp; }();

      total_cost += ( width * length * cost_per_sq_m );
   }

   std::cout << std::setprecision( 8 ) << std::fixed << total_cost << '\n';
   return EXIT_SUCCESS;
}