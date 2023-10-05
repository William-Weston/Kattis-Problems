/**
 * @file    Solver.cpp
 * @author  William Weston
 * @brief   Class to solve "Mate in One" Problem
 * @version 0.1
 * @date 2023-06-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Solver.h"

#include <cctype>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>






// --------------------------------------------- Move ----------------------------------------------

auto
operator<<( std::ostream& out, Move const& mv ) -> std::ostream&
{
   out << '[' << mv.from.first << ',' << mv.from.second << "] -> [" << mv.to.first << ',' << mv.to.second << ']';
   return out;
}

auto
output_format( Move const& move ) -> std::string
{
   if ( move == Move() )
      return "no solution";
      
   auto const& from = move.from;
   auto const from_file = 'a' + from.second;
   auto const from_rank = 8 - from.first;

   auto const& to = move.to;
   auto const to_file = 'a' + to.second;
   auto const to_rank = 8 - to.first;

   auto ret = std::string();

   ret.push_back( from_file );
   ret += std::to_string( from_rank );
   ret.push_back( to_file );
   ret += std::to_string( to_rank );

   return ret;
}

// --------------------------------------------- Solver -------------------------------------------

auto
Solver::load_board( std::istream& in ) -> bool
{
   board_.clear();                  // clear the previous board

   // no input validation required
   auto line = std::string();

   for ( auto i = 0; i < 8; ++i )
   {
      std::getline( in, line );
      if ( line.size() )
         board_.push_back( line );
   }

   return ( board_.size() == 8 );          // return false when no more valid boards can be loading from the stream
}

auto
Solver::solve() -> Move
{
   // generate all moves for white
   auto const white_moves = generate_moves( Side::white, board_ );

   return find_solution( white_moves );
}

auto
Solver::print_board() const -> void
{
   ::print_board( board_ );
}


// ------------------------------------------------------------------------------------------------

/**
 * @brief 
 * 
 * @param white_moves 
 * @return Move 
 * 
 * returing a default constructed move indicates no "mate in one move" could be found
 */
auto
Solver::find_solution( std::vector<Move> const& white_moves ) -> Move
{
   // check if a move results in checkmate
   for ( auto const& move : white_moves )
      if ( is_checkmate( move ) )
         return move;

   return Move{};       // no solution
}

