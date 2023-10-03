/**
 * @file    cups.cpp
 * @author  William Weston
 * @brief   Cups Problem From Kattis
 * @version 0.1
 * @date    2023-07-30
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/cups
 */


#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>


struct Cup final
{
   std::string colour;
   double      radius;
};


auto make_cup( std::string const& input ) -> Cup;

auto main() -> int
{
   for ( auto N = int{}; std::cin >> N; )
   {
      auto cups = std::vector<Cup>();
      cups.reserve( N );

      // call ignore when switching from stream to getline
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     

      while ( N-- )
      {
         auto line = std::string();
         std::getline( std::cin, line );

         cups.push_back( make_cup( line ) );
      }

      std::sort( cups.begin(), 
                 cups.end(), 
                 [] ( Cup const& lhs, Cup const& rhs ) { return lhs.radius < rhs.radius; } );

      for ( auto const& cup : cups )
         std::cout << cup.colour << '\n';

   }

   return EXIT_SUCCESS;
}


auto make_cup( std::string const& input ) -> Cup
{
   auto const is_alpha = []( char ch) { return std::isalpha( static_cast<unsigned char>( ch ) ); };

   auto iss = std::istringstream( input );

   char const first = iss.peek();

   if ( is_alpha( first ) )         
   {
      auto colour = std::string();
      auto radius = double{};

      iss >> colour >> radius;

      return Cup{ colour, radius };
   }
   else                                            // error path radius has been double
   {
      auto colour = std::string();
      auto radius = double{};

      iss >> radius >> colour; 

      return Cup{ colour, radius / 2.0 };
   }
}