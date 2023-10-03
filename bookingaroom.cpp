/**
 * @file    bookingaroom.cpp
 * @author  William Weston
 * @brief   Booking a Room - Kattis Problem
 * @version 0.1
 * @date    2023-06-16
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/bookingaroom
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

auto find_available_room( std::vector<int> const& booked_rooms, int number_of_rooms ) -> int;

auto
main() -> int
{
   int number_of_rooms;
   int number_of_booked_rooms;

   while ( std::cin >> number_of_rooms >> number_of_booked_rooms )
   {
      // Case 1: number_of_rooms == number_of_booked_rooms
      if ( number_of_rooms == number_of_booked_rooms )
      {
         for ( auto i = 0; i < number_of_booked_rooms; ++i )
         {
            int room_number;
            std::cin >> room_number;
         }
         std::cout << "too late\n";
      }
      // Case 2: number_of_booked_rooms < number_of_rooms
      else
      {
         auto booked_rooms = std::vector<int>();
         booked_rooms.reserve( number_of_booked_rooms );

         for ( auto i = 0; i < number_of_booked_rooms; ++i )
         {
            int room_number;
            std::cin >> room_number;
            booked_rooms.push_back( room_number );
         }

         std::sort( booked_rooms.begin(), booked_rooms.end() );

         auto const available_room = find_available_room( booked_rooms, number_of_rooms );
         std::cout << available_room << '\n';
      }
   }

   return EXIT_SUCCESS;
}

auto 
find_available_room( std::vector<int> const& booked_rooms, int number_of_rooms ) -> int
{
   for ( auto room_number = 1; room_number <= number_of_rooms; ++room_number )
   {
      // check if the room_number has been booked
      auto const booked = std::binary_search( booked_rooms.begin(), booked_rooms.end(), room_number );
      if ( !booked )
         return room_number;
   }

   return -1;  // no room found;
}