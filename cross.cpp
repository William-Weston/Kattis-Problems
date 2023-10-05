/**
 * @file    cross.cpp
 * @author  William Weston
 * @brief   Cross Problem From Kattis
 * @version 0.1
 * @date    2023-09-16
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/cross
 */


// ------------------------------------------------------------------------------------------------

#include <array>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>


// ------------------------------------------------------------------------------------------------
// --------------------------------------------- Solver.h -----------------------------------------

class Solver final
{
public:
   Solver( std::array<std::string, 9> const& board );

   auto solve() -> std::optional<std::array<std::string, 9>>;


private:
   std::array<std::array<int, 9>, 9> board_;
   std::array<std::array<int, 9>, 9> working_;

   static constexpr inline auto CROSSED = -1;

   auto cross_hatch()            -> bool;

   auto cross( int number )      -> void;
   auto cross_row( int row )     -> void;
   auto cross_col( int col )     -> void;
   auto cross_block( int block ) -> void; 

   auto deduce( int number ) -> bool;

   auto update_board( int row, int col, int number ) -> void;

   auto row_duplicates()   -> bool;
   auto col_duplicates()   -> bool;
   auto block_duplicates() -> bool;

   auto row_contains( int number, int row )     -> bool;
   auto col_contains( int number, int col )     -> bool;
   auto block_contains( int number, int block ) -> bool;
};


// ---------------------------------------- helper_functions.h ------------------------------------

auto convert_board( std::array<std::string, 9> const& board )        -> std::array<std::array<int, 9>, 9>;
auto convert_board( std::array<std::array<int, 9>, 9> const& board ) -> std::array<std::string, 9>;

auto to_char( int number ) -> char;
auto to_int( char number ) -> int;

auto block_start( int block )                        -> std::pair<int, int>;
auto block_number( int row, int col ) noexcept       -> int;


// -------------------------------------------- Solver.cpp ----------------------------------------


Solver::Solver( std::array<std::string, 9> const& board )
   : board_{ convert_board( board ) }, working_{}
{}

auto 
Solver::solve() -> std::optional<std::array<std::string, 9>>
{
   // return nullopt for invalid input or when no deductions can be made
   if ( row_duplicates() || col_duplicates() || block_duplicates() )
      return std::nullopt;

   try
   {
      while ( cross_hatch() )  {}
      
   }
   catch( std::runtime_error const& error )
   {
      std::cerr << error.what() << '\n';
      return std::nullopt;
   }
   
   return convert_board( board_ );
}

auto 
Solver::cross_hatch() -> bool
{
   auto deduction_made = false;

   for ( auto number = 1; number < 10; ++number  )
   {
      working_ = board_;
      cross( number );

      if ( deduce( number ) )
         deduction_made = true;
   }

   return deduction_made;
}

auto 
Solver::cross( int const number ) -> void
{
   for ( auto row = 0; row < 9; ++row )
   {
      for ( auto col = 0; col < 9; ++col )
      {
         if ( board_[row][col] == number )
         {
            cross_row( row );
            cross_col( col );
            cross_block( block_number( row, col ) );
         } 
      }
   } 
}

auto 
Solver::cross_row( int const row )     -> void
{
   for ( auto col = 0; col < 9; ++col )
   {
      working_[row][col] = CROSSED;
   }
}

auto 
Solver::cross_col( int const col )     -> void
{
   for ( auto row = 0; row < 9; ++row )
   {
      working_[row][col] = CROSSED;
   }
}

auto 
Solver::cross_block( int const block ) -> void
{
   auto const [row_start, col_start] = block_start( block );
   auto const row_end                = row_start + 3;
   auto const col_end                = col_start + 3;

   for ( auto row = row_start; row < row_end; ++row )
   {
      for ( auto col = col_start; col < col_end; ++col )
      {
         working_[row][col] = CROSSED;     
      }
   } 
}

auto 
Solver::deduce( int const number ) -> bool
{
   auto deduction_made = false;

   for ( auto block = 0; block < 9; ++block )
   {
      if ( block_contains( number, block ) )
         continue;
      
      auto const [row_start, col_start] = block_start( block );
      auto const row_end                = row_start + 3;
      auto const col_end                = col_start + 3;

      auto empties    = 0;
      auto row_update = 0;
      auto col_update = 0;

      for ( auto row = row_start; row < row_end; ++row )
      {
         for ( auto col = col_start; col < col_end; ++col )
         {
            if ( working_[row][col] == 0 )
            {
               ++empties;
               row_update = row;
               col_update = col;
            }
         }
      } 
      
      if ( empties == 0 )
         throw std::runtime_error( "Contradiction detected" );

      if ( empties == 1 )
      {
         update_board( row_update, col_update, number );
         deduction_made = true;
      }
   }

   return deduction_made;
}


