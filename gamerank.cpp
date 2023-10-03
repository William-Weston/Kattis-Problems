/**
 * @file    gamerank.cpp
 * @author  William Weston
 * @brief   Game Rank Problem From Kattis
 * @version 0.1
 * @date 2023-07-31
 *
 * @copyright Copyright (c) 2023
 *
 * Source: https://open.kattis.com/problems/gamerank
 */


#include <cstdlib>
#include <iostream>
#include <numeric>         // accumulate
#include <string>
#include <string_view>

struct Status final
{
   int rank       = 25;
   int stars      = 0;
   int win_streak = 0;
};

auto process_matches( std::string_view matches ) -> Status;
auto print_rank( int rank )                      -> void;


// ------------------------------------------- main -----------------------------------------------

auto main() -> int
{
   auto const matches = [] () { auto tmp = std::string(); std::getline( std::cin, tmp ); return tmp; }( );
   auto const status  = process_matches( matches );

   print_rank( status.rank );

   return EXIT_SUCCESS;
}

// ------------------------------------------------------------------------------------------------

auto process_match( Status status, char result ) -> Status;

// ------------------------------------------------------------------------------------------------

auto process_matches( std::string_view matches ) -> Status
{
   return std::accumulate( matches.begin(), matches.end(), Status{}, process_match );
}

auto print_rank( int rank ) -> void
{
   if ( rank > 0 )
      std::cout << rank << '\n';
   else
      std::cout << "Legend\n";
}

// ------------------------------------- Details ----------------------------------------------

auto process_win( Status status )  -> Status;
auto process_loss( Status status ) -> Status;
auto stars_per_rank( int rank )    -> int;


auto process_match( Status status, char result ) -> Status
{
   switch ( result )
   {
      case 'W':
         return process_win( status );

      case 'L':
         return process_loss( status );

      default:
         return status;
   }
}

auto process_win( Status status ) -> Status
{
   ++status.win_streak;
   ++status.stars;

   if ( status.win_streak >= 3 && status.rank > 5 )
      ++status.stars;
   
   if ( auto const rank_stars = stars_per_rank( status.rank ); status.stars > rank_stars )
   {
      status.stars -= rank_stars;
      --status.rank;
   }

   return status;
}

auto process_loss( Status status ) -> Status
{
   status.win_streak = 0;

   if ( status.rank == 0 )       // stay legend forever
      return status;
   
   if ( status.rank < 20 )
   {
      if ( status.stars > 0 )
         --status.stars;
      else
      {
         ++status.rank;
         status.stars = stars_per_rank( status.rank ) - 1;
      }
   }

   else if ( status.rank == 20 )
   {
      if ( status.stars > 0 )
         --status.stars;
   }

   return status;
}

auto stars_per_rank( int rank ) -> int
{
   switch ( rank )
   {
      case 0:        // legend
         return 0;

      case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
         return 5;

      case 11: case 12: case 13: case 14: case 15:
         return 4;
      
      case 16: case 17: case 18: case 19: case 20:
         return 3;
      
      case 21: case 22: case 23: case 24: case 25:
         return 2;
      
      default:
         return 0;
   }
}