auto 
Solver::is_checkmate( Move const& white_move ) -> bool
{
   // for each possible white move generate all possible black moves
   // if all black moves result in check mate for a specific white move, then return true

   auto const tmp_board   = do_move( white_move, board_ );

   if ( !is_in_check( Side::black, tmp_board ) )
      return false;
   
   auto const black_moves = generate_moves( Side::black, tmp_board );

   for ( auto const& black_move : black_moves )
      if ( can_escape( black_move, tmp_board ) )
         return false;  // no need to process any more black moves

   return true;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


auto
generate_moves( Side side, Board const& board ) -> std::vector<Move>
{
   auto is_side = ( side == Side::white )
      ? [] ( unsigned char ch ) { return std::isupper( ch ); }       // white's pieces are capital case
      : [] ( unsigned char ch ) { return std::islower( ch ); };      // black's pieces are lowercase 

   auto moves = std::vector<Move>();

   for ( auto row = 0u; row < 8u; ++row )
   {
      for ( auto col = 0u; col < 8u; ++col )
      {
         if ( is_side( board[row][col] ) )         // is it our piece?
         {
            auto tmp = generate_moves( { row, col }, board );
            moves.insert( moves.end(),
                          std::make_move_iterator( tmp.begin() ),
                          std::make_move_iterator( tmp.end() ) );
         }
      }
   }

   return moves;
}

auto
generate_moves( Cell const& cell, Board const& board ) -> std::vector<Move>
{
   auto const& [row, col] = cell;

   auto const piece = []( unsigned char ch ) { return ( ch != '.' ) ? std::toupper( ch ) : '.'; }( board[row][col] );

   // if a pawn is castled add moves for both 'Q' and 'N"  
   switch ( piece )
   {
      case 'P':
         return pawn_moves( cell, board );
      case 'N':
         return move_generator( cell, board, Knight, 1 );
      case 'B':
         return move_generator( cell, board, Diagonal, Unlimited );
      case 'R':
         return move_generator( cell, board, Cross, Unlimited );
      case 'Q':
         return move_generator( cell, board, All_Moves, Unlimited );
      case 'K':
         return move_generator( cell, board, All_Moves, 1 );
      default:
         throw std::runtime_error( "Error: Unknown Piece" );
   }

   return {};
}

auto 
move_generator( Cell const& cell, Board const& board, Directions const& directions, int distance ) -> std::vector<Move>
{
   auto moves = std::vector<Move>();

   for ( auto const& [row, col] = cell; auto const& direction : directions )
   {
      for ( auto dis = 1; dis <= distance; ++dis )
      {
         auto const& [row_dir, col_dir] = direction;
         auto const dest                = std::make_pair( row + row_dir * dis, col + col_dir * dis );
         auto tmp_move                  = Move( cell, dest );

         if ( is_valid( tmp_move, board ) )
         {
            moves.push_back( std::move( tmp_move ) );
            
            if ( auto const& target = board[dest.first][dest.second]; target != Empty )
               break;      // if we took a piece we can't go any farther in that direction ( the opponents piece is blocking us )
         }
         else
            break;     // a piece is in our way or edge of board;
      }
   }

   return moves;
}

auto 
pawn_moves( Cell const& cell, Board const& board ) -> std::vector<Move>
{
   auto const& [row, col] = cell;
   auto const& piece      = board[row][col];
   auto const  isWhite    = is_white( piece );

   // Special Case: Pawn is castled, add moves for both 'Q' and 'N'
   if ( is_castled( cell, piece) )
   {
      auto queen  = move_generator( cell, board, All_Moves, Unlimited );
      auto knight = move_generator( cell, board, Knight, 1 );

      queen.insert( queen.end(), std::make_move_iterator( knight.begin() ), std::make_move_iterator( knight.end() ) );
      return queen;
   }

   // All other cases:
   auto moves = std::vector<Move>();

   // pawn going forward
   auto const dir = isWhite ? -1 : 1;

   auto tmp_move = Move( cell, std::make_pair( row + dir, col ) );
   if ( is_valid( tmp_move, board ) )
   {
      if ( board[row + dir][col] == Empty )              // pawn can only move forward to an empty cell
         moves.push_back( std::move( tmp_move ) );
   }

   if ( ( isWhite && row == 6 ) || ( !isWhite && row == 1 ) )       // pawn in intial square, can move two squares
   {
      tmp_move = Move( cell, std::make_pair( row + 2 * dir, col ) );
      if ( is_valid( tmp_move, board ) )
         if ( board[row + dir][col] == Empty && board[row + 2 * dir][col] == Empty )
            moves.push_back( std::move( tmp_move ) );
   }

   // pawns can move diagonally one square to attack
   auto const top_row       = row + dir;
   auto const top_left_col  = col - 1;
   auto const top_right_col = col + 1;
   auto const& top_left     = board[top_row][top_left_col];
   auto const& top_right    = board[top_row][top_right_col];

   if ( top_left != Empty && ( isWhite != is_white( top_left ) ) )
   {
      tmp_move = Move( cell, std::make_pair( top_row, top_left_col ) );
      if ( is_valid( tmp_move, board ) )
         moves.push_back( std::move( tmp_move ) );
   }

   if ( top_right != Empty && ( isWhite != is_white( top_right ) ) )
   {
      tmp_move = Move( cell, std::make_pair( top_row, top_right_col ) );
      if ( is_valid( tmp_move, board ) )
         moves.push_back( std::move( tmp_move ) );
   } 

   return moves;
}

auto 
do_move( Move const& move, Board const& board ) -> Board
{
   auto const& [from_row, from_col] = move.from;
   auto const& [to_row, to_col]     = move.to;
   auto const& piece                = board[from_row][from_col];
   
   // handle special case of pawn being castled
   if ( is_castled( move.from, piece ) )
      return do_castling_move( move, board );

   // all other moves handled here
   auto new_board = board;

   new_board[from_row][from_col] = Empty;    // now empty
   new_board[to_row][to_col]     = piece;

   return new_board;
}

auto 
do_castling_move( Move const& move, Board const& board )  -> Board
{
   auto const& [from_row, from_col] = move.from;
   auto const& [to_row, to_col]     = move.to;
   auto const& piece                = board[from_row][from_col];
   auto const  isWhite              = is_white( piece );
   auto        new_board            = board;

   new_board[from_row][from_col] = Empty;    // now empty

   if ( is_knight_move( move ) )
      new_board[to_row][to_col] = ( isWhite ) ? 'N' : 'n';
   
   else  // queen move
      new_board[to_row][to_col] = ( isWhite ) ? 'Q' : 'q';

   return new_board;
}

auto 
can_escape( Move const& black, Board const& board )  -> bool
{
   auto const tmp_board = do_move( black, board );

   // need to check if white king is taken
   if ( is_king_taken( black, board, Side::black) )
      return true;                                 // black can escape by taking white's king

   // generate white moves and check if any of them result in a black king killed
   auto const white_moves = generate_moves( Side::white, tmp_board );

   for ( auto const& move : white_moves )          // if any of white's potential next moves can take the black king, black's move
   {                                               // doesn't result in his escape
      if ( is_king_taken( move, tmp_board, Side::white ) )
         return false;
   }

   return true;
}


auto 
print_board( Board const& board )  -> void
{
   std::cout << '\n' << "   0  1  2  3  4  5  6  7 \n";
   for ( auto row = 0; auto const& line : board )
   {  
      std::cout << row++ << ' ';
      for ( auto const& piece : line )
         std::cout << ' ' << piece << ' ';
      
      std::cout << '\n';
   }
}

auto 
is_in_check( Side side, Board const& board ) -> bool        
{
   auto const opponent = ( side == Side::white ) ? Side::black : Side::white;
   auto const moves    = generate_moves( opponent, board  );
  
   for ( auto move : moves )
   {
      if ( is_king_taken( move, board, opponent ) )
         return true;
   }

   return false;
}
// ------------------------------------------------------------------------------------------------
