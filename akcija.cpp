/**
 * @file    akcija.cpp
 * @author  William Weston
 * @brief   Akcija Problem from Kattis
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/akcija
 */


#include <algorithm>       // sort
#include <cstdlib>
#include <functional>      // greater
#include <iostream>
#include <vector>

auto 
main() -> int
{
   int N;
   while ( std::cin >> N )
   {
      auto book_prices = std::vector<int>();

      for ( auto idx = 0; idx < N; ++idx )
      {
         int tmp;
         std::cin >> tmp;
         book_prices.push_back( tmp );
      }

      std::sort( book_prices.begin(), book_prices.end(), std::greater{} );

      auto total_price = 0;

      for ( auto idx = 0; idx < N; ++idx )
      {
         if ( ( idx + 1 ) % 3 != 0 )
         {
            total_price += book_prices[idx];
         }
      }

      std::cout << total_price << '\n';
   }

   return EXIT_SUCCESS;
}