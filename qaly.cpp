/**
 * @file    qaly.cpp
 * @author  William Weston
 * @brief   Quality-Adjusted Life-Year Problem From Kattis
 * @version 0.1
 * @date    2023-09-19
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/qaly
 */


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <numeric>         // accumulate
#include <vector>

auto main() -> int
{
   auto const N = [] { int tmp; std::cin >> tmp; return tmp; }();

   auto qalys = std::vector<double>();

   for ( auto i = 0; i < N; ++i )
   {
      double q;
      double y;
      std:: cin >> q >> y;
      qalys.push_back( q * y );
   }

   auto const aqaly = std::accumulate( qalys.begin(), qalys.end(), 0.0 );

   std::cout << std::fixed << std::setprecision( 3 ) << aqaly << '\n';

}