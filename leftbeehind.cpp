/**
 * @file    leftbeehind.cpp
 * @author  William Weston
 * @brief   Left Beehind Problem from Kattis
 * @version 0.1
 * @date    2023-06-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/leftbeehind
 */



#include <cstdlib>
#include <iostream>

auto
main() -> int
{

   int sweet, sour;

   while ( std::cin >> sweet >> sour )
   {
      if ( sweet == 0 && sour == 0 )
         break;

      if ( ( sweet + sour ) == 13 )
         std::cout << "Never speak again.\n";
      else if ( sweet < sour )
         std::cout << "Left beehind.\n";
      else if ( sour < sweet )
         std::cout << "To the convention.\n";
      else if ( sour == sweet )
         std::cout << "Undecided.\n";
   }

   return EXIT_SUCCESS;
}