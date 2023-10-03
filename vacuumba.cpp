/**
 * @file    vacuumba.cpp
 * @author  William Weston
 * @brief   Vacuumba Problem From Kattis
 * @version 0.1
 * @date    2023-07-07
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/vacuumba
 */


#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <utility>

// ------------------------------------------------------------------------------------------------ 

struct Point final
{
   double x;
   double y;
};

auto operator<<( std::ostream& out, Point const& point ) -> std::ostream&
{
   out << std::setprecision( 6 ) << std::fixed << point.x << ' ' << point.y;
   return out;
}

// ------------------------------------------------------------------------------------------------ 

class Robot final
{
public:
   auto move( double angle, double distance ) -> void;
   auto location() const noexcept             -> Point;

private:
   Point  location_  = { 0, 0 };
   double direction_ = 90.0;      // degrees

   auto normalize_direction() -> void;
};

// ------------------------------------------------------------------------------------------------ 


auto main() -> int
{
   auto const test_cases = []() { int n; std::cin >> n; return n; }();

   for ( auto current_case = 0; current_case < test_cases; ++current_case )
   {
      auto const inputs = []() { int m; std::cin >> m; return m; }();
      auto vacuumba     = Robot();

      for ( auto input = 0; input < inputs; ++input )
      {
         auto const [angle, distance] = []() { double degrees, dist; std::cin >> degrees >> dist; return std::make_pair( degrees, dist ); }();

         vacuumba.move( angle, distance );
      }

      std::cout << vacuumba.location() << '\n';
   }

   return EXIT_SUCCESS;
}

// ------------------------------------------------------------------------------------------------ 

auto degrees_to_radians( double degrees ) -> double;

// ------------------------------------------------------------------------------------------------ 

auto Robot::move( double const angle, double const distance ) -> void
{
   direction_ += angle;
   normalize_direction();

   auto const radians = degrees_to_radians( direction_ );

   auto const delta_x = distance * std::cos( radians );
   auto const delta_y = distance * std::sin( radians );

   location_.x += delta_x;
   location_.y += delta_y;

}

auto Robot::location() const noexcept -> Point
{
   return location_;
}

auto Robot::normalize_direction() -> void
{
   while ( direction_ >= 360.0 ) 
   {
      direction_ -= 360.0;
   }
}

// ------------------------------------------------------------------------------------------------ 

auto degrees_to_radians( double const degrees ) -> double
{
   static constexpr auto pi = 3.14159265358979323846264338327;

   return degrees * pi / 180.0;
}

// ------------------------------------------------------------------------------------------------ 