/**
 * @file    herman.cpp
 * @author  William Weston
 * @brief 
 * @version 0.1
 * @date    2023-06-13
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/herman
 */


#include <cstdlib>   
#include <iomanip>
#include <iostream>


auto area( int radius ) noexcept -> void;

auto 
main() -> int
{
   int radius;
   while ( std::cin >> radius )
   {
      area( radius );
   }

   return EXIT_SUCCESS;
}

auto 
area( int radius ) noexcept -> void
{
   static constexpr long double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

   std::cout << std::setw(24) << std::fixed << std::setprecision( 6 ) << std::showpoint
             << pi * radius * radius << '\n';
   std::cout << std::setw(24) << std::fixed << std::setprecision( 6 ) << std::showpoint
             << 2.0 * radius * radius << '\n';
}