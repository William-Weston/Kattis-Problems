/**
 * @file    cold.cpp
 * @author  William Weston
 * @brief   Cold-puter Science
 * @version 0.1
 * @date    2023-09-19
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/cold
 */

#include <algorithm>    // sort, lower_bound
#include <cstdlib>
#include <iostream>
#include <iterator>     // distance
#include <vector>

auto main() -> int
{
   auto const n = [] { int tmp; std::cin >> tmp; return tmp; }();

   auto temperatures = std::vector<int>();
   temperatures.reserve( n );

   for ( auto count = 0; count < n; ++count )
   {
      int tmp;
      std::cin >> tmp;
      temperatures.push_back( tmp );
   }

   std::sort( temperatures.begin(), temperatures.end() );

   auto const zero_bound     = std::lower_bound( temperatures.begin(), temperatures.end(), 0 );
   auto const less_than_zero = std::distance( temperatures.begin(), zero_bound );

   std::cout << less_than_zero << '\n';

   return EXIT_SUCCESS;
}