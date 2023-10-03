/**
 * @file    jackolantern_juxtaposition.cpp
 * @author  William Weston
 * @brief   Jack-O'-Lantern Juxtaposition Problem From Kattis
 * @version 0.1
 * @date    2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/jackolanternjuxtaposition
 */

#include <cstdlib>
#include <iostream>


auto main() -> int
{
   auto const eye_designs   = [] { int tmp; std::cin >> tmp; return tmp; } ();
   auto const nose_designs  = [] { int tmp; std::cin >> tmp; return tmp; } ();
   auto const mouth_designs = [] { int tmp; std::cin >> tmp; return tmp; } ();

   std::cout << eye_designs * nose_designs * mouth_designs << '\n';
   
   return EXIT_SUCCESS;
}