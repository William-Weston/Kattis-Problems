/**
 * @file    securedoors.cpp
 * @author  William Weston
 * @brief   Secure Doors Problem From Kattis
 * @version 0.1
 * @date    2023-07-04
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/securedoors
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>

constexpr auto anomaly = " (ANOMALY)";

auto main() -> int
{
   for ( int N; std::cin >> N; )
   {
      auto in_building = std::unordered_set<std::string>();

      for ( auto log_entry = 0; log_entry < N; ++log_entry )
      {
         auto event    = std::string();
         auto employee = std::string();

         std::cin >> event >> employee;

         if ( event == "entry" )
         {

            // output event
            std::cout << employee << " entered";

            // check for anomaly ( employee already in building )
            if ( auto result = in_building.find( employee ); result != in_building.end() )
            {
               std::cout << anomaly;
            }

            std::cout << '\n';

            // add employee
            in_building.insert( employee );
         }
         else if ( event == "exit" )
         {
            // output event
            std::cout << employee << " exited";

            // check for anomaly ( employee NOT in building )
            if ( auto result = in_building.find( employee ); result == in_building.end() )
            {
               std::cout << anomaly;
            }

            std::cout << '\n';

            in_building.erase( employee );
         }
      }
   }

   return EXIT_SUCCESS;
}