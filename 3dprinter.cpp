/**
 * @file    3dprinter.cpp
 * @author  William Weston
 * @brief   3D Printed Statues Problem from Kattis
 * @version 0.1
 * @date    2023-06-18
 *
 * @copyright Copyright (c) 2023
 *
 * Source: https://open.kattis.com/problems/3dprinter
 */

#include <algorithm>          // min
#include <cmath>              // ceil, floor, sqrt
#include <cstdlib>
#include <iostream>

auto solve( int N ) -> int;

auto
main() -> int
{
   int N;

   while ( std::cin >> N )
   {
      std::cout << solve( N ) << '\n';
   }

   return EXIT_SUCCESS;
}

auto 
solve( int N ) -> int
{
  return std::ceil( std::log2( N ) ) + 1;
}