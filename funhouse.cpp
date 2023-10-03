/**
 * @file    funhouse.cpp
 * @author  William Weston
 * @brief   Fun House Problem From Kattis
 * @version 0.1
 * @date    2023-08-17
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/funhouse
 */

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>     // distance
#include <string>
#include <utility>
#include <vector>

// ------------------------------------------------------------------------------------------------

auto locate_exit( std::vector<std::string>& room )                     -> void;
auto print_results( std::vector<std::string> const& room, int number ) -> void;

// --------------------------------------------- main ---------------------------------------------

auto main() -> int
{
   auto house = 1;

   while ( true )
   {
      int width, length;
      std::cin >> width >> length;

      if ( width == 0 && length == 0 )
         break;                           // end of input

      auto room_diagram = std::vector<std::string>();
      room_diagram.reserve( length );

      for ( auto line = std::string(); length--; )
      {
         std::getline( std::cin >> std::ws, line );
         room_diagram.push_back( std::move( line ) );
      }

      locate_exit( room_diagram );
      print_results( room_diagram, house );

      ++house;  // next funhouse
   }
   return EXIT_SUCCESS;
}

// -------------------------------------------- Point ---------------------------------------------

struct Point final
{
   int x;
   int y;
};

auto operator<< ( std::ostream& out, Point point ) -> std::ostream&
{
   return out << '(' << point.x << ", " << point.y << ')';
}
// ------------------------------------------ Exit_Finder ------------------------------------------

enum Direction { north, south, east, west };
auto operator<<( std::ostream& out, Direction direction ) -> std::ostream&
{
   switch ( direction )
   {
   case north:
      return out << "north";
      
   case south:
      return out << "south";

   case east:
      return out << "east";

   case west:
      return out << "west";

   default:
      assert ( true && "invalid Direction" );
      return out;
   }
}

class Exit_Finder final
{
public:
   explicit Exit_Finder( std::vector<std::string>& room ) noexcept;

   auto run() -> void;

private:
   std::vector<std::string>& room_;
   Point                     position_;         // current position in room
   Direction                 direction_;        // 0 = east, 180 = west, 90 = north, 270 = south

   
};


auto           locate_entrance( std::vector<std::string> const& room ) -> Point;
constexpr auto set_initial_direction( Point entrance, int w, int h )   -> Direction;
constexpr auto advance( Point position, Direction direction )          -> Point;
constexpr auto reflect( char mirror, Direction direction )             -> Direction;
constexpr auto is_mirror( char ch )                                    -> bool;

Exit_Finder::Exit_Finder( std::vector<std::string>& room ) noexcept
   : room_( room )
   , position_( locate_entrance( room ) )
   , direction_( set_initial_direction( position_, room.front().size(), room.size() ) )
{}
 

auto 
Exit_Finder::run() -> void
{
   while ( room_[position_.y][position_.x] != 'x' )
   {
      position_           = advance( position_, direction_ );
      auto const contents = room_[position_.y][position_.x];

      if ( is_mirror( contents ) )
      {
         direction_ = reflect( contents, direction_ );
      }
   }

   room_[position_.y][position_.x] = '&';
}


auto 
locate_entrance( std::vector<std::string> const& room ) -> Point
{
   auto const sz = room.size();
   for ( std::vector<std::string>::size_type row = 0; row < sz; ++row )
   {
      auto const col = room[row].find( '*' );
      if ( col != std::string::npos )
         return Point{ static_cast<int>( col ), static_cast<int>( row ) };
   }

   assert( true && "Exit not found" );

   return Point{ 0, 0 };
}

constexpr auto 
set_initial_direction( Point const entrance, int const width, int const height ) -> Direction
{
   if ( entrance.x == 0 )           return east;
   if ( entrance.x == width - 1 )   return west;
   if ( entrance.y == 0 )           return south;
   
   return north;
}

constexpr auto 
advance( Point const position, Direction const direction ) -> Point
{
   switch ( direction )
   {
   case east:
      return Point{ position.x + 1, position.y };
   
   case west:
      return Point{ position.x - 1, position.y };

   case north:
      return Point{ position.x, position.y - 1 };

   case south:
      return Point{ position.x, position.y + 1 };

   default:
      assert( true && "Unknown Direction" );
      return {};
   }
}

constexpr auto 
reflect( char const mirror, Direction const direction ) -> Direction
{
   if ( mirror == '/' )
   {
      switch ( direction)
      {
      case east:
         return north;
      
      case west:
         return south;

      case north:
         return east;

      case south:
         return west;

      default:
         assert( true && "Unknown Direction" );
         return {};
      }
   }
   else if ( mirror == '\\' )
   {
      switch ( direction)
      {
      case east:
         return south;
      
      case west:
         return north;

      case north:
        return west;

      case south:
         return east;
        
      default:
         assert( true && "Unknown Direction" );
         return {};
      }
   }

   assert( true && "unknown mirror" );
   return east;
}

constexpr auto 
is_mirror( char ch ) -> bool
{
   return ch == '/' || ch == '\\';
}

// ------------------------------------------------------------------------------------------------

auto locate_exit( std::vector<std::string>& room ) -> void
{
   auto finder = Exit_Finder( room );
   finder.run();
}


auto print_results( std::vector<std::string> const& room, int number ) -> void
{
   std::cout << "HOUSE " << number << '\n';

   for ( auto const& line : room )
      std::cout << line << '\n';
}

// ------------------------------------------------------------------------------------------------