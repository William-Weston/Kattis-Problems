/**
 * @file    hradgreining.cpp
 * @author  William Weston
 * @brief   Hraðgreining Problem From Kattis
 * @version 0.1
 * @date    2023-09-24
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/hradgreining
 */

#include <cstdlib>
#include <iostream>
#include <string>


auto
main() -> int
{
   constexpr auto covid    = "COV";
   constexpr auto positive = "Veikur!";
   constexpr auto negative = "Ekki veikur!";

   auto const dna = []{ auto tmp = std::string(); std::cin >> tmp; return tmp; }();

   if ( auto const result = dna.find( covid ); result != std::string::npos )
   {
      std::cout << positive << '\n';
   }
   else
   {
      std::cout << negative << '\n';
   }

   return EXIT_SUCCESS;
}