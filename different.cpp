/**
 * @file    different.cpp
 * @author  William Weston
 * @brief   Different Problem From Kattis
 * @version 0.1
 * @date    2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/different
 */

#include <cmath>
#include <cstdlib>
#include <iostream>

auto main() -> int
{
   for ( long i1, i2; std::cin >> i1 >> i2; )
   {
      std::cout << std::abs( i1 - i2 ) << '\n';
   }
   
   return EXIT_SUCCESS;
}