  /**
 * @file    fifa.cpp
 * @author  William Weston
 * @brief   Fifa Problem From Kattis
 * @version 0.1
 * @date    2023-09-19
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https: //open.kattis.com/problems/fifa
 */

#include <cstdlib>
#include <iostream>


auto main() -> int
{
   constexpr auto base_year = 2022;

   auto const n = [] { long long tmp; std::cin >> tmp; return tmp; }();
   auto const k = [] { int tmp; std::cin >> tmp; return tmp; }();

   auto const years_since = n / k;
   auto const year        = base_year + years_since;

   std::cout << year << '\n';

}