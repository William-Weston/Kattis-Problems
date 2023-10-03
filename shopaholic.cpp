/**
 * @file    shopaholic.cpp
 * @author  William Weston
 * @brief   Shopaholic Problem From Kattis
 * @version 0.1
 * @date    2023-07-17
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/shopaholic
 */

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>


auto main() -> int
{

   for ( int n; std::cin >> n; )
   {
      auto prices = std::vector<int>();
      prices.reserve( n );

      for ( int price; n--; )
      {
         std::cin >> price;
         prices.push_back( price );
      }

      std::sort( prices.begin(), prices.end(), std::greater{} );

      auto const sz       = prices.size();
      auto total_discount = 0ll;

      for ( std::vector<int>::size_type idx = 2; idx < sz; idx += 3 )
      {
            total_discount += prices[idx];
      }

      std::cout << total_discount << '\n';
   }

   return EXIT_SUCCESS;
}