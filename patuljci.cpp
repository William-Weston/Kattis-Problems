/**
 * @file    patuljci.cpp
 * @author  William Weston
 * @brief   Patuljci Problem from Kattis
 * @version 0.1
 * @date    2023-06-16
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/patuljci
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// must be printed in the order in which they were inputed
auto print_results( std::vector<int> const& dwarves, std::vector<int> const& correct_dwarves ) -> void
{
   for ( auto dwarf : dwarves )
   {
      if ( std::binary_search( correct_dwarves.begin(), correct_dwarves.end(), dwarf ) )
      {
         std::cout << dwarf << '\n';
      }
   }
}

// return a sorted list of the right dwarves
auto find_right_dwarves( std::vector<int> dwarves ) -> std::vector<int>
{
   // sort the dwarves
   std::sort( dwarves.begin(), dwarves.end() );

   while ( std::next_permutation( dwarves.begin(), dwarves.end() ) )
   {
      auto const first = dwarves.begin();
      auto const last  = dwarves.end() - 2;  

      // accumulate the first 7 dwarves
      auto const result = std::accumulate( first, last, 0 );
      if ( result == 100 )
      {  
        auto correct = std::vector<int>{ dwarves.begin(), dwarves.end() - 2 };
        std::sort( correct.begin(), correct.end() );
        return correct;
      }
   }

   return {};
}

auto
main() -> int
{
   while ( std::cin )
   {
      auto dwarves = std::vector<int>();

      for ( auto i = 0; i < 9; ++i )
      {
         int dwarf_number;
         std::cin >> dwarf_number;
         
         dwarves.push_back( dwarf_number );
      }


      auto correct = find_right_dwarves( dwarves );

      print_results( dwarves, correct );
   }
   return EXIT_SUCCESS;
}