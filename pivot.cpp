/**
 * @file    pivot.cpp
 * @author  William Weston
 * @brief   Pivot Problem From Kattis
 * @version	0.1
 * @date    2023-07-03
 *
 * @copyright Copyright (c) 2023
 *
 * Source: https://open.kattis.com/problems/pivot
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>


auto 
main() -> int
{
   static constexpr auto int_min = std::numeric_limits<int>::min();
   static constexpr auto int_max = std::numeric_limits<int>::max();

   for ( int N; std::cin >> N; )
   {
      auto partitioned_array = std::vector<int>();
      partitioned_array.reserve( N );

      for ( auto idx = 0, data = 0; idx < N; ++idx )
      {
         std::cin >> data;
         partitioned_array.push_back( data );
      }

      auto lows = std::vector<int>();
      lows.reserve( N );

      lows.push_back( int_max );

      auto backward_finger    = partitioned_array.crbegin();
      auto const backward_end = partitioned_array.crend() - 1;

      for ( auto min = int_max; backward_finger != backward_end; ++backward_finger )
      {
         lows.push_back( *backward_finger < min
            ? ( min = *backward_finger, *backward_finger )
            : min
         );
      }

      auto pivots    = 0;
      auto max       = int_min;
      auto lows_iter = lows.crbegin();

      for ( auto const elem : partitioned_array )
      {
         if ( max < elem )
         {
            max = elem;

            if ( elem < *lows_iter )
               ++pivots;
            
         }
         ++lows_iter;
      }

      std::cout << pivots << '\n';
   }

   return EXIT_SUCCESS;
}
