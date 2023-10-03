/**
 * @file    leggjasaman.cpp
 * @author  William Weston
 * @brief   Leggja saman Problem From Kattis
 * @version 0.1
 * @date    2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/leggjasaman
 */


#include <cstdlib>
#include <iostream>


auto main() -> int
{
   auto const arnar  = [] { int tmp; std::cin >> tmp; return tmp; }();
   auto const hannes = [] { int tmp; std::cin >> tmp; return tmp; }();

   std::cout << arnar + hannes << '\n';

   return EXIT_SUCCESS;
}