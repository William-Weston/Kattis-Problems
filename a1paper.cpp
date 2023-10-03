/**
 * @file    a1paper.cpp
 * @author  William Weston
 * @brief   A1 Paper Problem From Kattis
 * @version 0.1
 * @date    2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/a1paper
 */

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <optional>
#include <vector>

auto construct_A1_sheet( std::vector<int> const& data )                                 -> std::optional<double>;
auto construct_sheet( int paper_size, int sheets_needed, std::vector<int> const& data ) -> std::optional<double>;
auto calculate_dimensions( int paper_size )                                             -> double;

auto main() -> int
{
   for ( int N; std::cin >> N; )
   {
      auto const number_of_sizes = N - 1;
      auto paper                 = std::vector<int>( 2,0 );  // Paper size A0 at index 0, A1 at index 1, A2 at index to and so on...

      paper.reserve( number_of_sizes + 2 );        // 

      for ( auto idx = 0; idx < number_of_sizes ; ++idx )
      {
         auto const count = []() { int tmp; std::cin >> tmp; return tmp; }();
         paper.push_back( count );
      }

      // Construct an A1 size paper out of smaller sizes
      auto const length_of_tape = construct_A1_sheet( paper );
      if ( length_of_tape )
      {
         std::cout << std::fixed << std::setprecision( 6 ) << *length_of_tape << '\n';
      }
      else
      {
         std::cout << "impossible\n";
      }
   }

   return EXIT_SUCCESS;
}


auto construct_A1_sheet( std::vector<int> const& data ) -> std::optional<double>
{
   auto const A2_height = calculate_dimensions( 2 );

   if ( data[2] >= 2 )
      return A2_height;
   
   if ( data[2] == 1 )
   {
      auto const tape_needed_for_subsheets = construct_sheet( 3, 2, data );
      if ( tape_needed_for_subsheets )
      {
         return A2_height + *tape_needed_for_subsheets;
      }
      else
         return std::nullopt;
   }

   auto const tape_needed_for_subsheets = construct_sheet( 3, 4, data );
   if ( tape_needed_for_subsheets )
   {
      return A2_height + *tape_needed_for_subsheets;
   }
   
   return std::nullopt;
}

auto construct_sheet( int const paper_size, int const sheets_needed, std::vector<int> const& data ) -> std::optional<double>
{
   if ( paper_size == data.size() )
      return std::nullopt;

   auto const  height           = calculate_dimensions( paper_size );
   auto const  base_tape_needed = height * std::floor( sheets_needed / 2 );
   auto const& sheets_possessed = data[paper_size];

   if ( sheets_possessed >= sheets_needed )
   {
      return base_tape_needed;
   }

   auto const missing = sheets_needed - sheets_possessed;
   auto const result  = construct_sheet( paper_size + 1, missing * 2, data );
   if ( result )
   {
      return base_tape_needed + *result;
   }
   
   return std::nullopt;
}

// maybe cache the results?
auto calculate_dimensions( int const paper_size ) -> double
{
   static auto constexpr A2_width  = 0.420'448'207'627;            //std::pow( 2.0, -5.0 / 4.0 );
   static auto constexpr A2_height = 0.594'603'557'5;

   auto height = A2_height;
   auto width  = A2_width;

   for ( auto current_size = 2; current_size != paper_size; ++current_size )
   {
      auto const tmp = height;
      height         = width;
      width          = tmp / 2.0;
   }
   return height;
}