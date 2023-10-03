/**
 * @file    flexible.cpp
 * @author  William Weston
 * @brief   Flexible Spaces Problem From Kattis
 * @version 0.1
 * @date    2023-08-14
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/flexible
 */

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

template <typename RIter, typename OutputIter, typename BinaryOp = std::minus<typename std::iterator_traits<RIter>::value_type>>
auto unordered_pairwise( RIter first, RIter last, OutputIter d_first, BinaryOp op = BinaryOp{} ) -> void;

auto print( std::vector<int> const& container ) -> void
{
   for ( auto const& elem : container )
      std::cout << elem << ' ';

   std::cout << '\n';
}

auto main() -> int
{
   auto const W = []() { int tmp; std::cin >> tmp; return tmp; }();
   auto const P = []() { int tmp; std::cin >> tmp; return tmp; }();

   auto partitions = std::vector<int>{ 0 };     // start with a zero
   partitions.reserve( P );

   for ( auto count = 0; count < P; ++count )
   {
      int tmp;
      std::cin >> tmp;
      partitions.push_back( tmp );
   }
   partitions.push_back( W ); // add the total width
   
   auto results = std::vector<int>();

   unordered_pairwise( partitions.begin(), partitions.end(), std::back_inserter( results ) );

   std::sort( results.begin(), results.end() );
   auto const new_end = std::unique( results.begin(), results.end() );

   if ( new_end != results.end() )
      results.erase( new_end, results.end() );

   auto const it = std::remove(results.begin(), results.end(), 0);
   results.erase(it, results.end());

   print( results );

   return EXIT_SUCCESS;
}

template <typename RIter, typename OutputIter, typename BinaryOp>
auto unordered_pairwise( RIter first, RIter last, OutputIter d_first, BinaryOp op ) -> void
{
   for ( auto const last_element = last - 1; first != last_element; ++first )
   {
      for( auto start = first + 1; start != last; ++start )
      {
         *d_first++ = op( *start, *first );
      }
   }
}