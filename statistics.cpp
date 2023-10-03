/**
 * @file    statistics.cpp
 * @author  William Weston
 * @brief   Statistics Problem From Kattis
 * @version 0.1
 * @date    2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/statistics
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>


auto main() -> int
{
   for ( int n, x = 1; std::cin >> n;  ++x )
   {
      auto data = std::vector<int>();
      data.reserve( n );

      for ( int tmp; n--; )
      {
         std::cin >> tmp;
         data.push_back( tmp );
      }

      auto [min_iter, max_iter] = std::minmax_element( data.begin(), data.end() );

      std::cout << "Case " << x << ": " << *min_iter << ' ' << *max_iter << ' ' << *max_iter - *min_iter << '\n';

   }

   return EXIT_SUCCESS;
}