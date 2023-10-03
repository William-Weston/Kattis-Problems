/**
 * @file    busyschedule.cpp
 * @author  William Weston
 * @brief   Busy Schedule Problem From Kattis
 * @version 0.1
 * @date    2023-07-22
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/busyschedule
 * 
 */

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Time final
{
   int  hour;
   int  minute;
   bool pm;             // false: am, true: pm
};

auto operator>>( std::istream& in, Time& time )        -> std::istream&;
auto operator<<( std::ostream& out, Time const& time ) -> std::ostream&;
auto operator< ( Time const& lhs, Time const& rhs )    -> bool;

auto main() -> int
{

   for ( int n; std::cin >> n; )
   {
      if ( n == 0 )     // no more test cases
         break;
      
      auto appointments = std::vector<Time>();

      while ( n-- )
      {
         auto tmp = Time{}; 
         std::cin >> tmp;
         appointments.push_back( tmp );
      }

      std::sort( appointments.begin(), appointments.end() );
      for ( auto const& elem : appointments )
      {
         std::cout << elem << '\n';
      }
      std::cout << '\n';
   }

   return EXIT_SUCCESS;
}

auto operator>>( std::istream& in, Time& time ) -> std::istream&
{
   auto colon  = char{};
   auto period = std::string();

   in >> time.hour >> colon >> time.minute >> period;

   time.pm = ( period == "p.m." );

   return in;
}

auto operator<<( std::ostream& out, Time const& time ) -> std::ostream&
{
   out << time.hour << ':' << std::setw( 2 ) << std::setfill( '0' ) <<  time.minute << ' ' << ( time.pm ? "p.m." : "a.m." );
 
   return out;
}

auto operator< ( Time const& lhs, Time const& rhs ) -> bool
{
   auto lhs_hour = lhs.hour % 12;
   auto rhs_hour = rhs.hour % 12;
   return std::tie( lhs.pm, lhs_hour, lhs.minute ) < std::tie( rhs.pm, rhs_hour, rhs.minute );
}