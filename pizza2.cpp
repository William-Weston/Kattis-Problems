/**
 * @file    pizza2.cpp
 * @author  William Weston
 * @brief   Kattis Pizza Crust Problem
 * @version 0.1
 * @date    2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 * Source: https://open.kattis.com/problems/pizza2
 */


#include <cstdlib>
#include <iomanip>
#include <iostream>

auto percent_cheese( int pizza_radius, int cm_of_crust ) -> long double;

auto
main() -> int
{
   int R, C;

   while ( std::cin >> R >> C )
   {
      std::cout << std::fixed << std::setprecision( 9 ) << std::showpoint
                << percent_cheese( R, C ) 
                << '\n';
   }

   return EXIT_SUCCESS;
}


auto
percent_cheese( int pizza_radius, int cm_of_crust ) -> long double
{
   static constexpr long double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

   auto const cheese_radius = pizza_radius - cm_of_crust;
   auto const pizza_area    = pi * pizza_radius * pizza_radius;
   auto const cheese_area   = pi * cheese_radius * cheese_radius;

   return ( cheese_area / pizza_area ) * 100.0;
}