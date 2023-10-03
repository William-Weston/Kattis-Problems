/**
 * @file    sibice.cpp
 * @author  William Weston
 * @brief   Sibice Problem from Kattis
 * @version 0.1
 * @date 2023-06-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/sibice
 */


#include <cmath>           // pow, sqrt
#include <cstdlib>
#include <iostream>


auto 
main() -> int
{
   int N, W, H;

   while ( std::cin >> N >> W >> H )
   {
      auto const max_length = sqrt( W * W + H * H );

      for ( auto match = 0; match < N; ++match )
      {
         auto const match_length = [](){ int tmp; std::cin >> tmp; return tmp; }();
         std::cout << 
            ( ( max_length < match_length ) 
            ? "NE\n" 
            : "DA\n" );
      }
   }
   

   return EXIT_SUCCESS;
}