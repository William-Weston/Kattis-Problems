/**
 * @file    ovissa.cpp
 * @author  William Weston
 * @brief   Óvissa Problem From Kattis
 * @version 0.1
 * @date    2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <cstdlib>
#include <iostream>
#include <string>


auto main() -> int
{

   auto sound = std::string();
   std::getline( std::cin, sound );

   auto const count = sound.size();
   std::cout << count << '\n';
   return EXIT_SUCCESS;
}