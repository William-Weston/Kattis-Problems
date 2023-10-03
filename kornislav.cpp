/**
 * @file    kornislav.cpp
 * @author  William Weston
 * @brief   Kornislav Problem from Kattis
 * @version 0.1
 * @date    2023-06-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/kornislav
 */


#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

auto
main() -> int
{

   int A, B, C, D;
   
   while ( std::cin >> A >> B >> C >> D )
   {
      auto numbers = std::vector<int>{ A, B, C, D };

      std::sort( numbers.begin(), numbers.end() );

      auto const result = numbers[0] * numbers[2];
      std::cout << result << '\n';
   }
   
   return EXIT_SUCCESS;
}