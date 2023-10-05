/**
 * @file    Solver.h
 * @author  William Weston
 * @brief   Class to solve "Mate in One" Problem
 * @version 0.1
 * @date    2023-06-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef WJTW_SOLVER_H_2023_06_09_INCLUDE
#define WJTW_SOLVER_H_2023_06_09_INCLUDE

#include <iosfwd>
#include <string>
#include <utility>
#include <vector>

using Board      = std::vector<std::string>;  // [row][col]
using Cell       = std::pair<int, int>;       // row by col
using Direction  = std::pair<int, int>;
using Directions = std::vector<Direction>;

struct Move
{
   using Cell = std::pair<int, int>;               // row by col

   Cell from = { -1, -1 };  // returing a default constructed move indicates no "mate in one move" could be found
   Cell to   = { -1, -1 };
};

          auto operator<<( std::ostream&, Move const& )                -> std::ostream&;
constexpr auto operator==( Move const& lhs, Move const& rhs ) noexcept -> bool;
          auto output_format( Move const& move )                       -> std::string;

class Solver final
{
public:
   auto load_board( std::istream& in ) -> bool;
   auto solve()             -> Move;
   auto print_board() const -> void;

private:
   using Board = std::vector<std::string>;  // [row][col]

   Board board_ = {};

   auto find_solution( std::vector<Move> const& white_moves ) -> Move;
   auto is_checkmate( Move const& white )                     -> bool;
};


constexpr auto Empty     = '.';
constexpr auto Unlimited = 16;      // max distance a piece can travel

auto const Cross     = Directions{ { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
auto const Diagonal  = Directions{ { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 } };
auto const Knight    = Directions{ { 1, 2 }, { 1, -2 }, { 2, 1 }, { 2, -1 }, { -1, 2 }, { -1, -2 }, { -2, 1 }, { -2, -1 } };
auto const All_Moves = Directions{ { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 } };


enum class Side
{
   white,
   black,
};

auto generate_moves( Side side, Board const& board )                     -> std::vector<Move>;
auto generate_moves( Cell const& cell, Board const& board )              -> std::vector<Move>;
auto pawn_moves( Cell const& cell, Board const& board )                  -> std::vector<Move>;
auto move_generator( Cell const&, Board const&, Directions const&, int ) -> std::vector<Move>;
auto do_move( Move const& move, Board const& board )                     -> Board;
auto do_castling_move( Move const& move, Board const& board )            -> Board;

auto can_escape( Move const& black, Board const& board )                 -> bool; 
constexpr auto is_white( unsigned char ch )                     noexcept -> bool; 
constexpr auto is_castled( Cell cell, char piece )              noexcept -> bool;
constexpr auto is_pawn( char piece )                            noexcept -> bool;
constexpr auto is_knight_move( Move const& move )               noexcept -> bool; 
constexpr auto is_king_taken( Move const&, Board const&, Side )          -> bool;    
constexpr auto is_valid( Move const& move, Board const& board ) noexcept -> bool;

auto is_in_check( Side side, Board const& board ) -> bool;
auto print_board( Board const& board )  -> void;

// -------------------------------------------------------------------------------------------------------------------


#include "Solver.inl"

#endif