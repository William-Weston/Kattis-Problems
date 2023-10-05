/**
 * @file    Solver.inl
 * @author  William Weston
 * @brief   Inline functions from Solver.h
 * @version 0.1
 * @date    2023-06-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef WJTW_SOLVER_INL_2023_06_12_INCLUDE
#define WJTW_SOLVER_INL_2023_06_12_INCLUDE

#include <cctype>       // isupper
#include <stdexcept>

constexpr auto 
operator==( Move const& lhs, Move const& rhs ) noexcept -> bool
{
   return lhs.from.first == rhs.from.first && lhs.from.second == rhs.from.second &&
          lhs.to.first   == rhs.to.first   && lhs.to.second   == rhs.to.second;
}


constexpr auto 
is_white( unsigned char ch ) noexcept -> bool
{ 
   return std::isupper( ch );
}

constexpr auto
is_pawn( char piece ) noexcept -> bool
{
   return ( piece == 'p' || piece =='P' );
}

constexpr auto 
is_castled( Cell cell, char piece )  noexcept -> bool
{
   if ( !is_pawn( piece ) )      // only pawns can be castled
      return false;
   
   [[maybe_unused]] auto const& [row, dummy] = cell;
   auto const                    isWhite     = is_white( piece );

   return ( ( isWhite && row == 0 ) || ( !isWhite && row == 7  ) );
}


constexpr auto 
is_knight_move( Move const& move )   noexcept -> bool
{
   auto const& [from_row, from_col] = move.from;
   auto const& [to_row, to_col]     = move.to;

   for ( auto const& direction : Knight )
   {
      auto const& [row_dir, col_dir] = direction;
      auto const dest_row = from_row + row_dir;
      auto const dest_col = from_col + col_dir;

      return ( ( dest_row == to_row ) && ( dest_col == to_col ) );
   }

   return false;
}

/**
 * @brief 
 * 
 * @param move 
 * @param board 
 * @param side    the side ( black/white ) whose piece the Move represents
 * @return true 
 * @return false 
 */
constexpr auto 
is_king_taken( Move const& move, Board const& board, Side side ) -> bool
{
   auto const& [to_row, to_col] = move.to;
   auto const& dest_piece       = board[to_row][to_col];

   switch ( side )
   {
      case Side::white: 
         return ( dest_piece == 'k' );
      case Side::black: 
         return ( dest_piece == 'K' );
      default:
         throw std::runtime_error( "Error: Unknown Side" );
   }
}

constexpr auto 
is_valid( Move const& move, Board const& board ) noexcept -> bool
{
   auto const& [from_row, from_col] = move.from;
   auto const& [to_row, to_col]     = move.to;
   
   // out of bounds
   if ( to_row < 0 || to_row > 7 || to_col < 0 || to_col > 7 )    
      return false;

   auto const& piece             = board[from_row][from_col];
   auto const& destination_piece = board[to_row][to_col];

   return ( ( destination_piece == Empty ) ||                              // empty square
            ( is_white( piece ) != is_white( destination_piece ) ) );      // the two pieces are not of the same side
}

#endif   // WJTW_SOLVER_INL_2023_06_12_INCLUDE