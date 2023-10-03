/**
 * @file    skener.cpp
 * @author  William Weston
 * @brief   Skener Problem From Kattis
 * @version 0.1
 * @date    2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/skener
 */


#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

auto duplicate_char( char ch, int dups )          -> std::string;
auto print( std::vector<std::string> const& doc ) -> void;

auto main() -> int
{
   for ( int R, C, ZR, ZC; std::cin >> R >> C >> ZR >> ZC; )
   {
      auto article = std::vector<std::string>();
      article.reserve( R );

      for ( auto i = 0; i < R; ++i )
      {
         auto line = std::string();
         std::cin >> line;
         article.push_back( std::move( line ) );
      }

      auto result = std::vector<std::string>();

      for ( auto const& line : article )
      {
         auto output_line = std::string();

         for ( auto ch : line )
         {
            output_line += duplicate_char( ch, ZC );
         }

         for ( auto i = 0; i < ZR; ++i )
            result.push_back( output_line );

      }
      print( result );
   }


   return EXIT_SUCCESS;
}

auto duplicate_char( char const ch, int dups ) -> std::string
{
   auto ret = std::string();

   while ( dups-- )
   {
      ret += ch;
   }

   return ret;
}

auto print( std::vector<std::string> const& doc ) -> void
{
   for ( auto const& line : doc )
      std::cout << line << '\n';
}