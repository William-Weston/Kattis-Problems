/**
 * @file    filip.cpp
 * @author  William Weston
 * @brief   Filip Problem From Kattis
 * @version 0.1
 * @date    2023-07-30
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/filip
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>


auto main() -> int
{
   for ( auto num1 = std::string(), num2 = std::string(); std::cin >> num1 >> num2; )
   {
      std::reverse( num1.begin(), num1.end() );
      std::reverse( num2.begin(), num2.end() );

      std::cout << ( ( num1 > num2 ) ? num1 : num2 ) << '\n';
   }

   return EXIT_SUCCESS;
}