/**
 * @file    detaileddifferences.cpp
 * @author  William Weston
 * @brief   Detailed Differences Problem From Kattis
 * @version 0.1
 * @date    2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/detaileddifferences
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>

auto main() -> int
{ 
   int n;
   std::cin >> n;

   while ( n-- )
   {
      auto const string1 = []() { auto tmp = std::string(); std::cin >> tmp; return tmp; }();
      auto const string2 = []() { auto tmp = std::string(); std::cin >> tmp; return tmp; }();

      auto result = std::string();
      result.reserve( string1.size() );

      auto binary_op = [] ( char lhs, char rhs )  { return ( lhs == rhs ) ? '.' : '*'; };

      std::transform( string1.begin(), string1.end(),
                      string2.begin(),
                      std::back_inserter( result ),
                      binary_op
                    );
      
      std::cout << string1 << '\n';
      std::cout << string2 << '\n';
      std::cout << result << "\n\n";
   }

   return EXIT_SUCCESS;
}