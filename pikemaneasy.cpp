/**
 * @file    pikemaneasy.cpp
 * @author  William Weston
 * @brief   A Vicious Pikeman (Easy) Problem From Kattis
 * @version 0.1
 * @date    2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/pikemaneasy
 */

#include <algorithm>    // sort
#include <cstdlib>
#include <iostream>
#include <iterator>     // back_inserter, distance
#include <numeric>      // partial_sum
#include <vector>


auto main() -> int
{
   constexpr auto modulo = 1'000'000'007ull;

   auto const N   = [] { unsigned long long tmp; std::cin >> tmp; return tmp; } ();  // number of problems in contest
   auto const T   = [] { unsigned long long tmp; std::cin >> tmp; return tmp; } ();  // total length of contest in minutes
   auto const A   = [] { unsigned long long tmp; std::cin >> tmp; return tmp; } ();
   auto const B   = [] { unsigned long long tmp; std::cin >> tmp; return tmp; } ();
   auto const C   = [] { unsigned long long tmp; std::cin >> tmp; return tmp; } ();
   auto const t_0 = [] { unsigned long long tmp; std::cin >> tmp; return tmp; } ();  // estimated time required to solve first problem in minutes

   auto time_estimates = std::vector<unsigned long long>();
   time_estimates.reserve( N );
   time_estimates.push_back( t_0 );

   for ( auto i = 1ull; i < N; ++i )
      time_estimates.push_back( ( ( A * time_estimates[i - 1] + B ) % C ) + 1 );

   std::sort( time_estimates.begin(), time_estimates.end() );

   auto sums = std::vector<unsigned long long>();
   sums.reserve( N );
   
   std::partial_sum( time_estimates.begin(), time_estimates.end(), std::back_inserter( sums ) );

   auto const lower_iter    = std::lower_bound( sums.begin(), sums.end(), T + 1 );
   auto const number_solved = std::distance( sums.begin(), lower_iter );
   auto const penalty       = std::accumulate( sums.begin(), lower_iter, 0ull );
  
   std::cout << number_solved << ' ' << penalty % modulo << '\n';

   return EXIT_SUCCESS;
}