auto 
Solver::update_board( int const row, int const col, int const number ) -> void
{
   if ( board_[row][col] != 0 )
   {
      std::cerr << "Update at: [" << row << ", " << col << "] = number\n";
      std::cerr << "Existing value: " << board_[row][col] << '\n';
   }
   assert( board_[row][col] == 0 && "Contradiction in board update" );

   board_[row][col] = number;
}


auto 
Solver::row_duplicates() -> bool
{
   for ( auto number = 1; number < 10; ++number )
   {
      for ( auto row = 0; row < 9; ++row )
      {
         auto count = 0;
         for ( auto col = 0; col < 9; ++col )
         {
            if ( board_[row][col] == number )
               ++count;
         }

         if ( count > 1 )
            return true;
      }
   }

   return false;
}


 auto 
Solver::col_duplicates()   -> bool
{
   for ( auto number = 1; number < 10; ++number )
   {
      for ( auto col = 0; col < 9; ++col )
      {
         auto count = 0;
         for ( auto row = 0; row < 9; ++row )
         {
            if ( board_[row][col] == number )
               ++count;
         }

         if ( count > 1 )
            return true;
      }
   }

   return false;
}


auto 
Solver::block_duplicates() -> bool
{
   for ( auto number = 1; number < 10; ++number )
   {
      for ( auto block = 0; block < 9; ++block )
      {
         auto count = 0;

         auto const [row_start, col_start] = block_start( block );
         auto const row_end                = row_start + 3;
         auto const col_end                = col_start + 3;

         for ( auto row = row_start; row < row_end; ++row )
         {
            for ( auto col = col_start; col < col_end; ++col )
            {
               if ( board_[row][col] == number )
                  ++count;
            }
         } 

         if ( count > 1 )
            return true;
      }
   }

   return false;
}

auto 
Solver::row_contains( int const number, int const row ) -> bool
{
   for ( auto col = 0; col < 9; ++col )
   {
      if ( board_[row][col] == number )
         return true;
   }
   
   return false;
}


auto 
Solver::col_contains( int const number, int const col ) -> bool
{
   for ( auto row = 0; row < 9; ++row )
   {
      if ( board_[row][col] == number )
         return true;
   }

   return false;
}


auto 
Solver::block_contains( int const number, int const block ) -> bool
{
   auto const [row_start, col_start] = block_start( block );
   auto const row_end = row_start + 3;
   auto const col_end = col_start + 3;

   for ( auto row = row_start; row < row_end; ++row )
   {
      for ( auto col = col_start; col < col_end; ++col )
      {
         if ( board_[row][col] == number )
            return true;
      }
   }

   return false;
}

// --------------------------------------- helper_functions.cpp -----------------------------------

auto 
convert_board( std::array<std::string, 9> const& board ) -> std::array<std::array<int, 9>, 9>
{
   auto array_board = std::array<std::array<int, 9>, 9>{ 0 };     // all zeros

   for ( auto row = 0; row < 9; ++row )
   {
      for ( auto col = 0; col < 9; ++col )
      {
         if ( board[row][col] != '.' )
            array_board[row][col] = to_int( board[row][col] );
      }
   }

   return array_board;
}

auto
convert_board( std::array<std::array<int, 9>, 9> const& board ) -> std::array<std::string, 9>
{
   auto string_board = std::array<std::string, 9>{};

   for ( auto row = 0; row < 9; ++row )
   {
      for ( auto col = 0; col < 9; ++col )
      {
         if ( board[row][col] == 0 )
            string_board[row].push_back( '.' );
         else
            string_board[row].push_back( to_char( board[row][col] ) );
      }
   }

   return string_board;
}

auto 
to_char( int const number ) -> char
{
   return number + '0';
}

auto 
to_int( char const number ) -> int
{
   return number - '0';
}


auto 
block_start( int const block ) -> std::pair<int, int>
{
   return { ( block / 3 ) * 3, ( block % 3 ) * 3 };
}


auto
block_number( int const row, int const col ) noexcept -> int
{
   return ( row / 3 ) * 3 + col / 3;
}


// ------------------------------------------------------------------------------------------------
// --------------------------------------------- main ---------------------------------------------


auto read_input()                                     -> std::array<std::string, 9>;
auto print( std::array<std::string, 9> const& board ) -> void;

auto
main() -> int
{
   auto const board = read_input();

   auto solver       = Solver( board );
   auto const result = solver.solve();

   if ( !result )
      std::cout << "ERROR\n";
   else
   {
       print( *result );
   }

   return EXIT_SUCCESS;
}

auto 
read_input() -> std::array<std::string, 9>
{
   auto board = std::array<std::string, 9>{};

   for ( auto idx = 0; idx < 9; ++ idx )
   {
      auto line = std::string();
      std::getline( std::cin, line );

      board[idx] = std::move( line );
   }

   return board;
}

auto 
print( std::array<std::string, 9> const& board ) -> void
{
   for ( auto const& row : board )
   {
      std::cout << row << '\n';
   }
}

// ------------------------------------------------------------------------------------------------