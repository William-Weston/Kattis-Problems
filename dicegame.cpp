/**
 * @file    dicegame.cpp
 * @author  William Weston
 * @brief   Dice Game Problem by Kattis
 * @version 0.1
 * @date 2023-06-17
 *
 * @copyright Copyright (c) 2023
 *
 * Source: https://open.kattis.com/problems/dicegame
 */


#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>


using range = std::pair<int, int>;

auto process_input()                            -> range;
auto process_result( range gunnar, range emma ) -> void;
auto sum_range( int start, int end )            -> int;       // [start, end]
auto avg( int total, int num_values )           -> double;

auto
main() -> int
{
   while ( true )
   {
      auto gunnar_range = process_input();
      if ( !std::cin )
         break;
      auto emma_range = process_input();

      process_result( gunnar_range, emma_range );
   }

   return EXIT_SUCCESS;
}

auto
process_input() -> range
{
   int a1, b1, a2, b2;
   std::cin >> a1 >> b1 >> a2 >> b2;

   return std::make_pair( a1 + a2, b1 + b2 );
}

auto
process_result( range gunnar, range emma ) -> void
{
   using namespace std::literals;

   auto const [gunnar_start, gunnar_end] = gunnar;
   auto const [emma_start, emma_end]     = emma;
   auto const gunnar_sum                 = sum_range( gunnar_start, gunnar_end );
   auto const emma_sum                   = sum_range( emma_start, emma_end );
   auto const gunnar_total_values        = gunnar_end - gunnar_start + 1;
   auto const emma_total_values          = emma_end - emma_start + 1;
   auto const gunnar_avg                 = avg( gunnar_sum, gunnar_total_values );
   auto const emma_avg                   = avg( emma_sum, emma_total_values );

   std::cout << ( ( gunnar_avg == emma_avg )
                  ? "Tie"s  : ( gunnar_avg < emma_avg )
                  ? "Emma"s : "Gunnar"s )
             << '\n';
}

auto
sum_range( int start, int end ) -> int       // [start, end]
{
   auto value = 0;

   while ( start <= end )
   {
      value += start;
      ++start;
   }

   return value;
}

auto
avg( int total, int num_values ) -> double
{
   return static_cast<double>( total ) / static_cast<double>( num_values );
}

