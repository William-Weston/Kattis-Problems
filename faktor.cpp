/**
 * @file    faktor.cpp
 * @author  William Weston
 * @brief 
 * @version 0.1
 * @date    2023-06-13
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source:  https://open.kattis.com/problems/faktor
 */

#include <cstdlib>   
#include <iostream>

auto min_citations_needed( int num_articles, int impact_required ) noexcept -> int;

auto 
main() -> int
{
   int articles, impact;
   while ( std::cin >> articles >> impact )
   {
      std::cout << min_citations_needed( articles, impact ) << '\n';
   }

   return EXIT_SUCCESS;
}


auto 
min_citations_needed( int num_articles, int impact_required ) noexcept -> int
{
   return num_articles * ( impact_required - 1 ) + 1;
}