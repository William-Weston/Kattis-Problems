/**
 * @file    aaah.cpp
 * @author  William Weston
 * @brief   Aaah! Problem from Kattis
 * @version 0.1
 * @date    2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/aaah
 */




#include <cstdlib>   
#include <iostream>
#include <string>
#include <string_view>

auto goto_doctor( std::string_view able_ahs, std::string_view required_ahs ) -> bool;

auto 
main() -> int
{
   auto able_ahs     = std::string();
   auto required_ahs = std::string();

   while ( std::cin >> able_ahs >> required_ahs )
   {
      std::cout << ( goto_doctor( able_ahs, required_ahs ) ? "go\n" : "no\n" ); 
   }
   
   return EXIT_SUCCESS;
}


auto 
goto_doctor( std::string_view able_ahs, std::string_view required_ahs ) -> bool
{
   return able_ahs.size() >= required_ahs.size();
}