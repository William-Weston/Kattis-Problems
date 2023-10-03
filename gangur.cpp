/**
 * @file    gangur.cpp
 * @author  William Weston
 * @brief   Gangur Problem From Kattis
 * @version 0.1
 * @date    2023-09-19
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/gangur
 */


#include <algorithm>    // count
#include <cstdlib>
#include <iostream>
#include <iterator>     // next
#include <string>
#include <vector>

constexpr auto right = '>';
constexpr auto left  = '<';

auto get_passes( std::string const& hallway ) -> std::vector<unsigned long long>;

auto 
main() -> int
{
   auto const hallway = [] { std::string tmp; std::getline( std::cin, tmp ); return tmp; }();
   auto const passes  = get_passes( hallway );
   auto total_passes  = 0ull;
  
   for ( auto pos = hallway.find( right, 0 ); pos != std::string::npos; pos = hallway.find( right, pos + 1 ) )
   {
      total_passes += passes[pos];
   }

   std::cout << total_passes << '\n';

   return EXIT_SUCCESS;
}


auto 
get_passes( std::string const& hallway ) -> std::vector<unsigned long long>
{
   auto passes = std::vector<unsigned long long>( hallway.size(), 0 );

   auto passes_rbegin      = passes.rbegin();
   auto hallway_rbegin     = hallway.rbegin();
   auto const hallway_rend = hallway.rend();

   auto count = 0ull;

   for ( ; hallway_rbegin != hallway_rend; ++passes_rbegin, ++hallway_rbegin )
   {
      if ( *hallway_rbegin == left )
      {
         ++count;
      }
      *passes_rbegin = count;
   }
   
   return passes;
}