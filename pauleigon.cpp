/**
 * @file    pauleigon.cpp
 * @author  William Weston
 * @brief   Paul Eigon Problem from Kattis
 * @version 0.1
 * @date    2023-06-16
 *
 * @copyright Copyright (c) 2023
 *
 * Source: https://open.kattis.com/problems/pauleigon
 */

#include <cstdlib>
#include <iostream>
#include <string>


auto
main() -> int
{
   using namespace std::literals;

   int N, P, Q;

   while ( std::cin >> N >> P >> Q )
   {
      auto const games_played = P + Q;
      auto const reduced = games_played / N;
      std::cout << ( ( reduced % 2 == 0 ) ? "paul\n"s : "opponent\n"s );
   }

   return EXIT_SUCCESS;
}