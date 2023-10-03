/**
 * @file    2048.cpp
 * @author  William Weston
 * @brief   2048 Problem From Kattis
 * @version 0.1
 * @date    2023-07-03
 *
 * @copyright Copyright (c) 2023
 *
 * Source: https://open.kattis.com/problems/2048
 */

#include <array>
#include <cstdlib>
#include <cstddef>
#include <iomanip>
#include <iostream>

constexpr auto Board_Size = 4;

class Game final
{
public:
   enum Move { left, up, right, dowm, error, };

   auto load_board( std::istream& ) -> bool;
   auto make_move( Move move ) -> void;

   auto display_board( std::ostream& ) const  -> void;
   auto pretty_print_board()           const  -> void;

private:
   using Board = std::array< std::array<int, Board_Size>, Board_Size>;

   Board board_ = {};

   auto move_left() -> void;
   auto move_right() -> void;
   auto move_up() -> void;
   auto move_down() -> void;
};


auto get_move( std::istream& in ) -> Game::Move;

auto main() -> int
{
   for ( auto game = Game{}; game.load_board( std::cin ); )
   {
      game.make_move( get_move( std::cin ) );
      game.display_board( std::cout );
   }

   return EXIT_SUCCESS;
}


auto
get_move( std::istream& in ) -> Game::Move
{
   int move;
   in >> move;

   switch ( move )
   {
      case 0:
         return Game::left;

      case 1:
         return Game::up;

      case 2:
         return Game::right;

      case 3:
         return Game::dowm;

      default:
         return Game::error;
   }
}

auto Game::load_board( std::istream& in ) -> bool
{
   for ( auto row = 0; row < Board_Size; ++row )
   {
      for ( auto col = 0; col < Board_Size; ++col )
      {
         int data;
         in >> data;

         if ( !in )
            return false;

         board_[row][col] = data;
      }
   }
   return true;
}

auto Game::make_move( Move move ) -> void
{
   switch ( move )
   {
      case Game::left:
         move_left();
         break;

      case Game::up:
         move_up();
         break;

      case Game::right:
         move_right();
         break;

      case Game::dowm:
         move_down();
         break;

      case Game::error:
         break;

      default:
         break;

   }
}

auto Game::display_board( std::ostream& out ) const  -> void
{
   for ( auto row = 0; row < Board_Size; ++row )
   {
      for ( auto col = 0; col < Board_Size; ++col )
      {
         out << board_[row][col] << ' ';
      }
      out << '\n';
   }
}


auto Game::pretty_print_board() const -> void
{
   std::cerr << '\n';
   for ( auto row = 0; row < Board_Size; ++row )
   {
      for ( auto col = 0; col < Board_Size; ++col )
      {
         std::cerr << std::setw( 6 ) << board_[row][col] << ' ';
      }
      std::cerr << '\n';
   }
   std::cerr << '\n';
}


auto Game::move_left()  -> void
{
   for ( auto row = 0; row < Board_Size; ++row )
   {
      auto empties    = 0;
      auto last_value = 0;

      for ( auto col = 0; col < Board_Size; ++col )
      {
         auto& current_value = board_[row][col];

         // case 1)
         if ( current_value == 0 )
         {
            ++empties;
         }
         else if ( current_value == last_value )
         {
            auto const updated             = current_value + last_value;
            board_[row][col - empties - 1] = updated;
            current_value                  = 0;
            last_value                     = 0;          // can't merge with an already merged value
            ++empties;
         }
         else if ( empties )
         {
            board_[row][col - empties] = current_value;
            last_value                 = current_value;
            current_value              = 0;
         }
         else
         {
            last_value = current_value;
         }
      }
   }
}

auto Game::move_right() -> void
{
   for ( auto row = 0; row < Board_Size; ++row )
   {
      auto empties    = 0;
      auto last_value = 0;

      for ( auto col = Board_Size - 1; col >= 0; --col )
      {
         auto& current_value = board_[row][col];

         if ( current_value == 0 )
         {
            ++empties;
         }
         else if ( current_value == last_value )
         {
            auto const updated             = current_value + last_value;
            board_[row][col + empties + 1] = updated;
            current_value                  = 0;
            last_value                     = 0;
            ++empties;
         }
         else if ( empties )
         {
            board_[row][col + empties] = current_value;
            last_value                 = current_value;
            current_value              = 0;
         }
         else
         {
            last_value = current_value;
         }
      }
   }
}

auto Game::move_up() -> void
{
   for ( auto col = 0; col < Board_Size; ++col )
   {
      auto empties    = 0;
      auto last_value = 0;

      for ( auto row = 0; row < Board_Size; ++row )
      {
         auto& current_value = board_[row][col];

         if ( current_value == 0 )
         {
            ++empties;
         }
         else if ( current_value == last_value )
         {
            auto const updated             = current_value + last_value;
            board_[row - empties - 1][col] = updated;
            current_value                  = 0;
            last_value                     = 0;
            ++empties;
         }
         else if ( empties )
         {
            board_[row - empties][col] = current_value;
            last_value                 = current_value;
            current_value              = 0;
         }
         else
         {
            last_value = current_value;
         }
      }
   }
}

auto Game::move_down()  -> void
{
   for ( auto col = 0; col < Board_Size; ++col )
   {
      auto empties    = 0;
      auto last_value = 0;

      for ( auto row = Board_Size - 1; row >= 0; --row )
      {
         auto& current_value = board_[row][col];

         if ( current_value == 0 )
         {
            ++empties;
         }
         else if ( current_value == last_value )
         {
            auto const updated             = current_value + last_value;
            board_[row + empties + 1][col] = updated;
            current_value                  = 0;
            last_value                     = 0;
            ++empties;
         }
         else if ( empties )
         {
            board_[row + empties][col] = current_value;
            last_value                 = current_value;
            current_value              = 0;
         }
         else
         {
            last_value = current_value;
         }
      }
   }
}