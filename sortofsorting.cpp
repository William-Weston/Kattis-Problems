/**
 * @file    sortofsorting.cpp
 * @author  William Weston
 * @brief   Sort of Sorting Problem From Kattis
 * @version 0.1
 * @date    2023-07-22
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/sortofsorting
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

auto main() -> int
{

   for ( auto n = int{}; std::cin >> n; )
   {
      if ( n == 0 )
         break;

      auto last_names = std::vector<std::string>();
      last_names.reserve( n );

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      for ( auto tmp = std::string(); n--; )
      {
         std::getline( std::cin, tmp );
         last_names.push_back( std::move( tmp ) );
      }

      auto comp = [] ( std::string const& lhs, std::string const& rhs)
      {
         if ( lhs[0] == rhs[0] )
         {
            if ( lhs[1] == rhs[1] )
               return false;
            
            return lhs[1] < rhs[1];
         }
         return lhs[0] < rhs[0];

         // if ( lhs[0] < rhs[0] )
         //    return true;
         // else if ( lhs[0] > rhs[0] )
         //    return false;
         // else
         // {
         //    if ( lhs[1] < rhs[1] )
         //       return true;
         // }

         // return false;
      };

      std::stable_sort( last_names.begin(), last_names.end(), comp );

      for ( auto const& elem : last_names )
         std::cout << elem << '\n';
      
      std::cout << '\n';
   }

   return EXIT_SUCCESS;
}